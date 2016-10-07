#ifndef TxJSON_H
#include "TxJSON.h"
#include <fstream>
#include <sstream>
#endif

#define Next(x) (++x!=fString.end())
#define SkipWhiteSpace(it)  --it;while( Next(it) && (*it==' ' || *it=='\t' || *it=='\n' || *it=='\r')){}

const std::regex TxJSON::re_boolean(R"(^true|false)");

bool TxJSON::LoadString( String s ){
  if( s.empty() ) return false;
  SetJSONString(s);
  return Compile();
}

bool TxJSON::LoadFile( String path ){
  std::ostringstream os;
  os << std::ifstream(path.c_str()
      //,std::ios::in|std::ios::binary|std::ios::ate
      ).rdbuf();
  SetJSONStringLV( std::move(os.str()) );
  return Compile();
}

bool TxJSON::Compile(){
  fResult = ScanItem(fIt);
  return fResult.status < kFail;
}

TxJSON::Result  TxJSON::ScanItem(Iterator &it){
  Result r;
  SkipWhiteSpace(it);

  if( *it == '"' || *it=='\'') r = ScanString(it, *it);
  else if( (*it>='0' && *it<='9') || *it == '.' || *it=='+' || *it=='-' )
    r=ScanNumber(it);
  else if( *it=='t' || *it=='f' ) r=ScanBoolean(it);
  else if( *it == '[' ) r=ScanArray(it);
  else if( *it == '{' ) r=ScanMap(it);
  else {
    r.Set(it+1, kUnknown);
  }
  return r;
}

TxJSON::Result  TxJSON::ScanArray(Iterator &it){
  bool closed = false;
  Result rArray;
  auto & dict = rArray.dic;
  dict = TxDict::Array() ;
  Result r;
  while( Next(it) && closed == false){
    r = ScanItem(it);
    SkipWhiteSpace(it);
    if( *it == ',' ){   // Allow traling comma
      auto nit = it+1;
      SkipWhiteSpace(nit);
      if( *nit == ']') it = nit;
    }
    if( *it == ']' ) closed = true;
    else if( *it !=',' ) return r.Set(it,kWrongArray);
    if( r.status < kFail ){
      dict.GetArray().push_back( std::move(r.dic) );
    }
    else return r;
  }
  if( closed ){ 
    rArray.it=it;rArray.status=kSuccess;
    return rArray;
  }
  return Result( it, kWrongArray );
}

TxJSON::Result  TxJSON::ScanMap(Iterator &it){ 
  Result rMap;
  rMap.dic = TxDict::Map();
  Result r;
  bool closed = false;
  bool wait_key = true;
  String key = "";
  while( Next(it) && closed == false){
    auto r = ScanItem(it);it=r.it;
    if( r.status > kFail ) return r;
    SkipWhiteSpace(it);
    if( *it == '}' && wait_key==false ) closed = true;
    if( *it == ':' && wait_key==true && (r.dic.IsInt()||r.dic.IsDouble()||r.dic.IsString())  ) { 
      key = r.dic.GetString();
      wait_key = false;
    }else if( (*it ==','||*it=='}') && wait_key==false ){
      //dict[key] = std::move(d);0
      rMap.dic.GetMap().emplace( key, std::move(r.dic));
      wait_key = true;
    }
    else return r.Set(it,kWrongMap);
  }
  rMap.it = it;rMap.status=kSuccess;
  if( closed ) return rMap;

  return r.Set( it, kWrongMap );
}

TxJSON::Result  TxJSON::ScanBoolean(Iterator &it){
  char * cp = &*it;
  if( *cp == 't' && *(cp+1)=='r' && *(cp+2)=='u' && *(cp+3)=='e' ){
    it=it+4;
    Result r(it,kSuccess);
    r.dic = 1;
    return r;
  }else if( *cp == 'f' && *(cp+1)=='a' && *(cp+2)=='l' && *(cp+3)=='s' && *(cp+4)=='e' ){
    it=it+5;
    Result r(it,kSuccess);
    r.dic = 0;
    return r;
  }
  return Result(it, kWrongBoolean );
}

TxJSON::Result TxJSON::ScanNumber(Iterator &it){
  int  sign = 1;
  bool begin_with_zero = false;
  bool begin_demical = false;
  bool begin_index   = false;
  bool closed = false;
  auto bit = it;

  long long rsi = 0;
  if( *it == '-' || *it== '+'){
    sign = *it=='-'?-1:1;bit++;
    if(!Next(it)) return Result(it,kWrongNumber);
  }
  if( *it == '0' ) {
    begin_with_zero=true;
    if( !Next(it) ){
      Result r(it,kInt); r.dic = 0;
      return r;
    }
    if( *it == 'x' ) {
      auto bit = it+1;
      while( Next(it) && ( (*it>='0' && *it<='9') || (*it>='a' && *it<='f') || (*it>='A'&&*it<='F')));
      Result r(it,kInt);
      r.dic=int(strtoul(String(bit,it).c_str(), NULL, 16))*sign;
      return r;
    }
  }
  rsi = *it-'0';
  while( (*it>='0' && *it<='9') && Next(it) ){ rsi = rsi*10+*it-'0';}
  if( *it == '.' && !begin_demical && !begin_index){
    begin_demical = true;
    Next(it);
    while( (*it>='0' && *it<='9') && Next(it));
  }
  if( (*it == 'e' || *it == 'E') && begin_index == false){
    begin_index = true;
    if(!Next(it))  return Result(it,kWrongNumber);
    if( *it == '-' || *it=='+' )
      if(!Next(it))  return Result(it,kWrongNumber);
    while( Next(it) && (*it>='0' && *it<='9') );
  }
  if( bit == it ) return Result(it,kWrongNumber);
  if( begin_demical || begin_index ){
    Result r(it,kFloat);
    r.dic = atof(String(bit,it).c_str())*sign;
    return r;
  }else if( !begin_with_zero ){
    Result r(it, kInt);
    //r.dic = atoi(String(bit,it).c_str())*sign;
    r.dic = int(rsi)*sign;
    return r;
  }
  it = bit;
  while( (*it>='0' && *it<='7' ) && Next(it) );
  Result r(it,kInt);
  if( it == bit ) r.dic = 0;
  else r.dic = int(strtoul(String(bit,it).c_str(), NULL, 8))*sign;
  return r;
}

TxJSON::Result  TxJSON::ScanString(Iterator &it, char quote){
  Result r;
  auto bit = it;
  bool flip_escape = false;
  bool closed = false;
  while(Next(it) && !closed){
    if( *it=='\\' ){
      do{
        flip_escape = flip_escape ? false : true;
      } while(Next(it) && *it=='\\');
    }
    if( *it==quote && !flip_escape ) closed = true;
    flip_escape=false;
  }
  if( !closed ) return r.Set(bit, kWrongString,"ERROR");
  r.it=it;r.status=kSuccess;
  r.dic = String(bit+1,it-1);
  return r;
}


#undef Next
#undef SkipWhiteSpace

