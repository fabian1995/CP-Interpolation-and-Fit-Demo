#include "spline.h"

#include <iostream>

using namespace std;

SplineInterpolation::SplineInterpolation(QVector<double>* x, QVector<double>* input, double lDeriv, double rDeriv) {
    this->x = x;
    this->input = input;
    this->lDeriv = lDeriv;
    this->rDeriv = rDeriv;
    this->size = input->size()+1;
    
    this->h = new QVector<double>();
    this->h->append(input[0]);
    
    for (int i = 1; i < size-1; i++) {
        this->h->append(x->at(i)-x->at(i-1));
    }
    
    //this->calculateSplineCoefficients();
}

void SplineInterpolation::calculateSplineCoefficients() {
    QVector<double> f(size);
    QVector<double> diag(size);
    
    f[0] = (input->at(1) - input->at(0)) / h->at(0) - lDeriv;
    f[size-1] = rDeriv - (input->at(size-2) - input->at(size-3)) / h->at(size-3);
    diag[0] = 2*h->at(0);
    diag[size-1] = 2*h->at(size-3);
    
    for (int i = 1; i < size-2; i++) {
        f[i] = (input->at(i+1) - input->at(i)) / h->at(i) - (input->at(i) - input->at(i-1)) / h->at(i-1);
        diag[i] = 2 * (h->at(i-1) + h->at(i));
    }
    
    this->triSolve(diag, f);
    
    this->coeffA = new QVector<double>();
    this->coeffB = new QVector<double>();
    this->coeffC = new QVector<double>();
    
    for(int i = 0; i < size-2; i++) {
        this->coeffA->append((fss->at(i+1)-fss->at(i))/(6*h->at(i)));
        this->coeffB->append(fss->at(i)/2);
        this->coeffC->append((input->at(i+1)-input->at(i))/h->at(i) - h->at(i)/6 * (fss->at(i+1)+2*fss->at(i)));
    }
}

void SplineInterpolation::triSolve(QVector<double> diag, QVector<double> f) {
    QVector<double> beta(size);
    QVector<double> rho(size);
    
    this->fss = new QVector<double>();
    
    beta[0] = diag[0];
    rho[0] = f[0];
    
    for(int i = 1; i < size; i++) {
        beta[i] = diag[i] - h->at(i-1)*h->at(i-1)/beta[i-1];
        rho[i] = f[i] - h->at(i-1)*rho[i-1]/beta[i-1];
    }
    
    fss->prepend(rho[size-1] / beta[size-1]);
    
    for(int i = size-2; i >= 0; i--) {
        fss->prepend((rho[i] - h->at(i) * fss->first() + 1 ) / beta[i]);
    }
}

int SplineInterpolation::lowerBoundsBinarySearch(double xValue) {
    int lowerIndex = 0;
    int upperIndex = this->size-2;
    int midIndex = (upperIndex + lowerIndex) / 2;
    
    //cout << "[UL " << upperIndex << "   " << this->x->at(upperIndex) << " -> " << this->input->isEmpty() << "] ";
    
    // Check if we are looking for boundary values
    if (xValue <= this->x->at(lowerIndex)) {
        return lowerIndex;
    }
    else if (xValue >= this->x->at(upperIndex)) {
        // Functions have one index less -> do not take last index
        
        return upperIndex-1;
    }
    
    // Searches for lower index of the interval that encloses xValue
    while (midIndex != lowerIndex) {
        //cout << "Lower: " << lowerIndex << " Mid: " << midIndex << " Upper: " << upperIndex << endl;
        if (xValue > this->x->at(midIndex)) {
            lowerIndex = midIndex;
        }
        else if (xValue < this->x->at(midIndex)) {
            upperIndex = midIndex;
        }
        else {
            return midIndex;
        }
        midIndex = (upperIndex + lowerIndex) / 2;
    }
    
    // Result index of this search is lowerIndex if not found in previous steps
    return lowerIndex;
}

double SplineInterpolation::splineInterpolate(double xValue) {
    // Find required interval: Binary search
    cout << "Looking for " << xValue;
    
    int index = lowerBoundsBinarySearch(xValue);
    
    cout << " Index: " << index << " Max: " << input->size() << " Internal: " << this->size << endl;
    
    // Calculate function value
    double result = input->at(index);
    //double helper = xValue - x->at(index);
    /*result += helper * coeffC->at(index);
    helper *= xValue - x->at(index);
    result += helper * coeffB->at(index);
    helper *= xValue - x->at(index);
    result += helper * coeffA->at(index);*/
    
    return result;
}