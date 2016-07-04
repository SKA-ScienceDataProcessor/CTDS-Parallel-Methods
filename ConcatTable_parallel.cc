// (c) SHAO
// 
// Nandan load 80, Shanghai WA 200030
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
//   lbq@shao.ac.cn


#include <casacore/tables/Tables/TableDesc.h>
#include <casacore/tables/Tables/SetupNewTab.h>
#include <casacore/tables/Tables/Table.h>
#include <casacore/tables/Tables/ScaColDesc.h>
#include <casacore/tables/Tables/ScalarColumn.h>
#include <casacore/tables/Tables/TableRecord.h>
#include <casacore/tables/TaQL/ExprNode.h>
#include <casacore/casa/Arrays/ArrayIO.h>
#include <casacore/casa/Arrays/ArrayUtil.h>
#include <casacore/casa/Containers/Block.h>
#include <casacore/casa/Utilities/Assert.h>
#include <casacore/casa/Exceptions/Error.h>
#include <casacore/casa/iostream.h>

#include <casacore/casa/namespace.h>

#include <mpi.h>

#include <string>

// <summary>
// Test parallel for the ConcatTable class
// </summary>
 
string filename;
int mpiRank, mpiSize;
int NrRows;

MPI_Status status;

// First build a description.
void createTable(const String& name, Int stval, Int nrrow)
{
  // Build the table description.
  TableDesc td;
  td.addColumn (ScalarColumnDesc<Int>("aint"));
  td.addColumn (ScalarColumnDesc<Float>("afloat"));
  // Now create a new table from the description.
  SetupNewTable newtab(name, td, Table::New);
  Table tab(newtab, nrrow);
  // Fill the table.
  ScalarColumn<Int>   icol(tab, "aint");
  ScalarColumn<Float> fcol(tab, "afloat");
  for (Int i=0; i<nrrow; ++i) {
    icol.put (i, i+stval);
    fcol.put (i, i+stval+1.);
  }
}

void checkTable (Int stval, uInt nrow)
///void checkTable (const Table& tab, uInt nkey, uInt nsubrow, Int stval,
///		 Bool reorder=True, uInt nrow=10)
{
  Table tab("tConcatTable_tmp.conctab");
  AlwaysAssertExit (tab.nrow() == nrow);
  /*
  AlwaysAssertExit (tab.keywordSet().nfields() == nkey);
  AlwaysAssertExit (tab.keywordSet().asInt("key1") == 1);
  AlwaysAssertExit (tab.keywordSet().asString("key2") == "abc");
  if (nkey == 3) {
    AlwaysAssertExit (tab.keywordSet().asTable("keysub").nrow() == nsubrow);
  }
  */
  ScalarColumn<Int> aint(tab, "aint");
  ScalarColumn<Float> afloat(tab,  "afloat");
  for (uInt i=0; i<tab.nrow(); i++) {
    AlwaysAssertExit (aint(i) == stval);
    AlwaysAssertExit (afloat(i) == stval+1.);
    ++stval;
  }
}

void concatTables(Block<String> &names)
{
  Table concTab (names, Block<String>(), Table::Old, TSMOption(), "SUBDIR");
  concTab.rename ("tConcatTable_tmp.conctab", Table::New);
}

int main(int argc, char **argv)
{
  MPI_Init(0,0);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
  MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

  if(argc < 1){
     cout << "./ConcatTable_parallel (int)nrRows" << endl;
     exit(1);
  }
  
  NrRows = atoi(argv[1]);

  //according mpi process rank to define filename
  stringstream filename_s;
  filename_s << "tConcatTable3_tmp.tab" << mpiRank;
  filename = filename_s.str();

  Block<String> names(mpiSize);
  int source;
  char recvfilename[100];

  try {
    createTable (filename, mpiRank*NrRows, NrRows);

  //  send filename to process 0
    if(mpiRank>0){
      MPI_Send(filename.c_str(),strlen(filename.c_str())+1,MPI_CHAR,0,99,MPI_COMM_WORLD);
      //cout<<"Rank="<<mpiRank<<","<<"filename="<<filename<<endl;
    }
    else{ //process 0 receive other process filename
      names[0]=filename;
      for(source=1;source<mpiSize;source++){
         MPI_Recv(recvfilename,sizeof(recvfilename),MPI_CHAR,source,99,MPI_COMM_WORLD,&status);
        // cout<<"Rank="<<source<<","<<"filename="<<recvfilename<<sizeof(recvfilename)<<endl;
         string s(recvfilename);
         names[source]=s;
       //  cout<<"Rank="<<source<<","<<"filename="<<names[source]<<endl;
      }     
    }
  //process 0 concatTable and checkTable 
    if(mpiRank==0){
      concatTables(names);
      checkTable (0, NrRows*mpiSize);
    }
  } catch (AipsError x) {
    cout << "Exception caught: " << x.getMesg() << endl;
    return 1;
  }

  MPI_Finalize(); 

  return 0;
}
