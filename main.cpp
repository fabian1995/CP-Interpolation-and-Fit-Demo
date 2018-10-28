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
#include <qt5/QtCore/qobject.h>
#include <cmath>

#include "plotDataModel.h"
#include "splineInterpolation.h"
#include "utils.h"
#include "lagrangeInterpolation.h"
#include "plotWrapper.h"

using namespace std;

QVector<double> fNoise {
    -1.2, 10.4, 3.2, 0.8, 2.2, 2.2, 3.1, 0.9, 2.0, 5.0, -4.4
};
QVector<double> xNoise {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

PlotDataModel noiseModel = PlotDataModel(xNoise, fNoise, DOT, QString("Noise"), false);

inline double polynom(double x) {
    return x*x*x-2*x*x+3*x-10;
}

PlotDataModel polModel = PlotDataModel(&polynom, 0, 10, 11, DOT, QString("Polynom"), false);

inline double task6funciton(double x) {
    return std::sin(x) / (1+x*x);
}

PlotDataModel t6h2 = PlotDataModel(&polynom, -6, 6, 7, DOT, QString("f(x)"), false);
PlotDataModel t6h1 = PlotDataModel(&polynom, -6, 6, 13, DOT, QString("f(x)"), false);
PlotDataModel t6h05 = PlotDataModel(&polynom, -6, 6, 25, DOT, QString("f(x)"), false);
PlotDataModel t6h02 = PlotDataModel(&polynom, -6, 6, 61, DOT, QString("f(x)"), false);

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    
    QGridLayout* layout = new QGridLayout();
    window->setLayout(layout);
    window->setMinimumSize(600, 500);
    
    PlotWidget* functionPlot = new PlotWidget(nullptr, PlotWidget::LINEAR, PlotWidget::LINEAR);
    layout->addWidget(functionPlot, 1, 0);
    
    PlotWidget* errorPlot = new PlotWidget(nullptr, PlotWidget::LINEAR, PlotWidget::LINEAR);
    layout->addWidget(errorPlot, 1, 1);
    
    QComboBox* combo = new QComboBox();
    layout->addWidget(combo, 0, 0);
    
    PlotWrapper* wrapper = new PlotWrapper(functionPlot, errorPlot, combo);
    wrapper->addDataModel(new InterpolationModel("Noise Model", 10, &noiseModel));
    wrapper->addDataModel(new InterpolationModel("Polynomial Model", 10, &polModel));
    wrapper->addDataModel(new InterpolationModel("Task 6 - h = 2", 20, &t6h2));
    wrapper->addDataModel(new InterpolationModel("Task 6 - h = 1", 20, &t6h1));
    wrapper->addDataModel(new InterpolationModel("Task 6 - h = 0.5", 20, &t6h05));
    wrapper->addDataModel(new InterpolationModel("Task 6 - h = 0.2", 20, &t6h02));
    
    QObject::connect(combo, SIGNAL(currentIndexChanged(QString)), wrapper, SLOT(plot(QString)));
    
    window->show();
    window->update();

    return app.exec();
}
