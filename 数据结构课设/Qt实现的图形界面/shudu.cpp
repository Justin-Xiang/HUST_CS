#include "shudu.h"

shudu::shudu(QWidget *parent)
    : QWidget(parent)
{
    ui->setupUi(this);
    lbs->move(280, 500);
    lbs->resize(150, 50);
    set_Btn->resize(150, 50);
    set_Btn->move(50, 500);
    set_Btn->setText("生成数独");
    ans_Btn->resize(150, 50);
    ans_Btn->move(set_Btn->x()+350, set_Btn->y());
    ans_Btn->setText("展示结果");
    //set_Btn->hide();
    connect(set_Btn, &QPushButton::clicked, this, &shudu::showQipan);
    connect(ans_Btn, &QPushButton::clicked, this, &shudu::showAns);
}

void shudu::SetQipan() {
    for (int i = 0; i < 36; ++i) {
        Btns.push_back(new QPushButton(this));
        Btns[i]->resize(60, 60);
        connect(Btns[i], &QPushButton::clicked, this, [=]() {changeNum(i); });
        if (i == 0) {
            Btns[i]->move(120, 100);
            Btns[i]->setText(" ");
        }
        else if (i % 6 == 0) {
            Btns[i]->move(Btns[i - 6]->x(), Btns[i - 6]->y() + 60);
            Btns[i]->setText(" ");
        }
        else {
            Btns[i]->move(Btns[i - 1]->x() + 60, Btns[i - 1]->y());
            Btns[i]->setText(" ");
        }
    }
}

void shudu::changeNum(int i) {
    if (qipan[i] == -1) {
        if (Btns[i]->text() == "1")
            Btns[i]->setText("0");
        else if (Btns[i]->text() == "0")
            Btns[i]->setText(" ");
        else
            Btns[i]->setText("1");
    }


}

void shudu::RandGener(char* filename)
{
    FILE* fp;
    int i = 0;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("fail to open file");
    }
    else {
        int integer;
        srand((unsigned)time(NULL));
        int x = 11 + rand() % 11;
        int j;
        while (fscanf(fp, "%d", &integer) != EOF)
        {
            qipan[i] = ans[i] = integer;
            //Btns[i]->setText(QString::number(integer, 10, 0));
            i++;
        }

        for (j = 0; j < x; j++)
        {
            int r = rand() % 6;
            int c = rand() % 6;
            qipan[r * 6 + c] = -1;
        }
    }
}

void shudu::showQipan() {
    lbs->setText("");
    char *rand_filename[] = {"/Users/justinxiang/DataStructure/StanSudo_1.txt","/Users/justinxiang/DataStructure/StanSudo_2.txt","/Users/justinxiang/DataStructure/StanSudo_3.txt","/Users/justinxiang/DataStructure/StanSudo_4.txt","/Users/justinxiang/DataStructure/StanSudo_5.txt"};
    srand((unsigned)time(NULL));
    int z = rand()%5;
    char *filename = rand_filename[z];
    RandGener(filename);
    for (int i = 0; i < 36; ++i) {
        Btns[i]->setStyleSheet("color:black;");
        if (qipan[i] == -1) {
            Btns[i]->setText(" ");

        }
        else if (qipan[i] == 0)
            Btns[i]->setText("0");
        else
            Btns[i]->setText("1");
    }
}

void shudu::showAns() {
    bool ifSuccess = 1;
    for (int i = 0; i < 36; ++i) {
        if (Btns[i]->text() != QString::number(ans[i], 10, 0)) {
            Btns[i]->setStyleSheet("color:red;  ");
            //ifSuccess = 0;
        }
        Btns[i]->setText(QString::number(ans[i], 10, 0));
    }
    if (ifSuccess)
        lbs->setText("成功！");

}

