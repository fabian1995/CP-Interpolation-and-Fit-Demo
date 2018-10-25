#ifndef MISC_H
#define MISC_H

#include <QVector>
#include <QString>
#include "plotwidget.h"

QVector<double> findBeautifulGrid(double min, double max, PlotWidget::AxisStyle as, int minTics=10);
QString sciPrint(double value);

#endif // MISC_H
