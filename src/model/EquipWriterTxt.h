#ifndef EQUIPWRITERTXT_H
#define EQUIPWRITERTXT_H

#include <QtCore>
#include "EquipWriter.h"
#include "../equipmant.h"

class EquipWriterTxt : public EquipWriter
{
    public:
        EquipWriterTxt(const Equip &e);
        void write(const QString &filename);
        QString text(void) const;

    private:
        /* data */
};


#endif
