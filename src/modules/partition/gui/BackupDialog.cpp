#include "BackupDialog.h"
#include "ui_BackupDialog.h"
#include "jobs/Backup.h"

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


BackupDialog::BackupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BackupDialog)
    , caCopy(nullptr)
    , caBackup(nullptr)
    , tmp(nullptr)
{
    ui->setupUi(this);
    
    // if userName allready exist
    if(getlogin() != NULL){
    caCopy = (char*)malloc(300);
    	strcat(caCopy,"/home/");
    	strcat(caCopy,getlogin());
    	
    	tmp = (char*)malloc(300);
    	strcpy(tmp,caCopy);
	    QString qstrCopy(trim(tmp));
	    free(tmp);
	
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
    selectPath();
}

void BackupDialog::on_backupButton_clicked()
{
}


char *BackupDialog::trim(char *s)
{    char *ptr;
    if (!s)
        return NULL;   // handle NULL string
    if (!*s)
        return s;      // handle empty string
    for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
    ptr[1] = '\0';
    return s;
}

