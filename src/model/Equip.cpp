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
    cleanSlot.remove(QRegExp("\\W"));

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
    cleanSlot.remove(QRegExp("\\W"));
    int i = QENUM_VALUECI(Equip, Slot, cleanSlot);
    if (i == -1)
        return "EQ_FALSE";
    return m_slots[(Slot) i];
}

void Equip::setExtraData(const QString &data)
{
    m_extra_data = data;
}

QString Equip::getExtraData(void) const
{
    return m_extra_data;
}

/**
 * Returns true when no equipment or extra data is stored in object
 */
bool Equip::isEmpty(void) const
{
    if (m_slots.isEmpty() && m_extra_data.isEmpty()) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Converts the slot's enum value into a string, inserting proper punctuation
 * when necessary
 *
 * @example:
 *  Main = "Main"
 *  LEar = "L.Ear"
 *  REar = "R.Ear"
 */
QString Equip::slotName(Slot slot) const
{
    QString returnSlot = Equip::staticMetaObject.enumerator(Main).key(slot);
    returnSlot.replace(QRegExp("([A-Z])([A-Z])"), "\\1.\\2");

    return returnSlot;
}

/**
 * Returns a list of all of the non-empty equipment slots and what equipment
 * they hold
 */
QList< QPair<QString, QString> > Equip::getEquipment(void) const
{
    QList< QPair<QString, QString> > gear;
    foreach (Slot slot, m_slots.keys()) {
        qDebug() << slotName(slot) << m_slots[slot];
        gear.append(qMakePair(slotName(slot), m_slots[slot]));
        // gear[slotName(slot)] = m_slots[slot];
    }

    return gear;
}
