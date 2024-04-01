#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct MessageStruct {
    char* name;
    char* arch;
    char* version;
} MessageStruct;

static int message_name_comparator(const void *a, const void *b) {
    const MessageStruct *p1 = (MessageStruct*) a;
    const MessageStruct *p2 = (MessageStruct*) b;
    return strcmp(p1->name, p2->name);
}

void sort_messages(MessageStruct arr[], int n) {
    qsort(arr, n, sizeof(MessageStruct), message_name_comparator);
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
            (*responseVals)[current_index].version = packages1[i].version;
            current_index++;
        }
    }
}

void cleanupMessageStruct (MessageStruct* pMem) {
    free(pMem);
}


int dotCount (char* s) {
    int count = 0;
    int size = strlen(s);
    for (int i = 0; i < size; i++) {
        if (s[i] == '.') count++;
    }
    return count;
}

char** str_split(char* s, int *size) {
    int str_size = strlen(s);
    char new_s[str_size];
    strcpy(new_s, s);

    int partCount = 1, index = 0;
    for (int i = 0; i < str_size; i++) {
        if (s[i] == '.') partCount++;
    }

    *size = partCount;

    char** ans = (char**) malloc(sizeof(char*) * partCount);

    if (partCount == 1) {
        ans[0] = (char*) malloc(sizeof(char) * str_size);
        strcpy(ans[0], s);
    } else {
        char *ptr = strtok(new_s, ".");

        while (ptr != NULL) {
            ans[index] = (char*) malloc(sizeof(char) * strlen(ptr));
            strcpy(ans[index], ptr);
            index++;

            ptr = strtok(NULL, ".");
        }
    }
    return ans;
}

int pow10N (int num) {
    int ans = 1;
    for (int i = 0; i < num; i++) {
        ans *= 10;
    }
    return ans;
}

int ctoi (char c) {
    int c_i = c - '0';
    if (c_i >= 49) c_i -= 32;
    if (c_i >= 17) c_i -= 7;
    return c_i;
}

int ctoi_compare (char* c1, char* c2) {
    int c1_size = strlen(c1);
    int c2_size = strlen(c2);
    
    int c_size = (c1_size < c2_size) ? c1_size : c2_size;

    for (int i = 0; i < c_size; i++) {
        int c1_i = ctoi(c1[i]);
        int c2_i = ctoi(c2[i]);
        if (c1_i > c2_i) return 1;
        else if (c1_i < c2_i) return -1;
    }

    if (c1_size == c2_size) return 0;
    return (c1_size < c2_size) ? -1 : 1;
}

int compare_versions(char* version1, char* version2) {
    int tokenParts1 = 1;
    char** tokens1 = str_split(version1, &tokenParts1);
    
    int tokenParts2 = 1;
    char** tokens2 = str_split(version2, &tokenParts2);
    
    int token_size = (tokenParts1 < tokenParts2) ? tokenParts1 : tokenParts2;

    for (int i = 0; i < token_size; i++) {
        int result = ctoi_compare(tokens1[i], tokens2[i]);
        if (result != 0) return result;
    }

    if (tokenParts1 == tokenParts2) return 0;
    return (tokenParts1 < tokenParts2) ? -1 : 1;
}


void versionDiff (MessageStruct* packages1, int packages1Num, MessageStruct* packages2, int packages2Num, MessageStruct** responseVals, int* responseNumVals) {
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
            if (strcmp(packages1[i].name, packages2[j].name) == 0
            && strcmp(packages1[i].arch, packages2[j].arch) == 0) {
                if (compare_versions(packages1[i].version, packages2[j].version) > 0) {
                    (*responseVals)[current_index].name = packages1[i].name;
                    (*responseVals)[current_index].arch = packages1[i].arch;
                    (*responseVals)[current_index].version = packages1[i].version;
                    current_index++;
                }
                break;
            }

            if (strcmp(packages1[i].name, packages2[j].name) < 0) {
                last_known = j;
                break;
            }
        }
    }
}