#include <string.h>
#include <stdio.h>

string str_split(string sub_tablename, const char * split){
    char * sub_tablename_c;
    const int len = sub_tablename.length();
    sub_tablename_c = new char[len+1];
    strcpy(sub_tablename_c,sub_tablename.c_str());
    char * p;
    string ss[10];
    int i=0;
    p=strtok(sub_tablename_c, split);
    while(p!=NULL){
//      cout<<p<<endl;
      ss[i]=p;
      p = strtok(NULL,split);
      i=i+1;
    }
    //cout<<ss[i-1]<<endl;
    sub_tablename=ss[i-1];

   return sub_tablename;
}
