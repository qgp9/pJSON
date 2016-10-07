#ifndef TxDict_H
#include "TxDict.h"
#endif
#include <utility>
//______________________________________________
TxDict::TxDict( const TxDict & o ){
  if( this != &o ) this->operator=(std::move(o));
}

//______________________________________________
TxDict::TxDict( TxDict && o ) noexcept {
  std::swap( fP, o.fP );
  std::swap( fType, o.fType );
}
//______________________________________________
TxDict& TxDict::operator=( TxDict &&o ){
  std::swap( fP, o.fP );
  std::swap( fType, o.fType );
  return *this;
}
//______________________________________________
TxDict& TxDict::operator=( const TxDict &o ){
  switch(o.fType){
    case kxString: Set(*o.fP.s) ;break;
    case kxArray:  Set(*o.fP.a) ;break;
    case kxMap:    Set(*o.fP.m)   ;break;
    default: fP=o.fP;fType=o.fType;break;
  }
  return *this;
}

//______________________________________________
void TxDict::Delete(){
  if( fP.p ){
    switch(fType){
      case kxString: delete fP.s; break;
      case kxArray:  delete fP.a; break;
      case kxMap:    delete fP.m; break;
      default: break; 
    }
  }
  fP.p = nullptr;
  fType = kxUnknown;
}

//______________________________________________
TxDict::String TxDict::Str(int _template,int step) const {
  if( !fP.ul && !IsInt() && !IsDouble()) return "NONE";
  String field_sep  = ", ";
  String array_open   = "[ ";
  String array_close  = " ]";
  String map_open     = "{ ";
  String map_close    = " }";
  String map_sep      = ":";
  String quote        = "\"";
  String step_sep     = "";
  if( _template==1 ){ 
    String _step_sep    = "    ";
    map_sep      = " : ";
    for( int i=0;i<step;i++ ) step_sep += _step_sep;
    array_close = "\n"+step_sep+"]";
    map_close   = "\n"+step_sep+"}";
    step_sep += _step_sep;
    field_sep   = ",\n"+step_sep;
    map_open    = "{\n"+step_sep;
    array_open  = "[\n"+step_sep;
  }
  std::ostringstream os;
  String sep = "";
  switch(fType){
    case kxInt:    os<<fP.i;break;
    case kxDouble: os<<fP.d;break;
    case kxString: os<<quote<<*fP.s<<quote;break;
    case kxArray:
                   os<<array_open;
                   for( auto &x : *(fP.a) ) {
                     os << sep<<x.Str(_template,step+1); 
                     sep=field_sep;
                   }
                   os<<array_close;
                   break;
    case kxMap:   os<<map_open;
                  for( auto &x : *(fP.m) ){ 
                    os << sep<<quote<<x.first<<quote<<map_sep<<x.second.Str(_template,step+1);
                    sep=field_sep;
                  } 
                  os<<map_close;
                  break;
    default: break;
  }
  return os.str();
}

TxDict::Int TxDict::GetInt() const{
  switch(fType){
    case kxInt: return fP.i;break;
    case kxDouble: return fP.d;break;
    case kxString: return atoi((*fP.s).c_str());break;
    default: ErrorType(fType,kxInt);
             break;
  }
  return 0;
}

TxDict::Double TxDict::GetDouble() const {
  switch(fType){
    case kxInt: WarnType( fType, kxDouble);
                return fP.i;break;
    case kxDouble: WarnType( fType, kxDouble);
                   return fP.d;
                   break;
    case kxString: WarnType(fType,kxDouble);
                   return atof((*fP.s).c_str());
                   break;
    default: ErrorType(fType,kxDouble);
             break;
  }
  return 0;
}
TxDict::String TxDict::GetString() const {
  switch(fType){
    case kxInt: WarnType( fType, kxInt);
                return (std::ostringstream()<<fP.i).str();
                break;
    case kxDouble: WarnType(fType,kxDouble );
                   return (std::ostringstream()<<fP.d).str();
                   break;
    case kxString: WarnType(kxString,fType);
                   return *fP.s;
                   break;
    default: ErrorType(fType,kxString);
             break;
  }
  return "";
}
TxDict::Array& TxDict::GetArray() const {
  if( !IsArray() ) ErrorType(fType, kxArray);
  return *fP.a;
}
TxDict::Map&  TxDict::GetMap() const {
  if( !IsMap() )ErrorType(fType, kxMap);
  return *fP.m;
}

void TxDict::WarnType( Type a, Type b) const {
  if( a == b ) return;
}

void TxDict::ErrorType( Type a, Type b) const {
  if( a==b) return;
  std::cout<<"ERROR: Converting from "<<a<<"\t"<<b<<std::endl;
  exit(1);
}
