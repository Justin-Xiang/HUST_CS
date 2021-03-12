#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/qstylepainter.h>
#include <QtWidgets/qlabel.h>
#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "def.h"
class myLabel : public QLabel {
	Q_OBJECT

public:
	myLabel(QWidget* parent);
	PathMatrix P;
	int pStart = 0, pEnd = 0;
	bool flag = 0;
	//std::vector<QPoint> points;
	Graph graph;
	ShortPathTable D;
	std::vector<int> path;
	std::vector<QPoint> edges;
	std::vector<QString> orgs;
	std::vector<vector<int>> locorgs;
	void setPath();
protected:
	void paintEvent(QPaintEvent*);
};