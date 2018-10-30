#include "plotCollectionModel.h"

#include <QVector>
#include <QImageReader>
#include <cmath>

#include "splineInterpolation.h"
#include "lagrangeInterpolation.h"

QString PlotCollectionModel::getName() {
    return this->name;
}

QString PlotCollectionModel::getEqImagePath() {
    return this->imagepath;
}
