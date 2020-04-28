#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include "xor_cipher.h"
#include <QSettings>
#include "settings.h"
#include <QRegularExpression>
#include <QDebug>
#include <experimental/filesystem>
#include <QSettings>


namespace filesys = std::experimental::filesystem;

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnCancel_clicked();

    void on_btnDecipher_clicked();

    void on_btnCipher_clicked();

    void on_btnSettings_clicked();

    void on_btnSearch_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
    xor_cipher encrypter;
    QString saved_path;
    QString get_name_from_path(QString name);
    void init();

};
#endif // DIALOG_H
