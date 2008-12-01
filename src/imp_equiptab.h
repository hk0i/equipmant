#ifndef __IMP_EQUIPTAB_H
#define __IMP_EQUIPTAB_H

#include <iostream>
#include <QMessageBox>
#include <QTextStream>
#include <QWidget>
#include <QFile>
#include "equipmant.h"
#include "ui_equipTab.h"

class equipTab : public QWidget, public Ui::equipTab
{

	Q_OBJECT

	public:

		equipTab(QWidget *parent = 0)
			: QWidget(parent), myParent(parent)
		{
			setupUi(this);


			//connetions
			connect(swView, SIGNAL(currentChanged(int)), this, SLOT(viewModeChanged(int)));

			//extra data widgets
			connect(tbAddToBin, SIGNAL(clicked()), this, SLOT(addToBin_clicked()));
			connect(cmbExtraCommand, SIGNAL(currentIndexChanged(int)), this, SLOT(extraCmd_changed(int)));
		}


	public:
		void setExtraData(QString);
		void setCurrentFile(QString);			//sets the current file name.
		QString getCurrentFile(void);			//returns current file name.


	public slots:

		//buttons
		void writeFile_clicked(void);


		//misc/unsorted

		void clearFields(void);
		void viewModeChanged(int);
		void readFile(QString);
		QString generateText(void);


		//extra data widgets
		void addToBin_clicked(void);
		void extraCmd_changed(int);

	private:
		void updateTitle(void);
		void addToDataBin(QString);
		QString myCurrentFile;					//the current document being modified
		QString parsePiece(QString, QString);	//retrieves the piece of equipment given
												//an input macro to parse, and which piece
												//to look for (i.e., head, body, main, gloves)
		QString myExtraData;					//extra non-equipmant related data (job abilities/spell casting, etc...)
		QWidget *myParent;


};


#endif
