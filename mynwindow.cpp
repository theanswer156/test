#include "mynwindow.h"
#include "drawline.h"
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
    QGridLayout *leftupLayout = new QGridLayout(leftupWidget);
    QWidget *leftdownWidget = new QWidget(leftWidget);
    QHBoxLayout *leftdownLayout = new QHBoxLayout(leftdownWidget);

    QWidget *rightupWidget = new QWidget(rightWidget);
    QVBoxLayout *rightupLayout = new QVBoxLayout(rightupWidget);
    Q_UNUSED(rightupLayout);
    QWidget *rightdownWidget = new QWidget(rightWidget);
    QVBoxLayout *rightdownLayout = new QVBoxLayout(rightdownWidget);


//    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
//    QVBoxLayout *leftVLayout = new QVBoxLayout(leftWidget);

//    用列表来维护SpinBox的顺序
    QList<QSpinBox*> SpinBoxs;

//    QVBoxLayout *leftupLayout = new QVBoxLayout(leftupWidget);

    QLineEdit *PointName = new QLineEdit(QString("名称"),leftupWidget);
    PointName->setFixedSize(100,20);
    PointName->setAlignment(Qt::AlignCenter);
    QLineEdit *AxisName_X = new QLineEdit(QString("X 轴坐标"),leftupWidget);
    AxisName_X->setFixedSize(100,20);
    AxisName_X->setReadOnly(true);
    AxisName_X->setAlignment(Qt::AlignCenter);
    QLineEdit *AxisName_Y = new QLineEdit(QString("Y 轴坐标"),leftupWidget);
    AxisName_Y->setFixedSize(100,20);
    AxisName_Y->setReadOnly(true);
    AxisName_Y->setAlignment(Qt::AlignCenter);
//    QHBoxLayout *LeftHLayout = new QHBoxLayout(leftupWidget);
//    采用垂直布局
    leftupLayout->addWidget(PointName,0,0);
    leftupLayout->addWidget(AxisName_X,0,1);
    leftupLayout->addWidget(AxisName_Y,0,2);
//    leftupWidget->setLayout(leftupHLayout);
//    leftupLayout->addLayout(LeftHLayout);

    for(int i = 1;i<4;++i){
        CreatNewPoint(leftupLayout,i);
    }
    CreatNewPoint(leftupLayout,4);


//    采用CreatNewPoint重载  利用gridlayout来添加widget
//    for (int i = 1;i<=3;++i) {
//        QHBoxLayout *LeftupHLayout = new QHBoxLayout(leftupWidget);
//        CreatNewPoint(LeftupHLayout,i,SpinBoxs);
//        leftupLayout->addLayout(LeftupHLayout);
//    }

    QPushButton *AddButton = new QPushButton("添加新点",leftdownWidget);
    connect(AddButton,&QPushButton::click,this,&MynWindow::AddButtonPushed);
    //! 添加按钮信号槽链接
    //!
    QPushButton *DeleteButton = new QPushButton("删除点",leftdownWidget);
    connect(DeleteButton,&QPushButton::click,this,&MynWindow::DeleteButtonPushed);
    //! 删除按钮信号槽链接
    //!
    AddButton->setFixedSize(200,50);
    DeleteButton->setFixedSize(200,50);

    leftdownLayout->addWidget(AddButton);
    leftdownLayout->addWidget(DeleteButton);

//    leftLayout->addLayout(leftupLayout);
//    leftLayout->addLayout(leftdownLayout);
    leftWidget->setLayout(leftLayout);
//    leftLayout->addWidget(leftdownWidget);
    QPushButton *PaintButton = new QPushButton("绘制曲线",rightdownWidget);
//    connect(PaintButton,&QPushButton::click,this,&MynWindow::PushPaintButton);
    PaintButton->setFixedSize(100,50);
    rightdownLayout->addWidget(PaintButton,0);

//    rightLayout->addLayout(rightdownLayout);

    rightWidget->setLayout(rightLayout);

    mainlayout->addWidget(leftupWidget,0,0);
    mainlayout->addWidget(leftdownWidget,1,0);

    mainlayout->addWidget(rightupWidget,0,1);
    mainlayout->addWidget(rightdownWidget,1,1);



//!    右边界面：B样条曲线的绘制
//!
//!
//!
//!
//!
    // 创建折线图小部件
    LineChartWidget *chartWidget = new LineChartWidget(rightupWidget);
//    chartWidget->setFixedSize(100,100);

    // 假设这是你已有的数据
    QList<QPointF> myData;

//    QRandomGenerator randomgen;
//    quint64 seed = QDateTime::currentMSecsSinceEpoch();
//    randomgen.seed(seed);
    qDebug()<<chartWidget->size();

    for (int i = 0; i < 25; i+=1) {
        // 这里应填入你的实际数据点

        myData.append(QPointF(i, (static_cast<float>(qrand() / 100)))); // someFunction 应替换为你的数据生成逻辑
    }


    chartWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    // 设置数据到折线图小部件
    chartWidget->drawPoint(myData);
    chartWidget->setdesData(myData);

//    layout->addWidget(chartWidget);
    rightupLayout->addWidget(chartWidget);








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
    PointName->setFixedSize(100,20);
    QSpinBox *X = new QSpinBox(LeftupHLayout->parentWidget());
    X->setSingleStep(1);
    X->setFixedSize(100,20);
    SpinBoxs.append(X);
    QSpinBox *Y = new QSpinBox(LeftupHLayout->parentWidget());
    Y->setSingleStep(1);
    Y->setFixedSize(100,20);
    SpinBoxs.append(Y);
    LeftupHLayout->addWidget(PointName);
    LeftupHLayout->addWidget(X);
    LeftupHLayout->addWidget(Y);
}


void MynWindow::PushDeleteButton()
{

}

void MynWindow::PushPaintButton(QList<QSpinBox *> SpinBoxs, QList<QPointF> PointIndex)
{

}

void MynWindow::PushAddButton()
{

}

//void MynWindow::DrawPaint(QWidget *PaintWidget,QList<QVector<int>> PointIndex)
//{

////    qSort(PointIndex.begin(),PointIndex.end());

//}
void MynWindow::GetData(QList<QSpinBox*> SpinBoxs,QList<QPointF> PointIndex)
{
//    QList<QVector<int>> PointIndex;
    QList<QSpinBox*>::iterator ite= SpinBoxs.begin();
    while(ite != SpinBoxs.end())
    {
        PointIndex.append(QPointF((*ite)->value(),(*(++ite))->value()));
        ite++;
    }
    std::sort(PointIndex.begin(),PointIndex.end(),[](const QPointF &a,const QPointF &b)
    {
       return a.x()== b.x()?a.y() < b.y():a.x() < b.x();
    });
}

void MynWindow::CreatNewPoint(QGridLayout *gridLayout, int index)
{
    QString name = "点"+str[index];
    QLineEdit *PointName = new QLineEdit(name);
    PointName->setReadOnly(true);
    PointName->setAlignment(Qt::AlignCenter);
    PointName->setFixedSize(100,20);
    QSpinBox *X = new QSpinBox(gridLayout->parentWidget());
    X->setSingleStep(1);
    X->setFixedSize(100,20);
    QSpinBox *Y = new QSpinBox(gridLayout->parentWidget());
    Y->setSingleStep(1);
    Y->setFixedSize(100,20);
    gridLayout->addWidget(PointName,index,0);
    gridLayout->addWidget(X,index,1);
    gridLayout->addWidget(Y,index,2);
}









