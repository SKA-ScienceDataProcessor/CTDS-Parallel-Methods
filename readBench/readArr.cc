//    (c) University of Western Australia
//    International Centre of Radio Astronomy Research
//    M468, 35 Stirling Hwy
//    Crawley, Perth WA 6009
//    Australia
//
//    This library is free software: you can redistribute it and/or
//    modify it under the terms of the GNU General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License along
//    with this library. If not, see <http://www.gnu.org/licenses/>.
//
//    Any bugs, questions, concerns and/or suggestions please email to
//    jason.wang@icrar.org

#include <casacore/tables/Tables/ArrayColumn.h>
#include <casacore/casa/namespace.h>

int main(int argc, char **argv){
    if (argc < 2){
        cout << "./rAdiosStMan /path/to/file" << endl;
        return -1;
    }
    string filename = argv[1];
    Table casa_table(filename);
    uInt gettingRow = 1;
    if (argc == 3){
        gettingRow = atoi(argv[2]);
    }


    ROArrayColumn<Float> col_Float(casa_table, "data");

    for (int j=0; j<10; j++){
        Array<Float> arr_Float = col_Float.get(j);
        Vector<Float> vec_Float = arr_Float.reform(IPosition(1,arr_Float.nelements()));
        cout << endl << "Column: data_Float, Shape: " << arr_Float.shape() << endl;
        for (int i=0; i<arr_Float.nelements(); i++){
            cout << vec_Float[i] << "  ";
            if ((i+1) % (arr_Float.shape())(0) == 0)
                cout << endl;
        }
    }


    return 0;
}


