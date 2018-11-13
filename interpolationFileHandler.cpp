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
