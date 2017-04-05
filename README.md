# pJSON
Lite and Handy JSON parser

## Compile

```bash
# Genereate example json
./gen_big_json.sh
# Compile
g++ -O2 --std=c++11  src/*.cxx tests/testTxJSON.cxx -o testjson
# test
./testjson > out.txt
```

### Big json example
```bash
ln -sf example_big.json example.json
time ./testjson > out.txt
```

### Parsing
#### JSON String
```C++
string json_string = R"({ "123":[ 2, 3, 4, "abc", { "453":"123", "abc":456 } ] })";
TxJSON j(json_string);
if( j.Compile() ){
  auto &d = j.GetDict();
  cout<<d.Str()<<endl;
  cout<<d["123"][4]["abc"].GetInt()<<endl;
}
```

#### Parse JSON file
```C++
TxJSON j;
if( j.LoadFile( "example.json" ) ){
  auto &d = j.GetDict();
  cout<<d.Str(1)<<endl
  cout<<
}else{
  cout<<"Error while loading file "<<j.GetErrorStr(j.GetStatus())<<endl;
}

```
