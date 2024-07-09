#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QVector>
#include <QPoint>
#include <QtMath>


class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *paintEvent,QList<QVector<int>> PointIndex){
        QPainter painter(this);
//        painter.begin(this);
        painter.setBrush(Qt::white);
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
signals:

public slots:

};

#endif // PLOTWIDGET_H
