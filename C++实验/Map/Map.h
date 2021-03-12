#pragma once

#include <QtWidgets/QWidget>
#include "ui_Map.h"
#include <QtWidgets/qstylepainter.h>
#include <QtWidgets/qlabel.h>
#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>
#include <vector>
#include "myLabel.h"
#include <qmessagebox.h>
#include <QDebug>
#include <QMenuBar>                         
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMouseEvent>
using namespace std;
class Map : public QWidget
{
    Q_OBJECT
public slots:
    void search();
public:
    Map(QWidget *parent = Q_NULLPTR);
    ~Map();
    //myLabel *label = new myLabel(this);
    //QLineEdit* start = new QLineEdit(this);
    //QLineEdit* end = new QLineEdit(this);
    //QPushButton* searchBtn = new QPushButton(this);
    std::vector<QLabel*> lbs;
    QMenuBar* menu_bar = new QMenuBar(this);             //����һ���˵���                                       //����ΪMainWindow�Ĳ˵���
    QToolBar* tool_bar = new QToolBar(this);                    //����һ��������                                           //��ӹ�������MainWindow
    QStatusBar* status_bar = new QStatusBar(this);         //����һ��״̬��
private:
    Ui::MapClass ui;
    
    //bool eventFilter(QObject* obj, QEvent* event);
    void setButtons();
    //void paintEvent(QPaintEvent* event);
    //bool Map::eventFilter(QObject* obj, QEvent* event);
};

int findOrg(const myLabel* label, const QLineEdit* edit);