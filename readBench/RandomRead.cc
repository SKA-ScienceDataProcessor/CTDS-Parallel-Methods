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

#include "RandomRead.h"
#include <time.h>

#define random(x) (rand()%x)
unsigned int tabRank;
unsigned int rowsRank;

unsigned int Random(int m, int n)
{
   int pos, dis;
   if(m == n){
      return m;
   }
   else if(m > n){
      pos = n;
      dis = m - n + 1;
      return rand() % dis + pos;
   }
   else{
      pos = m;
      dis = n - m + 1;
      return rand() % dis + pos;
   }
}

struct TableProperty random_read_multiTable(unsigned int mpiSize, string tablename, string tablePath){
   TableProperty TP;
   srand((unsigned int)time(0));
   tabRank = random(mpiSize);
   stringstream ss;
   ss<<tabRank;
   string tabRank_s = ss.str();
   Table tab(tablePath + tablename + tabRank_s);

   unsigned int nrow = tab.nrow();

   ArrayColumn<Float> data(tab, "data");
   Array<float> data_s;

   for (uInt i=0; i<tab.nrow(); i++) {
       data_s=data.get(i);
   }

   unsigned int len = sqrt(data_s.nelements());
   long CellSize = len*len*sizeof(float);
   long TableSize = CellSize * nrow;
   TP.TableSize = TableSize;
   TP.rows = nrow;
   TP.xsize = len;
   TP.ysize = len;

//   cout<<"TableSize = "<<TableSize<<","<<"rows = "<<nrow<<","<<"xsize = "<<len<<","<< "ysize = "<<len<<endl;
//   cout<<"read "<<tablename<<" finished, "<<endl;

   return TP;
}

struct TableProperty random_read_singleTable(unsigned int mpiRank, string tablename, unsigned int mpiSize){
   TableProperty TP;
   srand((unsigned int)time(0));
   Table tab(tablename);
   if (mpiSize > tab.nrow()){
      exit(-1);
   }
   
   unsigned int rows_per_process = tab.nrow()/mpiSize;
   unsigned int nrow = tab.nrow();
   
   ArrayColumn<Float> data(tab, "data");
   Array<float> data_s;

   for (uInt i=0; i<rows_per_process; i++) {
      rowsRank=Random(mpiRank * rows_per_process, (mpiRank + 1) * rows_per_process - 1);
      data_s=data.get(rowsRank);
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
