/* 
 * File:   plotDataModel.h
 * Author: fabian
 *
 * Created on 28. Oktober 2018, 10:36
 */

#ifndef PLOTDATAMODEL_H
#define PLOTDATAMODEL_H

#include <qt5/QtCore/qvector.h>

enum PlotStyle {DOT=0, LINE=1};

class PlotDataModel {
public:
    PlotDataModel(QVector<double> xData, QVector<double> yData, PlotStyle plotStyle, QString plotLabel, bool isoView);
    PlotDataModel(double (*func)(double), double T_min, double T_max, int steps, PlotStyle plotStyle, QString plotLabel, bool isoView);
    
    QVector<double> getXData() {return this->xData;}
    QVector<double> getYData() {return this->yData;}
    PlotStyle getPlotStyle() {return this->plotStyle;}
    QString getPlotLabel() {return this->plotLabel;}
    bool getIsoView() {return this->isoView;}
    
private:
    QVector<double> xData;
    QVector<double> yData;
    PlotStyle plotStyle;
    QString plotLabel;
    bool isoView;
};

#endif /* PLOTDATAMODEL_H */

