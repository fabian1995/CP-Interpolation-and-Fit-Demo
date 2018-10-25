#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QVector>

class PlotWidget : public QWidget
{
	Q_OBJECT
public:
        enum AxisStyle {LINEAR = 0, LOG = 1};
    
	explicit PlotWidget(QWidget *parent = 0, AxisStyle xStyle = AxisStyle::LINEAR, AxisStyle yStyle = AxisStyle::LINEAR);
	
	enum PlotStyle {DOT=0, LINE=1};
        
	
signals:
	
public slots:
	void plot(QVector<double> xData, QVector<double> yData, PlotStyle plotStyle, QString label=QString(), bool isoView=false);
	void clear();
	
private:
	void paintEvent(QPaintEvent * event);
	
	QPoint real2pixel(double x, double y);
	
	QVector<QVector<double>> xDatas;
	QVector<QVector<double>> yDatas;
	QVector<PlotStyle> plotStyles;
	QVector<QString> labels;
	
	double minX, maxX, minY, maxY;
        
        AxisStyle xStyle, yStyle;
	
	//double scaleX, scaleY;
	bool isoView;
	
};

#endif // PLOTWIDGET_H
