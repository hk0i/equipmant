#include "EquipReaderFactory.h"

EquipReader *EquipReaderFactory::createReader(QString filename)
{
    QFileInfo fileInfo(filename);
    if (fileInfo.suffix() == "txt" || fileInfo.suffix() == "equip")
        return new EquipReaderTxt(filename);
}
