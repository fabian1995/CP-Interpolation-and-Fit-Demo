/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   splineInterpolation.h
 * Author: fabian
 *
 * Created on 25. Oktober 2018, 12:30
 */

#ifndef SPLINE_H
#define SPLINE_H

#include <QVector>


class SplineInterpolation {
public:
    SplineInterpolation(QVector<double> x, QVector<double> input, double lDeriv, double rDeriv);
    
    double splineInterpolate(double xValue);
    
private:
    QVector<double>* fss;
    QVector<double> input;
    QVector<double> x;
    QVector<double>* coeffA;
    QVector<double>* coeffB;
    QVector<double>* coeffC;
    //QVector<double>* coeffD; coefficient d is equal to input data
    double lDeriv;
    double rDeriv;
    int size;
    
    QVector<double>* h;
    
    void calculateSplineCoefficients();
    
};

#endif /* SPLINE_H */

