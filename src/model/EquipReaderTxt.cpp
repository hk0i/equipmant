#include "EquipReaderTxt.h"

EquipReaderTxt::EquipReaderTxt(QString filename)
    : EquipReader(filename)
{
    read(filename);
}

/** * Reads text file
 */
void EquipReaderTxt::read(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Unable to open file for reading: " << filename;
        return;
    }

    QTextStream in(&file);
    QString line;
    QString extraData;
    while (!in.atEnd()) {
        line = in.readLine();
        if (!parsePiece(line) && !line.isEmpty()) {
            extraData += line + '\n';
        }
    }

    if (!extraData.isEmpty()) {
        m_equip->setExtraData(extraData);
    }
}

/**
 * Attempts to parse an input /equip line.
 * Returns false on failure, true on success
 */
bool EquipReaderTxt::parsePiece(const QString &lineBuffer)
{
    //parse using regex :D
    QRegExp regex(
        "input /equip (.+) \"(.+)\"",
        Qt::CaseInsensitive
    );

    QString extraData; //store unparsed data in here
    int i = regex.indexIn(lineBuffer);
    //if our line is an equipment line
    if (i >= 0) {
        m_equip->set(regex.cap(1), regex.cap(2));
        return true;
    }

    //check for version line and eat it up.
    QRegExp versionLine(
        "^//(Equipmant Script File|Get your copy)",
        Qt::CaseInsensitive
    );
    if (versionLine.indexIn(lineBuffer) >= 0)
        return true;

    //parse failure, return false
    return false;
}
