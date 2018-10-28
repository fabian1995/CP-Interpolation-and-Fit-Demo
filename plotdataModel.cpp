#include "plotDataModel.h"

PlotDataModel::PlotDataModel(QVector<double> xData, QVector<double> yData, PlotStyle plotStyle, QString plotLabel, bool isoView) {
    this->xData = xData;
    this->yData = yData;
    this->plotStyle = plotStyle;
    this->plotLabel = plotLabel;
    this->isoView = isoView;
}

PlotDataModel::PlotDataModel(double (*func)(double), double T_min, double T_max, int steps, PlotStyle plotStyle, QString plotLabel, bool isoView) {
    this->xData = QVector<double>(steps);
    this->yData = QVector<double>(steps);
    this->plotStyle = plotStyle;
    this->plotLabel = plotLabel;
    this->isoView = isoView;
    
    for(int i=0; i<steps; i++) {
        xData[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
        yData[i] = func(xData[i]);
    }
}