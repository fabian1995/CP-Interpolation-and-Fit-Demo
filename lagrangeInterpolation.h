/* 
 * File:   langrangeInterpolation.h
 * Author: fabian
 *
 * Created on 25. Oktober 2018, 11:04
 */

#ifndef LANGRANGEINTERPOLATION_H
#define LANGRANGEINTERPOLATION_H

#include <QVector>


class LagrInterpolate {
public:
    LagrInterpolate(QVector<double> xValues, QVector<double> fValues);
    
    double polynomial(double x);
    
private:
    QVector<double> xValues;
    QVector<double> fValues;
    
    QVector<double> denominators;
    
    double LagrPol(double x, int index);
};

#endif /* LANGRANGEINTERPOLATION_H */

