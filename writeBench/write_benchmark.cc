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




/*

void concatTables(Block<String> &names)
{
    Table concTab (names, Block<String>(), Table::Old, TSMOption(), "SUBDIR");
    concTab.rename (tablename, Table::New);
}

void checkTable (uInt nrow)
    ///void checkTable (const Table& tab, uInt nkey, uInt nsubrow, Int stval,
    ///		 Bool reorder=True, uInt nrow=10)
{
    Table tab(tablename);
    AlwaysAssertExit (tab.nrow() == nrow);

    ArrayColumn<Float> data(tab, "data");
    //cout<<data.get(0)<<endl;
    for (uInt i=0; i<tab.nrow(); i++) {
        Array<float> data_s=data.get(i);
        //2 d converted to a d array
        Vector<float> data_s_con=data_s.reform(IPosition(1, data_s.nelements()));
        Vector<float> data_s_rf=data_arr.reform(IPosition(1, data_arr.nelements()));

        for(int j=0; j<data_arr.nelements(); j++){
            if(data_s_rf[j] != data_s_con[j]){
                cout << "row = " << i << ", column = data, element = " << j << endl;
                cout << "write data value = " << data_s_con[j] << ", data_arr value = " << data_s_rf[j] << endl;
                exit(-1);
            }
        }

    }
}

// First build a description.
void addColumns(ParallelTable *tab)
{

    // Build the table description.
    TableDesc td("", "1", TableDesc::Scratch);
    // Now create a new table from the description.
    SetupNewTable newtab(name, td, Table::New);
    Table tab(newtab, nrrow);


    // define column objects and link them to the table

    for (Int i=0; i<nrrow; ++i) {
        data_col.put (i, data_arr);
    }
}


    */


int main(int argc, char **argv)
{
    int rows, xsize, ysize;
    string tablename;
    int mpiRank, mpiSize;

    MPI_Init(0,0);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

    if(argc < 5){
        cout << "./executable (int)nrRows (int)arrayX (int)arrayY (string)tablename" << endl;
        rows = 10;
        xsize = 20;
        ysize = 30;
        tablename = "tmp.tab";
    }
    else{
        rows = atoi(argv[1]);
        xsize = atoi(argv[2]);
        ysize = atoi(argv[3]);
        tablename = argv[4];
    }

    IPosition array_shape = IPosition(2, xsize, ysize);
    Array<Float> data_arr = Array<Float>(array_shape);
    indgen (data_arr);

    ParallelTable *tab = new NolockParallelTable(tablename, rows, mpiSize, mpiRank);
    tab->addColumn (ArrayColumnDesc<Float>("data", array_shape, ColumnDesc::Direct));
    tab->createTable();

    ArrayColumn<Float> data_col(*(tab->get_table()), "data");

    for (int i=0; i<tab->rows(); i++){
        int row = tab->row(i);
        data_arr = row+1;
        cout << "mpi_rank = " << mpiRank << "  writing Row " << row <<endl;
        data_col.put(tab->row(i), data_arr);
    }

    delete tab;

    //according mpi process rank to define filename
    /*
    stringstream filename_s;
    filename_s << "tConcatTable3_tmp.tab" << mpiRank;
    filename = filename_s.str();
    */



    /*
    Block<String> names(mpiSize);
    int source;
    char recvfilename[100];

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

    try {
        MPI_Barrier(MPI_COMM_WORLD);
        tictak_add((char*)filename.c_str(),0);
        createTable (filename, NrRows); //
        MPI_Barrier(MPI_COMM_WORLD);
        tictak_add((char*)"end",0);
        //process 0 concatTable and checkTable
        if(mpiRank==0){
            concatTables(names);
            //  if will check Table delete follow comment
            //    checkTable (NrRows*mpiSize);

            float Seconds = tictak_total(0,0);
            unsigned long long CellSize = atoi(argv[2])*atoi(argv[3])*sizeof(float);
            unsigned long long TableSize = CellSize * NrRows * mpiSize;
            int Mps = TableSize / Seconds / 1000000;

            cout << "MB/s," << Mps;
            cout << ",Seconds," << Seconds;
            cout << ",TableSize(Byte)," << TableSize;
            cout << ",NrRows," << NrRows;
            cout << ",CellSize(Byte)," << CellSize;
            cout << ",MpiSize," << mpiSize;
            cout << ",Xlength," << atoi(argv[2]);
            cout << ",Ylength," << atoi(argv[3]);
            cout << endl;
        }
    } catch (AipsError x) {
        cout << "Exception caught: " << x.getMesg() << endl;
        return 1;
    }
    */


    MPI_Finalize();
    return 0;
}
