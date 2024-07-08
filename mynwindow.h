#ifndef MYNWINDOW_H
#define MYNWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QSpinBox>
#include <QLineEdit>
namespace Ui {
class MynWindow;
}

class MynWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MynWindow(QWidget *parent = nullptr);
    ~MynWindow();


//private:
//    Ui::MynWindow *ui;
//    不借助UI的方法创建就没有这个变量？
};
class PointAndCoordinate
{
public:
    PointAndCoordinate(int index,QSpinBox X,QSpinBox Y);
    ~PointAndCoordinate();
private:
    QLineEdit pointName;
    QSpinBox coordinate_X;
    QSpinBox coordinate_Y;
};


#endif // MYNWINDOW_H
