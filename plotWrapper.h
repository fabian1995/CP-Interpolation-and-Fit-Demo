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


class PlotWrapper : public QObject {
    Q_OBJECT
public:
    PlotWrapper(PlotWidget* plotWidget, QComboBox* selector);
    
    void addDataModel(PlotDataModel* model);
    
    void clear();

public slots:
    void plot(QString name);
    
private:
    PlotWidget* plotWidget;
    QComboBox* selector;
    QVector<PlotDataModel*> dataModels;
};

#endif /* PLOTWRAPPER_H */

