 *   SPDX-FileCopyrightText: 2021 Kiyung <yongjae.choi20@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later

#ifndef TESTTHREAD_H
#define TESTTHREAD_H
 
#include <QThread>
#include <QDebug>
#include <unistd.h>
#include <string>

 
class BackupThread : public QThread
{
    Q_OBJECT
public:
    explicit BackupThread(QObject *parent = 0);
    void stop();
    int m_stopFlag = false;
 
private:
    void run();
    std::string strCopy;
    std::string strBackup; 
    
private slots:
void setStr(QString, QString);
    
 
signals:
    void ThreadEnd( int );
 
};
 
#endif // TESTTHREAD_H
