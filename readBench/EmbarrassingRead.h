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

#include "OpenTable.h"

class EmbarrassingRead : public OpenTable{
    public:
        EmbarrassingRead(const string, const unsigned int, const unsigned int, const unsigned int);
        virtual ~EmbarrassingRead();
        virtual void embarrassing_read(unsigned int mpiRank, const string tablename[]);
        virtual void func()
    private:
        int mpiRank;
        IPosition *data_pos;
        string nameStMan;


};
