#ifndef THREAD_H
#define THREAD_H
#include<QThread>
#include"game.h"
class gamethread:public QThread
{
    Q_OBJECT
public:
    game *g;
public:
    gamethread();
    gamethread(int start[3][3],int end[3][3]);
protected:
    void run();
};
#endif // THREAD_H
