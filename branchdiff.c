#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct MessageStruct {
    char* name;
    char* arch;
} MessageStruct;

void presenceDiff (MessageStruct* packages1, int packages1Num, MessageStruct* packages2, int packages2Num, MessageStruct** responseVals, int* responseNumVals) {
    if (packages1Num > packages2Num) {
        *responseNumVals = packages1Num;
    } else {
        *responseNumVals = packages2Num;
    }
    
    *responseVals = (MessageStruct*) malloc (sizeof(MessageStruct) * (*responseNumVals));
    memset(*responseVals, 0, sizeof(MessageStruct) * (*responseNumVals));
    int current_index = 0;

    for (int i = 0; i < packages1Num; i++) {
        int j;
        for (j = 0; j < packages2Num; j++) {
            if (strcmp(packages1[i].name, packages2[j].name) == 0
            && strcmp(packages1[i].arch, packages2[j].arch) == 0) break;
        }
        if (j == packages2Num) {
            (*responseVals)[current_index].name = packages1[i].name;
            (*responseVals)[current_index].arch = packages1[i].arch;
            current_index++;
        }
    }
}

void cleanupMessageStruct (MessageStruct* pMem) {
    free(pMem);
}