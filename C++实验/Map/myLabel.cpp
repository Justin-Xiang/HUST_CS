#include "myLabel.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
string location("src\\Location.txt"), edge("src\\Edge.txt"),
		org("src\\Organization.txt"), locorg("src\\Locorg.txt");
myLabel::myLabel(QWidget* parent) : QLabel(parent), 
									graph(read(location)),edges(read(edge)), orgs(read(org,1)), locorgs(read(1, locorg))
{
	for (int i = 0; i < 25; ++i)
		for (int j = 0; j < 25; ++j){
			if (i == j)
				D[i][j] = 0;
			else D[i][j] = MM;
		}
	for (auto e : edges) {
		D[e.x()][e.y()] = getDist(graph.vexs[e.x()], graph.vexs[e.y()]);
		D[e.y()][e.x()] = D[e.x()][e.y()];
	}
	Floyed(graph, P, D);
}

void myLabel::paintEvent(QPaintEvent* event)
{
	//QLabel::paintEvent(event);
	QLabel::paintEvent(event);
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing, true);
	QPen pen(QColor(0, 160, 230), 2);
	pen.setWidth(3);
	pen.setColor(Qt::red);
	painter.setPen(pen);
	if(flag)
	for (int i = 1; i < path.size(); ++i) {
		painter.drawLine(graph.vexs[path[i]], graph.vexs[path[i - 1]]);
	}
	//for (auto e : edges) {
		//painter.drawLine(graph.vexs[e.x()], graph.vexs[e.y()]);
	//}
	// ÉèÖÃ»­Ë¢ÑÕÉ«
	//painter.drawEllipse(916, 376, 3, 3);
}

void myLabel::setPath() {
	path.clear();
	flag = 1;
	path.push_back(pStart);
	getPath(P, pStart, pEnd, path);
	path.push_back(pEnd);
}