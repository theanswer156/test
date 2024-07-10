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
    explicit PlotWidget(QWidget *parent ,QVector<QPointF> PointIndex);
protected:
    void paintEvent(QPaintEvent *event) override;




signals:

public slots:


private:
    QVector<QPointF> PointIndex;
    QWidget *paintWidget;
};

#endif // PLOTWIDGET_H
