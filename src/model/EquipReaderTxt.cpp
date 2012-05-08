#include "EquipReaderTxt.h"

EquipReaderTxt::EquipReaderTxt(QString filename)
    : EquipReader(filename)
{
    read(filename);
}

void EquipReaderTxt::read(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
        // qDebug() << "hello";
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        parsePiece(line);
    }
}

QString EquipReaderTxt::parsePiece(const QString &lineBuffer)
{
    //parse using regex :D
    QRegExp regex("input /equip (.+) \"(.+)\"",
            Qt::CaseInsensitive
    );
    //if our line is an equipment line
    int i = regex.indexIn(lineBuffer);
    // qDebug() << "i: " << i;
    if (i >= 0) {
        //set the gear
        // qDebug() << "Capped: " << regex.captureCount();
        qDebug() << regex.cap(1) << regex.cap(2);
        m_equip->set(regex.cap(1), regex.cap(2));
    }
    else {
        //add it to extra data
    }
}

/**
 * Equips itemName to the location slot of the Equip object
 */
void EquipReaderTxt::equip(QString location, QString itemName)
{

}
