#include"game.h"
game::game(int s[N][N],int e[N][N]){
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++){
            startstatus[i][j]=s[i][j];
            endstatus[i][j]=e[i][j];
        }
}
list<node*>::iterator game::inOpen(node n){
    list<node*>::iterator t;
    for(t=open.begin();t!=open.end();++t){
        if(n.equal(**t)==true) return t;
    }
    return t;//t=open.end()
}
list<node*>::iterator game::inClose(node n){
    list<node*>::iterator t;
    for(t=close.begin();t!=close.end();++t){
        if(n.equal(**t)==true) return t;
    }
    return t;//t=close.end()
}
list<node*>::iterator game::findMinF(){
    list<node*>::iterator ret=open.begin();
    int minF=(*ret)->fvalue;
    for(list<node*>::iterator t=open.begin();t!=open.end();t++){
        if((*t)->fvalue < minF){
            ret=t;
            minF=(*t)->fvalue;
        }
    }
    return ret;
}
void game::deleteNode(){
    for(list<node*>::iterator t=open.begin();t!=open.end();t++){
        delete *t;
    }
    for(list<node*>::iterator t=close.begin();t!=close.end();t++){
        delete *t;
    }
}
void game::printSeqRoute(){
     for(vector<node*>::reverse_iterator t=route.rbegin();t!=route.rend();t++)
     {
         cout<<"before emit: "<<"close:"<<(**t).closenum<<"opennum:"<<(**t).opennum<<endl;
         emit changeStatus(**t);//这里用到复制构造函数！fuck！
         Sleep(2000);
     }
     emit endGame();
}
void game::printStepRoute(){

}
void game::on_step(int ctrl){
    if(ctrl==-1){
        if(point!=route.rbegin()){
            point--;
            emit changeStatus(**point);
        }
        else{
            //emit changeStatus(**point);
            emit endGame();
        }
    }
    if(ctrl==1&&point!=route.rend()){
        if(point!=route.rend()-1){
            point++;
            emit changeStatus(**point);
        }
        else{
            //emit changeStatus(**point);
            emit endGame();
        }
    }
}
void game::run(){
    node *startnode=new node(startstatus,0);
    node *endnode=new node(endstatus,0);
    startnode->opennum=0;startnode->closenum=0;
    endnode->opennum=0;endnode->closenum=0;

    open.push_back(startnode);
    node *temp;
    if(startnode->getReverse()%2!=endnode->getReverse()%2){
        cout<<"cannot be solved!"<<endl;
        exit(-1);
    }


    while(open.empty()==false){
        //open.sort();//fvalue最小值排在队尾
        list<node*>::iterator t=findMinF();
        temp=*t;//获得最优节点
        //cout<<"temp "<<(int)temp<<endl;
        if(temp->equal(*endnode)){
            cout<<"now we find the solution!!!!!!!!!!!!!!!!!"<<endl;
            emit endCalcute();
            node* p=temp;
            while(p!=NULL){
                route.push_back(p);
                p=p->parent;
            }

            if(runmode==SEQ_RUN){
                printSeqRoute();
            }
            if(runmode==STEP_RUN){
                point=route.rbegin();
                while(1){
                    qDebug()<<"in step while"<<endl;

                }
            }
            return ;
        }
        list<node*> child;
        int space=temp->findSpace();
        temp->createChild(space,child);
        for(list<node*>::iterator i=child.begin();i!=child.end();i++){
            list<node*>::iterator ret1=inOpen(**i);
            if(ret1!=open.end()){//如果该孩子节点在open表中
                if((*i)->fvalue<(*ret1)->fvalue){//跟新open表中的对应节点
                   free(*ret1);
                   *ret1=*i;

                   (*i)->opennum=openNum;
                   (*i)->closenum=closeNum;
                }
            }
            list<node*>::iterator ret2=inClose(**i);
            if(ret2!=close.end()){//如果该孩子节点在close表中
                if((*i)->fvalue<(*ret2)->fvalue){//将close表中的该节点移到open
                    open.push_front(*i);
                    ++openNum;
                    free(*ret2);
                    --closeNum;

                    (*i)->opennum=openNum;
                    (*i)->closenum=closeNum;

                    close.erase(ret2);
                }
            }
            //否则，节点放入open表
            open.push_front(*i);
            ++openNum;

            (*i)->opennum=openNum;
            (*i)->closenum=closeNum;
        }
        close.push_front(temp);
        open.erase(t);

        --openNum;
        ++closeNum;
    }

}
