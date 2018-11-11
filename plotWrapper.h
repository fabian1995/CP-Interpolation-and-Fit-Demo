/* 
 * File:   plotWrapper.h
 * Author: fabian
 *
 * Created on 28. Oktober 2018, 11:01
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

