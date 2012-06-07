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
    int newTabID = tabFiles->addTab(new equipTab(),"Untitled");
    setupTabSignals(newTabID);

    tabFiles->setCurrentIndex(newTabID);
    statusbar->showMessage("Editing new document");
}

void Imp_equipmant::fileOpen(void)
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open Equip Macro...",
        myLastFileDir,
        "Equipment Macros (*.txt *.equip)"
    );

    if (fileName.isEmpty())
        return;

    //check if file is already open :)
    equipTab *tab = 0;
    for (int i = 0; i < tabFiles->count(); i++) {
        tab = (equipTab*) tabFiles->widget(i);
        if (tab->getCurrentFile() == fileName) {
            tabFiles->setCurrentIndex(i);
            return;
        }
    }

    int newTabNum = tabFiles->addTab(new equipTab(), nameFromPath(fileName));

    tabFiles->setCurrentIndex(newTabNum);
    readFile(fileName);
    setupTabSignals(newTabNum);
}

void Imp_equipmant::fileClose(void)
{
    CTAB
    if (!cTab) {
        return;
    }

    if (cTab->getCurrentFile().isEmpty()) {
        statusbar->showMessage("Document closed.");
    }
    else {
        statusbar->showMessage("Closed File: " + cTab->getCurrentFile());
    }

    cTab->setCurrentFile("");

    // **** WARNING - I THINK THE ACTUAL WIDGETS NEED TO BE REMOVED ALSO ****
    tabFiles->removeTab(tabFiles->currentIndex());
    // **** WARNING - I THINK THE ACTUAL WIDGETS NEED TO BE REMOVED ALSO ****
}

void Imp_equipmant::fileSave(void)
{
    CTAB
    if (cTab->getCurrentFile().isEmpty()) {
        fileSaveAs();
    }
    else {
        writeFile();
    }
}

void Imp_equipmant::fileSaveAs(void)
{
    //pop dialog
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Equip Macro As...",
        myLastFileDir,
        "Equipment Macros (*.txt *.equip)"
    );

    CTAB
    //check for a valid file...
    if (!fileName.isEmpty()) {
        //check file extension, if any.
        int lastDot = fileName.lastIndexOf('.');
        if (lastDot > 0)
        {
            QString ext = fileName.mid(lastDot+1);
            if (ext != "equip" && ext != "txt")    //check for a reasonable file extension
                fileName += ".equip";            //add the extension
        }
        else
            fileName += ".equip";
        writeFile(fileName);
    }
    else {
        statusbar->showMessage("No filename selected. File has NOT been saved.");
        return;
    }

    cTab->setCurrentFile(fileName);
    tabFiles->setTabText(tabFiles->currentIndex(),nameFromPath(fileName));
}

void Imp_equipmant::fileQuit(void)
{
    //save program data
    saveData();
    //quit cleanly
    QApplication::quit();
}

void Imp_equipmant::fileRecent1(void) { openRecent(1); }
void Imp_equipmant::fileRecent2(void) { openRecent(2); }
void Imp_equipmant::fileRecent3(void) { openRecent(3); }
void Imp_equipmant::fileRecent4(void) { openRecent(4); }
void Imp_equipmant::fileRecent5(void) { openRecent(5); }
void Imp_equipmant::fileRecent6(void) { openRecent(6); }
void Imp_equipmant::fileRecent7(void) { openRecent(7); }
void Imp_equipmant::fileRecent8(void) { openRecent(8); }
void Imp_equipmant::fileRecent9(void) { openRecent(9); }
void Imp_equipmant::fileClearRecent(void) { clearRecent(true); updateRecent(); }

void Imp_equipmant::helpProjectPage(void)
{
    QDesktopServices::openUrl(QUrl("http://sourceforge.net/projects/equipmant"));
}
void Imp_equipmant::helpWebsite(void)
{
    QDesktopServices::openUrl(QUrl("http://equipmant.sourceforge.net"));
}
void Imp_equipmant::helpAbout(void)
{
    std::cout << "WTF" << std::endl;
    myAbout.show();
}

//view slots
void Imp_equipmant::viewEdit(void) {
    CTAB
    if (cTab)
        cTab->swView->setCurrentIndex(0);
}
void Imp_equipmant::viewOutput(void) {
    CTAB
    if (cTab)
        cTab->swView->setCurrentIndex(1);
}

//private functions
/**
 * Saves current file
 */
void Imp_equipmant::writeFile(void)
{
    CTAB
    if(!cTab->getCurrentFile().isEmpty()) {
        writeFile(cTab->getCurrentFile());
        cTab->setModified(false);
        updateTitle();
    }
}


QString Imp_equipmant::nameFromPath(QString fullPath)
{
    QString ret(QDir::fromNativeSeparators(fullPath));
    int lastSlash = -1;
    lastSlash = ret.lastIndexOf('/', ret.lastIndexOf('/') - 1);
    return ret.mid(lastSlash+1);
}

/**
 * Saves file as ...
 */
void Imp_equipmant::writeFile(QString fName)
{
    CTAB

    qDebug() << "Writing file...";
    cTab->writeFile(fName);

    //set last file path
    myLastFileDir = fName.left(fName.lastIndexOf('/'));
    addRecent(fName);
    saveData();    //save data now in case of a crash ;D
    statusbar->showMessage(fName + " saved.");

}

void Imp_equipmant::readFile(QString fileName)
{
    QFile check(fileName);
    if (!check.exists())
        return;
    CTAB

    cTab->readFile(fileName);

    //update last file path
    myLastFileDir = fileName.left(fileName.lastIndexOf('/'));
    saveData();    //save data now in case of a crash ;D
    statusbar->showMessage("Loaded File: " + fileName);
    addRecent(fileName);
}

void Imp_equipmant::updateTitle(void)
{
    QString title;
    QTextStream ts(&title);
    qDebug() << "Updating title main form";
    CTAB

    //update tab title on changes
    int currentIndex = tabFiles->currentIndex();
    QString currentText = tabFiles->tabText(currentIndex);
    if (cTab->getModified() && currentText.right(2) != " *") {
        tabFiles->setTabText(currentIndex, currentText + " *");
    }
    if (!cTab->getModified() && currentText.right(2) == " *") {
        currentText.chop(2);
        tabFiles->setTabText(currentIndex, currentText);
    }

    if (cTab->getCurrentFile().isEmpty())
        ts << "Equipmant Equipment Macro Manager v" << EQM_VERSION;
    else
        ts << "Equipmant Equipment Macro Manager [" << nameFromPath(cTab->getCurrentFile()) << "] " << myEditMode;
    this->setWindowTitle(title);
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

    fout << myLastFileDir << "\n";
    for (int i = 0; i < numRecent; i++)
        fout << myRecentDocs[i] << "\n";

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
    for (numEle = 0; numEle < 9; numEle++) {
        myRecentDocs[numEle] = fin.readLine();
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
    if (clearCache) {
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
    if (index >= 0) {
        int zeroRow = 0;
        //remove it from the list, by shifting all recent docs below it up and clobbering it.
        for (zeroRow = index; zeroRow < numRecent - 1; zeroRow++)
            myRecentDocs[zeroRow] = myRecentDocs[zeroRow + 1];
        myRecentDocs[zeroRow] = "";
    }
    //shift all menus downward.
    for (int i = 8; i > 0; i--)
        myRecentDocs[i] = myRecentDocs[i - 1];
    //insert our new item at the top
    myRecentDocs[0] = newRecent;
    //update the number of recent documents... maybe.
    if (numRecent < 8)
        numRecent++;
    updateRecent();
}

int Imp_equipmant::findRecent(QString search)
{
    for (int i = 0; i < 9; i++) {
        if (myRecentDocs[i] == search)
            return i;
    }
    return -1;
}

void Imp_equipmant::openRecent(int recNum)
{
    if (myRecentDocs[recNum - 1].isEmpty())
        return;

    QString fileName = myRecentDocs[recNum - 1];

    //check if file is already open :)
    equipTab *tab = 0;
    for (int i = 0; i < tabFiles->count(); i++) {
        tab = (equipTab*)tabFiles->widget(i);
        if (tab->getCurrentFile() == fileName)
        {
            tabFiles->setCurrentIndex(i);
            return;
        }
    }

    int newTabNum = tabFiles->addTab(new equipTab(), nameFromPath(fileName));
    tabFiles->setCurrentIndex(newTabNum);
    readFile(fileName);
}

void Imp_equipmant::modified(void)
{
    CTAB
    cTab->setModified();
    //always set modified back to false after we trigger the title update
    cTab->txtExtraData->document()->setModified(false);
    updateTitle();
}

/**
 * Hooks up ui changes to model update methods
 **/
void Imp_equipmant::setupTabSignals(int tabIndex)
{
    equipTab *tab = (equipTab *)tabFiles->widget(tabIndex);
    QList<QLineEdit *> lineEdits = tab->findChildren<QLineEdit *>(QRegExp("^txt"));
    for (int i = 0; i < lineEdits.count(); i++) {
        qDebug() << "Registering QLineEdit" << lineEdits[i];
        connect(lineEdits[i], SIGNAL(textChanged(QString)), this, SLOT(modified(void)));
    }
    QPlainTextEdit *scriptWidget = tab->findChild<QPlainTextEdit *>("txtExtraData");
    connect(scriptWidget, SIGNAL(modificationChanged(bool)), this, SLOT(modified(void)));
}

void Imp_equipmant::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {

        case QSystemTrayIcon::Trigger:

            if (this->isVisible()) {

                //be smart if it's not on windows cause windows can't handle this for some reason
                #ifndef Q_OS_WIN
                //hide window if it is active
                if (this->isActiveWindow()) {
                    this->hide();
                }
                //raise window when it is covered by other apps
                else {
                    this->raise();
                }
                #else
                    //just hide on windows, it's dumb that way.
                    this->hide();
                #endif
            }
            else {
                this->show();
                this->raise();
            }

            break;

        default:
            break;

    }
}

void Imp_equipmant::closeEvent(QCloseEvent *event)
{
    if (myTrayIcon->isVisible()) {
        QDir configPath = QDir::toNativeSeparators(QDir::homePath() + "/.equipmant");
        QFile file(QDir::toNativeSeparators(configPath.absolutePath() + "/.traynotify"));
        if (!file.exists()) {
            myTrayIcon->showMessage(
                    tr("Still Here!"),
                    tr(
                       "Hey, even though you appeared to have closed Equipmant, "
                       "it is still open. To close Equipmant, right click this tray icon "
                       "and click it from the menu there."
                    )
            );
            file.open(QIODevice::ReadWrite);
            file.close();
        }


        this->hide();
        event->ignore();
    }
}
