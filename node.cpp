#include"node.h"
node::node(int s[N][N],int g){
    setStatus(s);
    setG(g);
    setH();
    setF();
    parent=NULL;
}
node::node(const node& otherNode){
    setStatus(otherNode.status);
    setG(otherNode.gvalue);
    hvalue=otherNode.hvalue;
    fvalue=otherNode.fvalue;
    parent=otherNode.parent;
    opennum=otherNode.opennum;
    closenum=otherNode.closenum;
}
void node::setStatus(const int s[N][N]){
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++){
            status[i][j]=s[i][j];
        }
}
void node::setG(int g){
    gvalue=g;
}
void node::setH(){
    hvalue=heuristic(this->status,end);
}
void node::setF(){
    fvalue=gvalue+hvalue;
}
void node::setParent(node* p){
    parent=p;
}
int node::getReverse(){
    int reverse=0;
    for(int i=0;i<9;i++){
        for(int j=i+1;j<9;j++){
            if(status[i/3][i%3]>status[j/3][j%3]){
                reverse+=1;
            }
        }
    }
    return reverse;
}
bool node::equal(const node n){
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++){
            if(status[i][j]!=n.status[i][j]) {
                return false;
            }
        }
    return true;
}
bool node::operator<(const node a){
    return fvalue>a.fvalue;
}
bool node::operator<(const node* a){
    return this->fvalue > a->fvalue;
}
int node::heuristic(int nowStatue[N][N], int targetStatus[N][N]){
    int i,j,con=0;
    if(hmode==FUN1){
        cout<<"in FUN1"<<endl;
        for(i=0;i<N*N;i++)
            if(nowStatue[i/3][i%3]!=targetStatus[i/3][i%3]) con++;
    }
    if(hmode==FUN2){
       con=0;
       cout<<"in FUN2"<<endl;
       for(i=0;i<N*N;i++)
           for(j=0;j<N*N;j++)
                if(nowStatue[i/3][i%3]==targetStatus[j/3][j%3]&&nowStatue[i/3][i%3]!=0)
                {
                    con+=(int)sqrt(abs(i/3-j/3)*abs(i/3-j/3)+abs(i%3-j%3)*abs(i%3-j%3));
                    continue;
                }
    }
    if(hmode==FUN3){
        con=0;
        cout<<"in FUN3"<<endl;
        for(i=0;i<N*N;i++)
           for(j=0;j<N*N;j++)
                if(nowStatue[i/3][i%3]==targetStatus[j/3][j%3]&&nowStatue[i/3][i%3]!=0)
                {
                    con+=(abs(i/3-j/3)+abs(i%3-j%3));
                    continue;
                }
    }
    return con;
}
void node::print(){
    int i,j;
    cout<<"**node info "<<"f:"<<fvalue<<" g: "<<gvalue<<" h: "<<hvalue<<"**"<<endl;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cout<<status[i][j]<<" ";
        }
        cout<<endl;
    }
}
int node::findSpace(){
    for(int i=0;i<9;i++){
        if(status[i/3][i%3]==0) return i;
    }
    return -1;
}
void node::createChild(int space, list<node*> &childList){
    //cout<<"*****root:*****"<<(int)this<<endl;
    //this->print();
    if(space%3!=2){//可以右移
        node* tempNode=new node(*this);
        //*tempNode=*this;
        //int temp=status[space/3][space%3];
        tempNode->status[space/3][space%3]=tempNode->status[space/3][space%3+1];
        tempNode->status[space/3][space%3+1]=0;
        tempNode->setG(gvalue+1);
        tempNode->setH();
        tempNode->setF();
        tempNode->setParent(this);
        childList.push_front(tempNode);
        //tempNode->print();
    }
    if(space%3!=0){//可以左移
        node* tempNode=new node(*this);
        //int temp=status[space/3][space%3];
        tempNode->status[space/3][space%3]=tempNode->status[space/3][space%3-1];
        tempNode->status[space/3][space%3-1]=0;
        tempNode->setG(gvalue+1);
        tempNode->setH();
        tempNode->setF();
        tempNode->setParent(this);
        childList.push_front(tempNode);
        //tempNode->print();
    }
    if(space/3!=0){//可以上移
        node* tempNode=new node(*this);
        //int temp=status[space/3][space%3];
        tempNode->status[space/3][space%3]=tempNode->status[space/3-1][space%3];
        tempNode->status[space/3-1][space%3]=0;
        tempNode->setG(gvalue+1);
        tempNode->setH();
        tempNode->setF();
        tempNode->setParent(this);
        childList.push_front(tempNode);
        //tempNode->print();
    }
    if(space/3!=2){//可以下移
        node* tempNode=new node(*this);
        //int temp=status[space/3][space%3];
        tempNode->status[space/3][space%3]=tempNode->status[space/3+1][space%3];
        tempNode->status[space/3+1][space%3]=0;
        tempNode->setG(gvalue+1);
        tempNode->setH();
        tempNode->setF();
        tempNode->setParent(this);
        childList.push_front(tempNode);
        //tempNode->print();
    }
}
