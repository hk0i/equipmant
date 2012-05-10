#include "imp_equiptab.h"


void equipTab::clearFields(void)
{
    txtMain->clear();
    txtSub->clear();
    txtRanged->clear();
    txtAmmo->clear();

    txtHead->clear();
    txtNeck->clear();
    txtLEar->clear();
    txtREar->clear();

    txtBody->clear();
    txtHands->clear();
    txtLRing->clear();
    txtRRing->clear();

    txtBack->clear();
    txtWaist->clear();
    txtLegs->clear();
    txtFeet->clear();

    txtExtraData->clear();
    txtTextMode->clear();

    viewModeChanged(swView->currentIndex());

}

void equipTab::viewModeChanged(int newPage)
{
    updateModel();

    //need to figure out a better way to handle this,
    //removing the preview tab all together may be a possibility since I don't
    //even know if it's being used.
    QFileInfo fi(myCurrentFile);
    QString ext = fi.suffix();
    //use text as default extension in case no format is specified (i.e., new
    //unsaved files)
    if (ext.isEmpty()) {
        ext = "txt";
    }
    EquipWriter *w = EquipIoFactory::createWriter(
        ext,
        *myEquip
    );

    //always check for a writer!!
    if (w) {
        txtTextMode->setText(w->text());
    }
    else {
        txtTextMode->setText("WriterError: No writer available");
    }

}

void equipTab::readFile(QString fileName)
{
    EquipReader *reader = EquipIoFactory::createReader(fileName);
    if (myEquip) {
        delete myEquip;
    }

    myCurrentFile = fileName;
    myEquip = reader->getEquip();
    updateUi();
}

void equipTab::updateUi(void)
{
    txtMain->setText(myEquip->get(Equip::Main));
    txtSub->setText(myEquip->get(Equip::Sub));
    txtRanged->setText(myEquip->get(Equip::Range));
    txtAmmo->setText(myEquip->get(Equip::Ammo));

    txtHead->setText(myEquip->get(Equip::Head));
    txtNeck->setText(myEquip->get(Equip::Neck));
    txtLEar->setText(myEquip->get(Equip::LEar));
    txtREar->setText(myEquip->get(Equip::REar));

    txtBody->setText(myEquip->get(Equip::Body));
    txtHands->setText(myEquip->get(Equip::Hands));
    txtLRing->setText(myEquip->get(Equip::LRing));
    txtRRing->setText(myEquip->get(Equip::RRing));

    txtBack->setText(myEquip->get(Equip::Back));
    txtWaist->setText(myEquip->get(Equip::Waist));
    txtLegs->setText(myEquip->get(Equip::Legs));
    txtFeet->setText(myEquip->get(Equip::Feet));

    txtExtraData->setText(myEquip->getExtraData());
}

void equipTab::updateModel(void)
{
    myEquip->set(Equip::Main, txtMain->text());
    myEquip->set(Equip::Sub, txtSub->text());
    myEquip->set(Equip::Range, txtRanged->text());
    myEquip->set(Equip::Ammo, txtAmmo->text());

    myEquip->set(Equip::Head, txtHead->text());
    myEquip->set(Equip::Neck, txtNeck->text());
    myEquip->set(Equip::LEar, txtLEar->text());
    myEquip->set(Equip::REar, txtREar->text());

    myEquip->set(Equip::Body, txtBody->text());
    myEquip->set(Equip::Hands, txtHands->text());
    myEquip->set(Equip::LRing, txtLRing->text());
    myEquip->set(Equip::RRing, txtRRing->text());

    myEquip->set(Equip::Back, txtBack->text());
    myEquip->set(Equip::Waist, txtWaist->text());
    myEquip->set(Equip::Legs, txtLegs->text());
    myEquip->set(Equip::Feet, txtFeet->text());

    myEquip->setExtraData(txtExtraData->toPlainText());
}

// extra data widgets
void equipTab::addToBin_clicked(void)
{
    QString str;
    QTextStream qts(&str);
    bool ok = false;    //dummy variable used for dialog and commands
    int mult = 1;        //timeout multiplier

    if (cmbExtraType->currentIndex() == 0)
    {
        addToDataBin("input ");

        switch (cmbExtraCommand->currentIndex())
        {
            case 0:
            default:
                str = "/ja ";
                break;

            case 1:
                str = "/ma ";
                break;

            case 2:
                str = "/echo ";
                break;

            case 3:
                str = "/party ";
                break;

            case 4:
                str = "/linkshell ";
                break;
        }

        if (cmbExtraCommand->currentIndex() <= 1)
            ok = true;
        if (ok)    str += '"';
        str += cmbExtraParam->currentText();
        if (ok)    str += "\" " + cmbExtraTarget->currentText();
        str    += "\r\n";
        addToDataBin(str);
    }
    else
    {
        if (spnTimeout->value() > 0) {
            switch (cmbTimetype->currentIndex())
            {


                case 1:
                    mult = 60;
                    break;

                case 2:
                    mult = 60*60;
                    break;

                case 0:
                default:
                    mult = 1;
                    break;
            }

            qts << "pause " << (spnTimeout->value() * mult) << "\r\n";
            addToDataBin(str);
        }
        else {
            int ret = QMessageBox::warning(this,tr("No timeout specified!"),
                    tr("No pause time specified.\nNo changes have been made."),
                    QMessageBox::Ok);

        }
    }
}

void equipTab::extraCmd_changed(int newIndex)
{
    if (newIndex > 1)
        cmbExtraTarget->setHidden(true);
    else
        cmbExtraTarget->setVisible(true);
}

void equipTab::addToDataBin(QString textToAdd)
{
    txtExtraData->setText(txtExtraData->toPlainText() + textToAdd);
}

QString equipTab::getCurrentFile(void)
{
    return myCurrentFile;
}

void equipTab::setCurrentFile(QString newFile)
{
    myCurrentFile = newFile;
    updateTitle();
}

void equipTab::updateTitle(void)
{
    //figure out how to update the tab title from here.
}

void equipTab::writeFile(QString filename)
{
    updateModel();

    QFileInfo fileInfo(filename);
    QString ext = fileInfo.suffix();
    EquipWriter *writer = EquipIoFactory::createWriter(ext, *myEquip);

    if (writer) {
        writer->write(filename);
    }
    else {
        qCritical() << "Could not find an appropriate writer for extension: " << ext;
    }
}
