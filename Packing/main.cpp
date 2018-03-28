#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;

int constexpr N = 10;
size_t K;

int table[N][N];

struct rect {
	int w;
	int h;
	int index;

	rect() = default;

	rect(int _w, int _h, int _index) {
		w = _w;
		h = _h;
		index = _index;
	}


};

rect* rects;

void debug() {
	cout << "\n";
	for (size_t i = 0; i < K; i++) {
		cout << rects[i].w << " " << rects[i].h << " " << rects[i].index << endl;
	}
}

void debugTable() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}

bool getFirstEmpty(vector<pair<int, int>> &v) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if ( (i==0 && j==0 && table[0][0] != -1) || (table[i][j] == -1 && ( (i==0 && table[0][j-1]!=-1) || (j==0 && table[i-1][0]!=-1) || (table[i-1][j]!=0 && table[i][j-1]!=0) ) )   ) {
				v.push_back(make_pair(i,j));
				return true;	
			}
		}
	}
	return false;
}

bool putRect(int x, int y, int w, int h, int index) {

	if (x + w > N) return false;
	if (y + h > N) return false;

	for (int i = x; i < x + w; i++) {
		for (int j = y; j < y + h; j++) {
			table[j][i] = index;
		}
	}
	return true;
}


int main() {


	//Init
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			table[i][j] = -1;
		}
	}

	cin >> K;
	rects = new rect[K];

	//Beolvasás, feltöltés
	for (size_t i = 0; i < K; i++) {
		cin  >> rects[i].w >> rects[i].h;
		rects[i].index = i;
	}

	//debug();

	qsort(rects, K, sizeof(rect), [](const void *a, const void *b){
		rect arg1 = *static_cast<const rect*>(a);
		rect arg2 = *static_cast<const rect*>(b);

		if (max(arg1.w, arg1.h) < max(arg2.w, arg2.h)) return 1;
		if (max(arg1.w, arg1.h) > max(arg2.w, arg2.h)) return -1;
		if (min(arg1.w, arg1.h) < min(arg2.w, arg2.h)) return 1;
		if (min(arg1.w, arg1.h) > min(arg2.w, arg2.h)) return -1;
		return 0;
	});

	debug();

	vector<pair<int, int>> v;
	getFirstEmpty(v);

	for (auto a : v) {
		cout << a.first << " " << a.second << endl;
	}
	
	putRect(0, 0, 6, 3, 0);

	getFirstEmpty(v);

	for (auto a : v) {
		cout << a.first << " " << a.second << endl;
	}
	//debugTable();

	delete[] rects;
	return 0;
}
