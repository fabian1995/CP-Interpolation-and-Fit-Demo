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

#ifndef FIT_H
#define FIT_H

#include <qt5/QtCore/qvector.h>
#include <functional>
#include <utility>


class Fit {
public:
    typedef double (*FitFunction)(double x, QVector<double> params);
    using ParamFunction = std::function<double(QVector<double>)>;
    
    Fit(QVector<double> x, QVector<double> f, QVector<double> errors, FitFunction func, QVector<Fit::FitFunction> gradient, QVector<double> p0);
    
    double getSquareError();
    QVector<double> linearRegression();
    
    QVector<QVector<double>> params;
    
private:
    QVector<double> xValues;
    QVector<double> fValues;
    QVector<double> errors;
    FitFunction func;
    QVector<Fit::FitFunction> gradient;
    QVector<Fit::ParamFunction> paramFunc;
    
    void calculateFit();
    QVector<double> applyFunctions(QVector<ParamFunction>, QVector<double> params);
    QVector<QVector<double>> jacobiMatrix(QVector<Fit::ParamFunction> f, QVector<double> params);
};

#endif /* FIT_H */

