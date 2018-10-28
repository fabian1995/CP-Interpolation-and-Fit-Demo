/*
 * File:   main.cpp
 * Author: fabian
 *
 * Created on 25. Oktober 2018, 12:25
 */

#include <QApplication>
#include <iostream>
#include <QComboBox>
#include <QGridLayout>

#include "plotwidget.h"
#include "splineInterpolation.h"
#include "utils.h"
#include "lagrangeInterpolation.h"

using namespace std;

QVector<double> fNoise {
    -1.2, 10.4, 3.2, 0.8, 2.2, 2.2, 3.1, 0.9, 2.0, 5.0, -4.4
};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    
    QGridLayout* layout = new QGridLayout();
    window->setLayout(layout);
    window->setMinimumSize(500, 500);
    
    PlotWidget* noisePlot = new PlotWidget(nullptr, PlotWidget::LINEAR, PlotWidget::LINEAR);
    layout->addWidget(noisePlot, 1,0);
    
    double T_min = 0;
    double T_max = 10;
    int steps = 11;
    int moreSteps = 30;
    

    QVector<double> xValues(steps);
    for(int i=0; i<steps; i++) {
        xValues[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
    }
    
    cout << "Checking trisolve: " << testTrisolve() << endl;
    cout << "Checking LBBS:     " << testLBBinarySearch() << endl;
    
    SplineInterpolation* spline = new SplineInterpolation(&xValues,&fNoise,0,0);
    LagrInterpolate* lagrange = new LagrInterpolate(xValues, fNoise);
    
    T_min -= 0.25;
    T_max += 0.25;
    
    QVector<double> xValues2(steps*moreSteps);
    QVector<double> fSplines(steps*moreSteps);
    QVector<double> fLagrange(steps*moreSteps);
    for(int i = 0; i < steps*moreSteps; i++) {
        xValues2[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps*moreSteps-1);
        fSplines[i] = spline->splineInterpolate(xValues2[i]);
        fLagrange[i] = lagrange->polynomial(xValues2[i]);
    }
    
    noisePlot->plot(xValues, fNoise, DOT, QString("Input Data - Noise"));
    noisePlot->plot(xValues2, fSplines, LINE, QString("Spline Interpolation"));
    noisePlot->plot(xValues2, fLagrange, LINE, QString("Lagrange Interpolation"));
    
    QComboBox *comboBox = new QComboBox();
    comboBox->addItem("item 1");
    comboBox->addItem("item 2");
    layout->addWidget(comboBox, 0, 0);
    //comboBox->addItem(tr("item 3"));
    
    window->show();
    window->update();

    return app.exec();
}
