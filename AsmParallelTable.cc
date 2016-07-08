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

#include "AsmParallelTable.h"

AsmParallelTable::AsmParallelTable(const string pTablename, const unsigned int pRows, const unsigned int pMpisize, const unsigned int pMpirank)
    :ParallelTable(pTablename, pRows, pMpisize, pMpirank)
{
    stman = new AdiosStMan("POSIX");
    if(mpi_rank>0){
        stringstream tablename_s;
        tablename_s << "/tmp/rank" << mpi_rank << ".casa";
        tablename = tablename_s.str();
    }
}

// This function receives the MPI rank and the iterator from the benchmark code, and returns the row id that it should write to.
const unsigned int AsmParallelTable::row(unsigned int i)const{
    return mpi_rank * rows_per_process + i;
}

void AsmParallelTable::addColumn(const ColumnDesc &cd){
    addColumnBalanced(cd);
}

void AsmParallelTable::createTable(){
    SetupNewTable newtab(tablename, *td, Table::New);
    AdiosStMan stman("POSIX");
    newtab.bindAll(stman);
    table = new Table(newtab, rows_total);
}

