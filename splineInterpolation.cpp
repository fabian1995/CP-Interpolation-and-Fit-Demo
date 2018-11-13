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

#include <iostream>

#include "splineInterpolation.h"
#include "utils.h"

using namespace std;

/**
 * Calculates Spline interpolation for a given set of data nodes
 * @param x X values of data nodes
 * @param input Y values of data nodes
 * @param lDeriv First derivative of spline at left boundary
 * @param rDeriv First derivative of spline at right boundary
 */
SplineInterpolation::SplineInterpolation(QVector<double> x, QVector<double> input, double lDeriv, double rDeriv) {
    this->x = x;
    this->input = input;
    this->lDeriv = lDeriv;
    this->rDeriv = rDeriv;
    this->size = input.size();
    
    this->h = QVector<double>();
    
    for (int i = 1; i < size; i++) {
        this->h.append(x[i]-x[i-1]);
    }
    
    this->calculateSplineCoefficients();
}

/**
 * Calculates the Spline interpolation coefficients a, b and c. The coefficients
 * d are equal to the y values of the data nodes, therfore d[i] = f[i] does not
 * need to be calculated.
 */
void SplineInterpolation::calculateSplineCoefficients() {
    QVector<double> f(size);
    QVector<double> diag(size);
    
    // Initialize first and last elements of main diagonal and right side (f vector)
    f[0] = 6 * ((input.at(1) - input.at(0)) / h[0] - lDeriv);
    f[size-1] = 6 * (rDeriv - ((input.at(size-1) - input.at(size-2)) / h[size-2]));
    diag[0] = 2*h[0];
    diag[size-1] = 2*h[size-2];
    
    // Initialize remaining elements of main diagonal and right side (f vector)
    for (int i = 1; i < size-1; i++) {
        f[i] = 6 * ((input.at(i+1) - input.at(i)) / h[i] - (input.at(i) - input.at(i-1)) / h[i-1]);
        diag[i] = 2 * (h[i-1] + h[i]);
    }
    
    // Solve the equation created above
    this->fss = triSolve(h, diag, h, f);
    
    this->coeffA = QVector<double>();
    this->coeffB = QVector<double>();
    this->coeffC = QVector<double>();
    
    // Calculate Spline coefficients
    for(int i = 0; i < size-1; i++) {
        this->coeffA.append((fss[i+1]-fss[i])/(6*h[i]));
        this->coeffB.append(fss[i]/2);
        this->coeffC.append((input[i+1]-input[i])/h[i] - h[i]/6 * (fss[i+1]+2*fss[i]));
    }
}

/**
 * Get the function value of the Spline for a specific x value.
 * @param xValue Input value
 * @return Value of the Spline at x.
 */
double SplineInterpolation::splineInterpolate(double xValue) {
    // Find required interval: Binary search
    int index = lowerBoundsBinarySearch(xValue, x);
    
    // Calculate function value
    double result = input[index];
    double helper = xValue - x[index];
    result += helper * coeffC[index];
    helper *= xValue - x[index];
    result += helper * coeffB[index];
    helper *= xValue - x[index];
    result += helper * coeffA[index];
    
    return result;
}