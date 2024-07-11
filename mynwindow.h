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
signals:
    void AddButtonPushed();
    void DeleteButtonPushed();
    void PaintButtonPushed(QList<QSpinBox*> SpinBoxs,QList<QPointF> PointIndex);
public slots:

    void PushAddButton();
    void PushDeleteButton();
    void PushPaintButton(QList<QSpinBox*> SpinBoxs,QList<QPointF> PointIndex);
private:
    QString str{" 123456789"};
    QList<QPointF> points;
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
