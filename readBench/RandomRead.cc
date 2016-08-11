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
#include<time.h>

#define random(x) (rand()%x)
unsigned int tabRank;
unsigned int rowsRank;


void random_read_multiTable(unsigned int Ntable, string tablename, string tablePath){
   srand((unsigned int)time(0));
   for (uInt m=0; m<Ntable; m++){
      tabRank = random(Ntable);
      stringstream ss;
      ss<<tabRank;
      string tabRank_s = ss.str();
      Table tab(tablePath + tablename + tabRank_s);

      ArrayColumn<Float> data(tab, "data");
      for (uInt i=0; i<tab.nrow(); i++) {
         Array<float> data_s=data.get(i);
      }
   }
    //  cout<<"read "<<tablename+mpiRank_s<<" finished, "<<"Rank="<<mpiRank<<endl;
}

void random_read_singleTable(string tablename){
   srand((unsigned int)time(0));
   Table tab(tablename);
   
   ArrayColumn<Float> data(tab, "data");
   for (uInt i=0; i<tab.nrow(); i++) {
      rowsRank=random(tab.nrow());
      Array<float> data_s=data.get(rowsRank);
   }
}
