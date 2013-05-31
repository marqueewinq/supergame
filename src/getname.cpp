#include "getname.h"
#include "ui_getname.h"

GetName::GetName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetName)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
}

GetName::~GetName()
{
    *returnValue = ui->lineEdit->text();
    delete ui;
}
