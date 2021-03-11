#pragma once

#include <QtWidgets/QWidget>

#include <QPushButton>
#include <QLabel>

#include "ui_shudu.h"
#include <vector>
#include <iostream>
#include <string.h>
#include <qstring.h>
using namespace std;
namespace Ui{class shudu;}
class shudu : public QWidget
{
    Q_OBJECT
public:
    shudu(QWidget *parent = Q_NULLPTR);
    void SetQipan();
    void RandGener(char* filename);
public slots:
    void changeNum(int);
    void showQipan();
    void showAns();
private:
    QPushButton* set_Btn = new QPushButton(this);
    QPushButton* ans_Btn = new QPushButton(this);
    QLabel* lbs = new QLabel(this);
    Ui::shudu *ui;
    QString a = "1";
    QString b = "0";
    std::vector<QPushButton*> Btns;
    int qipan[36] = {0};
    int ans[36] = {0};
};


