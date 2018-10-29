/* 
 * File:   InterpolationFileHandler.h
 * Author: fabian
 *
 * Created on 29. Oktober 2018, 10:21
 */

#ifndef INTERPOLATIONFILEHANDLER_H
#define INTERPOLATIONFILEHANDLER_H

#include <QObject>
#include "plotWrapper.h"


class InterpolationFileHandler : public QObject {
    Q_OBJECT
public:
    InterpolationFileHandler(PlotWrapper* plotWrapper);
    
public slots:
    void saveCurrentFunctions();

private:
    PlotWrapper* plotWrapper;
};

#endif /* INTERPOLATIONFILEHANDLER_H */

