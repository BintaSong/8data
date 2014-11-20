#ifndef NODE_H
#define NODE_H
#include<QObject>
#include<iostream>
#include<list>
#include<vector>
#include<cstdlib>
#include<windows.h>
#include<math.h>
#include"sharehead.h"
using namespace std;
#define N 3
#define M 12
class node:public QObject
{
    Q_OBJECT

public:
    node* parent;
    int status[N][N];
    int opennum;
    int closenum;
    int fvalue;
    int gvalue;
    int hvalue;

public:
    node(){}
    node(int s[N][N],int g);
    node(const node& otherNode);
    void setStatus(const int s[N][N]);
    void setG(int g);
    void setH();
    void setF();
    void setParent(node* p);
    int  getReverse();
    bool operator<(const node a);
    bool operator<(const node* a);
    bool equal(const node n);
    int heuristic(int nowStatue[N][N],int targetStatus[N][N]);
    void print();
    int  findSpace();
    void createChild(int space,list<node*> &childList);
};

typedef node Mynode;

#endif // NODE_H
