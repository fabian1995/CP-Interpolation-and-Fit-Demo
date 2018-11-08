#include <QPainter>
#include <cmath>
#include "misc.h"
#include <iostream>

#include "plotwidget.h"
#include "plotDataModel.h"

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
    isInitialized = false;
}

void PlotWidget::setPlotTitle(QString plotTitle) {
    this->plotTitle = plotTitle;
}


void PlotWidget::plot(PlotDataModel model)
{
    
    // check sizes
    if(model.getXData().size() != model.getYData().size())
    {
            return;
    }
    int n=model.getXData().size();

    isInitialized = true;

    // copy data
    /*xDatas.append(xData);
    yDatas.append(yData);
    plotStyles.append(plotStyle);
    labels.append(label);*/
    this->models.append(model);

    // check for isoView
    if(model.getIsoView())
    {
        this->isoView=true;
    }

    // find limits
    for(int i=0; i<n; i++)
    {
        if(model.getXData()[i]<minX)
        {
            minX=model.getXData()[i];
        }
        if(model.getXData()[i]>maxX)
        {
            maxX=model.getXData()[i];
        }
        if(model.getYData()[i]<minY)
        {
            minY=model.getYData()[i];
        }
        if(model.getYData()[i]>maxY)
        {
            maxY=model.getYData()[i];
        }
    }

    show();
    update();
}

void PlotWidget::clear()
{
    minX=minY=qInf();
    maxX=maxY=-qInf();
    isInitialized = false;
    isoView=false;

    /*xDatas.clear();
    yDatas.clear();
    plotStyles.clear();
    labels.clear();*/
    models.clear();

    update();
}


void PlotWidget::paintEvent(QPaintEvent * /*event*/)
{
    if (!isInitialized) {
        return;
    }
    
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;

    // background
    p.fillRect(this->rect(), BACK_COLOR);
    
    QFont stdFont = p.font();
    QFont headerFont = p.font();
    headerFont.setPointSize ( 22 );
    
    // Title
    if (this->plotTitle != nullptr) {
        //pen.setColor(QColor(0, 0, 0));
        p.setFont(headerFont);
        int x = width() / 2 - this->plotTitle.length() * 7;
        p.drawText(QPoint(x, 32), this->plotTitle);
    }
    
    p.setFont(stdFont);

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
    int hueStep=360/models.size();
    int legendStep=width()/models.size();

    for(int i=0; i<models.size(); i++)
    {
        // set color
        QColor color=QColor::fromHsv((240+i*hueStep)%360, 255, 200);
        pen.setColor(color);
        p.setPen(pen);

        // generate data points
        QVector<QPoint> points;
        QVector<QLine> errorLines;
        for(int j=0; j<models[i].getXData().size(); j++)
        {
            if (!std::isnan(models[i].getYData()[j])) {
                double x = models[i].getXData()[j], y = models[i].getYData()[j];
                points.append(real2pixel(x, y));
                if (models[i].getErrors().size() > 0) {
                    double err = models[i].getErrors()[j];
                    errorLines.append(QLine(real2pixel(x, y-err), real2pixel(x, y+err)));
                    errorLines.append(QLine(real2pixel(x-0.25*err, y-err), real2pixel(x+0.25*err, y-err)));
                    errorLines.append(QLine(real2pixel(x-0.25*err, y+err), real2pixel(x+0.25*err, y+err)));
                }
            }
        }

        // print legend label
        const int legendY = 60;
        
        if(!models[i].getPlotLabel().isEmpty())
            p.drawText(50+i*legendStep, legendY, models[i].getPlotLabel());

        switch(models[i].getPlotStyle())
        {
            case DOT:
            {
                pen.setCapStyle(Qt::RoundCap);
                pen.setWidth(8);
                p.setPen(pen);
                p.drawPoints(QPolygon(points));
                
                pen.setWidth(1);
                pen.setStyle(Qt::SolidLine);
                p.setPen(pen);
                p.drawLines(errorLines);

                if(!models[i].getPlotLabel().isEmpty())	// legend
                    p.drawPoint(20+i*legendStep, legendY-5);
                break;
            }
            case LINE:
            {
                pen.setWidth(2);
                pen.setStyle(Qt::SolidLine);
                p.setPen(pen);
                p.drawPolyline(QPolygon(points));

                if(!models[i].getPlotLabel().isEmpty())	// legend
                    p.drawLine(20+i*legendStep, legendY-5, 40+i*legendStep, legendY-5);
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
