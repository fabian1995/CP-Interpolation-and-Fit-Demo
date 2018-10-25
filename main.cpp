/*
 * File:   main.cpp
 * Author: fabian
 *
 * Created on 25. Oktober 2018, 12:25
 */

#include <QApplication>
#include <iostream>

#include "plotwidget.h"
#include "spline.h"
#include "utils.h"

using namespace std;

QVector<double> fNoise {
    -1.2, 10.4, 3.2, 0.8, 2.2, 2.2, 3.1, 0.9, 2.0, 5.0, -4.4
};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    PlotWidget* noisePlot = new PlotWidget(0, PlotWidget::LINEAR, PlotWidget::LINEAR);
    
    double T_min = 0;
    double T_max = 10;
    int steps = 11;
    int moreSteps = 30;
    

    QVector<double> xValues(steps);
    QVector<double> fValues(steps);
    for(int i=0; i<steps; i++) {
        xValues[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
    }
    
    cout << "Checking trisolve: " << testTrisolve() << endl;
    cout << "Checking LBBS:     " << testLBBinarySearch() << endl;
    
    SplineInterpolation* spline = new SplineInterpolation(&xValues,&fNoise,0,0);
    
    QVector<double> xValues2(steps*moreSteps);
    QVector<double> fSplines(steps*moreSteps);
    for(int i = 0; i < steps*moreSteps; i++) {
        xValues2[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps*moreSteps-1);
        fSplines[i] = spline->splineInterpolate(xValues2[i]);
    }
    
    noisePlot->plot(xValues, fNoise, PlotWidget::DOT, QString("Input Data - Noise"));
    noisePlot->plot(xValues2, fSplines, PlotWidget::LINE, QString("Spline Interpolation"));

    return app.exec();
}
