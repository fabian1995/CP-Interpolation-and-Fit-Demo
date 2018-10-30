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

QVector<double> Fit::linearRegression() {
    double avgX = 0, avgY = 0;
    
    for (int i = 0; i < xValues.size(); i++) {
        avgX += xValues[i];
        avgY += fValues[i];
    }
    avgX /= xValues.size();
    avgY /= xValues.size();
    
    QVector<double> result(2, 0);
    double nom = 0, denom = 0;
    
    for (int i = 0; i < xValues.size(); i++) {
        nom += (xValues[i]-avgX) * (fValues[i]-avgY);
        denom += (xValues[i]-avgX) * (xValues[i]-avgX);
    }
    
    result[1] = nom / denom;
    result[0] = avgY - result[1] * avgX;
    
    return result;
}