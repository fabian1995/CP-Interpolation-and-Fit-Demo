/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plotCollectionModel.h
 * Author: fabian
 *
 * Created on 30. Oktober 2018, 10:59
 */

#ifndef PLOTCOLLECTIONMODEL_H
#define PLOTCOLLECTIONMODEL_H

#include <QVector>

#include "plotDataModel.h"

class PlotCollectionModel {
public:    
    QString getName();
    QString getEqImagePath();
    
    QVector<PlotDataModel*> plotModels;
    QVector<PlotDataModel*> errorModels;
    
protected:
    QString name;
    QString imagepath;
};

#endif /* PLOTCOLLECTIONMODEL_H */

