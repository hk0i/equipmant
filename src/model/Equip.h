#ifndef EQUIP_H
#define EQUIP_H

#include <QtCore>

class Equip
{
    public:
        Equip(void);
        virtual ~Equip(void);

        //setters
        void setMain(QString item);
        void setSub(QString item);
        void setRange(QString item);
        void setAmmo(QString item);

        void setHead(QString item);
        void setNeck(QString item);
        void setLEar(QString item);
        void setREar(QString item);

        void setBody(QString item);
        void setHands(QString item);
        void setLRing(QString item);
        void setRRing(QString item);

        void setBack(QString item);
        void setWaist(QString item);
        void setLegs(QString item);
        void setFeet(QString item);

        //getters
        QString getMain(void);
        QString getSub(void);
        QString getRange(void);
        QString getAmmo(void);

        QString getHead(void);
        QString getNeck(void);
        QString getLEar(void);
        QString getREar(void);

        QString getBody(void);
        QString getHands(void);
        QString getLRing(void);
        QString getRRing(void);

        QString getBack(void);
        QString getWaist(void);
        QString getLegs(void);
        QString getFeet(void);

    private:

        QString m_main;
        QString m_sub;
        QString m_range;
        QString m_ammo;

        QString m_head;
        QString m_neck;
        QString m_l_ear;
        QString m_r_ear;

        QString m_body;
        QString m_hands;
        QString m_l_ring;
        QString m_r_ring;

        QString m_back;
        QString m_waist;
        QString m_legs;
        QString m_feet;
};


#endif
