#ifndef EQUIPWRITER_H
#define EQUIPWRITER_H

#include <QtCore>
#include "Equip.h"

class EquipWriter
{
    public:
        EquipWriter(const Equip &e);

        virtual void write(const QString &filename) = 0;

    protected:
        const Equip *m_equip;
};


#endif
