#include <iostream>
#include <iomanip>
#include "../src/TxJSON.h"

using namespace std;

struct Test {
  string src;
  string expect;
  TxJSON::StatusCode es;
  Test( string s, string e, TxJSON::StatusCode _es ):src(s),expect(e),es(_es){}
  bool print_judge( TxJSON& j){
    string ss;
    auto e = j.GetDict().Str();
    auto _es = j.GetStatus();  
    bool me  = ( expect == e );
    bool mes = es == _es;
    ss += me  ? "S " :"F ";
    ss += mes ? "S " : "F "; 
    if( me && mes ) cout<<"PASS     "<<"  ";
    else cout<<"FAIL "<<ss<<"  ";
    cout<<setw(20)<<src<<"\t["<<setw(20)<<expect<<""<<setw(20)<<e<<"]\t"<<TxJSON::GetErrorStr(es)<<"/"<<TxJSON::GetErrorStr(_es)<<endl;
    //cout<<expect.length()<<"\t"<<e.length()<<endl;
    return me&&mes;
  }
};
void _testTxJSON(){
  /*
     string ss[] = {
  //R"("123)",
  };

  for ( auto s : ss ){
  TxJSON j(s);
  cout<<s<<endl;
  cout<<j.GetString(j.ScanString(j.GetIterator(),'"')+1)<<endl;
  cout<<endl;
  }
  */
  vector<Test> sf = {
    Test( R"("\"123\\s\\\"  \\\\")", R"("\"123\\s\\\"  \\\\")", TxJSON::kSuccess ),
    Test( R"("\"123\\s\\\"-"  \\\\")", R"("\"123\\s\\\"-")", TxJSON::kSuccess ),
    Test( R"("")", R"("")", TxJSON::kSuccess ),
    Test( R"("123")", R"("123")", TxJSON::kSuccess ),
    Test( R"("123)", R"("ERROR")", TxJSON::kWrongString ),
    Test( "123", "123", TxJSON::kInt ),
    Test( "+123", "123", TxJSON::kInt ),
    Test( "-456", "-456", TxJSON::kInt ),
    Test( "0x12", "18", TxJSON::kInt ),
    Test( "034", "28", TxJSON::kInt ),
    Test( "-0abc", "0", TxJSON::kInt ),
    Test( "12e13", "1.2e+14", TxJSON::kFloat ),
    Test( "-.5e-12", "-5e-13", TxJSON::kFloat ),
    Test( "5.3e10", "5.3e+10", TxJSON::kFloat ),
    Test( "0x123.4", "291", TxJSON::kInt ),
    Test( "0x123e3", "74723", TxJSON::kInt ),
    Test( "-abc", "\"ERROR\"", TxJSON::kWrongNumber ),
    // Array
    Test( R"([ 123  ])",R"([ 123 ])", TxJSON::kSuccess ),
    Test( R"([ 123,1 ,2,5.3e10,"abc"  ])",R"([ 123, 1, 2, 5.3e+10, "abc" ])", TxJSON::kSuccess ),
    // Map
    Test( R"({ 123 : 456 })",R"({ "123":456 })", TxJSON::kSuccess ),
    Test( R"({ 123 : [2,3,4,"abc"] })",R"({ "123":[ 2, 3, 4, "abc" ] })", TxJSON::kSuccess ),
    Test( R"({ 123 : [2,3,4,"abc", { "abc":456,453:"123"}] })"
        ,R"({ "123":[ 2, 3, 4, "abc", { "453":"123", "abc":456 } ] })", TxJSON::kSuccess ),
  };
  if(0){
    for ( auto s : sf ){
      TxJSON j(s.src);
      j.Compile();
      s.print_judge( j );
    }
  }
  if(0){
    TxJSON j;
    if( j.LoadString( sf.back().src ) ){
      TxDict &d = j.GetDict();
      cout<<d.Str()<<endl;
      cout<<d["123"][4]["abc"].GetString()<<endl;
    }else{
      cout<<"Compile Error! "<<j.GetStatus()<<endl;
      auto it = j.GetCurrentIter();
      cout<<string(it-10,it)<<"==>"<<string(it,it+1)<<"<=="<<string(it+1,it+10)<<endl;
    }
  }

  if( 1 ){
    TxJSON j;
    if( j.LoadFile( "example.json" ) ){
      auto &d = j.GetDict();
      //cout<<d.Str(1)<<endl;
    }else{
      cout<<"Error while loading file "<<j.GetErrorStr(j.GetStatus())<<endl;
      auto it = j.GetCurrentIter();
      cout<<string(it-10,it)<<"==>"<<string(it,it+1)<<"<=="<<string(it+1,it+10)<<endl;
    }
  }
}

#ifndef Tx__MAIN
#define Tx__MAIN
int main(){
  _testTxJSON();
  return 0;
}
#endif
