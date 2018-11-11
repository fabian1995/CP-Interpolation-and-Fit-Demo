/* 
 * File:   langrangeInterpolation.cpp
 * Author: fabian
 *
 * Created on 25. Oktober 2018, 11:04
 */

#include "lagrangeInterpolation.h"

/**
 * Calculates the Lagrangian Polynomaials for a given set of data nodes.
 * @param xValues X values of the data nodes.
 * @param fValues Y Values of the data nodes.
 */
LagrInterpolate::LagrInterpolate(QVector<double> xValues, QVector<double> fValues) {
    this->xValues = xValues;
    this->fValues = fValues;
    
    this->denominators = QVector<double>();
    
    for (int i = 0; i < xValues.size(); i++) {
        double helper = 1;
        for (int j = 0; j < xValues.size(); j++) {
            if (i == j)
                continue;
            helper /= this->xValues[i] - this->xValues[j];
        }
        this->denominators.append(helper);
    }
}

/**
 * Calculates the value of the Lagrangian interpolation function for a specific
 * x value.
 * @param x Input calue
 * @return  Corresponding interpolation function value.
 */
double LagrInterpolate::interpolate(double x) {
    
    double result = 0;
    
    for (int i = 0; i < this->xValues.size(); i++) {
        result += this->fValues[i] * this->LagrPol(x,i);
    }
    
    return result;
}

/**
 * The Lagrangian Polynomial L(n) itself.
 * @param x Input value on x axis
 * @param index Index of the Lagrangian Polynomial
 * @return Value of Lagrangian Polynomial with index i at point x.
 */
double LagrInterpolate::LagrPol(double x, int index) {
    
    double result = this->denominators[index];
    
    for (int i = 0; i < this->xValues.size(); i++) {
        if (i == index)
            continue;
        
        result *= (x-this->xValues[i]);
    }
    
    return result;
}

