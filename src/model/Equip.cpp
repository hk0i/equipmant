#include "Equip.h"

Equip::Equip(void)
{

}

Equip::~Equip(void)
{

}

bool Equip::set(const QString &slot, QString item)
{
    QString cleanSlot = slot;
    cleanSlot.remove('.');

    int i = QENUM_VALUECI(Equip,
        Slot,
        cleanSlot
    );
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
    QString cleanSlot = slot;
    cleanSlot.remove('.');
    int i = QENUM_VALUECI(Equip, Slot, cleanSlot);
    if (i == -1)
        return "EQ_FALSE";
    return m_slots[(Slot) i];
}
