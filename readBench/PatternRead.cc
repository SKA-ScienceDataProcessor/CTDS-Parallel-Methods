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

void pattern_read(unsigned int mpiRank, string tablename, unsigned int mpiSize){
   Table tab(tablename);
   unsigned int rows_per_process = tab.nrow()/mpiSize;

   ArrayColumn<Float> data(tab, "data");
   for (uInt i=0; i<rows_per_process; i++) {
      Array<float> data_s=data.get(mpiRank * rows_per_process + i); 
      cout<<"read table row ="<<mpiRank * rows_per_process + i<<", "<<"Rank="<<mpiRank<<endl;
   }
}



