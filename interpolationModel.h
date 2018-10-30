/* 
 * File:   InterpolationModel.h
 * Author: fabian
 *
 * Created on 28. Oktober 2018, 14:59
 */

#ifndef INTERPOLATIONMODEL_H
#define INTERPOLATIONMODEL_H

//#include <QVector>

#include "plotDataModel.h"
#include "plotCollectionModel.h"


class InterpolationModel : public PlotCollectionModel {
public:
    InterpolationModel(QString name, int intSteps, PlotDataModel* initialData);
    InterpolationModel(QString name, int intSteps, PlotDataModel* initialData, QString imagePath);
};

#endif /* INTERPOLATIONMODEL_H */

