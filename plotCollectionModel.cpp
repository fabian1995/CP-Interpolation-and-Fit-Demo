#include "plotCollectionModel.h"

#include <QVector>
#include <QImageReader>
#include <cmath>

#include "splineInterpolation.h"
#include "lagrangeInterpolation.h"

PlotCollectionModel::PlotCollectionModel(QString name, QString eqImage) {
    this->name = name;
    this->imagepath = eqImage;
}

QString PlotCollectionModel::getName() {
    return this->name;
}

QString PlotCollectionModel::getEqImagePath() {
    return this->imagepath;
}
