#ifndef BACKUP_DIALOG__H
#define BACKUP_DIALOG__H

#include <QDialog>
#include <string>
#include "gui/BackupThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BackupDialog; }
QT_END_NAMESPACE

class BackupDialog : public QDialog
{
    Q_OBJECT

public:
    BackupDialog(QWidget *parent = nullptr);
    ~BackupDialog();
    
    

private slots:

    void on_copyButton_clicked();

    void on_backupButton_clicked();
    
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();
    
    void listener(int);
    


private:
    Ui::BackupDialog *ui;
    BackupThread *backupthread;
    std::string strCopy;
    std::string strBackup;
    
signals:
    void fin();
    void start(QString, QString);
};
#endif // DIALOG_H
