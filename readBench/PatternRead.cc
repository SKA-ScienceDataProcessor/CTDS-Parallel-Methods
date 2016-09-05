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

#include "PatternRead.h"

struct TableProperty pattern_read(unsigned int mpiRank, string tablename, unsigned int mpiSize){
   TableProperty TP;

   Table tab(tablename);
   unsigned int rows_per_process = tab.nrow()/mpiSize;
   unsigned int nrow = tab.nrow();

   ArrayColumn<Float> data(tab, "data");
   Array<float> data_s;

   for (uInt i=0; i<rows_per_process; i++) {
      data_s=data.get(mpiRank * rows_per_process + i); 
      cout<<"read table row ="<<mpiRank * rows_per_process + i<<", "<<"Rank="<<mpiRank<<endl;
   }
   unsigned int len = sqrt(data_s.nelements());
   long CellSize = len*len*sizeof(float);
   long TableSize = CellSize * nrow;
   TP.TableSize = TableSize;
   TP.rows = nrow;
   TP.xsize = len;
   TP.ysize = len;

//   cout<<"TableSize = "<<TableSize<<","<<"rows = "<<nrow<<","<<"xsize = "<<len<<","<< "ysize = "<<len<<endl;
//   cout<<"read "<<tablename<<" finished, "<<"Rank="<<mpiRank<<endl;

   return TP;

}



