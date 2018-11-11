#include <iostream>

#include "splineInterpolation.h"
#include "utils.h"

using namespace std;

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

void SplineInterpolation::calculateSplineCoefficients() {
    QVector<double> f(size);
    QVector<double> diag(size);
    
    f[0] = 6 * ((input.at(1) - input.at(0)) / h[0] - lDeriv);
    f[size-1] = 6 * (rDeriv - ((input.at(size-1) - input.at(size-2)) / h[size-2]));
    diag[0] = 2*h[0];
    diag[size-1] = 2*h[size-2];
    
    for (int i = 1; i < size-1; i++) {
        f[i] = 6 * ((input.at(i+1) - input.at(i)) / h[i] - (input.at(i) - input.at(i-1)) / h[i-1]);
        diag[i] = 2 * (h[i-1] + h[i]);
    }
    
    //this->triSolve(diag, f);
    this->fss = triSolve(h, diag, h, f);
    
    this->coeffA = QVector<double>();
    this->coeffB = QVector<double>();
    this->coeffC = QVector<double>();
    
    for(int i = 0; i < size-1; i++) {
        this->coeffA.append((fss[i+1]-fss[i])/(6*h[i]));
        this->coeffB.append(fss[i]/2);
        this->coeffC.append((input[i+1]-input[i])/h[i] - h[i]/6 * (fss[i+1]+2*fss[i]));
    }
}

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