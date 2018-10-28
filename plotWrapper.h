/* 
 * File:   plotWrapper.h
 * Author: fabian
 *
 * Created on 28. Oktober 2018, 11:01
 */

#ifndef PLOTWRAPPER_H
#define PLOTWRAPPER_H

#include "plotDataModel.h"
#include "plotwidget.h"


class PlotWrapper {
public:
    PlotWrapper(PlotWidget* plotWidget);
    
    void addDataModel(PlotDataModel* model);
    
    void plot();
    
    void clear();
    
private:
    PlotWidget* plotWidget;
    QVector<PlotDataModel*> dataModels;
};

#endif /* PLOTWRAPPER_H */

