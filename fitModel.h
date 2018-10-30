/* 
 * File:   fitModel.h
 * Author: fabian
 *
 * Created on 30. Oktober 2018, 11:12
 */

#ifndef FITMODEL_H
#define FITMODEL_H

#include <QVector>

#include "plotDataModel.h"
#include "plotCollectionModel.h"
#include "fit.h"

class FitModel : public PlotCollectionModel {
public:
    FitModel(QString name, int intSteps, PlotDataModel* initialData, Fit::FitFunction func, QVector<double> params, QString imagePath);
};

#endif /* FITMODEL_H */

