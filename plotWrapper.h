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

#ifndef PLOTWRAPPER_H
#define PLOTWRAPPER_H

#include <QComboBox>
#include <QLabel>

#include "plotDataModel.h"
#include "plotwidget.h"
#include "plotCollectionModel.h"


/**
 * Controller class for selecting the Plot Collection to be displayed.
 * @see PlotCollectionModel
 * @see PlotWidget
 */
class PlotWrapper : public QObject {
    Q_OBJECT
public:
    PlotWrapper(PlotWidget* functionPlot, PlotWidget* errorPlot, QComboBox* selector, QWidget* eqSpace, QLabel* eqLabel, QLabel* eqCaption);
    
    void addDataModel(PlotCollectionModel* model);
    
    void clear();
    
    PlotCollectionModel* getCurrentDataModel();

public slots:
    void plot(QString name);
    
private:
    /** PlotWidget for function and interpolation plots */
    PlotWidget* functionPlot;
    
    /** PlotWidget for error Plots */
    PlotWidget* errorPlot;
    
    /** Placeholder for the PlotCollection image */
    QWidget* eqSpace;
    
    /** Label for the PlotCollection image pixmap */
    QLabel* eqLabel;
    
    /** Caption label for the PlotCollection image */
    QLabel* eqCaption;
    
    /** Combo box to select the PlotCollection */
    QComboBox* selector;
    
    /** List of available PlotCollections */
    QVector<PlotCollectionModel*> dataCollections;
    
    /** Index of currently selected (and displayed) PlotCollection */
    int currentIndex;
};

#endif /* PLOTWRAPPER_H */

