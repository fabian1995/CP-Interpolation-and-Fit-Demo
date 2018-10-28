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

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    
    QGridLayout* layout = new QGridLayout();
    window->setLayout(layout);
    window->setMinimumSize(500, 500);
    
    PlotWidget* plotArea = new PlotWidget(nullptr, PlotWidget::LINEAR, PlotWidget::LINEAR);
    layout->addWidget(plotArea, 1, 0);
    
    QComboBox* combo = new QComboBox();
    layout->addWidget(combo, 0, 0);
    
    InterpolationModel* ipm1 = new InterpolationModel("Noise Model", 10, &noiseModel);
    //ipm1->plotModels.append(&noiseModel);
    
    InterpolationModel* ipm2 = new InterpolationModel("Polynomial Model", 10, &polModel);
    //ipm2->plotModels.append(&polModel);
    
    PlotWrapper* wrapper = new PlotWrapper(plotArea, combo);
    wrapper->addDataModel(ipm1);
    wrapper->addDataModel(ipm2);
    //wrapper->addDataModel(&polModel);
    
    QObject::connect(combo, SIGNAL(currentIndexChanged(QString)), wrapper, SLOT(plot(QString)));
    
    window->show();
    window->update();

    return app.exec();
}
