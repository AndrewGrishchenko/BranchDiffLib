#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct MessageStruct {
    char* name;
    int epoch;
    char* version;
    char* release;
    char* arch;
} MessageStruct;

char *__strdup (const char *s) {
  size_t len = strlen (s) + 1;
  void *new = malloc (len);

  if (new == NULL)
    return NULL;

  return (char *) memcpy (new, s, len);
}

static int message_name_comparator(const void *a, const void *b) {
    const MessageStruct *p1 = (MessageStruct*) a;
    const MessageStruct *p2 = (MessageStruct*) b;
    if (strcmp(p1->name, p2->name) == 0) return strcmp(p1->arch, p2->arch);
	else return strcmp(p1->name, p2->name);
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
            int name_cmp = strcmp(packages1[i].name, packages2[j].name);
			int arch_cmp = strcmp(packages1[i].arch, packages2[j].arch);

			if (name_cmp < 0) {
                last_known = j;
                break;
            }
            
			if (name_cmp == 0) {
				if (arch_cmp < 0) {
					last_known = j;
					break;
				} else if (arch_cmp == 0) {
					present = 1;
					break;	
				}
			}
        }
        if (present == 0) {
            (*responseVals)[current_index].name = strdup(packages1[i].name);
            (*responseVals)[current_index].epoch = packages1[i].epoch;
            (*responseVals)[current_index].version = strdup(packages1[i].version);
            (*responseVals)[current_index].release = strdup(packages1[i].release);
            (*responseVals)[current_index].arch = strdup(packages1[i].arch);
            current_index++;
        }
    }
}

void cleanupMessageStruct (MessageStruct* pMem) {
    free(pMem);
}

int compare_versions (int epoch1, char* version1, char* release1, int epoch2, char* version2, char* release2) {
    if (epoch1 != epoch2) return epoch1 > epoch2 ? 1 : -1;

    int ver_comp = rpmvercmp(version1, version2);
	if (ver_comp != 0) return ver_comp;

	ver_comp = rpmvercmp(release1, release2);
	return ver_comp;
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
                if (compare_versions(packages1[i].epoch, packages1[i].version, packages1[i].release, 
                packages2[j].epoch, packages2[j].version, packages2[j].release) > 0) {
                    (*responseVals)[current_index].name = strdup(packages1[i].name);
                    (*responseVals)[current_index].epoch = packages1[i].epoch;
                    (*responseVals)[current_index].version = strdup(packages1[i].version);
                    (*responseVals)[current_index].release = strdup(packages1[i].release);
                    (*responseVals)[current_index].arch = strdup(packages1[i].arch);
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