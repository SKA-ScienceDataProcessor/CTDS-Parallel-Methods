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

ParallelTable::ParallelTable(const string pTablename, const unsigned int pRows, const unsigned int pMpisize, const unsigned int pMpirank){
    mpi_size = pMpisize;
    mpi_rank = pMpirank;
    tablename = pTablename;
    rows_total = pRows;
    rows_per_process = rows_total / mpi_size;

    if (mpi_rank == 0)
        td = new TableDesc("", "1", TableDesc::Scratch);
}

ParallelTable::~ParallelTable(){
    if (mpi_rank == 0){
        delete table;
        delete td;
    }
}

void ParallelTable::addColumn(const ColumnDesc &cd){
    if (mpi_rank == 0)
        td->addColumn (cd);
}

void ParallelTable::createTable(){
    if (mpi_rank == 0){
        SetupNewTable newtab(tablename, *td, Table::New);
        table = new Table(newtab, rows_total);
    }
    else{

    }

}

// This function returns the table that the benchmark code should write to.
Table* ParallelTable::get_table(){
    return table;
}

// This function receives the MPI rank and the iterator from the benchmark code, and returns the row id that it should write to.
const unsigned int ParallelTable::row(unsigned int i)const{
    return mpi_rank * rows_per_process + i;
}



