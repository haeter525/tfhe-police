# fhe-police
## How to compile
step 1:
Build and install OpenFHE using “make install”.

step 2:
Copy CMakeLists.User.txt from the OpenFHE root directory of the git repo to the folder for your project.

step 3:
Rename CMakeLists.User.txt to CMakeLists.txt.

step 4:


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
