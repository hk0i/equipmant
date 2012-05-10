#include "EquipIoFactory.h"

/**
 * Creates the appropriate EquipReader based on the filename given
 */
EquipReader *EquipIoFactory::createReader(QString filename)
{
    QFileInfo fileInfo(filename);
    if (fileInfo.suffix() == "txt" || fileInfo.suffix() == "equip")
        return new EquipReaderTxt(filename);

    //return NULL if no reader can be found
    return NULL;
}

/**
 * Creates the appropriate EquipWriter based on the format provided
 */
EquipWriter *EquipIoFactory::createWriter(const QString &format, const Equip &e)
{
    if (format == "txt" || format == "equip")
        return new EquipWriterTxt(e);

    //return NULL if no writer can be found
    return NULL;
}
