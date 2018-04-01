
#include <stdio.h>
#include <iostream>
#include <list>
#include <iterator>


int N, K, M;
using namespace std;



enum Type {
	Empty,
	Wall,
	Glass
};

struct Field {
	Type type;
	int min;
	int current;
	int lamp;

	Field() : current(0), lamp(0) {}
};

struct Lamp {
	int x;
	int y;
	char type;

	Lamp(int _x, int _y, char c) {
		x = _x + 1;
		y = _y + 1;
		type = c;
	}
};

Field **grid;

void Debug() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			if (grid[i][j].type == Wall) cout << "F";
			if (grid[i][j].type == Glass) cout << "U";
			if (grid[i][j].type == Empty) cout << grid[i][j].min;
		}
		cout << endl;
	}
}

int main(){

	cin >> N >> K;

	//grid = new Field[N][K];
	grid = new Field*[N];
	for (int i = 0; i < N; i++) {
		grid[i] = new Field[K];
	}


	//Beolvasás
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			char c;
			cin >> c;
			if (c < 58) {
				grid[i][j].type = Empty;
				grid[i][j].min = (int)c - (int)'0';
			}
			else if (c == 'F') {
				grid[i][j].type = Wall;
			}
			else {
				grid[i][j].type = Glass;
			}
		}
	}

	//Debug();

	list<Lamp> lampList;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			if (grid[i][j].type == Empty) {
				int min = grid[i][j].min;
				if (min > 0) {
					lampList.push_back(Lamp(j, i, 'S'));
					/*if (min <= 3) {
						grid[i][j].current = 3;
						lampList.push_back(Lamp(j, i, 'A'));
					}
					else if (min <= 5) {
						grid[i][j].current = 5;
						lampList.push_back(Lamp(j, i, 'B'));
					}
					else {
						grid[i][j].current = 10;
						lampList.push_back(Lamp(j, i, 'C'));
					}*/
				}
			}

		}
	}

	cout << lampList.size() << endl;

	for (auto a : lampList) {
		cout << a.x << " " << a.y << " " << a.type << endl;
	}



	for (int i = 0; i < N; i++) {
		delete[] grid[i];
	}
	delete[] grid;
	
	return 0;
}