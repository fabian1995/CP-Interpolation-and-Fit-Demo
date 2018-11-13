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

#ifndef INTERPOLATIONMODEL_H
#define INTERPOLATIONMODEL_H

//#include <QVector>

#include "plotDataModel.h"
#include "plotCollectionModel.h"


class InterpolationModel : public PlotCollectionModel {
public:
    InterpolationModel(QString name, int intSteps, PlotDataModel* initialData, QString imagePath);
};

#endif /* INTERPOLATIONMODEL_H */

