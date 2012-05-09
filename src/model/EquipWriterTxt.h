#ifndef EQUIPWRITERTXT_H
#define EQUIPWRITERTXT_H

#include <QtCore>
#include "EquipWriter.h"

class EquipWriterTxt : public EquipWriter
{
    public:
        EquipWriterTxt(const Equip &e);
        void write(const QString &filename);

    private:
        /* data */
};


#endif
