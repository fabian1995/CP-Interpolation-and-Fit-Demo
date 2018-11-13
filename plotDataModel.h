/*
 * CP Interpolation & Fit Demo
 * Copyright (C) 2018 Fabian Hummer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PLOTDATAMODEL_H
#define PLOTDATAMODEL_H

#include <QVector>

/**
 * Plot Style of one specific graph. May be DOT (plot single data nodes) or
 * LINE (paint lines between data nodes).
 */
enum PlotStyle {DOT=0, LINE=1};

/**
 * Model containing all information about <i>one</i> function graph or data node
 * plot in the PlotWidget.
 * @see PlotWidget
 */
class PlotDataModel {
public:
    typedef double (*BasisFunction)(double x);
    
    /** 
     * Default constructor. Required so that PlotDataModels can be stored in a
     * QVector. <b>This default constructor should not be used!</b>
     */
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
    BasisFunction getBasisFunction() {return this->func;}
    
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

