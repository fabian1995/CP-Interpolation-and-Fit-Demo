#include "spline.h"
#include "utils.h"

#include <iostream>

using namespace std;

SplineInterpolation::SplineInterpolation(QVector<double>* x, QVector<double>* input, double lDeriv, double rDeriv) {
    this->x = x;
    this->input = input;
    this->lDeriv = lDeriv;
    this->rDeriv = rDeriv;
    this->size = input->size()+1;
    
    this->h = new QVector<double>();
    
    for (int i = 1; i < size-1; i++) {
        this->h->append(x->at(i)-x->at(i-1));
    }
    
    cout << "vector h: ";
    printQVector(*h);
    
    this->calculateSplineCoefficients();
}

void SplineInterpolation::calculateSplineCoefficients() {
    QVector<double> f(size-1);
    QVector<double> diag(size-1);
    
    f[0] = (input->at(1) - input->at(0)) / h->at(0) - lDeriv;
    f[size-2] = rDeriv - (input->at(size-2) - input->at(size-3)) / h->at(size-3);
    diag[0] = 2*h->at(0);
    diag[size-2] = 2*h->at(size-3);
    
    for (int i = 1; i < size-2; i++) {
        f[i] = (input->at(i+1) - input->at(i)) / h->at(i) - (input->at(i) - input->at(i-1)) / h->at(i-1);
        diag[i] = 2 * (h->at(i-1) + h->at(i));
    }
    
    cout << "h size: " << h->size() << ", b size: " << diag.size() << ", system size: " << this->size << endl;
    
    //this->triSolve(diag, f);
    this->fss = new QVector<double>(this->size-1);
    triSolve(*fss, *h, diag, *h, f);
    
    cout << "vector f: ";
    printQVector(f);
    
    cout << "vector fss: ";
    printQVector(*fss);
    
    this->coeffA = new QVector<double>();
    this->coeffB = new QVector<double>();
    this->coeffC = new QVector<double>();
    
    for(int i = 0; i < size-2; i++) {
        this->coeffA->append((fss->at(i+1)-fss->at(i))/(6*h->at(i)));
        this->coeffB->append(fss->at(i)/2);
        this->coeffC->append((input->at(i+1)-input->at(i))/h->at(i) - h->at(i)/6 * (fss->at(i+1)+2*fss->at(i)));
    }
    
    cout << "vector a: ";
    printQVector(*coeffA);
    cout << "vector b: ";
    printQVector(*coeffB);
    cout << "vector c: ";
    printQVector(*coeffC);
}

double SplineInterpolation::splineInterpolate(double xValue) {
    // Find required interval: Binary search
    int index = lowerBoundsBinarySearch(xValue, *x);
    
    // Calculate function value
    double result = input->at(index);
    double helper = xValue - x->at(index);
    result += helper * coeffC->at(index);
    helper *= xValue - x->at(index);
    result += helper * coeffB->at(index);
    helper *= xValue - x->at(index);
    result += helper * coeffA->at(index);
    
    return result;
}