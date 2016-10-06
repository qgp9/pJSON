#include <iostream>
#include "TxDict.h"
using namespace std;
struct hasTxDict {
  TxDict dic;
  hasTxDict(TxDict d):dic(d){}
  hasTxDict(){}
};
hasTxDict returnTxDict(){ return hasTxDict(TxDict(string("123"))); }
void _testTxDict(){
  /*
  TxDict aa = {4.2,"ab",4, {12,13,14} };
  cout<<aa.Str()<<endl;
  TxDict any = {4.2,-2,"abc",{1,2},
    TxDict::Map{ 
      {"test","12.1"},
      {"test2",345},
      {"test3",
        { 1,2,
          {"a","b","c",3,5} 
        }
      }
    }
  };
  cout<<"DEBUG B"<<endl;
  cout<<"DEBUG 1 : "<<any.Str()<<endl;
  cout<<"DEBUG 2 : "<<any[0].GetDouble()<<endl;
  cout<<"DEBUG 2 : "<<any[1].GetInt()<<endl;
  cout<<"DEBUG 2 : "<<any[2].GetString()<<endl;
  cout<<"DEBUG 2 : "<<any[4]["test"].GetString()<<endl;
  cout<<"DEBUG 2 : "<<any[4]["test"].GetString()<<endl;
  cout<<"DEBUG 2 : "<<any[4]["test"].GetInt()<<endl;
  cout<<"DEBUG 2 : "<<any[4]["test"].GetDouble()<<endl;

  cout<<"DEBUG C"<<endl;
  int i = any[4]["test"];
  cout<<"DEBUG 3 : "<<i<<endl;
  double d = any[4]["test"];
  cout<<"DEBUG 3 : "<<d<<endl;

  TxDict a1 = aa;
  TxDict a2(aa);
  TxDict a3( TxDict(string("test")));
  */
  cout<<"DEBUG 1"<<endl;
  hasTxDict has ;
  cout<<"DEBUG 2"<<endl;
  has = returnTxDict();
  cout<<"DEBUG 3"<<endl;
}
#ifndef Tx__MAIN
#define Tx__MAIN
int main(){
  _testTxDict();
  return 0;
}
#endif


