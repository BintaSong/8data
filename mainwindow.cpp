#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioButton_1->setChecked(true);//设置第一个启发式函数为默认

    ui->pushButton_forward->setVisible(false);
    ui->pushButton_next->setVisible(false);
    ui->pushButton_stop->setVisible(false);

    hmode=FUN1;//设置第一个启发式函数为默认
    runmode=SEQ_RUN;//设置连续执行为默认
}
int MainWindow::getReverse(int s[N][N]){
    int reverse=0;
    for(int i=0;i<9;i++)
        for(int j=i+1;j<9;j++){
            if(s[i/3][i%3]==0||s[j/3][j%3]==0) continue;
            if(s[i/3][i%3] < s[j/3][j%3]) reverse++;
        }
    return reverse;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setStatus(Mynode n)
{
    //qDebug()<<"in slot \n";
    QFont ft;
    ft.setPointSize(36);
    QPushButton* button[9]={ui->pushButton_1,ui->pushButton_2,ui->pushButton_3,
                           ui->pushButton_4,ui->pushButton_5,ui->pushButton_6,
                           ui->pushButton_7,ui->pushButton_8,ui->pushButton_9};
    for(int i=0;i<9;i++)
    {
        button[i]->setFont(ft);
        if(n.status[i/3][i%3]!=0) button[i]->setText(QString::number(n.status[i/3][i%3],10));
        else button[i]->setText("");
    }
   // ui->textBrowser->moveCursor(QTextCursor::End);
    if(runmode==SEQ_RUN){
        QString str="<font face=\"verdana\" size=\"5\" color=\"ForestGreen\">open: ";
        str+=QString::number(n.opennum,10);
        str+=" close：";
        str+=QString::number(n.closenum,10);

        ui->textBrowser->append(str);
        cout<<"after emit: "<<"close:"<<n.closenum<<"open:"<<n.opennum<<endl;
    }
}
void MainWindow::setStatusByArray(int s[N][N])
{
    QFont ft;
    ft.setPointSize(36);
    QPushButton* button[9]={ui->pushButton_1,ui->pushButton_2,ui->pushButton_3,
                           ui->pushButton_4,ui->pushButton_5,ui->pushButton_6,
                           ui->pushButton_7,ui->pushButton_8,ui->pushButton_9};
    for(int i=0;i<9;i++)
    {
        button[i]->setFont(ft);
        if(s[i/3][i%3]!=0) button[i]->setText(QString::number(s[i/3][i%3],10));
        else button[i]->setText("");
    }
}

void MainWindow::on_pushButton_seq_clicked()
{
    qDebug()<<"in seq"<<endl;
    ui->pushButton_seq->setVisible(false);
    ui->pushButton_step->setVisible(false);
    ui->radioButton_1->setVisible(false);
    ui->radioButton_2->setVisible(false);
    ui->radioButton_3->setVisible(false);
    ui->pushButton_forward->setVisible(false);
    ui->pushButton_next->setVisible(false);
    ui->pushButton_stop->setVisible(false);

    openNum=0;
    closeNum=0;
    runmode=SEQ_RUN;
    setStatusByArray(start);
    if(hmode==FUN1) ui->textBrowser->append("<font face=\"verdana\" size=\"6\" color=\"red\">连续执行|启发函数一|请稍后...</font>");
    if(hmode==FUN2) ui->textBrowser->append("<font face=\"verdana\" size=\"6\" color=\"red\">连续执行|启发函数二|请稍后...</font>");
    if(hmode==FUN3) ui->textBrowser->append("<font face=\"verdana\" size=\"6\" color=\"red\">连续执行|启发函数三|请稍后...</font>");
    gamethread=new game(start,end);
    qRegisterMetaType<Mynode>("Mynode");
    connect(gamethread,SIGNAL(changeStatus(Mynode)),this,SLOT(setStatus(Mynode)),Qt::QueuedConnection);
    connect(gamethread,SIGNAL(endCalcute()),this,SLOT(on_endCalcute()));
    connect(gamethread,SIGNAL(endGame()),this,SLOT(on_endGame()));
    gamethread->start();
}

void MainWindow::on_pushButton_step_clicked()
{   qDebug()<<"in step"<<endl;

    ui->pushButton_seq->setVisible(false);
    ui->pushButton_step->setVisible(false);
    ui->radioButton_1->setVisible(false);
    ui->radioButton_2->setVisible(false);
    ui->radioButton_3->setVisible(false);
    ui->pushButton_forward->setVisible(true);
    ui->pushButton_next->setVisible(true);
    ui->pushButton_stop->setVisible(true);
    openNum=0;
    closeNum=0;
    runmode=STEP_RUN;
    setStatusByArray(start);
    //if(hmode==FUN1) ui->textBrowser->append("<font face=\"verdana\" size=\"6\" color=\"red\">单步执行|启发函数一|请稍后...</font>");
    //if(hmode==FUN2) ui->textBrowser->append("<font face=\"verdana\" size=\"6\" color=\"red\">单步执行|启发函数二|请稍后...</font>");
    //if(hmode==FUN3) ui->textBrowser->append("<font face=\"verdana\" size=\"6\" color=\"red\">单步执行|启发函数三|请稍后...</font>");

    gamethread=new game(start,end);
    qRegisterMetaType<Mynode>("Mynode");
    connect(gamethread,SIGNAL(changeStatus(Mynode)),this,SLOT(setStatus(Mynode)),Qt::QueuedConnection);
    connect(this,SIGNAL(step(int)),gamethread,SLOT(on_step(int)));
    connect(gamethread,SIGNAL(endCalcute()),this,SLOT(on_endCalcute()));
    connect(gamethread,SIGNAL(endGame()),this,SLOT(on_endGame()));
    gamethread->start();
}

void MainWindow::on_radioButton_1_clicked()
{
    qDebug()<<"ration 1"<<endl;
    hmode=FUN1;
}

void MainWindow::on_radioButton_2_clicked()
{
    qDebug()<<"ration 2"<<endl;
    hmode=FUN2;
}

void MainWindow::on_radioButton_3_clicked()
{
    qDebug()<<"ration 3"<<endl;
    hmode=FUN3;
}

void MainWindow::on_actionAa_triggered()
{
    int rindex,temp;
    //int vstart,vend;
    srand((unsigned)time(0));
    do{
        rindex=rand()%9;
        for(int i=0;i < 9;i++){
            start[i/3][i%3]=sgroup[rindex][i/3][i%3];

        }
    }while(getReverse(start)%2 != 0);
    setStatusByArray(start);
}

void MainWindow::on_pushButton_forward_clicked()
{
    //发出向前的信号
    emit step(-1);
}

void MainWindow::on_pushButton_next_clicked()
{
    //发出向后的信号
    emit step(1);
}

void MainWindow::on_pushButton_stop_clicked()
{
    //发出停止的信号
    //gamethread->terminate();
    ui->pushButton_forward->setVisible(false);
    ui->pushButton_next->setVisible(false);
    ui->pushButton_stop->setVisible(false);

    ui->pushButton_seq->setVisible(true);
    ui->pushButton_step->setVisible(true);
    ui->radioButton_1->setVisible(true);
    ui->radioButton_2->setVisible(true);
    ui->radioButton_3->setVisible(true);
}
void MainWindow::on_endCalcute(){
    if(runmode==SEQ_RUN) ui->textBrowser->append("<font face=\"verdana\" size=\"6\" color=\"red\">找到答案！</font>");
}
void MainWindow::on_endGame(){
    if(runmode==SEQ_RUN) ui->textBrowser->append("<font face=\"verdana\" size=\"6\" color=\"red\">游戏结束！</font>");
    ui->pushButton_seq->setVisible(true);
    ui->pushButton_step->setVisible(true);
    ui->radioButton_1->setVisible(true);
    ui->radioButton_2->setVisible(true);
    ui->radioButton_3->setVisible(true);
    ui->pushButton_forward->setVisible(false);
    ui->pushButton_next->setVisible(false);
    ui->pushButton_stop->setVisible(false);
}
