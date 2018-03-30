#include <iostream>
#include <vector>
#include <string>


using namespace std;

int N; //varosok szama
int K; //oszekotendo varosok szama

long long x2;
long long y2; //eddigi legsurubb szektor
long long a1; //egy szektor oldalhossza

struct point {
	int x;
	int y;
	int index;
	point()=default;
};



bool densitySearch(long long x0, long long y0, long long a0, vector<point>& cities){ //x0 y0: jobb felso sarok, a0: negyzet oldalhossza
	bool found=false;
	a1=a0/2; //egy szektor oldalhossza
	x2=x0;
	y2=y0; //eddigi legsurubb szektor
	long double r01=0;
	vector<point> sectorCities;
	vector<point> sectorCitiesTemp;
	for (int i=0;i<3;i++){
		for (int j=0;j<3;j++){
			long long x1=x0-j*a1/2; //aktualisan vizsgalt szektor jobb felso sarka
			long long y1=y0-i*a1/2;
			int count=0;
			sectorCitiesTemp.clear();
			for (size_t k=0;k<cities.size();k++) if (cities[k].x>=(x1-a1) && cities[k].x<=x1 && cities[k].y>=(y1-a1) && cities[k].y<=y1) {count++; sectorCitiesTemp.push_back(cities[k]);}
			if ( r01<(double(count)/(a1*a1)) && count>=K){
					found=true;
					cout << "talaltam surubbet" << endl;
					sectorCities=sectorCitiesTemp;
					r01=double(count)/(a1*a1);
					x2=x1;
					y2=y1;
				}
			}
	}
	if (found) cities=sectorCities;
	return found;
}

int main()
{
	cin >> N >> K;
	vector<point> cities(N);
	string* names=new string[N];
	for (int i=0;i<N;i++){
		cin >> names[i];
		cin >> cities[i].x >> cities[i].y;
		cities[i].index=i;
	}
	
	if (densitySearch(8,8,16, cities)) cout << x2 << " " << y2 << " " << a1 << " " << cities.size() << endl;
	for (auto v : cities) cout << v.x << " " << v.y << endl;

	
	bool repeat=densitySearch(8,8,16, cities);
	
	while (repeat)
	{
		repeat=densitySearch(x2,y2,a1, cities);
	}
	
	
	
	delete[] names;
	return 0;	
}