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
    
    this->h = new QVector<double>();
    
    for (int i = 1; i < size; i++) {
        this->h->append(x[i]-x[i-1]);
    }
    
    this->calculateSplineCoefficients();
}

void SplineInterpolation::calculateSplineCoefficients() {
    QVector<double> f(size);
    QVector<double> diag(size);
    
    f[0] = 6 * ((input.at(1) - input.at(0)) / h->at(0) - lDeriv);
    f[size-1] = 6 * (rDeriv - ((input.at(size-1) - input.at(size-2)) / h->at(size-2)));
    diag[0] = 2*h->at(0);
    diag[size-1] = 2*h->at(size-2);
    
    for (int i = 1; i < size-1; i++) {
        f[i] = 6 * ((input.at(i+1) - input.at(i)) / h->at(i) - (input.at(i) - input.at(i-1)) / h->at(i-1));
        diag[i] = 2 * (h->at(i-1) + h->at(i));
    }
    
    //this->triSolve(diag, f);
    this->fss = new QVector<double>(this->size);
    triSolve(*fss, *h, diag, *h, f);
    
    this->coeffA = new QVector<double>();
    this->coeffB = new QVector<double>();
    this->coeffC = new QVector<double>();
    
    for(int i = 0; i < size-1; i++) {
        this->coeffA->append((fss->at(i+1)-fss->at(i))/(6*h->at(i)));
        this->coeffB->append(fss->at(i)/2);
        this->coeffC->append((input.at(i+1)-input.at(i))/h->at(i) - h->at(i)/6 * (fss->at(i+1)+2*fss->at(i)));
    }
}

double SplineInterpolation::splineInterpolate(double xValue) {
    // Find required interval: Binary search
    int index = lowerBoundsBinarySearch(xValue, x);
    
    // Calculate function value
    double result = input.at(index);
    double helper = xValue - x.at(index);
    result += helper * coeffC->at(index);
    helper *= xValue - x.at(index);
    result += helper * coeffB->at(index);
    helper *= xValue - x.at(index);
    result += helper * coeffA->at(index);
    
    return result;
}