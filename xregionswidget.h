#ifndef XREGIONSWIDGET_H
#define XREGIONSWIDGET_H

#include <QWidget>

namespace Ui {
class XRegionsWidget;
}

class XRegionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XRegionsWidget(QWidget *parent = nullptr);
    ~XRegionsWidget();

private:
    Ui::XRegionsWidget *ui;
};

#endif // XREGIONSWIDGET_H
