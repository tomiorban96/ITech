
#include <stdio.h>
#include <iostream>
int N, M;
using namespace std;

enum Lamp {
	A,
	B,
	C,
	S
};

class Field {
public:
	virtual int Pass(int L) = 0;
};

class Empty : public Field {
public:

	int lumination;
	int required;
	Lamp lamp;

	Empty() {
		lumination = 0;
		required = 0;
	}

	Empty (int r) {
		required = r;
	}

	int Pass(int L) {
		return L - 1;
	}
};

class Wall : public Field {
public:
	int Pass(int L) {
		return 0;
	}
};

class Glass : public Field {
public:
	int Pass(int L) {
		return L - 3;
	}
};

class Grid {
public:
	static Field grid[][];

	static void read() {
		cin >> N >> K;
		grid = new Field[N][K];
	}
};

int getMaxLight(int x, int y) {

	int sum = 0;
	
	//Jobbra
	int light = 9;
	for (int i = x + 1; i < K; i++) {
		sum += light;
		light--;
	}

	//Balra
	light = 9;
	for (int i = x - 1; i >= 0; i--) {
		sum += light;
		light--;
	}

	//Lefelé
	light = 9;
	for (int i = y - 1; i >= 0; i--) {
		sum += light;
		light--;
	}

	//Felfelé
	light = 9;
	for (int i = y + 1; i < N; i++) {
		sum += light;
		light--;
	}

	return sum;
}

int main(){

	//Field f1;
	Wall w;
	Empty e;
	Glass g;
	return 0;
}