#include <qt5/QtCore/qvector.h>
#include <cmath>

#include "interpolationModel.h"
#include "splineInterpolation.h"
#include "lagrangeInterpolation.h"

InterpolationModel::InterpolationModel(QString name, int intSteps, PlotDataModel* initialData) {
    this->name = name;
    this->plotModels.append(initialData);
    
    const int steps = initialData->getXData().size() * intSteps;
    const double T_min = initialData->getXData()[0];
    const double T_max = initialData->getXData()[initialData->getXData().size()-1];
    
    SplineInterpolation splineInt(initialData->getXData(), initialData->getYData(), 0, 0);
    LagrInterpolate lagrInt(initialData->getXData(), initialData->getYData());
    
    PlotDataModel::BasisFunction exactFunc = initialData->getBasisFunction();
    
    QVector<double> xValues(steps);
    QVector<double> yValuesSpline(steps);
    QVector<double> yValuesLagr(steps);
    QVector<double> errValuesSpline(steps);
    QVector<double> errValuesLagr(steps);
    for (int i = 0; i < steps; i++) {
        xValues[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
        yValuesSpline[i] = splineInt.splineInterpolate(xValues[i]);
        yValuesLagr[i] = lagrInt.polynomial(xValues[i]);
        
        if (exactFunc != nullptr) {
            double exactValue = exactFunc(xValues[i]);
            errValuesSpline[i] = std::abs((exactValue - yValuesSpline[i]) / exactValue);
            errValuesLagr[i] = std::abs((exactValue - yValuesLagr[i]) / exactValue);
        }
    }
    
    this->plotModels.append(new PlotDataModel(xValues, yValuesSpline, LINE, QString("Spline"), false));
    this->plotModels.append(new PlotDataModel(xValues, yValuesLagr, LINE, QString("Lagrange"), false));
    
    if (exactFunc != nullptr) {
        this->errorModels.append(new PlotDataModel(xValues, errValuesSpline, LINE, QString("Error of Spline"), false));
        this->errorModels.append(new PlotDataModel(xValues, errValuesLagr, LINE, QString("Error of Lagrange"), false));
    }
}

QString InterpolationModel::getName() {
    return this->name;
}