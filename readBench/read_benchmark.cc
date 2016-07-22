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
#include "../getFiles/getfiles.h"
#include <adios.h>

int main(int argc, char **argv)
{
    int mpiRank, mpiSize;
    string tablePath;
    
    MPI_Init(0,0);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    if(argc < 2){
        cout << "./executable (string)tablePath" << endl;
        tablePath = "./data";
    }
    else{
        tablePath = atoi(argv[1]);
    }
    //EmbarrassingRead
    vector<string> tablename=getFiles(tablePath);
    for (int i=0; i<tablename.size(); i++)
    {
        cout<<tablename[i]<<endl;
    }
   
    if(mpiSize>tablename.size()){
      cout<<"number of processes must less than or equal to number of tables!"<<endl;
      exit(1);
    }
    embarrassing_read(mpiRank, tablename, tablePath);    
    
   MPI_Finalize();
    return 0;
}
