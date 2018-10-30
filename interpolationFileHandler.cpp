#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "interpolationFileHandler.h"
#include "plotCollectionModel.h"
#include "plotWrapper.h"

InterpolationFileHandler::InterpolationFileHandler(PlotWrapper* plotWrapper) {
    this->plotWrapper = plotWrapper;
}


void InterpolationFileHandler::saveCurrentFunctions() {
    PlotCollectionModel* model = this->plotWrapper->getCurrentDataModel();
    
    QString fileName = QFileDialog::getSaveFileName(nullptr,
        tr("Save current functions"), model->getName() + ".csv",
        tr("Comma Separated Values File (*.csv)"));
    
    if (fileName.isEmpty())
        return;
    
    std::cout << "File chosen: "  << fileName.toUtf8().constData() << std::endl;
    
    std::ofstream oFile;
    oFile.open (fileName.toUtf8().constData());
    
    if (!oFile.is_open()) {
        QMessageBox::information(nullptr, "Error", "Can not open the selected file");
        return;
    }
    
    if (model->plotModels.size() >= 1)
        oFile << "x raw data," << "y raw data";
    else
        return;
    
    if (model->plotModels.size() > 1)
        oFile << ",x functions";
    for (int j = 1; j < model->plotModels.size(); j++) {
        oFile << "," << model->plotModels[j]->getPlotLabel().toUtf8().constData();
    }
    for (int j = 0; j < model->errorModels.size(); j++) {
        oFile << "," << model->errorModels[j]->getPlotLabel().toUtf8().constData();
    }
        
    oFile << std::endl;
    
    int maxSizeRaw = model->plotModels[0]->getXData().size();
    int maxSize = model->plotModels.size() >= 1 ? model->plotModels[1]->getXData().size() : maxSizeRaw;
    
    for (int i = 0; i < maxSize; i++) {
        if (i < maxSizeRaw)
            oFile << model->plotModels[0]->getXData()[i] << "," << model->plotModels[0]->getYData()[i];
        else
            oFile << ",";
        
        if (model->plotModels.size() > 1)
            oFile << "," << model->plotModels[1]->getXData()[i];
        
        for (int j = 1; j < model->plotModels.size(); j++) {
            oFile << "," << model->plotModels[j]->getYData()[i];
        }
        for (int j = 0; j < model->errorModels.size(); j++) {
            oFile << "," << model->errorModels[j]->getYData()[i];
        }
        oFile << std::endl;
    }
    oFile.close();
}
