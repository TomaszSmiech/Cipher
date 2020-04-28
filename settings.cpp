#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    init();
}

settings::~settings()
{
    qDebug() << dirPath;
    delete ui;
}

void settings::on_buttonBox_accepted()
{
    accept();
}

void settings::on_buttonBox_rejected()
{
    reject();
}

void settings::on_pushButton_clicked()
{
    QSettings settings("TS","App");
    QString dr;
    dr = QFileDialog::getExistingDirectory(this, "Choose directory", "/");

    if(dr!="")
    dirPath=dr;

    qDebug() << dirPath;
    ui->path_saved->setText(dirPath);
    settings.setValue("path",dirPath);
    accept();
}

void settings::init()
{
    QSettings settings("TS","App");
    ui->path_saved->setText(settings.value("path").toString());
    dirPath=settings.value("path").toString();
}

QString settings::getDirPath() const
{
    return dirPath;
}
