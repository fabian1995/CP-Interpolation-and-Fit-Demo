#include "plotWrapper.h"

#include "plotwidget.h"
#include "plotDataModel.h"

PlotWrapper::PlotWrapper(PlotWidget* functionPlot, PlotWidget* errorPlot, QComboBox* selector) {
    this->functionPlot = functionPlot;
    this->errorPlot = errorPlot;
    this->selector = selector;
    this->currentIndex = -1;
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
            functionPlot->clear();
            errorPlot->clear();
            for (int j = 0; j < dataCollections[i]->plotModels.size(); j++) {
                functionPlot->plot(*(dataCollections[i]->plotModels[j]));
            }
            if (dataCollections[i]->errorModels.size() == 0)
                errorPlot->hide();
            else {
                for (int j = 0; j < dataCollections[i]->errorModels.size(); j++) {
                    errorPlot->plot(*(dataCollections[i]->errorModels[j]));
                }
            }
            currentIndex = i;
            return;
        }
    }
}

InterpolationModel* PlotWrapper::getCurrentDataModel() {
    if (currentIndex >= 0 && currentIndex < dataCollections.size())
        return dataCollections[currentIndex];
    return nullptr;
}
    
void PlotWrapper::clear() {
    dataCollections.clear();
    functionPlot->clear();
    errorPlot->clear();
    currentIndex = -1;
}