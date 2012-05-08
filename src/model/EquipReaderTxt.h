#ifndef EQUIPREADERTXT_H
#define EQUIPREADERTXT_H

#include "EquipReader.h"

class EquipReaderTxt : public EquipReader
{
    public:

        EquipReaderTxt(QString filename);
        void read(QString filename);

    private:

        bool parsePiece(const QString &lineBuffer);
};


#endif
