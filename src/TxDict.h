#ifndef TxDict_H
#define TxDict_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <sstream>
#include <cstdlib>

//_________________________________________
class TxDict {
public:
  enum Type { kxUnknown=-1,kxInt, kxDouble,kxString,kxMap, kxArray } ;
  typedef std::initializer_list<TxDict> ItemList;
  typedef int                 Int;
  typedef double              Double;
  typedef std::string         String;
  typedef std::vector<TxDict>  Array;
  typedef std::unordered_map<std::string,TxDict> Map;
  //typedef std::map<std::string,TxDict> Map;
  typedef union {
    unsigned long long ul;
    Int     i;
    Double  d;
    String *s;
    Array  *a;
    Map    *m;
    void   *p;
  } StoreType;
  TxDict():fP{0},fType{kxUnknown}{}
  template<class T> TxDict( T v ){ Set(v); }
  TxDict( ItemList v ){ Set(v); }
  TxDict( const TxDict & o );
  TxDict( TxDict && o ) noexcept;
  ~TxDict(){ Delete(); }

  void Delete();

  void WarnType( Type a, Type b) const;
  void ErrorType( Type a, Type b) const;

  bool IsInt()    const { return fType==kxInt; };
  bool IsDouble() const { return fType==kxDouble; };
  bool IsString() const { return fType==kxString; };
  bool IsArray()  const { return fType==kxArray; };
  bool IsMap()    const { return fType==kxMap; };

  void Set(Int       v){Delete();fType=kxInt;fP.i=v; }
  void Set(Double    v){Delete();fType=kxDouble;fP.d=v; }
  void Set(const char* v){ Set(String(v)); }
  void Set(String    v){Delete();fType=kxString;fP.s=new String(v);}
  void Set(Array     v){Delete();fType=kxArray;fP.p=new Array(v);}
  void Set(Map       v){Delete();fType=kxMap;fP.p=new Map(v);}
  void Set(ItemList &v){ Delete();fType=kxArray;fP.a=new Array{v} ; }

  String Str(int _template=0, int step=0) const;

  Int    GetInt()    const;
  Double GetDouble() const;
  String GetString() const; 
  Array& GetArray()  const;
  Map&   GetMap()    const;

  operator Int()    const { return GetInt(); }
  operator Double() const { return GetDouble();}
  operator String() const { return GetString();}

  template<class T>
    TxDict& operator=(T v){ Set(v);return *this; }
  TxDict& operator=( const TxDict &o );
  TxDict& operator=( TxDict &&o );
  TxDict& operator[](int i){
    if( IsArray() ) return GetArray()[i];
    ErrorType( fType, kxArray );return *this;
  }
  TxDict& operator[](const char * s){
    if( IsMap() ) return GetMap()[s];
    ErrorType( fType, kxMap );return *this;
  }
  TxDict& operator[](String s){
    if( IsMap() ) return GetMap()[s];
    ErrorType( fType, kxMap );return *this;
  }

private:
  StoreType fP = {0};
  Type fType  = kxUnknown;;
};
#endif
