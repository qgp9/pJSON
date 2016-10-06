#ifndef TxJSON_H
#define TxJSON_H
#include <string>
#include <regex>
#include <cstdlib>
#include "TxDict.h"

class TxJSON{
public:
  enum StatusCode { kSuccess, kInt, kFloat, kFail, kUnknown, kWrongNumber, kWrongString, kWrongArray, kWrongMap,kWrongBoolean, kNStatusCode};
  static std::string GetErrorStr(StatusCode s ){
    std::vector<std::string> strs = { "Success","Int","Float","Fail","Unknown","WrongNumber","WrongString","WrongArray" ,"WrongMap", "WrongBoolean"};
    if( s < kNStatusCode )
      return strs[s];
    return std::string("No Status Code ");
  }

  typedef std::string            String;
  typedef std::string::iterator  Iterator;
  struct Result{
    Iterator it;
    StatusCode status = kUnknown;
    TxDict   dic;
    Result(Iterator _it, StatusCode _st, TxDict d):it(_it),status(_st),dic(d){}
    Result(Iterator _it, StatusCode _st=kUnknown ):it(_it),status(_st){}
    Result(){}
    Result( Result && o ){
      if( this != &o ) this->operator=(std::move(o));
    }
    Result& operator=( Result && o ){
      it = o.it;
      status = o.status;
      dic = std::move(o.dic);
      return *this;
    }
    Result && Set(Iterator _it, StatusCode _st=kUnknown, TxDict d=TxDict() ){ it=_it;status=_st;dic=d; return std::move(*this);}
  };

  TxJSON(){}
  TxJSON( String s ):fString(s),fIt(fString.begin()){}

  TxDict& GetDict() { return fResult.dic; }
  StatusCode GetStatus() const { return fResult.status; }
  Iterator GetCurrentIter(){ return fResult.it; }
  void SetJSONString( String s){ fString = s;fIt=fString.begin(); }

  bool Compile();

  bool LoadString( String s );
  bool LoadFile( String path ); 

private:
  Result   ScanItem(Iterator &it);
  Result  ScanArray(Iterator &it);
  Result  ScanMap(Iterator &it);
  Result ScanNumber(Iterator &it);
  Result  ScanString(Iterator &it, char quote);
  Result  ScanBoolean(Iterator &it);

  bool SkipWhiteSpace(Iterator &it);
  bool Next(Iterator &it);
  bool Next(){ return Next(fIt); }
  String     fString;
  Iterator   fIt;
  Result     fResult;
  const static std::regex re_int;
  const static std::regex re_float;
  const static std::regex re_boolean;
};


#endif
