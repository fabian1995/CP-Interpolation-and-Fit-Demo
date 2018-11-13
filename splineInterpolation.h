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

#ifndef SPLINE_H
#define SPLINE_H

#include <QVector>


class SplineInterpolation {
public:
    SplineInterpolation(QVector<double> x, QVector<double> input, double lDeriv, double rDeriv);
    
    double splineInterpolate(double xValue);
    
private:
    QVector<double> fss;
    QVector<double> input;
    QVector<double> x;
    QVector<double> coeffA;
    QVector<double> coeffB;
    QVector<double> coeffC;
    //QVector<double>* coeffD; coefficient d is equal to input data
    double lDeriv;
    double rDeriv;
    int size;
    
    QVector<double> h;
    
    void calculateSplineCoefficients();
    
};

#endif /* SPLINE_H */

