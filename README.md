# fhe-police
## How to compile
step 1: 
Build and install OpenFHE using “make install”.

step 2: 
Create the build directory from the root directory of the this repo, and cd to it.
```
mkdir build
cd build
```
step 3: 
Run
```
cmake ..
```

step 4: 
Run “make” to build the executable.
```
make
```


## Notation
The deault security strength is MEDIUM

The deault thread number is 8

If you would like to run counter(), remember to add this statement to CMakeLists.txt.
```
target_link_libraries(server PRIVATE pthread)
```
web section url:
```
https://github.com/GGGCI/node.js
```
