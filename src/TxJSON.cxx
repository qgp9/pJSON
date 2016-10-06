#ifndef TxJSON_H
#include "TxJSON.h"
#include <fstream>
#include <sstream>
#endif

const std::regex TxJSON::re_int(R"(^[+-]?(0x[\da-fA-F]+|0[0-8]+|\d+))");;
const std::regex TxJSON::re_float(R"(^[+\-]?(?:\d+\.\d*|\d*\.\d+|\d+)([eE][+\-]?\d+)?)");
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
  return LoadString( os.str() );
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
  Result r;
  auto rend = std::sregex_iterator();
  auto rbool = std::sregex_iterator( it, fString.end(), re_boolean);
  if( rbool == rend )
    return r.Set( it, kWrongBoolean, "ERROR-WrongBoolean");
  char c = *it;
  it += rbool->str().length();
  r.it = it;
  r.status = kSuccess;
  r.dic =  (c=='t') ? 1 : 0;
  return r; // TODO Add bool to Dict. True or TRUE also?
}

TxJSON::Result TxJSON::ScanNumber(Iterator &it){
  Result r;
  auto rend = std::sregex_iterator();
  auto rinte = std::sregex_iterator( it, fString.end(), re_int );
  auto rfloat = std::sregex_iterator( it, fString.end(), re_float );
  if( rinte == rend && rfloat == rend ) {
    r.Set( it, kWrongNumber,"ERROR" );
    return r;
  }
  if( 
      (rfloat == rend && rinte != rend)
      || rfloat->str().length() <= rinte->str().length() 
    ) {
    int res;
    std::smatch sm = *rinte;
    String si  = sm.str();
    String sii = sm[1];
    if( sii == "0" ) res = 0;
    else if( sii[1] == 'x' ) res = strtoul(sii.substr(2).c_str(), NULL, 16);
    else if( sii[0] == '0' ) res = strtoul(sii.substr(1).c_str(), NULL, 8);
    else res = atoi( sii.c_str() );
    if( si[0] == '-' ) res = -res;
    it+=si.length();
    r.it = it;
    r.status = kInt;
    r.dic = res;
    return r;
  }
  it+= rfloat->str().length();
  r.it = it;
  r.status = kFloat;
  r.dic = atof(rfloat->str().c_str());
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

bool TxJSON::SkipWhiteSpace(Iterator &it){
  --it;
  while( Next(it) && (*it==' ' || *it=='\t' || *it=='\n' || *it=='\r')){
  }
  return it != fString.end();
}


bool TxJSON::Next(Iterator &it){
  if( it == fString.end() ) return false;
  it++; return (it != fString.end()) ;
}
