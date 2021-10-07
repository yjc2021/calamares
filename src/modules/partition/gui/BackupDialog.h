#ifndef BACKUP_DIALOG__H
#define BACKUP_DIALOG__H

#include <QDialog>

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

private:
    Ui::BackupDialog *ui;
};
#endif // DIALOG_H
