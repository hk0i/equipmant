#ifndef EQUIPREADERTXT_H
#define EQUIPREADERTXT_H

#include "EquipReader.h"

class EquipReaderTxt : public EquipReader
{
    public:

        EquipReaderTxt(QString filename);
        void read(QString filename);

    private:

        QString parsePiece(QString lineBuffer, QString slot);
        void equip(QString location, QString itemName);


        /* data */
};


#endif
