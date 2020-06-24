#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

extern "C" __declspec(dllimport) int c_add(int a, int b);
extern "C" __declspec(dllimport) bool c_nist_sch(int numCnt, quint32* mass,  quint32* abund,
                                                 int *resCnt, quint32* peakNums);

extern "C" __declspec(dllexport) bool c_nist_sch_one(int numCnt, quint32* mass, quint32* abund,
                                                     int *resCnt, int* CAS, quint32* MW,
                                                     int* Match, char** name, int* name_len,
                                                     quint32* peakNum, int* Prob, int* R_Match,
                                                     char** formula, int* formula_len);

//                                 bool c_nist_sch_one(int numCnt, quint32* mass, quint32* abund,
//                                                     int *resCnt, int* CAS, quint32* MW,
//                                                     int* Match, char** name, int* name_len,
//                                                     quint32* peakNum, int* Prob, int* R_Match,
//                                                     char** formula, int* formula_len);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << c_add(1, 22);
    quint32 mass[4] = { 91, 92, 78, 77 };
    quint32 abund[4] = {100, 67, 34 ,30 };
    quint32 peaknum = 0;
    int resCnt = 0;
//    bool res = c_nist_sch(4, &mass[0], &abund[0],  &resCnt, peaknums);
    int CAS = 0;
    quint32 MW = 0;
    int Match = 0;
    char* name = nullptr;
    int name_len = 0;
    int Prob = 0;
    int R_Match = 0;
    char* formula = nullptr;
    int formula_len = 0;
    bool res = c_nist_sch_one(4, &mass[0], &abund[0],
                              &resCnt, &CAS, &MW,
                              &Match, &name, &name_len,
                              &peaknum, &Prob, &R_Match,
                              &formula, &formula_len);
    qDebug() << "resCnt = " << resCnt;
    qDebug() << "CAS = " << CAS;
    qDebug() << "MW = " <<MW;
    qDebug() << "name = " << QString(name);
    qDebug() << "name_len = " << name_len;
    qDebug() << "peaknum = " << peaknum;
    qDebug() << "Prob = " << Prob;
    qDebug() << "R_Match = " << R_Match;
    qDebug() << "formula = " << QString(formula);
    qDebug() << "formula_len = " << formula_len;
    qDebug() << "res = " <<res;
}
