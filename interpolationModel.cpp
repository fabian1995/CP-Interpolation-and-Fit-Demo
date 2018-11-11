#include <QVector>
#include <QImageReader>
#include <cmath>

#include "interpolationModel.h"
#include "splineInterpolation.h"
#include "lagrangeInterpolation.h"

/**
 * Calculates the central difference quotient of function f at a given point.
 * @param f Input function
 * @param x Value on the x axis
 * @param h Small change (delta) for the difference quotient. This number should
 * be chosen as small as possible but without the risk of cancellation.
 * @return The derivative of f at point x.
 */
double firstDerivative(PlotDataModel::BasisFunction f, double x, double h) {
    return (f(x+h)-f(x-h)) / (2*h);
}

/**
 * Creates a Plot Collection Model containing Spline and Lagrange interpolation
 * of the given Plot Data Model.
 * @see PlotDataModel
 * @see PlotCollectionModel
 * @param name Name of this Plot Collection
 * @param intSteps Number of steps between the data nodes of the Plot Model
 * @param initialData Input Plot Model
 * @param imagePath Path to an image of the equation defining the input data (optional)
 */
InterpolationModel::InterpolationModel(QString name, int intSteps, PlotDataModel* initialData, QString imagePath = QString()) : PlotCollectionModel(name, imagePath) {
    this->plotModels.append(initialData);
    
    const int steps = initialData->getXData().size() * intSteps;
    const double T_min = initialData->getXData()[0];
    const double T_max = initialData->getXData()[initialData->getXData().size()-1];
    
    PlotDataModel::BasisFunction exactFunc = initialData->getBasisFunction();
    
    double lDer = 0, rDer = 0;
    
    if (exactFunc != nullptr) {
        lDer = firstDerivative(exactFunc, T_min, (T_max-T_min)/1000);
        rDer = firstDerivative(exactFunc, T_max, (T_max-T_min)/1000);
    }
    
    SplineInterpolation splineInt(initialData->getXData(), initialData->getYData(), lDer, rDer);
    LagrInterpolate lagrInt(initialData->getXData(), initialData->getYData());
    
    QVector<double> xValues(steps);
    QVector<double> yValuesExact(steps);
    QVector<double> yValuesSpline(steps);
    QVector<double> yValuesLagr(steps);
    QVector<double> errValuesSpline(steps);
    QVector<double> errValuesLagr(steps);
    for (int i = 0; i < steps; i++) {
        xValues[i] = T_min + (T_max-T_min) * (double)(i) / (double)(steps-1);
        yValuesSpline[i] = splineInt.splineInterpolate(xValues[i]);
        yValuesLagr[i] = lagrInt.interpolate(xValues[i]);

        if (exactFunc != nullptr) {
            double exactValue = exactFunc(xValues[i]);
            yValuesExact[i] = exactValue;
            errValuesSpline[i] = std::abs((exactValue - yValuesSpline[i]) / exactValue);
            errValuesLagr[i] = std::abs((exactValue - yValuesLagr[i]) / exactValue);
        }
    }
    
    if (exactFunc != nullptr) {
        this->plotModels.append(new PlotDataModel(xValues, yValuesExact, LINE, QString("Exact Function"), false));
        this->errorModels.append(new PlotDataModel(xValues, errValuesSpline, LINE, QString("Error of Spline"), false));
        this->errorModels.append(new PlotDataModel(xValues, errValuesLagr, LINE, QString("Error of Lagrange"), false));
    }
    this->plotModels.append(new PlotDataModel(xValues, yValuesLagr, LINE, QString("Lagrange"), false));
    this->plotModels.append(new PlotDataModel(xValues, yValuesSpline, LINE, QString("Spline"), false));
    
}