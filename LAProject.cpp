#include<iostream>
#include<cmath>
using namespace std;

const int n = 13, nr = 13, nc = 13;
int nexchange = 0, r = 1, c = 1;
double d[14][14];
double co[14][14];
bool flag[14] = { 0 };

void formation();
int nzero();
void exchange(int i, int j);
void Hermite1();
void detcalcu();
void Hermite2();
void hermite();
void maxindependent();
double innerpro(int a, int b);
void schmidt();

int main() {
	formation();
	for (int i = 1; i <= 13; i++) {
		for (int j = 1; j <= 13; j++) {
			co[i][j] = d[i][j];
		}
	}
	detcalcu();
	hermite();
	maxindependent();
	schmidt();
}

void formation() {
	int a[13] = { 0 }, t[13] = { 0 }, r[1000] = { 0 };
	int i, j = 1, k = 1, l = 1, m = 2;
	cout << "本程序可以根据你的学号（12位）生成13阶行列式，请输入你的学号，按空格隔开："
		<< endl;
	for (i = 1; i <= 12; i++) {
		cin >> a[i];
		t[i] = a[i];
	}
	cout << endl;
	while (j <= 169) {
		if (a[k] < 10) {
			r[j++] = a[k++];
		}
		else if (a[k] < 100) {
			r[j++] = a[k] / 10;
			r[j++] = a[k] % 10;
			k++;
		}
		else if (a[k] < 1000) {
			r[j++] = a[k] / 100;
			r[j++] = a[k] % 100 / 10;
			r[j++] = a[k] % 10;
			k++;
		}
		else if (a[k] < 10000) {
			r[j++] = a[k] / 1000;
			r[j++] = a[k] % 1000 / 100;
			r[j++] = a[k] % 100 / 10;
			r[j++] = a[k] % 10;
			k++;
		}
		else if (a[k] < 100000) {
			r[j++] = a[k] / 10000;
			r[j++] = a[k] % 10000 / 1000;
			r[j++] = a[k] % 1000 / 100;
			r[j++] = a[k] % 100 / 10;
			r[j++] = a[k] % 10;
			k++;
		}
		else if (a[k] < 1000000) {
			r[j++] = a[k] / 100000;
			r[j++] = a[k] % 100000 / 10000;
			r[j++] = a[k] % 10000 / 1000;
			r[j++] = a[k] % 1000 / 100;
			r[j++] = a[k] % 100 / 10;
			r[j++] = a[k] % 10;
			k++;
		}
		else if (a[k] < 10000000) {
			r[j++] = a[k] / 1000000;
			r[j++] = a[k] % 1000000 / 100000;
			r[j++] = a[k] % 100000 / 10000;
			r[j++] = a[k] % 10000 / 1000;
			r[j++] = a[k] % 1000 / 100;
			r[j++] = a[k] % 100 / 10;
			r[j++] = a[k] % 10;
			k++;
		}
		else if (a[k] < 100000000) {
			r[j++] = a[k] / 10000000;
			r[j++] = a[k] % 10000000 / 1000000;
			r[j++] = a[k] % 1000000 / 100000;
			r[j++] = a[k] % 100000 / 10000;
			r[j++] = a[k] % 10000 / 1000;
			r[j++] = a[k] % 1000 / 100;
			r[j++] = a[k] % 100 / 10;
			r[j++] = a[k] % 10;
			k++;
		}
		if (k > 12) {
			for (i = 1; i <= 12; i++) {
				a[i] = pow(t[i], m);
			}
			m++;
			k = 1;
		}
	}
	for (i = 1; i <= 13; i++) {
		for (j = 1; j <= 13; j++) {
			d[i][j] = r[l++];
		}
	}
	for (i = 1; i <= 13; i++) {
		for (j = 1; j <= 13; j++) {
			cout << d[i][j] << ',';
		}
		cout << endl;
	}
	return;
}

int nzero() {
	int i;
	for (i = r; i <= n; i++) {
		if (d[i][c] != 0) return i;
	}
	c++;
	nzero();
}

void exchange(int i, int j) {
	double tmp;
	for (int k = 1; k <= n; k++)
	{
		tmp = d[j][k];
		d[j][k] = d[i][k];
		d[i][k] = tmp;
	}
	nexchange++;
}

void Hermite1() {
	int i, j, l;
	if (r == n) return;
	l = nzero();
	if (l > r) exchange(l, r);
	for (i = r + 1; i <= n; i++) {
		for (j = c + 1; j <= n; j++) {
			d[i][j] -= d[i][c] / d[r][c] * d[r][j];
		}
		d[i][c] = 0;
	}
	r++;
	Hermite1();
}

void detcalcu() {
	int i;
	double ans = 1.0;
	cout << "接下来计算该行列式的值：";
	//for (i = 1; i <= n; i++)
	//	for (j = 1; j <= n; j++)
	//		cin >> d[i][j];
	Hermite1();
	for (i = 1; i <= n; i++) {
		ans *= d[i][i];
	}
	ans *= pow(-1, nexchange);
	cout << ans << endl << endl;
	return;
}

void Hermite2() {
	int i, j = 1, k, l;
	double t1, t2;
	for (i = 1; i <= nr; i++) {
		while (d[i][j] == 0 && j <= nc + 1) {
			j++;
		}
		if (j > nc) break;
		t1 = d[i][j];
		for (k = j; k <= nc; k++) {
			d[i][k] /= t1;
		}
		for (k = 1; k <= i - 1; k++) {
			t2 = d[k][j];
			for (l = j; l <= nc; l++) {
				d[k][l] -= (d[i][l] * t2);
			}
		}
	}
}

void hermite() {
	int i, j;
	cout << "将该矩阵化为Hermite标准型，得：" << endl;
	//for (i = 1; i <= nr; i++)
	//	for (j = 1; j <= nc; j++)
	//		cin >> d[i][j];
	Hermite1();
	Hermite2();
	for (i = 1; i <= nr; i++) {
		for (j = 1; j <= nc; j++)
			cout << d[i][j] << ' ';
		cout << endl;
	}
	cout << endl << endl;
	return;
}

void maxindependent() {
	cout << "该矩阵的极大无关组为：" << endl;
	int i, j, k;
	for (i = 1; i <= 13; i++) {
		for (j = 1; j <= 13; j++) {
			if (d[i][j] == 0) continue;
			else {
				flag[j] = 1;
				break;
			}
		}
	}
	for (j = 1; j <= 13; j++) {
		if (flag[j] == 1) {
			cout << '(';
			for (i = 1; i <= 13; i++) {
				cout << co[i][j] << ' ';
			}
			cout << ")T" << endl;
		}
	}
	cout << endl << endl;
}

double innerpro(int a, int b) {
	double s = 0;
	for (int i = 1; i <= 13; i++) {
		s += co[i][a] * co[i][b];
	}
	return s;
}

void unitization(int a) {
	double s = 0;
	for (int i = 1; i <= 13; i++) {
		s += co[i][a] * co[i][a];
	}
	s = sqrt(s);
	for (int i = 1; i <= 13; i++) {
		co[i][a] /= s;
	}
}

void schmidt() {
	cout << "经Schmidt正交化后得到的标准正交组为：" << endl;
	int i = 1, j, k = 1;
	for (j = 2; j <= 13; j++) {
		if (k == j) {
			k = 1;
			continue;
		}
		else {
			for (i = 1; i <= 13; i++) {
				co[i][j] -= innerpro(j, k) / innerpro(k, k) * co[i][k];
			}
			k++;
		}
	}
	for (i = 1; i <= 13; i++) {
		unitization(i);
	}
	for (j = 1; j <= 13; j++) {
		if (flag[j] == 1) {
			cout << '(';
			for (i = 1; i <= 13; i++) {
				cout << co[i][j] << ' ';
			}
			cout << ")T" << endl;
		}
	}
	cout << endl << endl;
}