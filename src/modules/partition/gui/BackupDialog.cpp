/*
 *   SPDX-FileCopyrightText: 2021 Kiyung <yongjae.choi20@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "BackupDialog.h"
#include "ui_BackupDialog.h"
#include "jobs/PathSelect.h"
#include "jobs/ExtractFileSize.h"
#include "gui/BackupThread.h"

#include <QtCore>
#include <QtGui>

#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <unistd.h>

using std::thread;
using namespace std;


string tmp;

//0-> ready, 1->running, 2->fin, 3->stop
int phase = 0;
extern int phase;

BackupDialog::BackupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BackupDialog)
{
    ui->setupUi(this);
        
    ui->copyLine->setReadOnly(true);
    ui->backupLine->setReadOnly(true);
    
    // backup thread
    backupthread = new BackupThread(this);
    connect(backupthread, SIGNAL(ThreadEnd(int)), this, SLOT(listener(int)));
    connect(this, SIGNAL(strPass(QString, QString)), backupthread, SLOT(setStr(QString, QString)));
    
    strCopy = "";
    strBackup = "";
    
    // if userName allready exist
    if(getlogin() != NULL){
    
    	tmp = "/home/";
    	strCopy += tmp;
    	tmp = getlogin();
    	strCopy += tmp;
    	
    	QString qstrCopy(strCopy.c_str());
	ui->copyLine->setText(qstrCopy);
	qstrCopy.clear();
    }
}

BackupDialog::~BackupDialog()
{
    delete ui;
}

void BackupDialog::on_copyButton_clicked()
{
    tmp = selectPath();
    if(tmp[0] == '/') strCopy = tmp;
    QString qstrCopy(strCopy.c_str());
    ui->copyLine->setText(qstrCopy);
    qstrCopy.clear();
}

void BackupDialog::on_backupButton_clicked()
{
    tmp = selectPath();
    if(tmp[0] == '/') strBackup = tmp;
    QString qstrCopy(strBackup.c_str());
    ui->backupLine->setText(qstrCopy);
    qstrCopy.clear();
}

void BackupDialog::on_nextButton_clicked(){
    if(strCopy.empty() || strBackup.empty()) {
    	QString e("Select both copy and backup paths.");
    	ui->detailsLabel->setText(e);
    	e.clear();
    }
    // leakness of capability
    else if(get_du_size(strCopy.c_str()) +1000 > get_df_size(strBackup.c_str())){
    	QString er("Not enough storage space, please reselect.");
        ui->detailsLabel->setText(er);
        er.clear();
    }
    // start backup
    else{ 
    	ui->nextButton->setEnabled(false);
    	emit strPass(*(new QString(strCopy.c_str())), *(new QString(strBackup.c_str())));
    	QString working("Working...");
    	ui->detailsLabel->setText(working);
    	working.clear();
    	phase =1;
    	
    	backupthread->start();
    }
}

void BackupDialog::listener(int result){
    QString lb("");
    if(result==0) {
    	lb = "Done.";
    	if(phase==1) phase =2;
    }else{
    	lb = "Unexpected exception occurs!";
    	phase =3;
    }
    ui->detailsLabel->setText(lb);
}

void BackupDialog::on_cancelButton_clicked(){
    close();
}

void BackupDialog::closeEvent(QCloseEvent *event){
   if(phase==1) {
    	backupthread->terminate();
    	backupthread->stop();
    	phase =0;
    }
    event->accept();
}
