#include "EquipWriterTxt.h"

EquipWriterTxt::EquipWriterTxt(const Equip &e)
    : EquipWriter(e)
{

}

void EquipWriterTxt::write(const QString &filename)
{
    QFile outFile(filename);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Unable to open file for writing: " << filename;
        return;
    }

    QTextStream outStream(&outFile);

    QList< QPair<QString, QString> > gear = m_equip->getEquipment();
    for (int i = 0; i < gear.count(); i++) {
        if (i % 4 == 0)
            outStream << '\n';
        outStream << "input /equip " << gear[i].first << " \"" << gear[i].second << "\"\n";
    }
}
