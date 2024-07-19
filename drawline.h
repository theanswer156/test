#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QWidget>
#include <QPainter>

#include <QList>

#include <QObject>
#include <QEvent>
#include <QDebug>
#include <QRandomGenerator>
#include <QtMath>

class LineChartWidget : public QWidget {
    Q_OBJECT

public:
    explicit LineChartWidget(QWidget *parent = nullptr) : QWidget(parent) {

    }


    void drawPoint(QList<QPointF> &srcdata){


        QPainter painter(this);
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
    void getDesdata1(QList<QPointF> &srcdata){


        for(qreal t = 0;t < 1.0000; t+=2*precis){
            int size = srcdata.size();
            QVector<qreal> coefficient(size, 0);
            coefficient[0] = 1.000;
            qreal u1 = 1.0 - t;
            //!这里就是递推计算

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
    void getDesdata2(QList<QPointF> &srcdata){
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
        painter.setPen(Qt::red);

        qreal reciprocalPrecis = 1/precis;
        int i = 2;
        int count = 1;
        QVector<QPointF> richardson(4);
        //!     不对  如果我们在i-1位置插了一个新点  那么desdata中的值就变了
        //!     那么后面的值也就会变  这样的话  用理查森外推法中心误差公式就
        //!     无法计算准确的数值了   所以前两个和后两个不能按照位置来
        //!     必须在计算后就改变   而不是按照坐标来
        for(qreal t = 0;t<1.0000;t+=precis){
            richardson[0] = desdata3.at(i-2);
            richardson[1] = desdata3.at(i-1);
            richardson[2] = desdata3.at(i+1);
            richardson[3] = desdata3.at(i+2);
            /*计算currPoint和nextPoint中间点的导数值f'(x)   如果大于阈值的话要画不同的线*/
            if(i<=desdata1.size()-3){
            QPointF gradF = (-richardson[3]+8*richardson[2]-8*(richardson[1])+(richardson[0]))*reciprocalPrecis/12;
            painter.drawLine(desdata1[i],(desdata1[i]+gradF));
            QPointF ggradF = (richardson[1]+richardson[2]-2*desdata1[i])*reciprocalPrecis*reciprocalPrecis;
            qreal curvate = qPow(qPow(gradF.x()*ggradF.y(),2)+qPow(gradF.y()*ggradF.x(),2),0.5)/qPow(gradF.x()*gradF.x()+gradF.y()*gradF.y(),0.75);
            QPointF insertPoint = desdata1.at(i) + gradF*precis/2 +ggradF*precis*precis/8;
            qreal dis1 = qPow((insertPoint.x()-desdata1.at(i).x()),2)+qPow((insertPoint.y()-desdata1.at(i).y()),2);
            qreal dis2 = qPow((insertPoint.x()-desdata1.at(i+1).x()),2)+qPow((insertPoint.y()-desdata1.at(i+1).y()),2);
            //!     把距离两点较近的新点给过滤掉  这样同时能够减少出现超出
            //!     左右两点范围的新点插入
            //!     不把相差较远的点过滤掉会出现超出旁边两点太多  图像出现紊乱
            //!     不过我们可以利用插入点和旁边两点的向量点乘来度量插入点的偏离程度
            //!     偏离程度太大的就都过滤掉
            if(dis1/dis2<1+ratio && dis1/dis2>1-ratio)
            {
                if(abs(gradF.x())>gradThreshold.x() || abs(gradF.y())>gradThreshold.y() || curvate>curvate_threshold){
                //!     依次往右边插值   这里就可以用泰勒公式了

                qDebug()<<i<<"\t"<<count<<"\t"<<i+count<<"\t"<<desdata3.size();
                desdata3.insert(i+count,insertPoint);
                count+=1;
                }
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
        double scaleFactor = 1.01;

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

        //!  没有这句话依然会调用paintevent
//        update();
    }

private:
    void updateChart(QPainter *painter){
        qDebug()<<this->size()<<"minmax"<<min_Y<< "\t"<<max_Y<<95;
        if(srcdata.isEmpty())
            return;
        //!     这里除了问题
        min_X = desdata1.at(0).x();
//        painter->translate(min_X,0);
        QList<QPointF>::reverse_iterator it = desdata1.rbegin();
        qreal max_X = (*it).x();
//        for(QPointF &point:srcdata)
//            point.setX(point.x()*this->size().width()/max_X);
        for(QPointF &point:desdata1)
            point.setX(point.x()*this->size().width()/max_X);
        for(QPointF &point:desdata2)
            point.setX(point.x()*this->size().width()/max_X);
        for(QPointF &point:desdata3)
            point.setX(point.x()*this->size().width()/max_X);


//        drawLineChart1(painter);
//        drawLineChart2(painter);
//        drawLineChart3(painter);
    }
    void drawLineChart1(QPainter *painter) {
        if (desdata1.isEmpty()) return;

        QPen pen(Qt::blue);
        pen.setWidth(1);
        painter->setPen(pen);
//        painter->translate(0,50);
        QList<QPointF>::reverse_iterator it = desdata1.rbegin();
        qreal max_X = (*it).x();

        painter->setBrush(Qt::NoBrush);
        for (int i = 0; i < desdata1.size() - 1; ++i) {
            QPointF start = desdata1[i];
            start.setX((start.x())*this->size().width()/max_X);
            QPointF end = desdata1[i + 1];
            end.setX((end.x())*this->size().width()/max_X);
            painter->drawLine(start, end);
            painter->drawEllipse(start,Point_Radius,Point_Radius);
        }


    }
    void drawLineChart2(QPainter *painter) {
        if (desdata2.isEmpty()) return;

        QPen pen(Qt::red);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->translate(0,20);
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
        painter->translate(0,20);
        QList<QPointF>::reverse_iterator it = desdata2.rbegin();
        qreal max_X = (*it).x();
        for (int i = 0; i < desdata3.size() - 1; ++i) {
            QPointF start = desdata3[i];
            start.setX(start.x()*this->size().width()/max_X);
            QPointF end = desdata3[i + 1];
            end.setX(end.x()*this->size().width()/max_X);
            painter->drawLine(start, end);

            painter->drawEllipse(start,Point_Radius,Point_Radius);
        }
    }
    /*  我们可以用currPoint表示起始点，用nextPoint表示终点  它们就可以表示是在第k个重采样的插值区间
        我们可以利用desdata得到nextPoint，也可以在重采样之前计算nextPoint然后在重采样 但是求二阶导
        需要f(x)好像是不可以——好像也行  直接递推插值的方法插出来就好了  但是对于误差估计就不知所措了
        同时  可以画hodograph 以及曲率梳形图以便观测哪些地方是很可能进行了重采样的地方  对于不正常的
        地方 我们这只其画的直线颜色与正常的不同以示区分    */

    /*不需要原始数据点   从左上布局中的控件获取初始值*/

    QList<QPointF> srcdata;//   存储原始数据点
    QList<QPointF> desdata1,desdata2,desdata3; // 存储数据点
    qreal min_Y,max_Y;
    qreal min_X;
    QPointF zoomCenter;
    QPointF gradThreshold={2e2,2e2};
    double zoomlevel = 1.0;
    //!     记录鼠标按下时的位置
    QPoint lastMousePosition;
    //!     标记是否在拖拽
    bool isDragging = false;
    qreal ratio = 9e-1;
    qreal precis = 2e-2;
    qreal curvate_threshold = 1e2;
    int Point_Radius = 3;
};

#endif
// MYWINDOW_H
