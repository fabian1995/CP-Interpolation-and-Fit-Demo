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
 * @param name Display name of this Plot Collection.
 * @param eqImage Path to an image that shall be displayed along with the plot
 * collection. Pass an empty string if no image is available.
 */
PlotCollectionModel::PlotCollectionModel(QString name, QString eqImage) {
    this->name = name;
    this->imagepath = eqImage;
}

/**
 * @return The display name of this Plot Collection.
 */
QString PlotCollectionModel::getName() {
    return this->name;
}

/**
 * @return The path to the display image of this Plot Collection. May be an empty
 * string if no image is available.
 */
QString PlotCollectionModel::getEqImagePath() {
    return this->imagepath;
}
