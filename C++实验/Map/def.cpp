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
    int flag[MAX];      // flag[i]=1��ʾ"����vs"��"����i"�����·���ѳɹ���ȡ��

    // ��ʼ��
    for (i = 0; i < G.vexnum; i++)
    {
        flag[i] = 0;              // ����i�����·����û��ȡ����
        prev[i] = 0;              // ����i��ǰ������Ϊ0��
        dist[i] = G.matrix[vs][i];// ����i�����·��Ϊ"����vs"��"����i"��Ȩ��
    }

    // ��"����vs"������г�ʼ��
    flag[vs] = 1;
    dist[vs] = 0;

    // ����G.vexnum-1�Σ�ÿ���ҳ�һ����������·����
    for (i = 1; i < G.vexnum; i++)
    {
        // Ѱ�ҵ�ǰ��С��·����
        // ������δ��ȡ���·���Ķ����У��ҵ���vs����Ķ���(k)��
        min = INF;
        for (j = 0; j < G.vexnum; j++)
        {
            if (flag[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        // ���"����k"Ϊ�Ѿ���ȡ�����·��
        flag[k] = 1;

        // ������ǰ���·����ǰ������
        // �������Ѿ�"����k�����·��"֮�󣬸���"δ��ȡ���·���Ķ�������·����ǰ������"��
        for (j = 0; j < G.vexnum; j++)
        {
            tmp = (G.matrix[k][j] == INF ? INF : (min + G.matrix[k][j])); // ��ֹ���
            if (flag[j] == 0 && (tmp < dist[j]))
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    // ��ӡdijkstra���·���Ľ��
    printf("dijkstra(%c): \n", G.vexs[vs]);
    for (i = 0; i < G.vexnum; i++)
        printf("  shortest(%c, %c)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);
}

void Floyed(Graph G, PathMatrix& P, ShortPathTable& D) {
    //��P�����D������г�ʼ��
    for (int v = 0; v < G.vexnum; v++) {
        for (int w = 0; w < G.vexnum; w++) {
            P[v][w] = -1;
        }
    }
    //�ó�ÿ��������Ϊ��������
    for (int k = 0; k < G.vexnum; k++) {
        //���ڵ�k��������˵���������������������㣬�жϼ�ӵľ����Ƿ����
        for (int v = 0; v < G.vexnum; v++) {
            for (int w = 0; w < G.vexnum; w++) {
                //�жϾ�������k�ľ����Ƿ���̣�����жϳ�������洢������̵�·��
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
        //˵��û����ת���㣬ֱ�ӷ���.
        return;
    getPath(p, a, k, path);//Ѱ��i��k֮��
    path.push_back(k);
    getPath(p, k, b, path);//Ѱ��k��j֮��
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