#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QObject>
#include "backenddatadto.h"

class GuiHandler
{
    Q_OBJECT
signals:

public:
    GuiHandler(){};
    GuiHandler(const BackendDataDto& dto);
public slots:

private:

private:

};

#endif // GUIHANDLER_H
