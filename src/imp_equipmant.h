/*
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

#ifndef __IMP_EQUIPMANT
#define __IMP_EQUIPMANT

#include <iostream>
#include <QDesktopServices>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QStack>
#include <iostream>
#include "ui_equipmant.h"
#include "imp_about.h"
#include "imp_equiptab.h"
#include "equipmant.h"


#define CTAB equipTab *cTab = (equipTab*) tabFiles->currentWidget();

class equipTab;

class Imp_equipmant: public QMainWindow, Ui::MainWindow
{

    Q_OBJECT

    public:
        Imp_equipmant() : QMainWindow(), numRecent(0), myEditMode("(Edit Mode)")
        {
            setupUi(this);
            updateTitle();        //set the title before anything else
            //load program data
            loadData();

            //connections
            //menus
            connect(mnuFileNew, SIGNAL(triggered()), this, SLOT(fileNew()));
            connect(mnuFileOpen, SIGNAL(triggered()), this, SLOT(fileOpen()));
            connect(mnuFileClose, SIGNAL(triggered()), this, SLOT(fileClose()));

            connect(mnuFileSave, SIGNAL(triggered()), this, SLOT(fileSave()));
            connect(mnuFileSaveAs, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

            connect(mnuFileQuit, SIGNAL(triggered()), this, SLOT(fileQuit()));

            //recent file menus
            connect(mnuRecent1, SIGNAL(triggered()), this, SLOT(fileRecent1()));
            connect(mnuRecent2, SIGNAL(triggered()), this, SLOT(fileRecent2()));
            connect(mnuRecent3, SIGNAL(triggered()), this, SLOT(fileRecent3()));
            connect(mnuRecent4, SIGNAL(triggered()), this, SLOT(fileRecent4()));
            connect(mnuRecent5, SIGNAL(triggered()), this, SLOT(fileRecent5()));
            connect(mnuRecent6, SIGNAL(triggered()), this, SLOT(fileRecent6()));
            connect(mnuRecent7, SIGNAL(triggered()), this, SLOT(fileRecent7()));
            connect(mnuRecent8, SIGNAL(triggered()), this, SLOT(fileRecent8()));
            connect(mnuRecent9, SIGNAL(triggered()), this, SLOT(fileRecent9()));
            connect(mnuRecentClear, SIGNAL(triggered()), this, SLOT(fileClearRecent()));

            connect(mnuHelpPPage, SIGNAL(triggered()), this, SLOT(helpProjectPage()));
            connect(mnuHelpWebsite, SIGNAL(triggered()), this, SLOT(helpWebsite()));
            connect(mnuHelpAbout, SIGNAL(triggered()), this, SLOT(helpAbout()));

            //view actions
            connect(mnuViewEdit, SIGNAL(triggered()), this, SLOT(viewEdit()));
            connect(mnuViewOutput, SIGNAL(triggered()), this, SLOT(viewOutput()));

            //tab widget
            connect(tabFiles, SIGNAL(currentChanged(int)), this, SLOT(updateTitle()));

            //buttons
            //connect(pbWriteFile,SIGNAL(clicked()), this, SLOT(writeFile_clicked()));

            //extra data widgets
            //connect(tbAddToBin, SIGNAL(clicked()), this, SLOT(addToBin_clicked()));
            //connect(cmbExtraCommand, SIGNAL(currentIndexChanged(int)), this, SLOT(extraCmd_changed(int)));


            //tabs
            //connect(tabWidget,SIGNAL(currentChanged(int)), this, SLOT(tabText_changed()));

        }


    public slots:

        //menus
        void fileNew(void);
        void fileOpen(void);
        void fileClose(void);

        void fileSave(void);
        void fileSaveAs(void);

        void fileQuit(void);

        //recent file menus
        void fileRecent1(void);
        void fileRecent2(void);
        void fileRecent3(void);
        void fileRecent4(void);
        void fileRecent5(void);
        void fileRecent6(void);
        void fileRecent7(void);
        void fileRecent8(void);
        void fileRecent9 (void);
        void fileClearRecent(void);

        void helpProjectPage(void);                //help-> project page
        void helpWebsite(void);              //help-> webpage
        void helpAbout(void);

        //View Actions
        void viewEdit(void);
        void viewOutput(void);


        //tabs

    private:

        void writeFile(void);
        void writeFile(QString);
        void readFile(QString);                    //opens file QString
        void updateTitle(void);                    //updates titlebar

        //files that relate to getting/setting program data
        //these functions deal with getting/saving ALL data to files:
        void saveData(void);                    //saves program data to home folder. (i.e., last file location,
                                                //recent docs.)
        void loadData(void);                    //loads program data (see above)

        //recent file menu stuff
        void clearRecent(bool);                    //clears the recent files menu. (true clears recent file data.
                                                // false only hides the menus.
        void updateRecent(void);                //updates the recent file menu (from myRecentDocs[])
        void addRecent(QString);                //adds a recent item to the menu, checking if it
                                                //already exists.
                                                //if the item exists, it is
                                                //bumped to the top of the list and the
                                                //other items are shifted down.
        int findRecent(QString);                //checks to see if a document
                                                //is already in the recent docs array.
                                                //returns the index position, -1 if not found.
        void openRecent(int);                    //opens recent document from myRecentDocs[int-1]
                                                //the number passed is a number 1-9, not 0-8.
        void addToDataBin(QString);                //adds text to data bin; no endlines added.


        QString generateText(void);
        QString nameFromPath(QString);            //retrieves and returns the filename from an absolute path.

        //variables
        int numRecent;                            //number of recent docs.
        QString myLastFileDir;                    //director where last accessed file is located.
        QString myRecentDocs[9];                //stack that stores recently accessed documents.
                                                // (used for the recent menu)

        QString myEditMode;                        //store the current edit mode:
                                                // "Edit Mode"
                                                //         or
                                                //     "View Output"

        //extra dialogs
        Imp_about    myAbout;                    //about screen dialog.

};

#endif
