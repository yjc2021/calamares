#include "BackupDialog.h"
#include "ui_BackupDialog.h"
#include "jobs/Backup.h"
#include "jobs/ExtractFileSize.h"

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

using namespace std;

string strCopy;
string strBackup;
string tmp;

BackupDialog::BackupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BackupDialog)
{
    ui->setupUi(this);
    
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
    strCopy = selectPath();
    QString qstrCopy(strCopy.c_str());
    ui->copyLine->setText(qstrCopy);
    qstrCopy.clear();
    
}

void BackupDialog::on_backupButton_clicked()
{
    strBackup = selectPath();
    QString qstrCopy(strBackup.c_str());
    ui->backupLine->setText(qstrCopy);
    qstrCopy.clear();
}


void BackupDialog::on_pushButton_clicked(){
    // leakness of capability
    if(get_du_size(strCopy.c_str()) +1000 > get_df_size(strBackup.c_str())){
    	QString er("not enough storage space, please reselect the file.");
        ui->detailsLabel->setText(er);
        er.clear();
    }
    // start backup
    else{ 
    	QString working("Working...");
    	ui->detailsLabel->setText(working);
    	working.clear();
    	
    	// done
    	if(execBackup(strCopy, strBackup)){
    	    QString success("The Backup is over!!");
    	    ui->detailsLabel->setText(success);
    	    success.clear();
    	}
    	// exception occurs!!
    	else{
    	    QString excp("Unexpected exception occured, please retry!!");
    	    ui->detailsLabel->setText(excp);
    	    excp.clear();
    	}
    }
}

void BackupDialog::on_pushButton_2_clicked(){
    close();
}


