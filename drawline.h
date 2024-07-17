#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QList>
#include <QRect>
#include <QObject>
#include <QEvent>
#include <QDebug>
#include <QRandomGenerator>
#include <cmath>
class LineChartWidget : public QWidget {
    Q_OBJECT

public:
    explicit LineChartWidget(QWidget *parent = nullptr) : QWidget(parent) {
        this->resize(400,400);
    }

    // 设置数据点的方法
    void setdesData(QList<QPointF> &point) {
//        dataPoints = data;
//        我们直接随机生成data  然后处理后得到srcdata
        srcdata.clear();
        srcdata = point;

//        QPainter painter(this);
//         绘制数据点
//        QBrush brush(Qt::blue);
//        painter.setBrush(brush);
//        for (const QPointF &point : srcdata) {
//            painter.drawEllipse(point, 10, 10);
//        }

        //!     给数据点排序
        std::sort(srcdata.begin(),srcdata.end(),[](const QPointF &a,const QPointF &b)
        {
           return a.x()== b.x()?a.y() < b.y():a.x() < b.x();
        });
        drawPoint();

        desdata1.clear();
        getDesdata1();
        desdata2.clear();
        getDesdata2();
        getDesdata_Resampling();
//        diff();
//        update(); // 通知QWidget重绘   也就是这里就给了信号了？？？
        //!updata（）就会通知这个类LineChartWidget要求重绘
        //! 这个时候就会调用paintevent事件处理器函数  而我们在子类中重写了
        //! paintevent函数   所以就会调用重写的paintevent事件处理器函数
        //! 从而完成我们想要的事件
        //!
        //! 所以我们只需要建立信号槽机制  使得收到信号时setdata就行了？？？
    }
    void drawPoint(){
        QPainter painter(this);
//         绘制数据点
        QBrush brush(Qt::green);
        painter.setBrush(brush);
        for (const QPointF &point : srcdata) {
            qreal index_X = point.x();
            qreal index_Y = point.y();
            min_Y = qMin(index_Y,min_Y);
            max_Y = qMax(index_Y,max_Y);
            painter.drawEllipse(point, 5, 5);
            qDebug()<<"point drawed";
        }
    }
    void getDesdata1(){

//        qreal precis = 1e-2;

        for(qreal t = 0;t < 1.0000; t+=precis){
            int size = srcdata.size();
            QVector<qreal> coefficient(size, 0);
            coefficient[0] = 1.000;
            qreal u1 = 1.0 - t;
            //!这里就是递归的计算
            //! 如果我们利用
            for (int j = 1; j <= size - 1; j++) {
                qreal saved = 0.0;
                for (int k = 0; k < j; k++){
                    qreal temp = coefficient[k];
                    coefficient[k] = saved + u1 * temp;
                    saved = t * temp;
                }
                coefficient[j] = saved;
            }

            QPointF resultPoint;
            for (int i = 0; i < size; i++) {
                QPointF point = srcdata.at(i);
                resultPoint = resultPoint + point * coefficient[i];
            }
            desdata1.append(resultPoint);
            desdata3.append(resultPoint);
        }
   }
    void getDesdata2(){
        //! 牛顿迭代法(Newton)
        //! 牛顿法得到的是位置而不是时间  所以不好计算Func(x_k),grad_Func(x_k)
        //! 所以牛顿法不适用于计算贝塞尔曲线
        //!
        //!
        //! 矩阵方法
        int size = srcdata.size();
        QVector<int> pascaTri(size+1,0);
        pascaTri[1] = 1;
        for(int i = 1;i<=size;++i){
            int temp1 = pascaTri[0];
            int temp2 = 0;
            for(int j = 1;j<=i;++j){
                temp2 = pascaTri[j];
                pascaTri[j]=temp1+temp2;
                temp1 = temp2;
            }
        }
//        qreal precis = 5e-2;
        for(qreal t = 0;t<1.0000;t+=precis){
            QPointF resultPoint={0,0};
            QVector<qreal> bernstein1(size,1),bernstein2(size,1);

            for(int i = 1;i<=size-1;++i){
                bernstein1[i]*=bernstein1[i-1]*t;
                bernstein2[size-i-1]*=bernstein2[size-i]*(1-t);
            }
            for(int i = 0;i<size;++i){
                resultPoint+=srcdata[i]*pascaTri[i+1]*bernstein1[i]*bernstein2[i];
            }
            desdata2.append(resultPoint);
        }
    }
    void getDesdata_Resampling(){

        QPainter painter(this);
//        QPointF currPoint = desdata1.at(0);
//        qreal precis = 1e-2;
        qreal reciprocalPrecis = 1/precis;
        int i = 2;
        int count = 1;
        QVector<QPointF> richardson(4);
        richardson[0] = desdata1[0];
        richardson[1] = desdata1[1];
        richardson[2] = desdata1[3];
        richardson[3] = desdata1[4];
        //!     不对  如果我们在i-1位置插了一个新点  那么desdata中的值就变了
        //!     那么后面的值也就会变  这样的话  用理查森外推法中心误差公式就
        //!     无法计算准确的数值了   所以前两个和后两个不能按照位置来
        //!     必须在计算后就改变   而不是按照坐标来
        for(qreal t = 0;t<1.0000;t+=precis){
//            QPointF left1 = desdata3.at(i-2);
//            QPointF left2 = desdata3.at(i-1);
//            QPointF right1 = desdata3.at(i+1);
//            QPointF right2 = desdata3.at(i+2);
            /*计算currPoint和nextPoint中间点的导数值f'(x)   如果大于阈值的话要画不同的线*/
            if(i<=desdata1.size()-3){
            QPointF gradF = (-richardson[3]+8*richardson[2]-8*(richardson[1])+(richardson[0]))*reciprocalPrecis/12;
            //!     在没有插入之前就要将参与理查森外推的四个点做平移
            //!     还是不对    还是会有影响  插了一个点会影响后面好几个点
            //!     所以该怎么解决
            richardson[0] = richardson[1];
            richardson[1] = desdata1.at(i);
            richardson[2] = richardson[3];
            richardson[3] = desdata1.at(i+2);


            //!     要计算中间点的位置
            //!     采用数值积分的方法已经有了3阶的误差了
            //!     如果再用泰勒展开近似的计算是不是会把误差放大
            //!     如果我采用精度为O(h^4)的理查森外推中心误差公式，
            //!     最终得到节点附近是否需要重采样
                if(abs(gradF.x())>gradThreshold.x() || abs(gradF.y())>gradThreshold.y()){
                //!     依次往右边插值   这里就可以用泰勒公式了  二阶误差就不管了
                //!     多项式函数是一个性质很好的函数
                //!     这里的插值容易超过下一个点的坐标  这该怎么办
                //!     还是说误差不能忽略
                QPointF insertPoint = desdata1.at(i) + gradF*precis/2;
                //  因为我们插入了一个新值
                qDebug()<<i<<"\t"<<count<<"\t"<<i+count<<"\t"<<desdata3.size();
                desdata3.insert(i+count,insertPoint);
                count+=1;
                }
                ++i;
            }

        }
    }
    void diff(){
        int size = desdata1.size();
        for(int i = 0;i<size;++i){
            if(desdata1.at(i)==desdata3.at(i))
                qDebug()<<"第"<<i<<"项相同";
        }
    }

protected:
    void wheelEvent(QWheelEvent *event)override{
        double scaleFactor = 1.005;
//        zoomlevel *= event->angleDelta().y()>0?scaleFactor:1/scaleFactor;
//        zoomCenter = event->pos();
        if(event->angleDelta().y()>0){
            zoomlevel*=scaleFactor;
        }else{
            zoomlevel/=scaleFactor;
        }
        //!     这里就是告诉event参数有改变
        //!     我希望能够根据更改后的参数重绘图像
        event->accept();
        update();
    }
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            // 记录鼠标按下时的位置
            lastMousePosition = event->pos();
            isDragging = true;
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (isDragging && (event->buttons() & Qt::LeftButton)) {
            // 计算鼠标移动的差值
            QPoint delta = event->pos() - lastMousePosition;
            // 更新图像位置（这里以移动widget为例）
            this->move(x() + delta.x(), y() + delta.y());
            // 更新最后鼠标位置
            lastMousePosition = event->pos();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            isDragging = false;
        }
    }
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);

        //! 保存当前的转换矩阵
        QTransform oldTransform = painter.transform();

        //! 移动到缩放中心的负向位置，然后应用缩放
        painter.translate(-zoomCenter.x(), -zoomCenter.y());
        painter.scale(zoomlevel, zoomlevel);



        painter.scale(zoomlevel,zoomlevel);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);

        // 绘制折线图
//        setdesdata();
//        drawPoint();
        drawLineChart1(&painter);
        drawLineChart3(&painter);
        drawLineChart2(&painter);


        //! 恢复之前的转换矩阵
        painter.setTransform(oldTransform);
    }
    void resizeEvent(QResizeEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        updateChart(&painter);
//        QWidget::resizeEvent(event);
//        setdesData();
        //!  没有这句话依然会调用paintevent
        update();
    }

private:
    void updateChart(QPainter *painter){
//        QSize windowsize = this->size();
        qDebug()<<this->size()<<"minmax"<<min_Y<< "\t"<<max_Y;
//        qreal wid = windowsize.width();
//        qreal hei = windowsize.height();
        QList<QPointF>::reverse_iterator it = desdata1.rbegin();
        qreal max_X = (*it).x();
        for(QPointF &point:srcdata)
            point.setX(point.x()*this->size().width()/max_X);
        for(QPointF &point:desdata1)
            point.setX(point.x()*this->size().width()/max_X);
        for(QPointF &point:desdata2)
            point.setX(point.x()*this->size().width()/max_X);
        for(QPointF &point:desdata3)
            point.setX(point.x()*this->size().width()/max_X);
//            point.setY((point.y()+min_Y)*this->size().width()/(max_Y-min_Y));
            //!因为这里我们没有实时更新srcdata的min_Y、max_Y
            //! 所以这里的min_Y、max_Y没有实时更新  因此放缩一下就会瞬间爆炸
            //! 所以必须得把随机生成的数据用srcdata保存起来   并且在resizeevent
            //! 发送update（）以后我们同样的要重新绘制数据点   同时更新新的曲线
            //! 这样我们可以实时的更新min_Y、max_Y  从而达到自适应界面的问题

        drawLineChart1(painter);
        drawLineChart2(painter);
        drawLineChart3(painter);
    }
    void drawLineChart1(QPainter *painter) {
        if (desdata1.isEmpty()) return;

        QPen pen(Qt::blue);
        pen.setWidth(1);
        painter->setPen(pen);
//        painter->translate(0,50);
        QList<QPointF>::reverse_iterator it = desdata1.rbegin();
        qreal max_X = (*it).x();
        painter->setBrush(Qt::blue);
        for(const QPointF &point:srcdata){

            painter->drawEllipse(point,Point_Radius,Point_Radius);
        }
        painter->setBrush(Qt::NoBrush);
        for (int i = 0; i < desdata1.size() - 1; ++i) {
            QPointF start = desdata1[i];
            start.setX(start.x()*this->size().width()/max_X);
            QPointF end = desdata1[i + 1];
            end.setX(end.x()*this->size().width()/max_X);
            painter->drawLine(start, end);
            painter->drawEllipse(start,Point_Radius,Point_Radius);
        }


    }
    void drawLineChart2(QPainter *painter) {
        if (desdata2.isEmpty()) return;

        QPen pen(Qt::red);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->translate(0,10);
        QList<QPointF>::reverse_iterator it = desdata2.rbegin();
        qreal max_X = (*it).x();
        for (int i = 0; i < desdata2.size() - 1; ++i) {
            QPointF start = desdata2[i];
            start.setX(start.x()*this->size().width()/max_X);
            QPointF end = desdata2[i + 1];
            end.setX(end.x()*this->size().width()/max_X);
            painter->drawLine(start, end);
            painter->drawEllipse(start,Point_Radius,Point_Radius);
        }
    }
    void drawLineChart3(QPainter *painter) {
        if (desdata3.isEmpty()) return;


        QPen pen(Qt::black);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->translate(0,10);
        QList<QPointF>::reverse_iterator it = desdata2.rbegin();
        qreal max_X = (*it).x();
        for (int i = 0; i < desdata3.size() - 1; ++i) {
            QPointF start = desdata3[i];
            start.setX(start.x()*this->size().width()/max_X);
            QPointF end = desdata3[i + 1];
            end.setX(end.x()*this->size().width()/max_X);
            painter->drawLine(start, end);
            /*painter->setBrush(Qt::black);*/
            painter->drawEllipse(start,Point_Radius,Point_Radius);
        }
    }
    /*  我们可以用currPoint表示起始点，用nextPoint表示终点  它们就可以表示是在第k个重采样的插值区间
        我们可以利用desdata得到nextPoint，也可以在重采样之前计算nextPoint然后在重采样 但是求二阶导
        需要f(x)好像是不可以——好像也行  直接递推插值的方法插出来就好了  但是对于误差估计就不知所措了
        同时  可以画hodograph 以及曲率梳形图以便观测哪些地方是很可能进行了重采样的地方  对于不正常的
        地方 我们这只其画的直线颜色与正常的不同以示区分    */
    QList<QPointF> srcdata;
    QList<QPointF> desdata1,desdata2,desdata3; // 存储数据点
    qreal min_Y,max_Y;
    QPointF zoomCenter;
    QPointF gradThreshold={2e2,2e2};
    double zoomlevel = 1.0;
    //!     记录鼠标按下时的位置
    QPoint lastMousePosition;
    //!     标记是否在拖拽
    bool isDragging = false;
    qreal precis = 1e-2;
    int Point_Radius = 2;
};

#endif // MYWINDOW_H
