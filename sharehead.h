#ifndef SHAREHEAD_H
#define SHAREHEAD_H
#include<time.h>
#define FUN1 1
#define FUN2 2
#define FUN3 3
#define STEP_RUN 1
#define SEQ_RUN 2

typedef int group[3][3];

extern int start[][3];
extern int end[][3];
extern int hmode;
extern int runmode;
extern int openNum;
extern int closeNum;
extern int sgroup[12][3][3];
#endif // SHAREHEAD_H
