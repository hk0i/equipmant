#ifndef EQUIPIOFACTORY_H
#define EQUIPIOFACTORY_H

#include <QtCore>
#include "EquipReader.h"
#include "EquipReaderTxt.h"

/**
 * Handles the creation of all Equipmant I/O classes
 */
class EquipIoFactory
{
    public:
        EquipIoFactory(void);

        static EquipReader *createReader(QString filename);
        // static EquipWriter *createWriter(QString filename);

    private:
        /* data */
};


#endif
