#include <QtTest/QtTest>
#include "../Equip.h"
#include "../EquipIoFactory.h"

#define TESTPATH "../../../test_suite"

class TestReaders : public QObject
{
    Q_OBJECT

public:
    TestReaders() {}

private slots:
    void initTestCase()
    {
        m_reader = EquipIoFactory::createReader(
            QString(TESTPATH "/1.equip")
        );
        m_equip = m_reader->getEquip();

        m_writer = EquipIoFactory::createWriter(
            "equip",
            *m_equip
        );

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

    void testExtraData()
    {
        qDebug() << m_equip->getExtraData();
        QCOMPARE(m_equip->getExtraData(), QString("//this suite illustrates files open properly\n"));
    }

    void testWriterEquipFile()
    {
        m_writer->write(QString(TESTPATH "/output-test.equip"));
    }

private:

    EquipReader *m_reader;
    EquipWriter *m_writer;
    Equip *m_equip;
};

QTEST_APPLESS_MAIN(TestReaders)
#include "TestReaders.moc"
