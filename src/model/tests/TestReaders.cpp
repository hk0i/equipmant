#include <QtTest/QtTest>
#include "../Equip.h"
#include "../EquipReaderFactory.h"

#define TESTPATH "../../../test_suite"

class TestReaders : public QObject
{
    Q_OBJECT

public:

    TestReaders() {}

private slots:

    void initTestCase()
    {
        m_reader = EquipReaderFactory::createReader(
            QString(TESTPATH "/1.equip")
        );
        m_equip = m_reader->getEquip();
    }

    void cleanupTestCase()
    {
        if (m_reader)
            delete m_reader;
    }

    void testReaderGetHead()
    {
        QCOMPARE(m_equip->get(Equip::Head), QString("5"));
    }

    void testReaderGetLRing()
    {
        QCOMPARE(m_equip->get(Equip::LRing), QString("11"));
    }

private:

    EquipReader *m_reader;
    Equip *m_equip;
};

QTEST_APPLESS_MAIN(TestReaders)
#include "TestReaders.moc"
