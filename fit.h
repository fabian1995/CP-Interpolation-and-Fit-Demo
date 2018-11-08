/* 
 * File:   fit.h
 * Author: fabian
 *
 * Created on 30. Oktober 2018, 10:37
 */

#ifndef FIT_H
#define FIT_H

#include <qt5/QtCore/qvector.h>
#include <functional>
#include <utility>


class Fit {
public:
    typedef double (*FitFunction)(double x, QVector<double> params);
    //typedef double (*ParamFunction)(QVector<double> params);
    using ParamFunction = std::function<double(QVector<double>)>;
    Fit(QVector<double> x, QVector<double> f, FitFunction func, QVector<Fit::FitFunction> gradient, QVector<double> p0);
    
    double getSquareError();
    QVector<double> linearRegression();
    
    QVector<QVector<double>> params;
    
private:
    QVector<double> xValues;
    QVector<double> fValues;
    QVector<double> modelValues;
    FitFunction func;
    QVector<Fit::FitFunction> gradient;
    QVector<Fit::ParamFunction> paramFunc;
    
    void calculateFit();
    QVector<double> applyFunctions(QVector<ParamFunction>, QVector<double> params);
    QVector<QVector<double>> jacobiMatrix(QVector<Fit::ParamFunction> f, QVector<double> params);
};

#endif /* FIT_H */

