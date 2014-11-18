#ifndef GAME_H
#define GAME_H
#include"sharehead.h"
#include"node.h"
#include<QThread>
#include<QDebug>
#include<windows.h>
class game : public QThread
{
    Q_OBJECT

public:
    int startstatus[N][N];
    int endstatus[N][N];
    list<node*> open;
    list<node*> close;
    vector<node*> route;
    vector<node*>::reverse_iterator point;

public:
    game(int s[N][N],int e[N][N]);
    bool test(int startstatus[N][N],int endstatus[N][N]);//test if the game can be solved
    list<node*>::iterator inOpen(node n);
    list<node*>::iterator inClose(node n);
    list<node*>::iterator findMinF();
    void deleteNode();
    void printSeqRoute();
    void printStepRoute();
protected:
    void run();
signals:
    void changeStatus(Mynode );
    void endCalcute();
    void endGame();
private slots:
    void on_step(int);
};

#endif // GAME_H
