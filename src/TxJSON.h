#ifndef TxJSON_H
#define TxJSON_H
#include <string>
#include <regex>
#include <cstdlib>
#ifndef TxDict_H
#include "TxDict.h"
#endif

#define Next(x) (++x!=fString.end())
#define SkipWhiteSpace(it)  --it;while( Next(it) && (*it==' ' || *it=='\t' || *it=='\n' || *it=='\r')){}
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
  TxJSON( String s ):fString(s),fStrPtr(&fString),fIt(fStrPtr->begin()){}
  TxJSON( String *s ):fString(),fStrPtr(s),fIt(fStrPtr->begin()){}
  TxJSON( String &&s ):fString(std::move(s)),fStrPtr(&fString),fIt(fStrPtr->begin()){}

  TxDict& GetDict() { return fResult.dic; }
  StatusCode GetStatus() const { return fResult.status; }
  Iterator GetCurrentIter(){ return fResult.it; }
  void SetJSONString( String s){ fString = s;fStrPtr=&fString;fIt=fStrPtr->begin(); }
  void SetJSONStringLV( String &&s) noexcept { fString = std::move(s);fStrPtr=&fString;fIt=fStrPtr->begin(); }
  void SetJSONStrPtr( String *s){ fStrPtr=s;fIt=fStrPtr->begin(); }

  bool Compile();

  bool LoadString( String s );
  bool LoadFile( String path ); 

private:
  Result ScanItem(Iterator &it);
  Result ScanArray(Iterator &it);
  Result ScanMap(Iterator &it);
  Result ScanNumber(Iterator &it);
  Result ScanString(Iterator &it, char quote);
  Result ScanBoolean(Iterator &it);

  /*
  inline bool SkipWhiteSpace(Iterator &it){
    --it;
    while( Next(it) && (*it==' ' || *it=='\t' || *it=='\n' || *it=='\r')){
    }
    return it != fStrPtr->end();
  }
  */
  //inline bool Next(Iterator &it);
  /*
  inline bool Next(Iterator &it){
    if( it == fString.end() ) return false;
    it++; return (it != fString.end()) ;
  }
  inline bool Next(){ return Next(fIt); }
  */

//  inline bool Next(Iterator &it){return (++it != fStrPtr->end()) ;}
  String     fString;
  String *   fStrPtr;
  Iterator   fIt;
  Result     fResult;
  const static std::regex re_boolean;
};


#endif
