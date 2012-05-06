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

#include <QApplication>
#include "imp_equipmant.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    std::cout << "Equipmant V" << EQM_VERSION << " Copyright (C) 2007 Gregory McQuillan" << std::endl
              << "Equipmant comes with ABSOLUTELY NO WARRANTY; for details see the included text file LICENSE" << std:: endl
              << "This is free software, and you are welcome to redistribute it" << std::endl
              << "Under certain conditions; see LICENSE for more information." << std::endl << std:: endl
              << "This program is distributed in the hope that it will be useful," << std::endl
              << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl
              << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl
              << "GNU General Public License for more details." << std::endl << std::endl
              << "You should have received a copy of the GNU General Public License along" << std::endl
              << "with this program; if not, write to the Free Software Foundation, Inc.," << std::endl
              << "51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA." << std::endl;
    
    Imp_equipmant form;
    form.show();

    return app.exec();
}
