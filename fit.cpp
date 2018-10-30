#include <cmath>
#include <qt5/QtCore/qvector.h>

#include "fit.h"

Fit::Fit(QVector<double> x, QVector<double> f, Fit::FitFunction func, QVector<double> params) {
    this->xValues = x;
    this->fValues = f;
    this->func = func;
    this->params = params;
}

double Fit::getSquareError() {
    double result = 0;
    for (int i = 0; i < xValues.size(); i++) {
        double diff = (this->func(xValues[i], params)-fValues[i]);
        result += diff * diff;
    }
    return result;
}