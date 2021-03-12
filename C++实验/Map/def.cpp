#include "def.h"
using namespace std;
Graph::Graph(vector<QPoint> p):vexs(p){}

int getDist(QPoint a, QPoint b) {
    return (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y());
}
vector<QPoint> read(string file) {
	int x = 0, y = 0;
	int i = 0, j = 0;

	string token;
	ifstream input;
	input.open(file, ios::in);
	string  m;
	vector<int> v;
	vector<QPoint> points;
	if (!input.is_open())
		cout << "Error!";
	while (getline(input, m)) {
		istringstream iss(m);
		while (getline(iss, token, ',')) {
			v.push_back(stoi(token));
		}
		//painter.drawEllipse(v[i], v[i + 1], 3, 3);
		QPoint pos(v[i], v[i + 1]);
		points.push_back(pos);
		i += 2;
	}
	input.close();
	return points;
}

vector<QString> read(string file, bool flag) {
    char c[20];
    vector<QString> org;
    //wcout.imbue(locale("chs"));
    QTextCodec* coder = QTextCodec::codecForName("utf-8");
    string m;
    ifstream input;
    input.open(file);
    while (getline(input, m)) {
        string w = m;
        strcpy(c, w.c_str());
        org.push_back(QString::fromStdString(GBKToUTF8(c)));
    }
    input.close();
    return org;
}

vector<vector<int>> read(bool flag, string file) {
    int i = 0;
    string token;
    ifstream input;
    input.open(file, ios::in);
    string  m;
    vector<vector<int>> v;
    if (!input.is_open())
        cout << "Error!";
    while (getline(input, m)) {
        vector<int> p;
        v.push_back(p);
        istringstream iss(m);
        while (getline(iss, token, ',')) {
            v[i].push_back(stoi(token));
        }
        ++i;
        //painter.drawEllipse(v[i], v[i + 1], 3, 3);
    }
    input.close();
    return v;
}

void dijkstra(Graph G, int vs, int prev[], int dist[])
{
    int i, j, k;
    int min;
    int tmp;
    int flag[MAX];      // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。

    // 初始化
    for (i = 0; i < G.vexnum; i++)
    {
        flag[i] = 0;              // 顶点i的最短路径还没获取到。
        prev[i] = 0;              // 顶点i的前驱顶点为0。
        dist[i] = G.matrix[vs][i];// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }

    // 对"顶点vs"自身进行初始化
    flag[vs] = 1;
    dist[vs] = 0;

    // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
    for (i = 1; i < G.vexnum; i++)
    {
        // 寻找当前最小的路径；
        // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
        min = INF;
        for (j = 0; j < G.vexnum; j++)
        {
            if (flag[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        // 标记"顶点k"为已经获取到最短路径
        flag[k] = 1;

        // 修正当前最短路径和前驱顶点
        // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < G.vexnum; j++)
        {
            tmp = (G.matrix[k][j] == INF ? INF : (min + G.matrix[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp < dist[j]))
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    // 打印dijkstra最短路径的结果
    printf("dijkstra(%c): \n", G.vexs[vs]);
    for (i = 0; i < G.vexnum; i++)
        printf("  shortest(%c, %c)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);
}

void Floyed(Graph G, PathMatrix& P, ShortPathTable& D) {
    //对P数组和D数组进行初始化
    for (int v = 0; v < G.vexnum; v++) {
        for (int w = 0; w < G.vexnum; w++) {
            P[v][w] = -1;
        }
    }
    //拿出每个顶点作为遍历条件
    for (int k = 0; k < G.vexnum; k++) {
        //对于第k个顶点来说，遍历网中任意两个顶点，判断间接的距离是否更短
        for (int v = 0; v < G.vexnum; v++) {
            for (int w = 0; w < G.vexnum; w++) {
                //判断经过顶点k的距离是否更短，如果判断成立，则存储距离更短的路径
                if (D[v][w] > D[v][k] + D[k][w]) {
                    D[v][w] = D[v][k] + D[k][w];
                    D[w][v] = D[v][w];
                    P[v][w] = k;
                    P[w][v] = k;
                }
            }
        }
    }
}

void getPath(PathMatrix& p, int a, int b, vector<int> &path) {
    int k = p[a][b];
    if (k == -1)
        //说明没有中转顶点，直接返回.
        return;
    getPath(p, a, k, path);//寻找i和k之间
    path.push_back(k);
    getPath(p, k, b, path);//寻找k和j之间
}

string GBKToUTF8(const char* strGBK)
{
    int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    string strTemp = str;
    if (wstr) delete[] wstr;
    if (str) delete[] str;
    return strTemp;
}