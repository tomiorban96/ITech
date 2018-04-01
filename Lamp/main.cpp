
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
	int lamp;		//0 = Nincs; 3, 5, 10 = Hagyományos; 11 = Spot

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
			cout << grid[i][j].current << " ";
		}
		cout << endl;
	}
}

bool putLamp(int x, int y, char type, int l) {

	if (type == 'S') {
		if (grid[x][y].lamp == 0) {
			grid[x][y].lamp = 11;
			grid[x][y].current = 10;
			return true;
		}
		return false;
	}

	int ray = l - 1;

	if (grid[x][y].current != 0 || grid[x][y].type == Wall || grid[x][y].type == Glass) return false;

	for (int i=x+1;i<K;i++) {
		if (ray==0) break;
		if (grid[y][i].type == Wall) break;
		else if (grid[y][i].type == Glass) ray -= 2;
		else if (grid[y][i].lamp != 0 && grid[y][i].lamp != 11) return false;
		ray--;
	} 

	ray = l - 1;
	for (int i=x-1;i>-1;i--) {
		if (ray==0) break;
		if (grid[y][i].type == Wall) break;
		else if (grid[y][i].type == Glass) ray -= 2;
		else if (grid[y][i].lamp != 0 && grid[y][i].lamp != 11) return false;
		ray--;
	}

	ray = l - 1;
	for (int i=y+1;i<N;i++) {
		if (ray==0) break;
		if (grid[i][x].type == Wall) break;
		else if (grid[i][x].type == Glass) ray -= 2;
		else if (grid[i][x].lamp != 0 && grid[i][x].lamp != 11) return false;
		ray--;
	}

	ray = l - 1;
	for (int i=y-1;i>-1;i--) {
		if (ray==0) break;
		if (grid[i][x].type == Wall) break;
		else if (grid[i][x].type == Glass) ray -= 2;
		else if (grid[i][x].lamp != 0 && grid[i][x].lamp != 11) return false;
		ray--;
	}

	grid[y][x].current = l;
	grid[y][x].lamp = l;

	ray = l - 1;
	for (int i=x+1;i<K;i++) {
		if (ray<=0) break;
		if (grid[y][i].type == Wall) break;
		else if (grid[y][i].type == Glass) ray -= 2;
		else grid[y][i].current += ray;
		ray--;
	} 

	ray = l - 1;
	for (int i=x-1;i>-1;i--) {
		if (ray<=0) break;
		if (grid[y][i].type == Wall) break;
		else if (grid[y][i].type == Glass) ray -= 2;
		else grid[y][i].current += ray;
		ray--;
	}

	ray = l - 1;
	for (int i=y+1;i<N;i++) {
		if (ray<=0) break;
		if (grid[i][x].type == Wall) break;
		else if (grid[i][x].type == Glass) ray -= 2;
		else grid[i][x].current += ray;
		ray--;
	}

	ray = l - 1;
	for (int i=y-1;i>-1;i--) {
		if (ray<=0) break;
		if (grid[i][x].type == Wall) break;
		else if (grid[i][x].type == Glass) ray -= 2;
		else grid[i][x].current += ray;
		ray--;
	}

	return true;
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

	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			if (grid[i][j].type == Empty) {
				int min = grid[i][j].min;
				if (min > 0) {
					//lampList.push_back(Lamp(j, i, 'S'));
					if (putLamp(i, j, 'S', 11))
						lampList.push_back(Lamp(j, i, 'S'));

				}
			}

		}
	}

	cout << lampList.size() << endl;

	for (auto a : lampList) {
		cout << a.x << " " << a.y << " " << a.type << endl;
	}*/
	cout << endl;
	putLamp(0, 0, 'C', 10);
	putLamp(3, 3, 'C', 10);
	putLamp(0, 4, 'C', 10);
	Debug();


	for (int i = 0; i < N; i++) {
		delete[] grid[i];
	}
	delete[] grid;
	
	return 0;
}