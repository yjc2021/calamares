/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "PartUtils.h"

#include "PartitionCoreModule.h"

#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/PartitionIterator.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <utils/Logger.h>
#include <JobQueue.h>
#include <GlobalStorage.h>

#include <QProcess>
#include <QTemporaryDir>

namespace PartUtils
{

/**
 * Does the given @p device contain the root filesystem? This is true if
 * the device contains a partition which is currently mounted at / .
 */
static bool
hasRootPartition( Device* device )
{
    for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
        if ( ( *it )->mountPoint() == "/" )
            return true;
    return false;
}

static bool
isMounted( Device* device )
{
    cDebug() << "Checking for mounted partitions in" << device->deviceNode();
    for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
    {
        if ( ! ( *it )->mountPoint().isEmpty() )
        {
            cDebug() << "  .." << ( *it )->partitionPath() << "is mounted on" << ( *it )->mountPoint();
            return true;
        }
    }
    return false;
}

static bool
isIso9660( const Device* device )
{
    QString path = device->deviceNode();
    if ( path.isEmpty() )
        return false;

    QProcess blkid;
    blkid.start( "blkid", { path } );
    blkid.waitForFinished();
    QString output = QString::fromLocal8Bit( blkid.readAllStandardOutput() );
    if ( output.contains( "iso9660" ) )
        return true;

    if ( device->partitionTable() &&
            !device->partitionTable()->children().isEmpty() )
    {
        for ( const Partition* partition : device->partitionTable()->children() )
        {
            path = partition->partitionPath();
            blkid.start( "blkid", { path } );
            blkid.waitForFinished();
            QString output = QString::fromLocal8Bit( blkid.readAllStandardOutput() );
            if ( output.contains( "iso9660" ) )
                return true;
        }
    }
    return false;
}


QList< Device* > getDevices( bool writableOnly )
{
    using DeviceList = QList< Device* >;

    CoreBackend* backend = CoreBackendManager::self()->backend();
    DeviceList devices = backend->scanDevices( true );

    cDebug() << "Removing unsuitable devices:" << devices.count() << "candidates.";

    // Remove the device which contains / from the list
    for ( DeviceList::iterator it = devices.begin(); it != devices.end(); )
        if ( ! ( *it ) ||
                ( *it )->deviceNode().startsWith( "/dev/zram" )
        )
        {
            cDebug() << "  .. Removing" << ( ( *it ) ? ( *it )->deviceNode() : QString( "<null device>" ) );
            it = devices.erase( it );

        }
        else if ( writableOnly && (
                hasRootPartition( *it ) ||
                isIso9660( *it ) ||
                isMounted( *it ) )
           )
        {
            cDebug() << "  .. Removing" << ( ( *it ) ? ( *it )->deviceNode() : QString( "<null device>" ) );
            it = devices.erase( it );
        }
        else
            ++it;

    return devices;
}

}  // namespace PartUtils
