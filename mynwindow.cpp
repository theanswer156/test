#include "mynwindow.h"
//#include "ui_mynwindow.h"

#include <QSplitter>
#include <QLabel>
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

    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setSpacing(10);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    QPushButton *leftbutton = new QPushButton("左边布局");
    QPushButton *rightbutton = new QPushButton("右边布局————");

//    layout->addWidget(leftLabel);
//    layout->addWidget(rightLabel);

    leftLayout->addWidget(leftbutton);
    leftLayout->addWidget(rightbutton);
    layout->addWidget(rightbutton);


    // 调整centralWidget的大小策略
//    leftLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    rightLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}
MynWindow::~MynWindow()
{
//    delete MynWindow;
}
