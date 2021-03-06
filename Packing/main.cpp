#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <list>

using namespace std;

int constexpr N = 4000;
size_t K;

int table[N][N];

struct rect {
	int w; //output eseten: x koord
	int h; //output eseten: y koord
	int index; //output eseten: -1: K -2: R -3: nem lett leteve
	rect() = default;
};

rect* rects;

void debugTable() {
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			cout << table[j][i] << " ";
		}
		cout << endl;
	}
}

bool putRect(int y, int x, int w, int h, int index) {
	for (int i=0;i<w;i++) if (x+i>=N || table[y][x+i]!=-1) return false;
	for (int i=0;i<h;i++) if (y+i>=N || table[y+i][x]!=-1) return false;
	for (int j = y; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			table[j][i] = index;
		}
	}
	return true;
}

int main() {
	

	//Init
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			table[j][i] = -1;
		}
	}
	
	//Beolvasás, feltöltés
	cin >> K;
	rects = new rect[K];
	for (size_t i = 0; i < K; i++) {
		cin  >> rects[i].w >> rects[i].h;
		rects[i].index = i;
	}
	
	//Tervrajzok rendezése
	qsort(rects, K, sizeof(rect), [](const void *a, const void *b){
		rect arg1 = *static_cast<const rect*>(a);
		rect arg2 = *static_cast<const rect*>(b);

		if (max(arg1.w, arg1.h) < max(arg2.w, arg2.h)) return 1;
		if (max(arg1.w, arg1.h) > max(arg2.w, arg2.h)) return -1;
		if (min(arg1.w, arg1.h) < min(arg2.w, arg2.h)) return 1;
		if (min(arg1.w, arg1.h) > min(arg2.w, arg2.h)) return -1;
		return 0;
	});
	
	//kimenethez rendezett tomb
	rect* output=new rect[K];
	for (size_t i=0;i<K;i++) output[i].index=-3; //kezdetben egyik tervrajz sem lett leteve
	
	//Tervrajzok listaba fuzese
	list<rect> rectsList;
	for (size_t i=0;i<K;i++) rectsList.push_back(rects[i]);
	
	long long sumArea=0;
	for (auto r : rectsList) sumArea+=(r.w*r.h); //ha nagyon nagy az osszterulete a tervrajzoknak, akkor a legnagyobbakat eldobjuk
	while (sumArea>=0.9*16000000){
		sumArea-=rectsList.front().w*rectsList.front().h;
		rectsList.pop_front();
	}
	

	int count=0;
	bool placed=false;
	while (!rectsList.empty()){ //elforgatas nelkul

		placed=false;
		rect current=rectsList.front();
		
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < N; i++) {
				if ( table[j][i] == -1 && ( (i==0 && j==0) || (j==0 && table[0][i-1]!=-1) || (i==0 && table[j-1][0]!=-1) || (table[j-1][i]!=-1 && table[j][i-1]!=-1) ) ) {
					placed=putRect(j,i,current.w,current.h,current.index);
					if (placed){
						rectsList.pop_front();
						count++;                             //sikerult letenni
						output[current.index].index=-2;
						output[current.index].w=i;
						output[current.index].h=j;
						j=N;
						break;
					}
				}
			}
		}
		if (!placed){
			rectsList.pop_front();
		}	
	}
	
	cout << count << endl;
	for (size_t i=0;i<K;i++){
		if (output[i].index==-2) cout << i << " " << output[i].w << " " << output[i].h <<  " K" << endl;
	}
	
	delete[]output;
	delete[] rects;
	return 0;
}