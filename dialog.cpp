#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    init();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnCancel_clicked()
{
    reject();
}

void Dialog::on_btnDecipher_clicked()
{
    QString name;
    name = get_name_from_path(ui->lineEdit->text());

    if(!encrypter.load_file(ui->lineEdit->text().toStdString()))
    {
        QMessageBox::critical(this,"Error","Cannot open file!");
        return;
    }

    try {
         encrypter.decipher(name.toStdString(),saved_path.toStdString()); //dodać ścieżkę zapisu
    }
    catch (std::invalid_argument &exp) {
        QMessageBox::critical(this,"Error",exp.what());
        accept();
    }
    catch (std::length_error &exp)
    {
        QMessageBox::critical(this, "Error", exp.what());
        accept();
    }
}

void Dialog::on_btnCipher_clicked()
{
    QString name;
    name = get_name_from_path(ui->lineEdit->text());

    if(!encrypter.load_file(ui->lineEdit->text().toStdString()))
    {
        QMessageBox::critical(this,"Error","Cannot open file!");
        accept();
    }

    string key = encrypter.key_generator();
    if(!encrypter.load_file(ui->lineEdit->text().toStdString()))
    {
        QMessageBox::critical(this,"Error","Cannot open file!");

    }

    try {  encrypter.cipher(key,name.toStdString(), saved_path.toStdString()); }
    catch (std::invalid_argument &exp) {
        QMessageBox::critical(this,"Error",exp.what());
    }

    QMessageBox::information(this,"Success!","Your file is now ciphered prorly!");

}

void Dialog::on_btnSettings_clicked()
{
    QSettings set("TS","App");
    settings *setWind = new settings(this);
    setWind->exec();
    saved_path=setWind->getDirPath();
    qDebug() << saved_path;
    set.setValue("path_to_saved",saved_path);
}

void Dialog::on_btnSearch_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Wybierz plik", "/");
    ui->lineEdit->setText(fileName);

}

void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    ui->btnCipher->setEnabled(true);
    ui->btnDecipher->setEnabled(true);
}

QString Dialog::get_name_from_path(QString name)
{
    filesys::path path(name.toStdString());

    if(path.has_stem())
    {
        return QString::fromStdString(path.filename().string());
    }
    else
    {
        return "";
    }

}

void Dialog::init()
{
    QSettings set("TS","App");
    saved_path=set.value("path_to_saved").toString();
}
