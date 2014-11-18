#include "mainwindow.h"
#include <QApplication>
#include<windows.h>
int hmode;
int runmode;
int sgroup[M][3][3]={{{1,2,3},{4,5,6},{7,0,8}},
                     {{2,5,3},{1,7,6},{4,8,0}},
                     {{2,5,3},{0,8,7},{1,4,6}},
                                            };
//int start[N][N]={{5,3,7},{2,8,0},{1,4,6}};
//int start[N][N]={{5,3,0},{2,8,7},{1,4,6}};
//int start[N][N]={{5,0,3},{2,8,7},{1,4,6}};
//int start[N][N]={{2,5,3},{0,8,7},{1,4,6}};
int start[N][N]={{1,2,3},{4,5,6},{7,8,0}};
//int start[N][N]={{2,5,3},{1,7,6},{4,8,0}};
//int start[N][N]={{1,2,3},{4,5,6},{7,0,8}};
int end[N][N]={{1,2,3},{4,5,6},{7,8,0}};

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
