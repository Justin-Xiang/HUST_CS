#include "Map.h"
using namespace std;
Map::Map(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	connect(ui.searchBtn, SIGNAL(clicked()), this, SLOT(search()));
    ui.label->resize(1676, 820);
	for (int i = 0; i < 25; ++i) {
		lbs.push_back(new QLabel(this));
	}
	QString str = "";
	menu_bar->addMenu(str);
	setButtons();
    ui.label->update();
	update();
}

Map::~Map() {
    delete &ui;
}

void Map::setButtons() {
	int x = 0, y = 0;
	int i = 0, j = 0;
	QString style = "QLabel{min-width: 3px; min-height: 3px;max-width:3px; max-height: 3px;border-radius: 8px;  border:1px solid black;background:red;}\
					QToolTip{border:1px solid rgb(118, 118, 118); background-color: #ffffff; color:#484848; font-size:12px;}";
	vector<int> v;
	string file("src\\Location.txt");
	string token;
	ifstream input;
	input.open(file, ios::in);
	string  m;
	
	if (!input.is_open())
		cout << "Error!";
	while (getline(input, m)) {
		istringstream iss(m);
		while (getline(iss, token, ',')) {
			v.push_back(stoi(token));
		}
		//painter.drawEllipse(v[i], v[i + 1], 3, 3);
		lbs[j]->setStyleSheet(style);
		QString str = "";
		for (auto a : ui.label->locorgs[j]) {
			str += ui.label->orgs[a];
			str += '\n';
		}
		str.chop(1);
		lbs[j]->setToolTip(str);
		lbs[j++]->move(v[i] + 190, v[i + 1] + 110);
		i += 2;
	}
	input.close();
	ui.label->update();
}

void Map::search() {
	int end, start;
	ui.label->pStart = findOrg(ui.label, ui.start); 
	ui.label->pEnd = findOrg(ui.label, ui.end);
	ui.label->setPath();
	ui.label->update();
}

int findOrg(const myLabel* label, const QLineEdit* edit) {
	int i = 0, j = 0;
	for (auto a : label->orgs) {
		if (a == edit->text()) {
			break;
		}
		++i;
	}
	if (i == label->orgs.size()) {
		throw "Can't find";
	}
	for (auto a : label->locorgs) {
		for (auto b : a) {
			if (b == i)
				return j;
		}
		++j;
	}
}