#include "mynwindow.h"
//#include "ui_mynwindow.h"

//#include <QSplitter>
//#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
//#include <QtCharts/QChart>
//#include <QtCore/QTimer>
MynWindow::MynWindow(QWidget *parent) :
    QMainWindow(parent)
//    ui(new Ui::MynWindow)
{
//    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    //    没有使用过的变量也会引起警告
    // 创建水平布局
    QHBoxLayout *layout = new QHBoxLayout(centralWidget);
    // 创建两个标签作为示例控件，并添加到布局中
//    QLabel *leftLabel = new QLabel("左侧区域", centralWidget);
//    QLabel *rightLabel = new QLabel("右侧区域", centralWidget);

    QWidget *leftWidget = new QWidget(centralWidget);
    QWidget *rightWidget = new QWidget(centralWidget);

    QPushButton *leftbutton1 = new QPushButton("左边按钮1");
    QPushButton *leftbutton2 = new QPushButton("左边按钮2");
    QPushButton *rightbutton = new QPushButton("右边布局");

    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setSpacing(10);
    leftLayout->addWidget(leftbutton1);
    leftLayout->addWidget(leftbutton2);

    QHBoxLayout *rightLayout = new QHBoxLayout(rightWidget);
    rightLayout->addWidget(rightbutton);

    layout->addWidget(leftWidget);
    layout->addWidget(rightWidget);


}
MynWindow::~MynWindow()
{
//    delete MynWindow;
}



PointAndCoordinate::PointAndCoordinate(QWidget *parent,int index,QSpinBox &X,QSpinBox &Y)
{
    QHBoxLayout *HLayout = new QHBoxLayout(parent);
    QString str = "点";
    QLineEdit *PointName = new QLineEdit(str.append(index));
    HLayout->addWidget(PointName);
    HLayout->addWidget(&X);
    HLayout->addWidget(&Y);
};
PointAndCoordinate::~PointAndCoordinate()
{

}










