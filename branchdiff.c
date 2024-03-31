#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct MessageStruct {
    char* name;
    char* arch;
} MessageStruct;

static int message_comparator(const void *a, const void *b) {
    const MessageStruct *p1 = (MessageStruct*) a;
    const MessageStruct *p2 = (MessageStruct*) b;
    return strcmp(p1->name, p2->name);
}

void sort_messages(MessageStruct arr[], int n) {
    qsort(arr, n, sizeof(MessageStruct), message_comparator);
}

void presenceDiff (MessageStruct* packages1, int packages1Num, MessageStruct* packages2, int packages2Num, MessageStruct** responseVals, int* responseNumVals) {
    *responseNumVals = packages1Num;
    
    *responseVals = (MessageStruct*) malloc (sizeof(MessageStruct) * (*responseNumVals));
    memset(*responseVals, 0, sizeof(MessageStruct) * (*responseNumVals));
    int current_index = 0;

    sort_messages(packages1, packages1Num);
    sort_messages(packages2, packages2Num);

    int last_known = 0;
    for (int i = 0; i < packages1Num; i++) {
        int present = 0;
        for (int j = last_known; j < packages2Num; j++) {
            if (strcmp(packages1[i].name, packages2[j].name) < 0) {
                last_known = j;
                break;
            }
            
            if (strcmp(packages1[i].name, packages2[j].name) == 0
            && strcmp(packages1[i].arch, packages2[j].arch) == 0) {
                present = 1;
                break;
            }
        }
        if (present == 0) {
            (*responseVals)[current_index].name = packages1[i].name;
            (*responseVals)[current_index].arch = packages1[i].arch;
            current_index++;
        }
    }
}

void cleanupMessageStruct (MessageStruct* pMem) {
    free(pMem);
}