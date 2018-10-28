#include "plotWrapper.h"

#include "plotwidget.h"
#include "plotDataModel.h"

PlotWrapper::PlotWrapper(PlotWidget* plotWidget) {
    this->plotWidget = plotWidget;
}

void PlotWrapper::addDataModel(PlotDataModel* model) {
    dataModels.append(model);
}

void PlotWrapper::plot() {
    plotWidget->plot(*(dataModels[0]));
}
    
void PlotWrapper::clear() {
    dataModels.clear();
    plotWidget->clear();
}