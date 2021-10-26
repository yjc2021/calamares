/*
 *   SPDX-FileCopyrightText: 2021 Kiyung <yongjae.choi20@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "BackupThread.h"
#include "BackupDialog.h"
#include "jobs/PathSelect.h"

using namespace std;
 
BackupThread::BackupThread(QObject *parent) :
    QThread(parent)
{
 
}
 
void BackupThread::run()
{
    string last = getLastPathToken(strCopy);
    string cmd = "tar -zcvf ";
    cmd += strBackup+"/"+ last +".tar.gz -C "+ strCopy.substr(0, strCopy.size()-last.size())+" "+last;

    switch( system(cmd.c_str()) ){
    	case 0: 
    	    emit ThreadEnd(0);
    	    break;
    	default :
    	    cmd = "rm -f " + strBackup+"/"+getLastPathToken(strCopy)+".tar.gz";
    	    if(system(cmd.c_str()));
    	    emit emit ThreadEnd(1);
    }
}
 
void BackupThread::stop()
{
    string cmd = "rm -f " + strBackup+"/"+getLastPathToken(strCopy)+".tar.gz";
    if(system(cmd.c_str()));
    cmd = "pkill tar";
    if(system(cmd.c_str()));
}

void BackupThread::setStr(QString from, QString to){
    strCopy = from.toUtf8().constData();
    strBackup = to.toUtf8().constData();
}
