#include <qt5/QtCore/qvector.h>

#include "interpolationModel.h"
#include "splineInterpolation.h"

InterpolationModel::InterpolationModel(QString name, int intSteps, PlotDataModel* initialData) {
    this->name = name;
    this->plotModels.append(initialData);
    
    const int steps = initialData->getXData().size() * intSteps;
    const double T_min = initialData->getXData()[0];
    const double T_max = initialData->getXData()[initialData->getXData().size()-1];
    
    SplineInterpolation splineInt(initialData->getXData(), initialData->getYData(), 0, 0);
    
    QVector<double> xValues(steps);
    QVector<double> yValues(steps);
    for (int i = 0; i < steps; i++) {
        xValues[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
        yValues[i] = splineInt.splineInterpolate(xValues[i]);
    }
    
    this->plotModels.append(new PlotDataModel(xValues, yValues, LINE, QString("Spline"), false));
    
    //delete splineInt;*/
}

QString InterpolationModel::getName() {
    return this->name;
}