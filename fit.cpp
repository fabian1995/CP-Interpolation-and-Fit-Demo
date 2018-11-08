#include <cmath>
#include <qt5/QtCore/qvector.h>
#include <iostream>

#include "fit.h"

#include "utils.h"

double f1(QVector<double> params) {
    return params[0]+params[1];
}

double f2(QVector<double> params) {
    return 1 + 2*params[0]*params[1];
}

Fit::Fit(QVector<double> x, QVector<double> f, Fit::FitFunction func, QVector<Fit::FitFunction> gradient, QVector<double> p0) {
    this->xValues = x;
    this->fValues = f;
    this->func = func;
    this->gradient = gradient;
    this->params = QVector<QVector<double>>();
    this->params.append(p0);
    
    this->paramFunc = QVector<ParamFunction>(gradient.size());
    for (int i = 0; i < paramFunc.size(); i++) {
        paramFunc[i] = [=](QVector<double> p) -> double {
            double result = 0;
            for (int j = 0; j < xValues.size(); j++) {
                result += (fValues[j]-func(xValues[j], p)) * gradient[i](xValues[j], p);
            }
            return result;
        };
    }
    
    std::cout << "func: " << paramFunc[0](params.last()) << std::endl;
    std::cout << "func: " << paramFunc[1](params.last()) << std::endl;
    std::cout << "func: " << paramFunc[2](params.last()) << std::endl;
    
    QVector<QVector<double>> mat = jacobiMatrix(paramFunc, params.last(), 0.0001);
    printQMatrix(mat);
    
    QVector<double> delta_x = linSolve(mat, applyFunctions(paramFunc, params.last()), true);
    
    std::cout << "delta_x: " << std::endl;
    printQVector(delta_x);
    
    params.append(QVector<double>(params.last()));
    for (int i = 0; i < delta_x.size(); i++) {
        params.last()[i] += delta_x[i];
    }
}

double Fit::getSquareError() {
    double result = 0;
    for (int i = 0; i < xValues.size(); i++) {
        double diff = (this->func(xValues[i], params.last())-fValues[i]);
        result += diff * diff;
    }
    return result;
}

QVector<double> Fit::applyFunctions(QVector<Fit::ParamFunction> f, QVector<double> params) {
    QVector<double> values (f.size());
    for (int i = 0; i < values.size(); i++) {
        values[i] = f[i](params);
    }
    return values;
}

QVector<QVector<double>> Fit::jacobiMatrix(QVector<Fit::ParamFunction> f, QVector<double> params, double h) {
    QVector<QVector<double>> mat (params.size());
    
    for (int j = 0; j < mat.size(); j++) {
        QVector<double> col (f.size());
        QVector<double> params2 (params);
        params2[j] += h;
        
        for (int i = 0; i < f.size(); i++) {
            col[i] = (f[i](params2) - f[i](params))/h;
        }
        mat[j] = col;
    }
    return mat;
}

void Fit::calculateFit() {
    
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