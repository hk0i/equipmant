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

    //getter/setter row 1
    void testSetGetMain()
    {
        m_equip->setMain("Dagger");
        QCOMPARE(m_equip->getMain(), QString("Dagger"));
    }

    void testSetGetSub()
    {
        m_equip->setSub("Shield");
        QCOMPARE(m_equip->getSub(), QString("Shield"));
    }

    void testSetGetRange()
    {
        m_equip->setRange("Bow");
        QCOMPARE(m_equip->getRange(), QString("Bow"));
    }

    void testSetGetAmmo()
    {
        m_equip->setAmmo("Arrow");
        QCOMPARE(m_equip->getAmmo(), QString("Arrow"));
    }


    //getter/setter row 2
    void testSetGetHead()
    {
        m_equip->setHead("Helmet");
        QCOMPARE(m_equip->getHead(), QString("Helmet"));
    }
    void testSetGetNeck()
    {
        m_equip->setNeck("Necklace");
        QCOMPARE(m_equip->getNeck(), QString("Necklace"));
    }
    void testSetGetLEar()
    {
        m_equip->setLEar("Earring");
        QCOMPARE(m_equip->getLEar(), QString("Earring"));
    }
    void testSetGetREar()
    {
        m_equip->setREar("Earring");
        QCOMPARE(m_equip->getREar(), QString("Earring"));
    }


    //getter/setter row 3
    void testSetGetBody()
    {
        m_equip->setBody("Body");
        QCOMPARE(m_equip->getBody(), QString("Body"));
    }
    void testSetGetHands()
    {
        m_equip->setHands("Hands");
        QCOMPARE(m_equip->getHands(), QString("Hands"));
    }
    void testSetGetLRing()
    {
        m_equip->setLRing("LRing");
        QCOMPARE(m_equip->getLRing(), QString("LRing"));
    }
    void testSetGetRRing()
    {
        m_equip->setRRing("RRing");
        QCOMPARE(m_equip->getRRing(), QString("RRing"));
    }


    //getter/setter row 4
    void testSetGetBack()
    {
        m_equip->setBack("Back");
        QCOMPARE(m_equip->getBack(), QString("Back"));
    }
    void testSetGetWaist()
    {
        m_equip->setWaist("Waist");
        QCOMPARE(m_equip->getWaist(), QString("Waist"));
    }
    void testSetGetLegs()
    {
        m_equip->setLegs("Legs");
        QCOMPARE(m_equip->getLegs(), QString("Legs"));
    }
    void testSetGetFeet()
    {
        m_equip->setFeet("Feet");
        QCOMPARE(m_equip->getFeet(), QString("Feet"));
    }

private:
    Equip *m_equip;

};

QTEST_MAIN(TestEquip)
#include "TestEquip.moc"
