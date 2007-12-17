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

#ifndef __IMP_ABOUT_H
#define __IMP_ABOUT_H

#include <iostream>
#include "ui_about.h"
#include "equipmant.h"

class Imp_about: public QDialog, Ui::dlgAbout
{
	Q_OBJECT
	
	public:
		Imp_about() : QDialog()
		{
			setupUi(this);
			//add the version # to the about "screen"
			label_17->setText(label_17->text().replace("$EQM_VERSION",EQM_VERSION));
		}

	private slots:

	private:

};

#endif
