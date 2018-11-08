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

Fit::Fit(QVector<double> x, QVector<double> f, QVector<double> errors, Fit::FitFunction func, QVector<Fit::FitFunction> gradient, QVector<double> p0) {
    this->xValues = x;
    this->fValues = f;
    this->func = func;
    this->gradient = gradient;
    this->params = QVector<QVector<double>>();
    this->params.append(p0);
    
    if (errors.size() == xValues.size())
        this->errors = errors;
    else
        this->errors = QVector<double>(xValues.size(), 1);
    
    this->paramFunc = QVector<ParamFunction>(gradient.size());
    for (int i = 0; i < paramFunc.size(); i++) {
        paramFunc[i] = [=](QVector<double> p) -> double {
            double result = 0;
            for (int j = 0; j < xValues.size(); j++) {
                result += (fValues[j]-func(xValues[j], p)) * gradient[i](xValues[j], p) / std::pow(errors[j], 2);
            }
            return result;
        };
    }
    
    double lastSquareError = getSquareError();
    
    for (int i = 0; i < 100; i++) {
        QVector<QVector<double>> mat = jacobiMatrix(paramFunc, params.last());
        //printQMatrix(mat);

        QVector<double> delta_x = linSolve(mat, applyFunctions(paramFunc, params.last()), true);

        params.append(QVector<double>(params.last()));
        for (int j = 0; j < delta_x.size(); j++) {
            params.last()[j] += delta_x[j];
        }
        std::cout << "Square error for step " << (i+1) << ": " << getSquareError() << std::endl;
        
        if (almostEqual(lastSquareError, this->getSquareError()))
            break;
        else
            lastSquareError = this->getSquareError();
    }
}

double Fit::getSquareError() {
    double result = 0;
    for (int i = 0; i < xValues.size(); i++) {
        double diff = (this->func(xValues[i], params.last())-fValues[i]) / errors[i];
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

QVector<QVector<double>> Fit::jacobiMatrix(QVector<Fit::ParamFunction> f, QVector<double> params) {
    QVector<QVector<double>> mat (params.size());
    
    for (int j = 0; j < mat.size(); j++) {
        double h = params[j] / 1000;
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