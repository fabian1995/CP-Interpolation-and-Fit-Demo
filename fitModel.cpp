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

#include <QVector>

#include "fitModel.h"
#include "plotCollectionModel.h"

/**
 * Creates a Plot Collection model containing input data nodes and an
 * approximated fit function. 
 * @param name Name of this Plot Collection
 * @param intSteps Number of steps between the data nodes of the Plot Model
 * @param initialData Input Plot Model
 * @param func Fit model function
 * @param gradient Symbolic partial derivatives of fit model function for each parameter
 * @param params Vector of parameters for the fit model function
 * @param imagePath Path to an image of the equation defining the input data (optional)
 */
FitModel::FitModel(QString name, int intSteps, PlotDataModel* initialData, Fit::FitFunction func, QVector<Fit::FitFunction> gradient, QVector<double> params, QString imagePath) : PlotCollectionModel(name, imagePath, QString ("Model function: ")) {
    this->plotModels.append(initialData);
    
    Fit* fit = new Fit(initialData->getXData(), initialData->getYData(), initialData->getErrors(), func, gradient, params);
    
    const int steps = initialData->getXData().size() * intSteps;
    const double T_min = initialData->getXData()[0];
    const double T_max = initialData->getXData()[initialData->getXData().size()-1];
    
    QVector<double> xValues(steps);
    QVector<double> yValFunc(steps);
    QVector<double> yValFunc2(steps);
    for (int i = 0; i < steps; i++) {
        xValues[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
        yValFunc[i] = func(xValues[i], params);
        yValFunc2[i] = func(xValues[i], fit->params.last());
    }
    
    this->plotModels.append(new PlotDataModel(xValues, yValFunc, LINE, QString("Initial guess"), false));
    this->plotModels.append(new PlotDataModel(xValues, yValFunc2, LINE, QString("Fit function"), false));
}