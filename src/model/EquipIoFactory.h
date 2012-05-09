#ifndef EQUIPIOFACTORY_H
#define EQUIPIOFACTORY_H

#include <QtCore>
#include "EquipReader.h"
#include "EquipWriter.h"

#include "EquipReaderTxt.h"
#include "EquipWriterTxt.h"

/**
 * Handles the creation of all Equipmant I/O classes
 */
class EquipIoFactory
{
    public:
        EquipIoFactory(void);

        static EquipReader *createReader(QString filename);
        static EquipWriter *createWriter(
            const QString &filename,
            const Equip &e
        );

    private:
        /* data */
};


#endif
