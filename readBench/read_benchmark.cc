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

#include "EmbarrassingRead.h"
#include "PatternRead.h"  
#include "RandomRead.h"
#include "../getFiles/getfiles.h"
#include <adios.h>
#include "../timing/tictak.h"

int main(int argc, char **argv)
{
    int mpiRank, mpiSize;
    string tablePath;
    string tablename;
    TableProperty TP;
    
    MPI_Init(0,0);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    if(argc < 2){
        cout << "./executable (string)tablePath" << endl;
        tablePath = "/home/blao/CTDS-Parallel-Methods/readBench/data/";
        tablename = "Table";
    }
    else{
        tablePath = atoi(argv[1]);
        tablename = atoi(argv[2]);
    }
    //EmbarrassingRead
   MPI_Barrier(MPI_COMM_WORLD); 
   tictak_add((char*)tablename.c_str(),0);
   TP = embarrassing_read(mpiRank, tablename, tablePath);
//   pattern_read(mpiRank, tablename, mpiSize); 
//   random_read_multiTable(Ntable, tablename, tablePath);   
//   random_read_singleTable(tablename); 
   MPI_Barrier(MPI_COMM_WORLD);
   tictak_add((char*)"end",0);

   if(mpiRank == 0){

       float Seconds = tictak_total(0,0);
       uint64_t CellSize = TP.xsize*TP.ysize*sizeof(float);
       uint64_t TableSize = TP.TableSize;
       int Mps = TableSize / Seconds / 1000000;

       cout << "MB/s," << Mps;
       cout << ",Seconds," << Seconds;
       cout << ",TableSize(Byte)," << TableSize;
       cout << ",NrRows," << TP.rows;
       cout << ",CellSize(Byte)," << CellSize;
       cout << ",MpiSize," << mpiSize;
       cout << ",Xlength," << TP.xsize;
       cout << ",Ylength," << TP.ysize;
       cout << endl;
   }
 
   MPI_Finalize();
    return 0;
}
