#include "EquipWriterTxt.h"

EquipWriterTxt::EquipWriterTxt(const Equip &e)
    : EquipWriter(e)
{

}

/**
 * Writes Equip data to file
 */
void EquipWriterTxt::write(const QString &filename)
{
    QFile outFile(filename);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Unable to open file for writing: " << filename;
        return;
    }

    QTextStream outStream(&outFile);
    outStream << this->text();
}

/**
 * Generates Equip data output returns it as a string.
 */
QString EquipWriterTxt::text(void) const
{
    QString output;
    QTextStream outStream(&output);

    QList< QPair<QString, QString> > gear = m_equip->getEquipment();

    for (int i = 0; i < gear.count(); i++) {
        if (i % 4 == 0)
            outStream << '\n';
        if (!gear[i].second.isEmpty()) {
            outStream << "input /equip " << gear[i].first << " \"" << gear[i].second << "\"\n";
        }
    }
    if (!m_equip->getExtraData().isEmpty()) {
        outStream << '\n' << m_equip->getExtraData();
    }

    return output;
}
