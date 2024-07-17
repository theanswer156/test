#ifndef MYNWINDOW_H
#define MYNWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QSpinBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPointF>
namespace Ui {
class MynWindow;
}

class MynWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MynWindow(QWidget *parent = nullptr);
    ~MynWindow();

//    void DrawPaint(QWidget *PaintWidget,QList<QVector<int>> PointIndex);
    void GetData(QList<QSpinBox*> SpinBoxs,QList<QPointF> PointIndex);
    void CreatNewPoint(QGridLayout *gridLayout,int index);
    void CreatNewPoint(QHBoxLayout *leftupLayout,int index,QList<QSpinBox*> SpinBoxs);
//!     就没有自定义的信号
//signals:
//    void PushAddButton(QGridLayout *gridLayout,int index);
//    void PushDeleteButton(QGridLayout *gridLayout,int index);
//    void PushPaintButton(QList<QSpinBox*> SpinBoxs,QList<QPointF> PointIndex);

public slots:
    void AddButtonPushed(QGridLayout *gridLayout);
    void DeleteButtonPushed(QGridLayout *gridLayout);
    void PaintButtonPushed(QGridLayout *gridlayout,QWidget *widget);
private:
//    QString str{" 123456789"};
    QList<QPointF> PointIndex;
    QList<QPointF> DesIndex;
    int index = 6;
//private:
//    Ui::MynWindow *ui;
//    不借助UI的方法创建就没有这个变量？
};
//class PointAndCoordinate
//{
//public:
//    PointAndCoordinate();
//    ~PointAndCoordinate();
//private:
//    QString str{" 123456789"};
//};


#endif // MYNWINDOW_H
