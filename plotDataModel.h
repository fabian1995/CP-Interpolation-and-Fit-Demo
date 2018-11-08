/* 
 * File:   plotDataModel.h
 * Author: fabian
 *
 * Created on 28. Oktober 2018, 10:36
 */

#ifndef PLOTDATAMODEL_H
#define PLOTDATAMODEL_H

#include <QVector>

enum PlotStyle {DOT=0, LINE=1};

class PlotDataModel {
public:
    typedef double (*BasisFunction)(double x);
    
    PlotDataModel() {}
    PlotDataModel(QVector<double> xData, QVector<double> yData, PlotStyle plotStyle, QString plotLabel, bool isoView);
    PlotDataModel(QVector<double> xData, QVector<double> yData, QVector<double> errors, PlotStyle plotStyle, QString plotLabel, bool isoView);
    PlotDataModel(BasisFunction func, double T_min, double T_max, int steps, PlotStyle plotStyle, QString plotLabel, bool isoView);
    
    QVector<double> getXData() {return this->xData;}
    QVector<double> getYData() {return this->yData;}
    QVector<double> getErrors() {return this->errors;}
    PlotStyle getPlotStyle() {return this->plotStyle;}
    QString getPlotLabel() {return this->plotLabel;}
    bool getIsoView() {return this->isoView;}
    BasisFunction getBasisFunction();
    
private:
    QVector<double> xData;
    QVector<double> yData;
    QVector<double> errors;
    PlotStyle plotStyle;
    QString plotLabel;
    bool isoView;
    BasisFunction func;
};

#endif /* PLOTDATAMODEL_H */

