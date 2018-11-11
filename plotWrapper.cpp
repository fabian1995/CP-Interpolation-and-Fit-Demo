#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

#include "plotWrapper.h"
#include "plotwidget.h"
#include "plotDataModel.h"

/**
 * @param functionPlot Pointer to PlotWidget for function plots
 * @param errorPlot Pointer to PlotWidget for error plots
 * @param selector Pointer to ComboBox (drop-down menu) for selecting the Plot Collection
 * @param eqSpace Placeholder for Plot Collection image
 * @param eqLabel Label for Plot Collection image
 */
PlotWrapper::PlotWrapper(PlotWidget* functionPlot, PlotWidget* errorPlot, QComboBox* selector, QWidget* eqSpace, QLabel* eqLabel) {
    this->functionPlot = functionPlot;
    this->errorPlot = errorPlot;
    this->selector = selector;
    this->eqSpace = eqSpace;
    this->eqLabel = eqLabel;
    this->currentIndex = -1;
}

/**
 * Add a Plot Collection to the selection.
 * @param model Pointer to the new Plot Collection
 */
void PlotWrapper::addDataModel(PlotCollectionModel* model) {
    dataCollections.append(model);
    selector->addItem(model->getName());
    if(dataCollections.length()==1)
        this->plot(model->getName());
}

/**
 * Set the plot collection to be displayed
 * @param name Display name of the plot collection
 */
void PlotWrapper::plot(QString name) {
    for (int i = 0; i < dataCollections.size(); i++) {
        if (name == dataCollections[i]->getName()) {
            functionPlot->clear();
            errorPlot->clear();
            for (int j = 0; j < dataCollections[i]->plotModels.size(); j++) {
                functionPlot->plot(*(dataCollections[i]->plotModels[j]));
            }
            if (dataCollections[i]->errorModels.size() == 0) {
                errorPlot->hide();
            }
            else {
                for (int j = 0; j < dataCollections[i]->errorModels.size(); j++) {
                    errorPlot->plot(*(dataCollections[i]->errorModels[j]));
                }
            }
            if (dataCollections[i]->getEqImagePath().isNull()) {
                eqSpace->hide();
            }
            else {
                eqSpace->show();
                eqLabel->setPixmap(QPixmap(dataCollections[i]->getEqImagePath()));
            }
            currentIndex = i;
            return;
        }
    }
}

/**
 * @return A pointer to the currently selected PlotCollection
 */
PlotCollectionModel* PlotWrapper::getCurrentDataModel() {
    if (currentIndex >= 0 && currentIndex < dataCollections.size())
        return dataCollections[currentIndex];
    return nullptr;
}
    
/**
 * Remove all Plot Collections and clear PlotWidgets
 */
void PlotWrapper::clear() {
    dataCollections.clear();
    functionPlot->clear();
    errorPlot->clear();
    currentIndex = -1;
}