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

#include "ConcatParallelTable.h"

ConcatParallelTable::ConcatParallelTable(const string pTablename, const unsigned int pRows, const unsigned int pMpisize, const unsigned int pMpirank)
    :ParallelTable(pTablename, pRows, pMpisize, pMpirank),
    master_tablename(pTablename)
{
    stringstream tablename_s;
    tablename_s << pTablename << mpi_rank;
    tablename = tablename_s.str();
}

const unsigned int ConcatParallelTable::row(unsigned int i)const{
    return i;
}

void ConcatParallelTable::addColumn(const ColumnDesc &cd){
    addColumnBalanced(cd);
}

void ConcatParallelTable::createTable(){
    createTableBalanced(rows_per_process);

    // Close sub-tables first.
    if(table){
        delete table;
    }

    if (mpi_rank == 0){
        // Concatenate sub-tables.
        Block<String> names(mpi_size);
        for (int i=0; i<mpi_size; i++){
            stringstream tablename_s;
            tablename_s << master_tablename << i;
            names[i] = tablename_s.str();
        }
        Table concTab (names, Block<String>(), Table::Old, TSMOption(), "subtables");
        concTab.rename (master_tablename, Table::New);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // Re-open sub-tables.
    tablename = master_tablename + "/subtables/" + tablename;
    table = new Table(tablename, Table::Update);
}


