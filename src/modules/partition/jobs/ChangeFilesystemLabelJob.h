/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Lisa Vitolo <shainer@chakraos.org>
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

#ifndef CHANGEFILESYSTEMLABELJOB_H
#define CHANGEFILESYSTEMLABELJOB_H

#include <jobs/PartitionJob.h>

#include <kpmcore/core/partitiontable.h>

class Device;
class Partition;

/**
 * This job changes the flags on an existing partition.
 */
class ChangeFilesystemLabelJob : public PartitionJob
{
    Q_OBJECT
public:
    ChangeFilesystemLabelJob( Device* device, Partition* partition, const QString& newLabel );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    Device* device() const;

private:
    Device* m_device;
    QString m_label;
};

#endif // CHANGEFILESYSTEMLABELJOB_H
