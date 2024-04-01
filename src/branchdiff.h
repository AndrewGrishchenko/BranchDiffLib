#ifndef branchdiff_h__
#define branchdiff_h__

struct MessageStruct;
extern void presenceDiff (MessageStruct* packages1, int packages1Num, MessageStruct* packages2, int packages2Num, MessageStruct** responseVals, int* responseNumVals);
extern void cleanupMessageStruct (MessageStruct* pMem);

extern void versionDiff (MessageStruct* packages1, int packages1Num, MessageStruct* packages2, int packages2Num, MessageStruct** responseVals, int* responseNumVals);

#endif