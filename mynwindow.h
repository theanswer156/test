#ifndef MYNWINDOW_H
#define MYNWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QSpinBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
namespace Ui {
class MynWindow;
}

class MynWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MynWindow(QWidget *parent = nullptr);
    ~MynWindow();

    void DrawPaint(QWidget *PaintWidget,QList<QVector<int>> PointIndex);
    void GetData(QList<QSpinBox*> SpinBoxs,QList<QVector<int>> PointIndex);
signals:
    void AddButtonPushed(QHBoxLayout *HLayout,int index,QList<QSpinBox*> SpinBoxs);
public slots:
    void CreatNewPoint(QHBoxLayout *HLayout,int index,QList<QSpinBox*> SpinBoxs);
    void PushAddButton(QHBoxLayout *HLayout,int index,QList<QSpinBox*> SpinBoxs);
    void DeletePoint();
private:
    QString str{" 123456789"};
    QWidget *leftWidget;
    QWidget *rightWidget;
    QVBoxLayout *rightLayout;
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
