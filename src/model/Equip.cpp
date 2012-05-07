#include "Equip.h"

Equip::Equip(void)
{

}

Equip::~Equip(void)
{

}

//setters
void Equip::setMain(QString item) { m_main = item; }
void Equip::setSub(QString item) { m_sub = item; }
void Equip::setRange(QString item) { m_range = item; }
void Equip::setAmmo(QString item) { m_ammo = item; }

void Equip::setHead(QString item) { m_head = item; }
void Equip::setNeck(QString item) { m_neck = item; }
void Equip::setLEar(QString item) { m_l_ear = item; }
void Equip::setREar(QString item) { m_r_ear = item; }

void Equip::setBody(QString item) { m_body = item; }
void Equip::setHands(QString item) { m_hands = item; }
void Equip::setLRing(QString item) { m_l_ring = item; }
void Equip::setRRing(QString item) { m_r_ring = item; }

void Equip::setBack(QString item) { m_back = item; }
void Equip::setWaist(QString item) { m_waist = item; }
void Equip::setLegs(QString item) { m_legs = item; }
void Equip::setFeet(QString item) { m_feet = item; }

//getters
QString Equip::getMain(void) { return m_main; }
QString Equip::getSub(void) { return m_sub; }
QString Equip::getRange(void) { return m_range; }
QString Equip::getAmmo(void) { return m_ammo; }

QString Equip::getHead(void) { return m_head; }
QString Equip::getNeck(void) { return m_neck; }
QString Equip::getLEar(void) { return m_l_ear; }
QString Equip::getREar(void) { return m_r_ear; }

QString Equip::getBody(void) { return m_body; }
QString Equip::getHands(void) { return m_hands; }
QString Equip::getLRing(void) { return m_l_ring; }
QString Equip::getRRing(void) { return m_r_ring; }

QString Equip::getBack(void) { return m_back; }
QString Equip::getWaist(void) { return m_waist; }
QString Equip::getLegs(void) { return m_legs; }
QString Equip::getFeet(void) { return m_feet; }
