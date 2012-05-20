#ifndef __IMP_EQUIPTAB_H
#define __IMP_EQUIPTAB_H

#include <iostream>
#include <QMessageBox>
#include <QTextStream>
#include <QWidget>
#include <QFile>
#include <QCompleter>

#include "equipmant.h"
#include "ui_equipTab.h"

#include "model/Equip.h"
#include "model/EquipIoFactory.h"

#include "ui/GScriptHighlighter.h"

class equipTab : public QWidget, public Ui::equipTab
{

    Q_OBJECT

    public:

        equipTab(QWidget *parent = 0)
            : QWidget(parent)
        {
            setupUi(this);

            myEquip = new Equip();
            myModified = false;

            //connetions
            connect(swView, SIGNAL(currentChanged(int)), this, SLOT(viewModeChanged(int)));

            //extra data widgets
            connect(tbAddToBin, SIGNAL(clicked()), this, SLOT(addToBin_clicked()));
            connect(cmbExtraCommand, SIGNAL(currentIndexChanged(int)), this, SLOT(extraCmd_changed(int)));

            //load and set up auto completion
            QFile items("items.txt");
            if (items.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&items);
                QStringList completionWords;

                while (!in.atEnd()) {
                    completionWords << in.readLine();
                }

                QCompleter *completer = new QCompleter(completionWords, this);
                completer->setCaseSensitivity(Qt::CaseInsensitive);
                QList<QLineEdit *> allSlots = this->findChildren<QLineEdit *>(
                    QRegExp("^txt")
                );
                foreach (QLineEdit *l, allSlots) {
                    l->setCompleter(completer);
                }
            }
            else {
                qCritical() << "Could not load items.txt:"
                            << " auto-completion will not function properly";
            }

            int tabSize = txtExtraData->fontMetrics().width(' ') * 4;
            txtExtraData->setTabStopWidth(tabSize);



            myHighlighter = new GScriptHighlighter(txtExtraData->document());
            myPreviewHighlighter = new GScriptHighlighter(txtTextMode->document());
        }


    public:
        void writeFile(QString);                //writes to specified file
        void setCurrentFile(QString);           //sets the current file name.
        QString getCurrentFile(void);           //returns current file name.

        bool getModified(void) const;           //returns whether or not file is modified


    public slots:

        //misc/unsorted

        void clearFields(void);
        void viewModeChanged(int);
        void readFile(QString);

        //extra data widgets
        void addToBin_clicked(void);
        void extraCmd_changed(int);

        void setModified(bool modified = true);                 //sets whether the file was modified or not

    private:
        void updateUi(void);                //loads model data into ui
        void updateModel(void);             //loads ui data into model

        void addToDataBin(QString);

        bool myModified;                    //keeps track of whether file was modified or not
        QString myCurrentFile;              //the current document being modified

        GScriptHighlighter *myHighlighter;  //syntax highlighters :D
        GScriptHighlighter *myPreviewHighlighter;

        Equip *myEquip;                     //Equip instance, should handle all data

};


#endif
