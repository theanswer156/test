#include "mynwindow.h"
#include "plotwidget.h"
#include "plotwidget.cpp"
//#include "ui_mynwindow.h"

//#include <QSplitter>
//#include <QLabel>
//#include <QSpinBox>
//#include <QLineEdit>
//#include <QVBoxLayout>
//#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QtAlgorithms>
#include <QPainter>
#include <QLayout>

//#include <QtCharts/QChart>
//#include <QtCore/QTimer>

//PointAndCoordinate::PointAndCoordinate()
//{
//    QWidget *parent = new QWidget();
//    QHBoxLayout *HLayout = new QHBoxLayout(parent);

//};
//PointAndCoordinate::~PointAndCoordinate()
//{

//}

MynWindow::MynWindow(QWidget *parent) :
    QMainWindow(parent)
//    ui(new Ui::MynWindow)
{
//    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    //    没有使用过的变量也会引起警告
    // 创建水平布局
    QGridLayout *mainlayout = new QGridLayout(centralWidget);
//    已经说明centralwidget是个水平布局了  所以可以有下面两句
//    分别得到左边和右边的界面
    QWidget *leftWidget = new QWidget(centralWidget);
    QWidget *rightWidget = new QWidget(centralWidget);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

//    QHBoxLayout *LeftupLayout = new QHBoxLayout(leftupWidget);

    QWidget *leftupWidget = new QWidget(leftWidget);
    QVBoxLayout *leftupLayout = new QVBoxLayout(leftupWidget);
    QWidget *leftdownWidget = new QWidget(leftWidget);
    QHBoxLayout *leftdownLayout = new QHBoxLayout(leftdownWidget);

    QWidget *rightupWidget = new QWidget(rightWidget);
    QVBoxLayout *rightupLayout = new QVBoxLayout(rightupWidget);
    QWidget *rightdownWidget = new QWidget(rightWidget);
    QVBoxLayout *rightdownLayout = new QVBoxLayout(rightdownWidget);


//    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
//    QVBoxLayout *leftVLayout = new QVBoxLayout(leftWidget);

//    用列表来维护SpinBox的顺序
    QList<QSpinBox*> SpinBoxs;
//    QVBoxLayout *leftupLayout = new QVBoxLayout(leftupWidget);

    QLineEdit *PointName = new QLineEdit(QString("名称"),leftupWidget);
    PointName->setFixedWidth(100);
    PointName->setAlignment(Qt::AlignCenter);
    QLineEdit *AxisName_X = new QLineEdit(QString("X 轴坐标"),leftupWidget);
    AxisName_X->setReadOnly(true);
    AxisName_X->setAlignment(Qt::AlignCenter);
    QLineEdit *AxisName_Y = new QLineEdit(QString("Y 轴坐标"),leftupWidget);
    AxisName_Y->setReadOnly(true);
    AxisName_Y->setAlignment(Qt::AlignCenter);
    QHBoxLayout *LeftHLayout = new QHBoxLayout(leftupWidget);
    LeftHLayout->addWidget(PointName);
    LeftHLayout->addWidget(AxisName_X);
    LeftHLayout->addWidget(AxisName_Y);
//    leftupWidget->setLayout(leftupHLayout);
    leftupLayout->addLayout(LeftHLayout);


    for (int i = 1;i<=3;++i) {
        QHBoxLayout *LeftupHLayout = new QHBoxLayout(leftupWidget);
        CreatNewPoint(LeftupHLayout,i,SpinBoxs);
        leftupLayout->addLayout(LeftupHLayout);
    }
//    layout->addLayout(leftLayout);
//    PointAndCoordinate *point1 = new PointAndCoordinate(1);
//    PointAndCoordinate *point2 = new PointAndCoordinate(2);

//    leftLayout->setSpacing(10);
//    由于PointAndCoordinate类指定了父类  所以这里属于是在布局中添加界面？？
//    leftLayout->addWidget(point1);
//    leftLayout->addWidget(point2);
//    leftLayout->addSpacing(10);


    //!  信号的类和槽的类都不是同一个类
    //!
    //!
    //!connect(AddButton,&MynWindow::AddButtonPushed,this,&MynWindow::CreatNewPoint);
    //!
    //! \brief AxisName_X
    //!
    //!
    //!


//    rightLayout->addWidget(rightbutton1);
//    rightLayout->addWidget(rightbutton2);

//    leftWidget->setLayout(leftLayout);
//    rightWidget->setLayout(rightLayout);

//    QHBoxLayout *leftdownLayout = new QHBoxLayout;
    QPushButton *AddButton = new QPushButton("添加新点",leftdownWidget);
    QPushButton *DeleteButton = new QPushButton("删除点",leftdownWidget);
    AddButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    DeleteButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    leftdownLayout->addWidget(AddButton);
    leftdownLayout->addWidget(DeleteButton);

//    leftLayout->addLayout(leftupLayout);
//    leftLayout->addLayout(leftdownLayout);
    leftWidget->setLayout(leftLayout);
//    leftLayout->addWidget(leftdownWidget);
    QPushButton *PaintButton = new QPushButton("绘制曲线",rightdownWidget);
    PaintButton->setFixedSize(100,50);
    rightdownLayout->addWidget(PaintButton);

//    rightLayout->addLayout(rightdownLayout);

    rightWidget->setLayout(rightLayout);

    mainlayout->addWidget(leftupWidget,0,0);
    mainlayout->addWidget(leftdownWidget,1,0);

    mainlayout->addWidget(rightupWidget,0,1);
    mainlayout->addWidget(rightdownWidget,1,1);



//!    右边界面：B样条曲线的绘制


}
MynWindow::~MynWindow()
{
//    delete MynWindow;
}

void MynWindow::CreatNewPoint(QHBoxLayout *LeftupHLayout,int index,QList<QSpinBox*> SpinBoxs)
{
//    QWidget *leftWidget = new QWidget(parent);
//    QHBoxLayout *leftLayout = new QHBoxLayout(parent);
//    QWidget VWidget = new QWidget(VLayout->parentWidget());

//    QWidget *LeftWidget = new QWidget(HLayout->parentWidget());
//    QHBoxLayout *HLayout = new QHBoxLayout(widget);
    QString name = "点"+str[index];
    QLineEdit *PointName = new QLineEdit(name);
    PointName->setReadOnly(true);
    PointName->setAlignment(Qt::AlignCenter);
    PointName->setFixedWidth(100);
    QSpinBox *X = new QSpinBox(LeftupHLayout->parentWidget());
    X->setSingleStep(1);
    SpinBoxs.append(X);
    QSpinBox *Y = new QSpinBox(LeftupHLayout->parentWidget());
    Y->setSingleStep(1);
    SpinBoxs.append(Y);
    LeftupHLayout->addWidget(PointName);
    LeftupHLayout->addWidget(X);
    LeftupHLayout->addWidget(Y);


}
void MynWindow::DeletePoint()
{

}

void MynWindow::PushAddButton(QHBoxLayout *HLayout ,int index ,QList<QSpinBox*> SpinBoxs)
{

}

void MynWindow::DrawPaint(QWidget *PaintWidget,QList<QVector<int>> PointIndex)
{

//    qSort(PointIndex.begin(),PointIndex.end());

}
void MynWindow::GetData(QList<QSpinBox*> SpinBoxs,QList<QVector<int>> PointIndex)
{
//    QList<QVector<int>> PointIndex;
    QList<QSpinBox*>::iterator ite= SpinBoxs.begin();
    while(ite != SpinBoxs.end())
    {
        PointIndex.append(QVector<int>{(*ite)->value(),(*(++ite))->value()});

        ite++;
    }
    std::sort(PointIndex.begin(),PointIndex.end(),[](const QVector<int> &a,const QVector<int> &b)
    {
       return a.at(0)==b.at(0)?a.at(1) < b.at(1):a.at(0) < b.at(0);
    });
}









