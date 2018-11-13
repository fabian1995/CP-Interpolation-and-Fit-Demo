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

#include "plotCollectionModel.h"

#include <QVector>
#include <QImageReader>
#include <cmath>

#include "splineInterpolation.h"
#include "lagrangeInterpolation.h"

/**
 * Abstract base class for Plot Collections. A Plot Collection is a bunch of plot
 * data that belong together and shall be displayed at once in one or more plots.
 * Each Plot Collection has a name and an optional image path.
 * @param displayName Display name of this Plot Collection.
 * @param eqImage Path to an image that shall be displayed along with the plot
 * collection. Pass an empty string if no image is available.
 * @param eqLabel Label/caption for the optional image.
 */
PlotCollectionModel::PlotCollectionModel(QString displayName, QString eqImage, QString eqLabel) {
    this->displayName = displayName;
    this->imagepath = eqImage;
    this->imageCaption = eqLabel;
}

/**
 * @return The display name of this Plot Collection.
 */
QString PlotCollectionModel::getName() {
    return this->displayName;
}

/**
 * @return The path to the display image of this Plot Collection. May be an empty
 * string if no image is available.
 */
QString PlotCollectionModel::getEqImagePath() {
    return this->imagepath;
}

/**
 * @return Label/caption for the optional Plot Collection image
 */
QString PlotCollectionModel::getEqImageCaption() {
    return this->imageCaption;
}
