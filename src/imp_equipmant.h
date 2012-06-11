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
#include <QShortcut>
#include <QStack>
#include <QSystemTrayIcon>
#include <QFileSystemModel>
#include <QTreeView>

#include <iostream>
#include "ui_equipmant.h"
#include "imp_about.h"
#include "imp_equiptab.h"
#include "equipmant.h"


#define CTAB equipTab *cTab = (equipTab*) tabFiles->currentWidget();
#ifdef Q_OS_WIN
    #define TRAY_ICON_PATH ":/img/equip.ico"
#else
    #define TRAY_ICON_PATH ":/img/res/equip_icon_64.png"
#endif

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
            connect(mnuViewFileBrowser, SIGNAL(triggered(bool)), this, SLOT(viewFileBrowser(bool)));

            //tab widget
            connect(tabFiles, SIGNAL(tabCloseRequested(int)), this, SLOT(fileClose()));

            //buttons
            //connect(pbWriteFile,SIGNAL(clicked()), this, SLOT(writeFile_clicked()));

            //extra data widgets

            //tabs
            //connect(tabWidget,SIGNAL(currentChanged(int)), this, SLOT(tabText_changed()));
            setupTabSignals(0);


            //setup shortcuts
            // QShortcut *s = new QShortcut(
                // QKeySequence(tr("Ctrl+T", "File|New")),
                // this
            // );

            //TROLOLO
            this->setUnifiedTitleAndToolBarOnMac(true);

            //set up system tray icon
            myTrayMenu = new QMenu();
            myTrayMenu->addAction(mnuFileNew);
            myTrayMenu->addAction(mnuFileOpen);
            myTrayMenu->addMenu(mnuFileOpenRecent);
            myTrayMenu->addSeparator();
            myTrayMenu->addAction(mnuFileQuit);

            myTrayIcon = new QSystemTrayIcon(this);
            myTrayIcon->setIcon(QIcon(TRAY_ICON_PATH));
            //only show context menu on windows system tray
            #ifdef Q_OS_WIN
            myTrayIcon->setContextMenu(myTrayMenu);
            #endif
            connect(
                    myTrayIcon,
                    SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    this,
                    SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason))
            );
            myTrayIcon->show();

            //example code for creating startup shortcut
            //get startup folder path windows
            /*
            wchar_t startupFolder[MAX_PATH];
            HRESULT hr = SHGetFolderPath(0, CSIDL_STARTUP, 0, 0, startupFolder);
            if (SUCCEEDED(hr)) {
                QString startupPath = QString::fromWCharArray(startupFolder);
                qDebug() << startupPath;
                std::wcout << startupFolder;
            }

            //create link
            CoInitialize(NULL);
            */

            connect(
                tbFBUp,
                SIGNAL(clicked()),
                this,
                SLOT(fbUp_clicked())
            );
            connect(
                tvFileView,
                SIGNAL(doubleClicked(QModelIndex)),
                this,
                SLOT(fileTreeDoubleClicked(QModelIndex))
            );

            QStringList filters;
            filters << "*.equip" << "*.txt";

            myFSModel = new QFileSystemModel();
            myFSModel->setRootPath(myLastFileDir);
            myFSModel->setNameFilters(filters);
            //hide filtered files instead of graying them out
            myFSModel->setNameFilterDisables(false);

            tvFileView->setModel(myFSModel);
            lblFBDirectory->setText(myLastFileDir);
            tvFileView->setRootIndex(myFSModel->index(myLastFileDir));
            //hide size, file type and date modified columns
            tvFileView->setColumnHidden(1, true);
            tvFileView->setColumnHidden(2, true);
            tvFileView->setColumnHidden(3, true);

            //hide the buttons that are not yet implemented
            //@TODO: implement these.
            tbFBDown->hide();
            tbFBAdd->hide();
            tbFBRemove->hide();

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
        void viewFileBrowser(bool);

        //tabs
        void updateTitle(void);                    //updates titlebar
        void modified(void);                    //tab contents gets modified

        //system tray icon
        void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

        //file view widget
        void fileTreeDoubleClicked(const QModelIndex &index);
        void fbUp_clicked(void);

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        QFileSystemModel *myFSModel;

        void writeFile(void);
        void writeFile(QString);
        void openFile(QString);                 //handles file tab opening
        void readFile(QString);                 //opens file QString

        //files that relate to getting/setting program data
        //these functions deal with getting/saving ALL data to files:
        void saveData(void);                    //saves program data to home folder. (i.e., last file location,
                                                //recent docs.)
        void loadData(void);                    //loads program data (see above)

        //recent file menu stuff
        void clearRecent(bool);                 //clears the recent files menu. (true clears recent file data.
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
        void openRecent(int);                   //opens recent document from myRecentDocs[int-1]
                                                //the number passed is a number 1-9, not 0-8.
        void addToDataBin(QString);             //adds text to data bin; no endlines added.
        void setupTabSignals(int);              //sets up tab signals for title updating


        QString nameFromPath(QString);          //retrieves and returns the filename from an absolute path.

        //variables
        int numRecent;                          //number of recent docs.
        QString myLastFileDir;                  //director where last accessed file is located.
        QString myRecentDocs[9];                //stack that stores recently accessed documents.
                                                // (used for the recent menu)

        QString myEditMode;                     //store the current edit mode:
                                                // "Edit Mode"
                                                //         or
                                                //     "View Output"

        //extra widgets
        Imp_about    myAbout;                   //about screen dialog.
        QSystemTrayIcon *myTrayIcon;            //system tray icon
        QMenu *myTrayMenu;                      //system tray context menu
};

#endif
