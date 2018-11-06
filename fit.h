/* 
 * File:   fit.h
 * Author: fabian
 *
 * Created on 30. Oktober 2018, 10:37
 */

#ifndef FIT_H
#define FIT_H

#include <qt5/QtCore/qvector.h>


class Fit {
public:
    typedef double (*FitFunction)(double x, QVector<double> params);
    Fit(QVector<double> x, QVector<double> f, FitFunction func, QVector<Fit::FitFunction> gradient, QVector<double> params);
    
    double getSquareError();
    QVector<double> linearRegression();
    
private:
    QVector<double> xValues;
    QVector<double> fValues;
    FitFunction func;
    QVector<Fit::FitFunction> gradient;
    QVector<double> params;
};

#endif /* FIT_H */

