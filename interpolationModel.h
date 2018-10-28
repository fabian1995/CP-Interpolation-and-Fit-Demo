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
    InterpolationModel(QString name);
    
    QString getName();
    
    QVector<PlotDataModel*> plotModels;
    
private:
    QString name;
};

#endif /* INTERPOLATIONMODEL_H */

