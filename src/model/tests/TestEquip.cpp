#include <QtTest/QtTest>
#include "../Equip.h"

class TestEquip : public QObject
{
    Q_OBJECT

public:

    TestEquip() {}

private slots:

    void initTestCase()
    {
        m_equip = new Equip();
    }

    void cleanupTestCase()
    {
        if (m_equip)
            delete m_equip;
    }

    //getter/setter using enum
    void testSetGetEnum()
    {
        m_equip->set(Equip::Main, "Dagger");
        QCOMPARE(m_equip->get(Equip::Main), QString("Dagger"));
    }

    void testSetStringGetEnum()
    {
        m_equip->set("sub", "Shield");
        QCOMPARE(m_equip->get(Equip::Sub), QString("Shield"));
    }

    void testSetStringGetString()
    {
        m_equip->set("hands", "Gloves");
        QCOMPARE(m_equip->get("hands"), QString("Gloves"));
    }

    void testSetBadString()
    {
        m_equip->set("ringfinger", "Diamond Ring");
        QCOMPARE(m_equip->get("ringfinger"), QString("EQ_FALSE"));
    }



private:

    Equip *m_equip;

};

// QTEST_APPLESS_MAIN(TestEquip)
// #include "TestEquip.moc"
