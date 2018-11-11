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
    PlotCollectionModel(QString name, QString eqImage);
    
    QString getName();
    QString getEqImagePath();
    
    /** All Plot Models for the default function plot */
    QVector<PlotDataModel*> plotModels;
    
    /** Plot Models for the additional error plot. */
    QVector<PlotDataModel*> errorModels;
    
protected:
    /** Display name of this Plot Collection */
    QString name;
    
    /** Path to optional image that can be shown besides the graph */
    QString imagepath;
};

#endif /* PLOTCOLLECTIONMODEL_H */

