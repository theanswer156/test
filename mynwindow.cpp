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
#include <QRandomGenerator>


MynWindow::MynWindow(QWidget *parent) :
    QMainWindow(parent)

{

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



//    index = 4;
    for(int i = 1;i<index;++i){
        CreatNewPoint(leftupLayout);
    }
//    CreatNewPoint(leftupLayout,4);


//    采用CreatNewPoint重载  利用gridlayout来添加widget
//    for (int i = 1;i<=3;++i) {
//        QHBoxLayout *LeftupHLayout = new QHBoxLayout(leftupWidget);
//        CreatNewPoint(LeftupHLayout,i,SpinBoxs);
//        leftupLayout->addLayout(LeftupHLayout);
//    }

    QPushButton *AddButton = new QPushButton("添加新点",leftdownWidget);
    connect(AddButton,&QPushButton::clicked,[this,leftupLayout](){
        AddButtonPushed(leftupLayout);
    });

    //! 添加按钮信号槽链接
    //!
    QPushButton *DeleteButton = new QPushButton("删除点",leftdownWidget);
    connect(DeleteButton,&QPushButton::clicked,[this,leftupLayout](){
        DeleteButtonPushed(leftupLayout);
    });
    //! 删除按钮信号槽链接
    //!
    AddButton->setFixedSize(200,50);
    DeleteButton->setFixedSize(200,50);

    leftdownLayout->addWidget(AddButton);
    leftdownLayout->addWidget(DeleteButton);


    leftWidget->setLayout(leftLayout);

    QPushButton *PaintButton = new QPushButton("绘制曲线",rightdownWidget);

    PaintButton->setFixedSize(100,50);
    rightdownLayout->addWidget(PaintButton,0);
    connect(PaintButton,&QPushButton::clicked,[this,leftupLayout,rightupWidget](){
      PaintButtonPushed(leftupLayout,rightupWidget);
    });





//!    右边界面：B样条曲线的绘制
//!
//!
//!
//!

//    LineChartWidget *chartWidget = new LineChartWidget(rightupWidget);

//    chartWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


//    rightupLayout->addWidget(chartWidget);

    rightWidget->setLayout(rightLayout);

    mainlayout->addWidget(leftupWidget,0,0);
    mainlayout->addWidget(leftdownWidget,1,0);

    mainlayout->addWidget(rightupWidget,0,1);
    mainlayout->addWidget(rightdownWidget,1,1);



}

MynWindow::~MynWindow()
{

}



//!     信号不需要实现  只需要定义   而且就没有这些信号


void MynWindow::CreatNewPoint(QGridLayout *gridLayout)
{

    QRandomGenerator randomgen;
    quint32 seed = QRandomGenerator::global()->bounded(0,500);
    randomgen.seed(seed);
    QString name = "点"+QString::number(index);
    QLineEdit *PointName = new QLineEdit(name);
    PointName->setReadOnly(true);
    PointName->setAlignment(Qt::AlignCenter);
    PointName->setFixedSize(100,20);
    QSpinBox *X = new QSpinBox(gridLayout->parentWidget());
    X->setSingleStep(1);
    X->setFixedSize(100,20);
//    X->setMaximum(500);

    X->setValue(randomgen.bounded(0,500));
    QSpinBox *Y = new QSpinBox(gridLayout->parentWidget());
    Y->setSingleStep(1);
    Y->setFixedSize(100,20);
    Y->setMinimum(100);
//    Y->setMaximum(500);
    Y->setValue(randomgen.bounded(100,500));

    gridLayout->addWidget(PointName,index,0);
    gridLayout->addWidget(X,index,1);
    gridLayout->addWidget(Y,index,2);
    ++index;
}

void MynWindow::AddButtonPushed(QGridLayout *gridLayout){


    QRandomGenerator randomgen;
    quint32 seed = QRandomGenerator::global()->bounded(0,500);
    randomgen.seed(seed);
    QString name = "点"+QString::number(index);
    QLineEdit *PointName = new QLineEdit(name);
    PointName->setReadOnly(true);
    PointName->setAlignment(Qt::AlignCenter);
    PointName->setFixedSize(100,20);
    QSpinBox *X = new QSpinBox(gridLayout->parentWidget());
    X->setSingleStep(1);
    X->setFixedSize(100,20);
    X->setValue(randomgen.bounded(500));
    QSpinBox *Y = new QSpinBox(gridLayout->parentWidget());
    Y->setSingleStep(1);
    Y->setFixedSize(100,20);
    Y->setMinimum(100);
    Y->setValue(randomgen.bounded(100,500));

    gridLayout->addWidget(PointName,index+1,0);
    gridLayout->addWidget(X,index+1,1);
    gridLayout->addWidget(Y,index+1,2);
    qDebug()<<"Add index :"<<index;
    ++index;
}
void MynWindow::DeleteButtonPushed(QGridLayout *gridLayout){

    if(index<5) return;
    if(gridLayout){
        for(int col = 0;col<3;col++){
            QLayoutItem *item = gridLayout->itemAtPosition(index,col);
            if(item){
                delete item->widget();
            }
        }
        gridLayout->update();
    }
    --index;
    qDebug()<<"Delete index :"<<index;
}
void MynWindow::PaintButtonPushed(QGridLayout *gridlayout,QWidget *rightupwidget){

//    return;
    QPainter painter(rightupwidget);
    srcdata.clear();
    qDebug()<<"绘制图像时，有几个点的坐标"<<index-1;
    for(int row = index-1;row>1;--row){
        //!     这里有什么毛病
        //!     row==index的时候就退出了   why

        QSpinBox *Y = qobject_cast<QSpinBox*>(gridlayout->itemAtPosition(row,2)->widget());
        QSpinBox *X = qobject_cast<QSpinBox*>(gridlayout->itemAtPosition(row,1)->widget());
        //!     总是执行到row=7的时候强制退出了
        if(X){
            qDebug()<<"X->value():"<<X->value();
        }
        if(Y){
            qDebug()<<"Y->value():"<<Y->value();
        }

        if (X && Y) {
            srcdata.append(QPointF(X->value(), Y->value()));
        } else {
            qDebug() << "Failed to cast widget to QSpinBox at row" << row;
        }
        qDebug()<<"row :"<<row;
        qDebug()<<"size of srcdata"<<srcdata.size();
        //!      到了三就强制退出了
        //!      都还没执行到后面的debug
    }
    qDebug()<<"还没执行到这";
    std::sort(srcdata.begin(),srcdata.end(),[](const QPointF &a,const QPointF &b)
    {
       return a.x()== b.x()?a.y() < b.y():a.x() < b.x();
    });
    qDebug()<<"efgjo"<<srcdata.size();
    if(srcdata.isEmpty())
        return;
    painter.setBrush(Qt::blue);
    for (const QPointF &point : srcdata) {
        qDebug()<<point;
        painter.drawEllipse(point, 2, 2);
    }
    desdata1.clear();
    desdata3.clear();
    getDesdata1(srcdata);
    desdata2.clear();
    getDesdata2(srcdata);
    getDesdata_Resampling();
    drawLineChart1(&painter);
    drawLineChart3(&painter);
    drawLineChart2(&painter);
}






