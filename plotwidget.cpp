#include "plotwidget.h"
#include <QPainter>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QPaintEvent>

#define POINT_SIZE 1000;    /*用1000个点绘制B样条曲线*/
#define POINT_RADIUS 5;     /*点的大小*/


PlotWidget::PlotWidget(QWidget *parent,QVector<QPointF> pointindex) : QWidget(parent)
{
    paintWidget = parent;
    PointIndex=pointindex;

}
void PlotWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
//        painter.begin(this);
    painter.setBrush(Qt::blue);
    painter.drawRect(rect());

    // 简单绘制一条正弦曲线示例
    const int points = 100;
    QPointF lastPoint;
    for (int i = 0; i < points; ++i) {
        double x = width() * (i / (points - 1.0));
        double y = height() / 2 + 50 * sin(i * (2 * M_PI / points));
        QPointF currentPoint(x, y);
        if (i > 0) {
            painter.drawLine(lastPoint, currentPoint);
        }
        lastPoint = currentPoint;
    }
//        painter.end();
}
