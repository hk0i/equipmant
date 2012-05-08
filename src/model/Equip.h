#ifndef EQUIP_H
#define EQUIP_H

#include <QtCore>
#define QENUM_VALUECI(o,e,k) (enum_value(o::staticMetaObject.enumerator(o::staticMetaObject.indexOfEnumerator(#e)),k,Qt::CaseInsensitive))

class Equip : public QObject
{
    Q_OBJECT

    public:
        enum Slot {
            Main,
            Sub,
            Range,
            Ammo,

            Head,
            Neck,
            LEar,
            REar,

            Body,
            Hands,
            LRing,
            RRing,

            Back,
            Waist,
            Legs,
            Feet
        };

        Q_ENUMS(Slot)

        inline int enum_value(const QMetaEnum & e,
            const QString & key, Qt::CaseSensitivity s)
        {
            for (int i=0; i < e.keyCount(); i++) {
                if (QString(key).compare(e.key(i), s) == 0)
                    return e.value(i);
            }
            return -1;
        }

        Equip(void);
        virtual ~Equip(void);

        //setters
        bool set(const QString &slot, QString item);
        void set(Slot slot, const QString &item);

        //getters
        QString get(Slot) const;
        QString get(const QString &slot);

    private:

        QMap <Slot, QString> m_slots;

};


#endif
