#pragma once
#include <vector>
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
class Position {
	Q_OBJECT
public:
	int x = 0, y = 0;
	Position() = default;
	Position(int x, int y);
	~Position();
};