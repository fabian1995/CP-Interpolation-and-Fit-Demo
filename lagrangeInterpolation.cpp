/* 
 * File:   langrangeInterpolation.cpp
 * Author: fabian
 *
 * Created on 25. Oktober 2018, 11:04
 */

#include "lagrangeInterpolation.h"

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

double LagrInterpolate::polynomial(double x) {
    
    double result = 0;
    
    for (int i = 0; i < this->xValues.size(); i++) {
        result += this->fValues[i] * this->LagrPol(x,i);
    }
    
    return result;
}

double LagrInterpolate::LagrPol(double x, int index) {
    
    double result = this->denominators[index];
    
    for (int i = 0; i < this->xValues.size(); i++) {
        if (i == index)
            continue;
        
        result *= (x-this->xValues[i]);
    }
    
    return result;
}

