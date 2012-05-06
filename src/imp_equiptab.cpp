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
    myExtraData = txtExtraData->toPlainText();
    txtTextMode->setText(generateText());
    if (newPage == 0)
    {
        /*myEditMode = "(Edit Mode)";
        updateTitle();*/
    }
    else
    {
        /*
        myEditMode = "(View Output)";
        updateTitle();*/
    }

}

QString equipTab::generateText(void)
{
    QString result;
    QTextStream strOut(&result);
    
    //windows line terminations \r\n (since FF is a PC/windows game)
    
    // if a text field is empty, it will write a commented line,
    // this line acts as a placeholder, to make the layout of the
    // files uniform. It is commented so that equipment won't be
    // removed from the macro.

    strOut << EQM_OPC1;    //Equipmant output comment1
    strOut << EQM_OPC2; //equipmant output comment2 - both are #defined in imp_equipmant.h

    if (txtMain->text().isEmpty())
        COMMENT
    strOut << "input /equip main \"" << txtMain->text() << "\"\r\n";

    if (txtSub->text().isEmpty())
        COMMENT
    strOut << "input /equip sub \"" << txtSub->text() << "\"\r\n";

    if (txtRanged->text().isEmpty())
        COMMENT
    strOut << "input /equip range \"" << txtRanged->text() << "\"\r\n";

    if (txtAmmo->text().isEmpty())
        COMMENT
    strOut << "input /equip ammo \"" << txtAmmo->text() << "\"\r\n";

    if (txtHead->text().isEmpty())
        COMMENT
    strOut << "input /equip head \"" << txtHead->text() << "\"\r\n";
    
    if (txtNeck->text().isEmpty())
        COMMENT
    strOut << "input /equip neck \"" << txtNeck->text() << "\"\r\n";
    
    if (txtLEar->text().isEmpty())
        COMMENT
    strOut << "input /equip L.Ear \"" << txtLEar->text() << "\"\r\n";
     
    if (txtREar->text().isEmpty())
        COMMENT
    strOut << "input /equip R.Ear \"" << txtREar->text() << "\"\r\n";

    if (txtBody->text().isEmpty())
        COMMENT
    strOut << "input /equip body \"" << txtBody->text() << "\"\r\n";
    
    if (txtHands->text().isEmpty())
        COMMENT
    strOut << "input /equip hands \"" << txtHands->text() << "\"\r\n";
    
    if (txtLRing->text().isEmpty())
        COMMENT
    strOut << "input /equip L.Ring \"" << txtLRing->text() << "\"\r\n";
    
    if (txtRRing->text().isEmpty())
        COMMENT
    strOut << "input /equip R.Ring \"" << txtRRing->text() << "\"\r\n";
    
    if (txtBack->text().isEmpty())
        COMMENT
    strOut << "input /equip back \"" << txtBack->text() << "\"\r\n";
    
    if (txtWaist->text().isEmpty())
        COMMENT
    strOut << "input /equip waist \"" << txtWaist->text() << "\"\r\n";
    
    if (txtLegs->text().isEmpty())
        COMMENT
    strOut << "input /equip legs \"" << txtLegs->text() << "\"\r\n";
    
    if (txtFeet->text().isEmpty())
        COMMENT
    strOut << "input /equip feet \"" << txtFeet->text() << "\"\r\n";
    
    //EXTRA DATA STUFF - added in 1.2.3
    myExtraData = txtExtraData->toPlainText();
    if (!myExtraData.isEmpty())
    {
        strOut << "\r\n" << EQM_EXTRADATA << myExtraData << "\r\n";
    }
    
    return result;
}

void equipTab::readFile(QString fileName)
{
    QFile inFile(fileName);
    if (!inFile.exists())
        return;
    inFile.open(QFile::ReadOnly);
    setCurrentFile(fileName);
    //set last file path
    //myLastFileDir = fileName.left(fileName.lastIndexOf('/'));
    //saveData();        //save data now, in case of a program crash ;D



    //clear fields to prove test cases.
    clearFields();

    //clear textmode area.
    txtTextMode->clear();

    char buff[1024];
    QString tmp;
    QString parseCheck;    //used to check for Left/Right equips. i.e., if file contains
                        // L.Ring or ring1 etc..
    qint64 len = 1;
    int firstQuote = 0;

    //EXTRA DATA CODE
    //myExtraData.clear();    //clear extra data variable


    //version checking (commented out for removal)

    //len = inFile.readLine(buff, sizeof(buff));
    //tmp = buff;

    //if (!tmp.contains("_EV10_"))
    //    return;

    while (len > 0)
    {
        len = inFile.readLine(buff, sizeof(buff));
        tmp = buff;
        firstQuote = 0;
        
        if (len > 0)
        {
        
                //clear parsecheck.
                parseCheck = "";
                
                //EXTRA DATA CHECKING
                /* this part here is added to make sure all extra data that isn't part
                   of a standard Equipmant generated file isn't just thrown out. */
                //Extra comments checking code:
                if (tmp.trimmed().left(2) == "//") {
                    //if it's not our standrad first two lines of comments,
                    if (tmp.left(11) != "//Equipmant" &&
                        tmp.left(5) != "//Get" &&
                        tmp.trimmed() != "//Extra data found in file:" &&
                        !tmp.contains("input /equip")) {
                        myExtraData += tmp.trimmed() + "\r\n";
                        std::cerr << "[Extra Data Found]: \"" <<
                                     tmp.trimmed().toStdString().c_str() << "\"" << std::endl;
                        
                    }
                }
                else {
                    //if it DOESN'T begin with a // and DOESN'T contain input /equip
                    if (!tmp.contains("input /equip")) {
                        //fixing a random blank line bug.
                        if (!tmp.trimmed().isEmpty()) {
                            myExtraData += tmp.trimmed() + "\r\n";                //add it to extra data ;)
                            std::cerr << "[Extra Data Found2]: \"" <<
                                         tmp.trimmed().toStdString().c_str() << "\"" << std::endl;
                        }
                    }
                    
                
                }
                
                
                if (txtMain->text().isEmpty())
                    txtMain->setText(parsePiece(tmp,"main"));
                if (txtSub->text().isEmpty())
                    txtSub->setText(parsePiece(tmp,"sub"));
                if (txtRanged->text().isEmpty())
                    txtRanged->setText(parsePiece(tmp, "range"));
                if (txtAmmo->text().isEmpty())
                    txtAmmo->setText(parsePiece(tmp, "ammo"));
                if (txtHead->text().isEmpty())
                    txtHead->setText(parsePiece(tmp, "head"));
                if (txtNeck->text().isEmpty())
                    txtNeck->setText(parsePiece(tmp, "neck"));

                //left and right pieces require some scratch space
                //to check if L.Ear or ear1 is present.
                if (txtLEar->text().isEmpty())
                {
                    parseCheck = parsePiece(tmp,"l.ear");
                    if (parseCheck.isEmpty())
                        txtLEar->setText(parsePiece(tmp,"ear1"));
                    else
                        txtLEar->setText(parseCheck);
                }
                if (txtREar->text().isEmpty())
                {
                    parseCheck = parsePiece(tmp,"r.ear");
                    if (parseCheck.isEmpty())
                        txtREar->setText(parsePiece(tmp,"ear2"));
                    else
                        txtREar->setText(parseCheck);
                }
                //

                if (txtBody->text().isEmpty())
                    txtBody->setText(parsePiece(tmp, "body"));
                if (txtHands->text().isEmpty())
                    txtHands->setText(parsePiece(tmp, "hands"));
                
                //again with lefts, 1s, rights and 2s
                if (txtLRing->text().isEmpty())
                {
                    parseCheck = parsePiece(tmp,"l.ring");
                    if (parseCheck.isEmpty())
                        txtLRing->setText(parsePiece(tmp,"ring1"));
                    else
                        txtLRing->setText(parseCheck);
                }
                if (txtRRing->text().isEmpty())
                {
                    parseCheck = parsePiece(tmp,"r.ring");
                    if (parseCheck.isEmpty())
                        txtRRing->setText(parsePiece(tmp,"ring2"));
                    else
                        txtRRing->setText(parseCheck);
                }
                //


                if (txtBack->text().isEmpty())
                    txtBack->setText(parsePiece(tmp, "back"));
                if (txtWaist->text().isEmpty())
                    txtWaist->setText(parsePiece(tmp, "waist"));
                if (txtLegs->text().isEmpty())
                    txtLegs->setText(parsePiece(tmp, "legs"));
                if (txtFeet->text().isEmpty())
                    txtFeet->setText(parsePiece(tmp, "feet"));
                
        }
        else    //len > 0
            break;
        
    }    //while loop

    txtExtraData->setText(myExtraData);
}

// extra data widgets
void equipTab::addToBin_clicked(void)
{
        /*txtExtraData->setText(txtExtraData->toPlainText() + "\r\n");
    txtExtraData->setText(txt    */
    /*if (!txtExtraData->toPlainText().isEmpty())
        addToDataBin("\r\n");*/
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

QString equipTab::parsePiece(QString pString, QString loc)
{
    //this function has been tested and it works.
    QString result = "";
    int firstQuote = 0;
    //trim excess space and eat carriage returns.
    pString = pString.trimmed();
    //trim quotes
    pString = pString.left(pString.length() - 1);
    if (pString.contains("input /equip " + loc, Qt::CaseInsensitive))
    {
        //get the second to last quote, aka the FIRST quote of our "equipment_piece"
        firstQuote = pString.lastIndexOf('"');
        //subtract 4 below; 2 for \r\n and 2 for both quotes.
        result = pString.mid(firstQuote + 1, -1);
    }
    
    return result;
    
}

void equipTab::setExtraData(QString data)
{
    myExtraData = data;
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

//button slots
void equipTab::writeFile_clicked(void)
{

}
