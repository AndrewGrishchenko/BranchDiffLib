# BranchDiffLib

This library provides functionality to perform operations on a list of packages

## Overview

A package is represented by the following structure:
```c
typedef struct MessageStruct {
    char* name;
    int epoch;
    char* version;
    char* release;
    char* arch;
} MessageStruct;
```

## Functions
1. presenceDiff
    - Description: Returns a list of packages that are present in the first list but not in the second list
    - Prototype: ```void presenceDiff(MessageStruct* packages1, int packages1Num, MessageStruct* packages2, int packages2Num, MessageStruct** responseVals, int* responseNumVals)```
2. versionDiff
    - Description: Returns a list of packages whose version in the first list is greater than in the second list
    - Prototype: ```void versionDiff(MessageStruct* packages1, int packages1Num, MessageStruct* packages2, int packages2Num, MessageStruct** responseVals, int* responseNumVals)```

## Installation
1. Create a build directory
`mkdir build && cd build`
2. Configure with CMake
`cmake ..`
3. Install
`sudo make install`

### Note
On ALT Linux, the library might not be visible to programs. To fix this, open the file `/etc/ld.so.conf.d/local.conf` in any text editor and add the following lines:
```
/usr/local/lib
/usr/local/lib64
/usr/local/libexec
/usr/local/libx32
```
