#include "plotWrapper.h"

#include "plotwidget.h"
#include "plotDataModel.h"

PlotWrapper::PlotWrapper(PlotWidget* plotWidget, QComboBox* selector) {
    this->plotWidget = plotWidget;
    this->selector = selector;
}

void PlotWrapper::addDataModel(PlotDataModel* model) {
    dataModels.append(model);
    selector->addItem(model->getPlotLabel());
    if(dataModels.length()==1)
        this->plot(model->getPlotLabel());
}

void PlotWrapper::plot(QString name) {
    for (int i = 0; i < dataModels.size(); i++) {
        if (name == dataModels[i]->getPlotLabel()) {
            plotWidget->clear();
            plotWidget->plot(*(dataModels[i]));
        }
    }
}
    
void PlotWrapper::clear() {
    dataModels.clear();
    plotWidget->clear();
}