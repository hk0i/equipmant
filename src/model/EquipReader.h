#ifndef EQUIPREADER_H
#define EQUIPREADER_H

#include <QtCore>
#include "Equip.h"

class EquipReader
{
    public:
        EquipReader(QString filename);
        ~EquipReader(void);

        virtual void read(QString filename) = 0;

        Equip *getEquip(void);

    protected:
        Equip *m_equip;
};


#endif
