#include "plotwidget.h"

#include <QPainter>
#include <cmath>
#include "misc.h"
#include "plotDataModel.h"
#include <iostream>

#define BACK_COLOR QColor(255, 255, 255)			// white
#define AXIS_COLOR QColor(25, 25, 25)
#define GRID_COLOR QColor(191, 191, 191)			// light gray

#define BORDER	80									// border in pixels


PlotWidget::PlotWidget(QWidget *parent, AxisStyle xStyle, AxisStyle yStyle) : QWidget(parent)
{
	minX=minY=qInf();
	maxX=maxY=-qInf();
        this->xStyle = xStyle;
        this->yStyle = yStyle;
	isoView=false;
}


void PlotWidget::plot(PlotDataModel model) {
    this->plot(model.getXData(), model.getYData(), model.getPlotStyle(), model.getPlotLabel(), model.getIsoView());
}


void PlotWidget::plot(QVector<double> xData, QVector<double> yData, PlotStyle plotStyle, QString label, bool isoView)
{
	// check sizes
	if(xData.size() != yData.size())
	{
		return;
	}
	int n=xData.size();
	
	// copy data
	xDatas.append(xData);
	yDatas.append(yData);
	plotStyles.append(plotStyle);
	labels.append(label);
	
	// check for isoView
	if(isoView)
	{
		this->isoView=true;
	}
	
	// find limits
	for(int i=0; i<n; i++)
	{
		if(xData[i]<minX)
		{
			minX=xData[i];
		}
		if(xData[i]>maxX)
		{
			maxX=xData[i];
		}
		if(yData[i]<minY)
		{
			minY=yData[i];
		}
		if(yData[i]>maxY)
		{
			maxY=yData[i];
		}
	}
	
	show();
	update();
}

void PlotWidget::clear()
{
	minX=minY=qInf();
	maxX=maxY=-qInf();
	isoView=false;
	
	xDatas.clear();
	yDatas.clear();
	plotStyles.clear();
	labels.clear();
	
	update();
}


void PlotWidget::paintEvent(QPaintEvent * /*event*/)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	QPen pen;
	
	// background
	p.fillRect(this->rect(), BACK_COLOR);
	
	// y-grid
	pen.setColor(GRID_COLOR);
	pen.setWidth(1);
	
	QVector<double> yGrid=findBeautifulGrid(minY, maxY, yStyle);
	foreach(double tic, yGrid)
	{
		// make 0 line solid
		if(tic==0)
		{
			pen.setStyle(Qt::SolidLine);
                        pen.setColor(AXIS_COLOR);
			p.setPen(pen);
		}
		else
		{
			pen.setStyle(Qt::DashLine);
                        pen.setColor(GRID_COLOR);
			p.setPen(pen);
		}
		
		// draw line
		p.drawLine(real2pixel(minX, tic), real2pixel(maxX, tic));
		
		// label
		p.drawText(real2pixel(minX, tic)+QPoint(-BORDER+5, +5), sciPrint(tic));
	}
	
	// x-grid
	QVector<double> xGrid=findBeautifulGrid(minX, maxX, xStyle);
	foreach(double tic, xGrid)
	{
		// make 0 line solid
		if(tic==0)
		{
			pen.setStyle(Qt::SolidLine);
                        pen.setColor(AXIS_COLOR);
			p.setPen(pen);
		}
		else
		{
			pen.setStyle(Qt::DashLine);
                        pen.setColor(GRID_COLOR);
			p.setPen(pen);
		}
		
		// draw line
		p.drawLine(real2pixel(tic, minY), real2pixel(tic, maxY));
		
		// label
		p.save();
		p.translate(real2pixel(tic, minY));  
		p.rotate(-90);
		p.drawText(QPoint(-BORDER+5, +5), sciPrint(tic));
		p.restore();
	}
	
	
	// data traces
	int hueStep=360/xDatas.size();
	int legendStep=width()/xDatas.size();
	
	for(int i=0; i<xDatas.size(); i++)
	{
		// set color
		QColor color=QColor::fromHsv((240+i*hueStep)%360, 255, 200);
		pen.setColor(color);
		p.setPen(pen);
		
		// generate data points
		QVector<QPoint> points;
		for(int j=0; j<xDatas[i].size(); j++)
		{
                    if (!std::isnan(yDatas[i][j]))
			points.append(real2pixel(xDatas[i][j], yDatas[i][j]));
		}
		
		// print legend label
		if(!labels[i].isEmpty())
			p.drawText(50+i*legendStep, 20, labels[i]);
		
		switch(plotStyles[i])
		{
			case DOT:
			{
				pen.setCapStyle(Qt::RoundCap);
				pen.setWidth(10);
				p.setPen(pen);
				p.drawPoints(QPolygon(points));
				
				if(!labels[i].isEmpty())	// legend
					p.drawPoint(20+i*legendStep, 20);
				break;
			}
			case LINE:
			{
				pen.setWidth(2);
				pen.setStyle(Qt::SolidLine);
				p.setPen(pen);
				p.drawPolyline(QPolygon(points));
				
				if(!labels[i].isEmpty())	// legend
					p.drawLine(20+i*legendStep, 20, 40+i*legendStep, 20);
			}
		}
	}
}


QPoint PlotWidget::real2pixel(double x, double y)
{
	// find scaling
	double scaleX, scaleY;
        
        if (xStyle == AxisStyle::LOG) {
            std::cout << "Transform x: " << x;
            x = log10(x)*500;
            std::cout << " -> " << x << std::endl;
        }
        
        if (yStyle == AxisStyle::LOG)
            y = pow(10,y);
	
	if(minX==maxX)
	{
		scaleX=1;
	}
	else
	{
		scaleX=(width()-2*BORDER)/(maxX-minX);
	}
	
	if(minY==maxY)
	{
		scaleY=1;
	}
	else
	{
		scaleY=(height()-2*BORDER)/(maxY-minY);
	}
	
	if(isoView)
	{
		scaleX=std::min(scaleX, scaleY);
		scaleY=scaleX;
	}
	
        double xCoord = (x - (maxX+minX)/2)*scaleX + width()/2;
        double yCoord = ((maxY+minY)/2 - y)*scaleY + height()/2;
        
	return QPoint(xCoord, yCoord);
}
