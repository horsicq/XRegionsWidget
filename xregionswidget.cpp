#include "xregionswidget.h"
#include "ui_xregionswidget.h"

XRegionsWidget::XRegionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XRegionsWidget)
{
    ui->setupUi(this);
}

XRegionsWidget::~XRegionsWidget()
{
    delete ui;
}
