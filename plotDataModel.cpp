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

#include "plotDataModel.h"

/**
 * Model containing all information about <i>one</i> function graph or data node
 * plot in the PlotWidget.
 * @param xData X values of input data nodes.
 * @param yData Y values of input data nodes.
 * @param errors Error values of input data nodes (optional).
 * @param plotStyle Plot style (DOT or LINE).
 * @param plotLabel Display name of this graph.
 * @param isoView
 */
PlotDataModel::PlotDataModel(QVector<double> xData, QVector<double> yData, QVector<double> errors, PlotStyle plotStyle, QString plotLabel, bool isoView) {
    this->xData = xData;
    this->yData = yData;
    this->errors = errors;
    this->plotStyle = plotStyle;
    this->plotLabel = plotLabel;
    this->isoView = isoView;
    this->func = nullptr;
}

/**
 * Model containing all information about <i>one</i> function graph or data node
 * plot in the PlotWidget.
 * @param xData X values of input data nodes.
 * @param yData Y values of input data nodes.
 * @param plotStyle Plot style (DOT or LINE).
 * @param plotLabel Display name of this graph.
 * @param isoView
 */
PlotDataModel::PlotDataModel(QVector<double> xData, QVector<double> yData, PlotStyle plotStyle, QString plotLabel, bool isoView) : PlotDataModel(xData, yData, QVector<double>(), plotStyle, plotLabel, isoView) {}

/**
 * Model containing all information about <i>one</i> function graph or data node
 * plot in the PlotWidget. This constructor generates the input data from a
 * function passed as parameter.
 * @param func Function that is used for generating input data nodes.
 * @param T_min Start of input data interval
 * @param T_max End of input data interval.
 * @param steps Number of steps (data nodes) in the input data interval.
 * @param plotStyle Plot style (DOT or LINE).
 * @param plotLabel Display name of this graph.
 * @param isoView
 */
PlotDataModel::PlotDataModel(PlotDataModel::BasisFunction func, double T_min, double T_max, int steps, PlotStyle plotStyle, QString plotLabel, bool isoView) {
    this->xData = QVector<double>(steps);
    this->yData = QVector<double>(steps);
    this->plotStyle = plotStyle;
    this->plotLabel = plotLabel;
    this->isoView = isoView;
    this->func = func;
    
    for(int i=0; i<steps; i++) {
        xData[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
        yData[i] = func(xData[i]);
    }
}