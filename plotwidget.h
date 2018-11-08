#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QVector>

#include "plotDataModel.h"

class PlotWidget : public QWidget
{
	Q_OBJECT
public:
    enum AxisStyle {LINEAR = 0, LOG = 1};

    explicit PlotWidget(QWidget *parent = 0, AxisStyle xStyle = AxisStyle::LINEAR, AxisStyle yStyle = AxisStyle::LINEAR);
        
    void setPlotTitle(QString plotTitle);
	
signals:
	
public slots:
    void plot(PlotDataModel model);
    
    void clear();
	
private:
    void paintEvent(QPaintEvent * event);

    QPoint real2pixel(double x, double y);

    QVector<PlotDataModel> models;

    double minX, maxX, minY, maxY;
    
    QString plotTitle;

    AxisStyle xStyle, yStyle;

    //double scaleX, scaleY;
    bool isoView;
    bool isInitialized;
};

#endif // PLOTWIDGET_H
