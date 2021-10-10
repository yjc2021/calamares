#include "BackupThread.h"
#include "BackupDialog.h"
#include "jobs/Backup.h"

using namespace std;
 
BackupThread::BackupThread(QObject *parent) :
    QThread(parent)
{
 
}
 
void BackupThread::run()
{
    string cmd = "tar -zcvf ";
    cmd += strBackup+"/"+getLastPathToken(strCopy)+".tar.gz "+ strCopy;

    switch( system(cmd.c_str()) ){
    	case 0: 
    	    emit ThreadEnd(0);
    	    break;
    	default :
    	    cmd = "rm -f " + strBackup+"/"+getLastPathToken(strCopy)+".tar.gz";
    	    system(cmd.c_str());
    	    emit emit ThreadEnd(1);
    }
}
 
void BackupThread::stop()
{
    string cmd = "rm -f " + strBackup+"/"+getLastPathToken(strCopy)+".tar.gz";
    system(cmd.c_str());
    cmd = "pkill tar";
    system(cmd.c_str());
}

void BackupThread::setStr(QString from, QString to){
    strCopy = from.toUtf8().constData();
    strBackup = to.toUtf8().constData();
}
