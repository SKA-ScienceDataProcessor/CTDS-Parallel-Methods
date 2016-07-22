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

#include "../ConcatParallelTable.h"
#include "../NolockParallelTable.h"
#include "../AsmParallelTable.h"
#include <string>
#include "../timing/tictak.h"


int main(int argc, char **argv)
{
    int rows, xsize, ysize;
    string tablename;
    int mpiRank, mpiSize;
    string nameStMan;

    MPI_Init(0,0);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

    if(argc < 6){
        cout << "./executable (int)nrRows (int)arrayX (int)arrayY (string)tablename (string)nameStMan" << endl;
        rows = 10;
        xsize = 20;
        ysize = 30;
        tablename = "tmp.tab";
        nameStMan = "StandardStMan";
    }
    else{
        rows = atoi(argv[1]);
        xsize = atoi(argv[2]);
        ysize = atoi(argv[3]);
        tablename = argv[4];
        nameStMan = argv[5];
    }

    // generate some data
    IPosition array_shape = IPosition(2, xsize, ysize);
    Array<Float> data_arr = Array<Float>(array_shape);
    indgen (data_arr);

    // define parallel table, add columns, and create table
    ParallelTable *tab = new ConcatParallelTable(tablename, rows, mpiSize, mpiRank);
//    ParallelTable *tab = new AsmParallelTable(tablename, rows, mpiSize, mpiRank);
//    ParallelTable *tab = new NolockParallelTable(tablename, rows, mpiSize, mpiRank, xsize, ysize, nameStMan);
    tab->addColumn (ArrayColumnDesc<Float>("data", array_shape, ColumnDesc::Direct));
    tab->createTable();

    // put data in, which is the same as serial CTDS tables
    ArrayColumn<Float> data_col(*(tab->get_table()), "data");
    for (int i=0; i<tab->rows(); i++){
        int row = tab->row(i);
        data_arr = row+1;
        cout << "mpi_rank = " << mpiRank << "  writing Row " << row <<endl;
        data_col.put(tab->row(i), data_arr);
    }

    delete tab;

    MPI_Finalize();
    return 0;
}
