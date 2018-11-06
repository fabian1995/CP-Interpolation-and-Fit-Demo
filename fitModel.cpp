#include <qt5/QtCore/qvector.h>

#include "fitModel.h"
#include "plotCollectionModel.h"

FitModel::FitModel(QString name, int intSteps, PlotDataModel* initialData, Fit::FitFunction func, QVector<Fit::FitFunction> gradient, QVector<double> params, QString imagePath) : PlotCollectionModel(name, imagePath) {
    this->plotModels.append(initialData);
    
    Fit* fit = new Fit(initialData->getXData(), initialData->getYData(), func, gradient, params);
    
    const int steps = initialData->getXData().size() * intSteps;
    const double T_min = initialData->getXData()[0];
    const double T_max = initialData->getXData()[initialData->getXData().size()-1];
    
    QVector<double> xValues(steps);
    QVector<double> yValFunc(steps);
    QVector<double> params2 = fit->linearRegression();
    for (int i = 0; i < steps; i++) {
        xValues[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
        yValFunc[i] = func(xValues[i], params2);
    }
    
    this->plotModels.append(new PlotDataModel(xValues, yValFunc, LINE, QString("Fit function"), false));
}