# pJSON

## Usage

```bash
# Genereate example json
./gen_big_json.sh
# Compile
g++ --std=c++11  src/*.cxx tests/testTxJSON.cxx -o testjson
# test
./testjson > out.txt
```

### Big json example
```bash
ln -sf example_big.json example.json
time ./testjson > out.txt
```
