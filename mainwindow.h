#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QDebug>
#include"gamethread.h"
#include"game.h"
#include"node.h"
#include"sharehead.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    game *gamethread;
public:
    explicit MainWindow(QWidget *parent = 0);
    int getReverse(int s[N][N]);
    ~MainWindow();
signals:
    void step(int );

public slots:
    void setStatus(Mynode);
    void setStatusByArray(int s[N][N]);
    void on_endCalcute();
    void on_endGame();
private slots:
    void on_pushButton_seq_clicked();

    void on_pushButton_step_clicked();

    void on_radioButton_1_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_actionAa_triggered();

    void on_pushButton_forward_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_stop_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
