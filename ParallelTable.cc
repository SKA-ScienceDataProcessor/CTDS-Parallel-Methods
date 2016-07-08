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

ParallelTable::ParallelTable(const string pTablename, const unsigned int pRows, const unsigned int pMpisize, const unsigned int pMpirank)
    :mpi_size(pMpisize),
    mpi_rank(pMpirank),
    tablename(pTablename),
    rows_total(pRows),
    rows_per_process(rows_total / mpi_size),
    stman(0),
    table(0),
    td(0)
{
    td = new TableDesc("", "1", TableDesc::Scratch);
}

ParallelTable::~ParallelTable(){
    if (stman){
        delete stman;
        stman = 0;
    }
    if (table){
        delete table;
        table = 0;
    }
    if (td){
        delete td;
        td = 0;
    }
}


void ParallelTable::addColumnBalanced(const ColumnDesc &cd){
    td->addColumn (cd);
}

void ParallelTable::addColumnUnbalanced(const ColumnDesc &cd){
    if (mpi_rank == 0)
        td->addColumn (cd);
}

void ParallelTable::createTableBalanced(unsigned int pRows){
    SetupNewTable newtab(tablename, *td, Table::New);
    if (stman){
        newtab.bindAll(*stman);
    }
    table = new Table(newtab, pRows);
}

void ParallelTable::createTableUnbalanced(unsigned int pRows){
    if (mpi_rank == 0){
        // On master rank, create a table and then close it.
        SetupNewTable newtab(tablename, *td, Table::New);
        table = new Table(newtab, pRows);
        delete table;
    }
}

// This function returns the table that the benchmark code should write to.
Table* ParallelTable::get_table(){
    return table;
}


const unsigned int ParallelTable::rows()const{
    return rows_per_process;
}


