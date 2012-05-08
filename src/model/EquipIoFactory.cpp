#include "EquipIoFactory.h"

EquipReader *EquipIoFactory::createReader(QString filename)
{
    QFileInfo fileInfo(filename);
    if (fileInfo.suffix() == "txt" || fileInfo.suffix() == "equip")
        return new EquipReaderTxt(filename);
}

// EquipReader *EquipIoFactory::createWriter(QString filename)
// {
    // QFileInfo fileInfo(filename);
    // if (fileInfo.suffix() == "txt" || fileInfo.suffix() == "equip")
        // return new EquipReaderTxt(filename);
// }
