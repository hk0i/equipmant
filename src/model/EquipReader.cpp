#include "EquipReader.h"

EquipReader::EquipReader(QString filename)
{
    m_equip = new Equip();
}

EquipReader::~EquipReader(void)
{
    // if (m_equip)
        // delete m_equip;
}

Equip *EquipReader::getEquip(void)
{
    return m_equip;
}
