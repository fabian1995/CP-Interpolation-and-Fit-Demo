/*
 * CP Interpolation & Fit Demo
 * Copyright (C) 2018 Fabian Hummer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <iostream>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QObject>
#include <cmath>
#include <qt5/QtCore/qvector.h>

#include "plotDataModel.h"
#include "splineInterpolation.h"
#include "utils.h"
#include "lagrangeInterpolation.h"
#include "plotWrapper.h"
#include "interpolationFileHandler.h"
#include "plotCollectionModel.h"
#include "interpolationModel.h"
#include "fitModel.h"

using namespace std;

QVector<double> fNoise {
    -1.2, 10.4, 3.2, 0.8, 2.2, 2.2, 3.1, 0.9, 2.0, 5.0, -4.4
};
QVector<double> xNoise {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

QVector<double> fNoise2 {
    2.2, 3.1, -1.2, 2.2, 3.1, 0.9, 2.0, 5.0, -4.4, -4.4
};
QVector<double> xNoise2 {
    1.5, 2.5, 4, 4.5, 5, 5.2, 7.4, 8.1, 9.1, 10
};

PlotDataModel noiseModel = PlotDataModel(xNoise, fNoise, DOT, QString("Noise"), false);
PlotDataModel noiseModel2 = PlotDataModel(xNoise2, fNoise2, DOT, QString("Noise"), false);

QVector<double> scatteringEnergy {
    0, 25, 50, 75, 100, 125, 150, 175, 200
};

QVector<double> scatteringData {
    10.6, 16, 45, 83, 52, 19.9, 10.8, 8.25, 4.7
};

QVector<double> scatteringErrors {
    5, 5, 5, 5, 10, 5, 5, 5, 5
};

PlotDataModel linearModel = PlotDataModel(scatteringEnergy, scatteringData, scatteringErrors, DOT, QString("Input Data"), false);

inline double polynom(double x) {
    return x*x*x-2*x*x+3*x-10;
}

PlotDataModel polModel = PlotDataModel(&polynom, 0, 10, 11, DOT, QString("Polynom"), false);

inline double task6function(double x) {
    return std::sin(x) / (1+x*x);
}

PlotDataModel t6h2 = PlotDataModel(&task6function, -6, 6, 7, DOT, QString("f(x)"), false);
PlotDataModel t6h1 = PlotDataModel(&task6function, -6, 6, 13, DOT, QString("f(x)"), false);
PlotDataModel t6h05 = PlotDataModel(&task6function, -6, 6, 25, DOT, QString("f(x)"), false);
PlotDataModel t6h02 = PlotDataModel(&task6function, -6, 6, 61, DOT, QString("f(x)"), false);

double linearFunction(double x, QVector<double>params) {
    return params[1]*x+params[0];
}

double nonLinFunc(double x, QVector<double> params) {
    return params[0]/(pow(x-params[1],2)+params[2]);
}

double nonLinFuncD0(double x, QVector<double> params) {
    return 1/(pow(x-params[1],2)+params[2]);
}

double nonLinFuncD1(double x, QVector<double> params) {
    return -2*params[0]*(x-params[1])/pow(pow(x-params[1],2)+params[2],2);
}

double nonLinFuncD2(double x, QVector<double> params) {
    return -params[0]/pow(pow(x-params[1],2)+params[2],2);
}

QVector<Fit::FitFunction> gradient = {&nonLinFuncD0, &nonLinFuncD1, &nonLinFuncD2};

int main(int argc, char *argv[]) {
    
    //testLinAlgFunctions();
    
    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    
    QGridLayout* layout = new QGridLayout();
    window->setLayout(layout);
    window->setMinimumSize(600, 500);
    
    PlotWidget* functionPlot = new PlotWidget(nullptr, PlotWidget::LINEAR, PlotWidget::LINEAR);
    functionPlot->setPlotTitle("Function Plots");
    layout->addWidget(functionPlot, 1, 0);
    
    PlotWidget* errorPlot = new PlotWidget(nullptr, PlotWidget::LINEAR, PlotWidget::LINEAR);
    errorPlot->setPlotTitle("Relative Errors");
    layout->addWidget(errorPlot, 1, 1);
    
    QComboBox* combo = new QComboBox();
    layout->addWidget(combo, 0, 0);
    
    QWidget* eqSpace = new QWidget();
    layout->addWidget(eqSpace, 0, 1);
    
    QHBoxLayout* eqLayout = new QHBoxLayout();
    eqSpace->setLayout(eqLayout);
    
    QLabel* eqLabel = new QLabel();
    QLabel* eqCaption = new QLabel();
    eqLayout->addWidget(eqCaption);
    eqLayout->addWidget(eqLabel);
    
    PlotWrapper* wrapper = new PlotWrapper(functionPlot, errorPlot, combo, eqSpace, eqLabel, eqCaption);
    QVector<double> params {9000,75,100};
    wrapper->addDataModel(new FitModel("Nonlinear Fit", 30, &linearModel, &nonLinFunc, gradient, params, QString("img/eq_nonlinfit.png")));
    
    wrapper->addDataModel(new InterpolationModel("Noise Model - x equally spaced", 30, &noiseModel, QString()));
    wrapper->addDataModel(new InterpolationModel("Noise Model - x unequally spaced", 30, &noiseModel2, QString()));
    
    wrapper->addDataModel(new InterpolationModel("Polynomial Model", 30, &polModel, QString("img/eq_pol_nw.png")));
    wrapper->addDataModel(new InterpolationModel("Task 6 - h = 2", 30, &t6h2, QString("img/eq_t6_nw.png")));
    wrapper->addDataModel(new InterpolationModel("Task 6 - h = 1", 20, &t6h1, QString("img/eq_t6_nw.png")));
    wrapper->addDataModel(new InterpolationModel("Task 6 - h = 0.5", 20, &t6h05, QString("img/eq_t6_nw.png")));
    wrapper->addDataModel(new InterpolationModel("Task 6 - h = 0.2", 20, &t6h02, QString("img/eq_t6_nw.png")));
    
    QObject::connect(combo, SIGNAL(currentIndexChanged(QString)), wrapper, SLOT(plot(QString)));
    
    QWidget* exportBar = new QWidget();
    exportBar->setMaximumHeight(40);
    QHBoxLayout* exportLayout = new QHBoxLayout();
    exportBar->setLayout(exportLayout);
    
    QLabel* exportLabel = new QLabel("Export data to CSV file");
    exportLayout->addWidget(exportLabel);
    
    QPushButton* exportButton = new QPushButton("Choose file");
    exportLayout->addWidget(exportButton);
    
    layout->addWidget(exportBar, 2, 0);
    
    InterpolationFileHandler* fileHandler = new InterpolationFileHandler(wrapper);
    
    QObject::connect(exportButton, SIGNAL(pressed()), fileHandler, SLOT(saveCurrentFunctions()));
    
    window->show();
    window->update();

    return app.exec();
}
