# install

```
sudo apt install libprotobuf-dev protobuf-compiler
// uninstall
sudo apt purge protobuf-compiler libprotobuf-dev
// 查看protobuf版本
protoc --version
libprotoc 3.0.0
```

# usage

```
protoc example.proto --cpp_out=./
```
