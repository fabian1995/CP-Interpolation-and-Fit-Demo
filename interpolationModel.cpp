#include "interpolationModel.h"

InterpolationModel::InterpolationModel(QString name) {
    this->name = name;
}

QString InterpolationModel::getName() {
    return this->name;
}