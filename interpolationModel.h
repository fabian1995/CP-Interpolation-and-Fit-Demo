/* 
 * File:   InterpolationModel.h
 * Author: fabian
 *
 * Created on 28. Oktober 2018, 14:59
 */

#ifndef INTERPOLATIONMODEL_H
#define INTERPOLATIONMODEL_H

#include <qt5/QtCore/qvector.h>

#include "plotDataModel.h"


class InterpolationModel {
public:
    InterpolationModel(QString name, int intSteps, PlotDataModel* initialData);
    InterpolationModel(QString name, int intSteps, PlotDataModel* initialData, QString imagePath);
    
    QString getName();
    QString getEqImagePath();
    
    QVector<PlotDataModel*> plotModels;
    QVector<PlotDataModel*> errorModels;
    
private:
    QString name;
    QString imagepath;
};

#endif /* INTERPOLATIONMODEL_H */

