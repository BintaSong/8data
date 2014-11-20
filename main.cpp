#include "mainwindow.h"
#include <QApplication>
#include<windows.h>
int hmode;
int runmode;
int sgroup[M][3][3]={{{2,5,3},{1,7,6},{4,8,0}},
                     {{2,5,3},{0,8,7},{1,4,6}},
                     {{2,4,3},{1,6,8},{7,0,5}},
                     {{2,3,0},{1,4,8},{7,6,5}},
                     {{2,3,8},{1,4,0},{7,6,5}},
                     {{2,0,8},{1,3,4},{7,6,5}},
                     {{0,5,3},{2,8,7},{1,4,6}},
                     {{5,3,0},{2,8,7},{1,4,6}},
                     {{0,3,7},{5,2,8},{1,4,6}},

                                             };

int start[N][N]={{1,2,3},{4,5,6},{7,8,0}};

int start7[N][N]={{5,3,7},{2,8,0},{1,4,6}};
int start6[N][N]={{5,3,0},{2,8,7},{1,4,6}};
int start5[N][N]={{5,0,3},{2,8,7},{1,4,6}};
int start4[N][N]={{2,5,3},{0,8,7},{1,4,6}};
int start3[N][N]={{1,2,3},{4,5,6},{7,8,0}};
int start2[N][N]={{2,5,3},{1,7,6},{4,8,0}};
int start1[N][N]={{1,2,3},{4,5,6},{7,0,8}};
int end[N][N]={{1,2,3},{4,5,6},{7,8,0}};
//group g[7]={start1,start2,start3,start4,start5,start6,start7};

int openNum=0;
int closeNum=0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("八数码");
    w.setStatusByArray(start);
    w.show();
    return a.exec();
}
