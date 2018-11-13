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

#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QVector>

#include "plotDataModel.h"

class PlotWidget : public QWidget
{
	Q_OBJECT
public:
    enum AxisStyle {LINEAR = 0, LOG = 1};

    explicit PlotWidget(QWidget *parent = 0, AxisStyle xStyle = AxisStyle::LINEAR, AxisStyle yStyle = AxisStyle::LINEAR);
        
    void setPlotTitle(QString plotTitle);
	
signals:
	
public slots:
    void plot(PlotDataModel model);
    
    void clear();
	
private:
    void paintEvent(QPaintEvent * event);

    QPoint real2pixel(double x, double y);

    QVector<PlotDataModel> models;

    double minX, maxX, minY, maxY;
    
    QString plotTitle;

    AxisStyle xStyle, yStyle;

    //double scaleX, scaleY;
    bool isoView;
    bool isInitialized;
};

#endif // PLOTWIDGET_H
