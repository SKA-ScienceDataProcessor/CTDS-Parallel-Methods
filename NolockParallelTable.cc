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

#include "NolockParallelTable.h"

NolockParallelTable::NolockParallelTable(const string pTablename, const unsigned int pRows, const unsigned int pMpisize, const unsigned int pMpirank)
    :ParallelTable(pTablename, pRows, pMpisize, pMpirank)
{
}

NolockParallelTable::~NolockParallelTable(){
    for (int i=0; i<mpi_size; i++){
        if (mpi_rank == i){
            if (table){
                delete table;
                table = 0;
            }
            if (td){
                delete td;
                td = 0;
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

void NolockParallelTable::addColumn(const ColumnDesc &cd){
    addColumnUnbalanced(cd);
}

void NolockParallelTable::createTable(){
    // On master rank, create a table and then close it.
    createTableUnbalanced();
    MPI_Barrier(MPI_COMM_WORLD);
    // Then open the table on all ranks.
    for (int i=0; i<mpi_size; i++){
        // To avoid any ranks open the table at the same time.
        if (mpi_rank == i){
            table = new Table(tablename, Table::Update);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}




