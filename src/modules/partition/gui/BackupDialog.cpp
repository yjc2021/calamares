#include "BackupDialog.h"
#include "ui_BackupDialog.h"

#include <QtCore>
#include <QtGui>

BackupDialog::BackupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BackupDialog)
{
    ui->setupUi(this);
   // ui->label->setText("<b >Hello </b> Everyone");
}

BackupDialog::~BackupDialog()
{
    delete ui;
}

void BackupDialog::on_copyButton_clicked()
{
}

void BackupDialog::on_backupButton_clicked()
{
}
