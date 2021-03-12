#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/qstylepainter.h>
#include <QtWidgets/qlabel.h>
#include <QDialog>
#include <vector>
#include <QCheckBox>
#include <locale>
#include <codecvt>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>
#include <iostream>
#include <fstream>
#include <string>
#include <qtextcodec.h>
#include <sstream>
#include <Windows.h>
#define MAX 25
#define MM 123456
#define INF -1
typedef int PathMatrix[MAX][MAX];     //用于存储最短路径中经过的顶点的下标
typedef int ShortPathTable[MAX][MAX];
using namespace std;
struct Graph {
	vector<QPoint> vexs;
	int matrix[MAX][MAX];
	int vexnum = MAX;
	Graph() = default;
	Graph(vector<QPoint>);
};

struct Edge {
	char start;
	char end;
	int distance;
};
vector<QPoint> read(string);
vector<QString> read(string, bool);
vector<vector<int>> read(bool,string);
void Floyed(Graph G, PathMatrix& P, ShortPathTable& D);
int getDist(QPoint a, QPoint b);
void getPath(PathMatrix& p, int a, int b, vector<int> &);
string GBKToUTF8(const char* strGBK);
