#include "plotWrapper.h"

#include "plotwidget.h"
#include "plotDataModel.h"

PlotWrapper::PlotWrapper(PlotWidget* plotWidget, QComboBox* selector) {
    this->plotWidget = plotWidget;
    this->selector = selector;
}

void PlotWrapper::addDataModel(InterpolationModel* model) {
    dataCollections.append(model);
    selector->addItem(model->getName());
    if(dataCollections.length()==1)
        this->plot(model->getName());
}

void PlotWrapper::plot(QString name) {
    for (int i = 0; i < dataCollections.size(); i++) {
        if (name == dataCollections[i]->getName()) {
            plotWidget->clear();
            for (int j = 0; j < dataCollections[i]->plotModels.size(); j++) {
                plotWidget->plot(*(dataCollections[i]->plotModels[j]));
            }
            return;
            //lotWidget->plot(*(dataModels[i]));
        }
    }
}
    
void PlotWrapper::clear() {
    dataCollections.clear();
    plotWidget->clear();
}