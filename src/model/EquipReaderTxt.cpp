#include "EquipReaderTxt.h"

EquipReaderTxt::EquipReaderTxt(QString filename)
    : EquipReader(filename)
{
}

void EquipReaderTxt::read(QString filename)
{
    QFile file(filename);
}

QString EquipReaderTxt::parsePiece(QString lineBuffer, QString slot)
{
    //parse using regex :D
    QRegExp regex("^input /equip \"??([^\"]+)\"?? \"([^\"]+)\"$");
    //if our line is an equipment line
    if (regex.indexIn(lineBuffer)) {
        //set the gear
    }
    else {
        //add it to extra data
    }
}

/**
 * Equips itemName to the location slot of the Equip object
 */
void EquipReaderTxt::equip(QString location, QString itemName)
{

}
