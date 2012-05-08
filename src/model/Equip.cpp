#include "Equip.h"

Equip::Equip(void)
{

}

Equip::~Equip(void)
{

}

bool Equip::set(const QString &slot, QString item)
{
    int i = QENUM_VALUECI(Equip, Slot, slot);
    if (i == -1)
        return false;
    set((Slot) i, item);
    return true;
}

void Equip::set(Slot slot, const QString &item)
{
    m_slots[slot] = item;
}

QString Equip::get(Slot slot) const { return m_slots[slot]; }
QString Equip::get(const QString &slot)
{
    int i = QENUM_VALUECI(Equip, Slot, slot);
    if (i == -1)
        return "EQ_FALSE";
    return m_slots[(Slot) i];
}
