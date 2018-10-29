/* 
 * File:   plotWrapper.h
 * Author: fabian
 *
 * Created on 28. Oktober 2018, 11:01
 */

#ifndef PLOTWRAPPER_H
#define PLOTWRAPPER_H

#include <QComboBox>

#include "plotDataModel.h"
#include "plotwidget.h"
#include "interpolationModel.h"


class PlotWrapper : public QObject {
    Q_OBJECT
public:
    PlotWrapper(PlotWidget* functionPlot, PlotWidget* errorPlot, QComboBox* selector);
    
    void addDataModel(InterpolationModel* model);
    
    void clear();
    
    InterpolationModel* getCurrentDataModel();

public slots:
    void plot(QString name);
    
private:
    PlotWidget* functionPlot;
    PlotWidget* errorPlot;
    QComboBox* selector;
    QVector<InterpolationModel*> dataCollections;
    int currentIndex;
};

#endif /* PLOTWRAPPER_H */

