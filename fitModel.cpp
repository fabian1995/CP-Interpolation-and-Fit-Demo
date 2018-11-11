#include <QVector>

#include "fitModel.h"
#include "plotCollectionModel.h"

/**
 * Creates a Plot Collection model containing input data nodes and an
 * approximated fit function. 
 * @param name Name of this Plot Collection
 * @param intSteps Number of steps between the data nodes of the Plot Model
 * @param initialData Input Plot Model
 * @param func Fit model function
 * @param gradient Symbolic partial derivatives of fit model function for each parameter
 * @param params Vector of parameters for the fit model function
 * @param imagePath Path to an image of the equation defining the input data (optional)
 */
FitModel::FitModel(QString name, int intSteps, PlotDataModel* initialData, Fit::FitFunction func, QVector<Fit::FitFunction> gradient, QVector<double> params, QString imagePath) : PlotCollectionModel(name, imagePath) {
    this->plotModels.append(initialData);
    
    Fit* fit = new Fit(initialData->getXData(), initialData->getYData(), initialData->getErrors(), func, gradient, params);
    
    const int steps = initialData->getXData().size() * intSteps;
    const double T_min = initialData->getXData()[0];
    const double T_max = initialData->getXData()[initialData->getXData().size()-1];
    
    QVector<double> xValues(steps);
    QVector<double> yValFunc(steps);
    QVector<double> yValFunc2(steps);
    for (int i = 0; i < steps; i++) {
        xValues[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
        yValFunc[i] = func(xValues[i], params);
        yValFunc2[i] = func(xValues[i], fit->params.last());
    }
    
    this->plotModels.append(new PlotDataModel(xValues, yValFunc, LINE, QString("Initial guess"), false));
    this->plotModels.append(new PlotDataModel(xValues, yValFunc2, LINE, QString("Fit function"), false));
}