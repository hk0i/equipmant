/*
imp_equipmant.cpp

Equipmant V2.0 Copyright (C) 2007 Gregory McQuillan <gmcquillan@gmail.com>
Equipmant comes with ABSOLUTELY NO WARRANTY; for details see the included text file LICENSE
This is free software, and you are welcome to redistribute it
under certain conditions; see LICENSE for more information.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "imp_equipmant.h"

//menu actions

void Imp_equipmant::fileNew(void)
{
	//std::cerr << this->height() << "x" << this->width() << std::endl;
	fileClose();
	statusbar->showMessage("Editing new document");
}

void Imp_equipmant::fileOpen(void)
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open Equip Macro...",
														myLastFileDir, "Equipment Macros (*.txt *.equip)");
	readFile(fileName);
	txtTextMode->setText(generateText());
}

void Imp_equipmant::fileClose(void)
{
	if (myCurrentFile.isEmpty())
		statusbar->showMessage("Document closed.");
	else
		statusbar->showMessage("Closed File: " + myCurrentFile);
	setCurrentFile("");
	clearFields();
}

void Imp_equipmant::fileSave(void)
{
	myExtraData = txtExtraData->toPlainText();
	if (myCurrentFile.isEmpty())
	{
		fileSaveAs();
	}
	else {
		writeFile();
	}
}

void Imp_equipmant::fileSaveAs(void)
{
	//pop dialog
	QString fileName = QFileDialog::getSaveFileName(this, "Save Equip Macro As...",
													myLastFileDir, "Equipment Macros (*.txt *.equip)");
	myExtraData = txtExtraData->toPlainText();
													
	//check for a valid file...
	if (!fileName.isEmpty())
	{
		//check file extension, if any.
		int lastDot = fileName.lastIndexOf('.');
		if (lastDot > 0)
		{
			QString ext = fileName.mid(lastDot+1);
			if (ext != "equip" && ext != "txt")	//check for a reasonable file extension
				fileName += ".equip";			//add the extension
		}
		else
			fileName += ".equip";
		writeFile(fileName);
	}
	else
		statusbar->showMessage("No filename selected. File has NOT been saved.");
	
	setCurrentFile(fileName);
}

void Imp_equipmant::fileQuit(void)
{
	//save program data
	saveData();
	//quit
	exit(0);
}

void Imp_equipmant::fileRecent1(void) {	openRecent(1); }
void Imp_equipmant::fileRecent2(void) { openRecent(2); }
void Imp_equipmant::fileRecent3(void) { openRecent(3); }
void Imp_equipmant::fileRecent4(void) { openRecent(4); }
void Imp_equipmant::fileRecent5(void) { openRecent(5); }
void Imp_equipmant::fileRecent6(void) { openRecent(6); }
void Imp_equipmant::fileRecent7(void) { openRecent(7); }
void Imp_equipmant::fileRecent8(void) { openRecent(8); }
void Imp_equipmant::fileRecent9(void) { openRecent(9); }
void Imp_equipmant::fileClearRecent(void) { clearRecent(true); updateRecent(); }

void Imp_equipmant::helpPPage(void)
{
/* until i find a universal way of doing this, i know this will
   probably work under windows, I still need to figure out a way
   for this to work under unix systems, and possible a cross-platform
   way to do this for all systems in one snippet. */
#ifdef WINDOWS
	ShellExecute(NULL, "open", "http://sourceforge.net/projects/equipmant",
					NULL, NULL, SW_SHOWNORMAL);
#else
	/* run web browser and open project page 
	QProcess *wb = new QProcess(this);
	wb->start("http://sourceforge.net/projects/equipmant");*/
#endif
}
void Imp_equipmant::helpWebsite(void)
{
#ifdef WINDOWS
	ShellExecute(NULL, "open", "http://equipmant.sourceforge.net/",
					NULL, NULL, SW_SHOWNORMAL);
#else
	/* I need to figure this out...
	QProcess *wb = new QProcess(this);
	wb->start("http://equipmant.sourceforge.net");*/
#endif
}
void Imp_equipmant::helpAbout(void)
{
	std::cout << "WTF" << std::endl;
	myAbout.show();
}

//view slots
void Imp_equipmant::viewEdit(void) { swView->setCurrentIndex(0); }
void Imp_equipmant::viewOutput(void) { swView->setCurrentIndex(1); }

void Imp_equipmant::viewModeChanged(int newPage)
{
	myExtraData = txtExtraData->toPlainText();
	txtTextMode->setText(generateText());
	if (newPage == 0)
	{
		myEditMode = "(Edit Mode)";
		updateTitle();
	}
	else
	{
		myEditMode = "(View Output)";
		updateTitle();
	}

}

//button slots
void Imp_equipmant::writeFile_clicked(void)
{
	fileSave();
}

// extra data widgets
void Imp_equipmant::addToBin_clicked(void)
{
		/*txtExtraData->setText(txtExtraData->toPlainText() + "\r\n");
	txtExtraData->setText(txt	*/
	/*if (!txtExtraData->toPlainText().isEmpty())
		addToDataBin("\r\n");*/
	QString str;
	QTextStream qts(&str);
	bool ok = false;	//dummy variable used for dialog and commands
	int mult = 1;		//timeout multiplier

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
		if (ok)	str += '"';
		str += cmbExtraParam->currentText();
		if (ok)	str += "\" " + cmbExtraTarget->currentText();
		str	+= "\r\n";
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

void Imp_equipmant::extraCmd_changed(int newIndex)
{
	if (newIndex > 1)
		cmbExtraTarget->setHidden(true);
	else
		cmbExtraTarget->setVisible(true);
}

//tab slots
/*void Imp_equipmant::tabText_changed(void)
{
	txtTextMode->setText(generateText());
}*/


//private functions
void Imp_equipmant::writeFile(void)
{
	if(!myCurrentFile.isEmpty())
	{
		writeFile(myCurrentFile);
	}
	
}

QString Imp_equipmant::generateText(void)
{
	QString result;
	QTextStream strOut(&result);
	
	//windows line terminations \r\n (since FF is a PC/windows game)
	
	// if a text field is empty, it will write a commented line,
	// this line acts as a placeholder, to make the layout of the
	// files uniform. It is commented so that equipment won't be
	// removed from the macro.

	strOut << EQM_OPC1;	//Equipmant output comment1
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
	if (!myExtraData.isEmpty())
	{
		strOut << "\r\n" << EQM_EXTRADATA << myExtraData;
	}
	
	return result;
}

QString Imp_equipmant::nameFromPath(QString fullPath)
{
	QString ret(QDir::fromNativeSeparators(fullPath));
	int lastSlash = -1;
	lastSlash = ret.lastIndexOf('/');
	return ret.mid(lastSlash+1);
}

void Imp_equipmant::writeFile(QString fName)
{
	QFile file(fName);
	file.open(QIODevice::WriteOnly);
	QTextStream fout(&file);
	
	fout << generateText();
	
	//set last file path
	myLastFileDir = fName.left(fName.lastIndexOf('/'));
	addRecent(fName);
	saveData();	//save data now in case of a crash ;D
	statusbar->showMessage(fName + " saved.");

}

void Imp_equipmant::readFile(QString fileName)
{
	QFile inFile(fileName);
	if (!inFile.exists())
		return;
	inFile.open(QFile::ReadOnly);
	
	setCurrentFile(fileName);
	//set last file path
	myLastFileDir = fileName.left(fileName.lastIndexOf('/'));
	saveData();		//save data now, in case of a program crash ;D
	
	
	//clear fields to prove test cases.
	clearFields();
	
	//clear textmode area.
	txtTextMode->clear();
	
	char buff[1024];
	QString tmp;
	QString parseCheck;	//used to check for Left/Right equips. i.e., if file contains
						// L.Ring or ring1 etc..
	qint64 len = 1;
	int firstQuote = 0;
	
	//EXTRA DATA CODE
	myExtraData.clear();	//clear extra data variable
	
	
	//version checking (commented out for removal)
	
	//len = inFile.readLine(buff, sizeof(buff));
	//tmp = buff;
	
	//if (!tmp.contains("_EV10_"))
	//	return;
	
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
							myExtraData += tmp.trimmed() + "\r\n";				//add it to extra data ;)
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
		else	//len > 0
			break;
		
	}	//while loop

	txtExtraData->setText(myExtraData);
	
	statusbar->showMessage("Loaded File: " + fileName);
	addRecent(fileName);
}

void Imp_equipmant::clearFields(void)
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

void Imp_equipmant::updateTitle(void)
{
	QString title;
	QTextStream ts(&title);
	if (myCurrentFile.isEmpty())
		ts << "Equipmant Equipment Macro Manager v" << EQM_VERSION << " [New File] " << myEditMode;
	else
		ts << "Equipmant Equipment Macro Manager [" << nameFromPath(myCurrentFile) << "] " << myEditMode;
	this->setWindowTitle(title);
}

void Imp_equipmant::updateTitle(QString newTitle)
{
	//this method is now deprecated :D
	updateTitle();
	//this->setWindowTitle(this->windowTitle() + ' ' + newTitle + ' ' + myEditMode);
}

void Imp_equipmant::setCurrentFile(QString newFile)
{
	myCurrentFile = newFile;
	if (newFile.isEmpty())		// if the new file is empty, set the title to say "No File"
		updateTitle("[New File]");
	else
		updateTitle("[" + nameFromPath(myCurrentFile) + "]");
}

void Imp_equipmant::saveData(void)
{
	//path to configuration file
	QDir configPath = QDir::toNativeSeparators(QDir::homePath() + "/.equipmant");
	//check if config dir exists; if not, create it.
	if (!configPath.exists())
		configPath.mkpath(configPath.absolutePath());
	
	//now create/save file.
	QFile file(QDir::toNativeSeparators(configPath.absolutePath() + "/equip.rc"));
	file.open(QIODevice::WriteOnly);
	QTextStream fout(&file);
	
	fout << myLastFileDir << "\r\n";
	for (int i = 0; i < numRecent; i++)
		fout << myRecentDocs[i] << "\r\n";
	
}
void Imp_equipmant::loadData(void)
{
	QDir configPath = QDir::toNativeSeparators(QDir::homePath() + "/.equipmant");
	QFile file(QDir::toNativeSeparators(configPath.absolutePath() + "/equip.rc"));
	
	//fill the menu with the recent documents
	//assume nothing. clear all data.
	clearRecent(false);
	updateRecent();
	
	//if the file doesn't exist, exit function. There is no data to load.
	if (!file.exists())
		return;		
	file.open(QIODevice::ReadOnly);
	QTextStream fin(&file);
	
	myLastFileDir = fin.readLine();
	
	//load recent documents into our data structure
	int numEle = 0;
	for (numEle = 0; numEle < 9; numEle++)
	{
		myRecentDocs[numEle] = fin.readLine();
		//std::cerr << "myRecentDocs[" << numEle << "]: " << myRecentDocs[numEle].toStdString().c_str() << std::endl;
		if (myRecentDocs[numEle].isEmpty())
			break;
	}
	numRecent = numEle;
	
	//update the menu (i.e., enable all menu items that have recent file data).
	updateRecent();
}

void Imp_equipmant::clearRecent(bool clearCache)
{
	//hide menu items
	mnuRecent1->setVisible(false);
	mnuRecent2->setVisible(false);
	mnuRecent3->setVisible(false);
	mnuRecent4->setVisible(false);
	mnuRecent5->setVisible(false);
	mnuRecent6->setVisible(false);
	mnuRecent7->setVisible(false);
	mnuRecent8->setVisible(false);
	mnuRecent9->setVisible(false);
	
	//clear data.
	if (clearCache)
	{
		for (int i = 0; i < 9; i++)
			myRecentDocs[i].clear();
		numRecent = 0;
	}
}

void Imp_equipmant::updateRecent(void)
{
	int numEle = 0;
	for (numEle = 0; numEle < 9; numEle++)
		if (myRecentDocs[numEle].isEmpty())
			break;

	switch (numEle)
	{
		case 9:
			mnuRecent9->setText("&9. " + nameFromPath(myRecentDocs[8]));
			mnuRecent9->setVisible(true);
			//no break, fall through.
		
		case 8:
			mnuRecent8->setText("&8. " + nameFromPath(myRecentDocs[7]));
			mnuRecent8->setVisible(true);
		
		case 7:
			mnuRecent7->setText("&7. " + nameFromPath(myRecentDocs[6]));
			mnuRecent7->setVisible(true);
		
		case 6:
			mnuRecent6->setText("&6. " + nameFromPath(myRecentDocs[5]));
			mnuRecent6->setVisible(true);
		
		case 5:
			mnuRecent5->setText("&5. " + nameFromPath(myRecentDocs[4]));
			mnuRecent5->setVisible(true);
		
		case 4:
			mnuRecent4->setText("&4. " + nameFromPath(myRecentDocs[3]));
			mnuRecent4->setVisible(true);
			
		case 3:
			mnuRecent3->setText("&3. " + nameFromPath(myRecentDocs[2]));
			mnuRecent3->setVisible(true);
			
		case 2:
			mnuRecent2->setText("&2. " + nameFromPath(myRecentDocs[1]));
			mnuRecent2->setVisible(true);
		
	
		case 1:
			mnuRecent1->setText("&1. " + nameFromPath(myRecentDocs[0]));
			mnuRecent1->setVisible(true);
			mnuFileOpenRecent->setEnabled(true);
			break;
			
		default:
			mnuFileOpenRecent->setEnabled(false);
	}

}

void Imp_equipmant::addRecent(QString newRecent)
{
	int index = findRecent(newRecent);
	
	//if it's in the recent list..
	if (index >= 0)
	{
		int zeroRow = 0;
		//remove it from the list, by shifting all recent docs below it up and clobbering it.
		for (zeroRow = index; zeroRow < numRecent-1; zeroRow++)
			myRecentDocs[zeroRow] = myRecentDocs[zeroRow+1];
		myRecentDocs[zeroRow] = "";
	}
	//shift all menus downward.
	for (int i = 8; i > 0; i--)
		myRecentDocs[i] = myRecentDocs[i-1];
	//insert our new item at the top
	myRecentDocs[0] = newRecent;
	//update the number of recent documents... maybe.
	if (numRecent < 8)
		numRecent++;
	updateRecent();
}

int Imp_equipmant::findRecent(QString search)
{
	for (int i = 0; i < 9; i++)
	{
		if (myRecentDocs[i] == search)
			return i;
	}
	return -1;
}

void Imp_equipmant::openRecent(int recNum)
{
	if (myRecentDocs[recNum-1].isEmpty())
		return;
	
	readFile(myRecentDocs[recNum-1]);
}

void Imp_equipmant::addToDataBin(QString textToAdd)
{
	txtExtraData->setText(txtExtraData->toPlainText() + textToAdd);
}

QString Imp_equipmant::parsePiece(QString pString, QString loc)
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
