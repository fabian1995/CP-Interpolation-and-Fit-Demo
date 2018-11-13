/*
 * CP Interpolation & Fit Demo
 * Copyright (C) 2018 Fabian Hummer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PLOTCOLLECTIONMODEL_H
#define PLOTCOLLECTIONMODEL_H

#include <QVector>

#include "plotDataModel.h"

class PlotCollectionModel {
public:
    PlotCollectionModel(QString name, QString eqImage, QString eqLabel);
    
    QString getName();
    QString getEqImagePath();
    QString getEqImageCaption();
    
    /** All Plot Models for the default function plot */
    QVector<PlotDataModel*> plotModels;
    
    /** Plot Models for the additional error plot. */
    QVector<PlotDataModel*> errorModels;
    
protected:
    /** Display name of this Plot Collection */
    QString displayName;
    
    /** Path to optional image that can be shown besides the graph */
    QString imagepath;
    
    /** Label for the optional plot image */
    QString imageCaption;
};

#endif /* PLOTCOLLECTIONMODEL_H */

