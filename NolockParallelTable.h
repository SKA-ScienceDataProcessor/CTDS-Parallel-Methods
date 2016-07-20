// (c) Shanghai Astronomical Observatory (SHAO), Chinese Academy of Sciences
//
// 80 Nandan Road, Shanghai 200030
// China
//
// This library is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this library. If not, see <http://www.gnu.org/licenses/>.
//
// Any bugs, questions, concerns and/or suggestions please email to
// lbq@shao.ac.cn

#include "ParallelTable.h"
#include <casacore/tables/DataMan/TiledShapeStMan.h>
#include <casacore/tables/DataMan/StandardStMan.h>

class NolockParallelTable : public ParallelTable{
    public:
        NolockParallelTable(const string, const unsigned int, const unsigned int, const unsigned int, const unsigned int, const unsigned int, const string);
        virtual ~NolockParallelTable();
        virtual void addColumn(const ColumnDesc &columnDesc);
        virtual void createTable();
        const unsigned int row(unsigned int) const;
    private:
        int xsize, ysize;
        IPosition *data_pos;
        string nameStMan;


};


