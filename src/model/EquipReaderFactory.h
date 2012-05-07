#ifndef EQUIPREADERFACTORY_H
#define EQUIPREADERFACTORY_H

#include <QtCore>
#include "EquipReader.h"
#include "EquipReaderTxt.h"

class EquipReaderFactory
{
    public:
        EquipReaderFactory(void);

        static EquipReader *createReader(QString filename);

    private:
        /* data */
};


#endif
