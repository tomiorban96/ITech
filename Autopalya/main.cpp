#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <list>

using namespace std;

int N; //varosok szama
int K; //oszekotendo varosok szama

long long x2;
long long y2; //eddigi legsurubb szektor jobb felso sarka
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
	long long r01=1000000000000000000;
	vector<point> sectorCities;
	vector<point> sectorCitiesTemp;
	for (int i=0;i<2;i++){
		for (int j=0;j<2;j++){
			long long x1=x0-j*a1; //aktualisan vizsgalt szektor jobb felso sarka
			long long y1=y0-i*a1;
			int count=0;
			sectorCitiesTemp.clear();
			for (size_t k=0;k<cities.size();k++) if (cities[k].x>=(x1-a1) && cities[k].x<=x1 && cities[k].y>=(y1-a1) && cities[k].y<=y1) {count++; sectorCitiesTemp.push_back(cities[k]);}
			if ( r01>((a1*a1)/double(count)) && count>=K){
					found=true;
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


	bool repeat=densitySearch(1000000000,1000000000,2000000000, cities); //talalunk-e a teljes palyanak legsurubb reszletet
	while (repeat) //ha igen, akkor tovabb keresunk, ha nem, akkor igy jartunk
	{
		repeat=densitySearch(x2,y2,a1, cities);
	} //ekkor a cities legalabb K varost tartalmaz, a palya kb legsurubb reszletebol
	
	list<point> citiesList;
	int highway[K];
	for (size_t i=0;i<cities.size();i++) citiesList.push_back(cities[i]);
	auto currentCity=citiesList.front();
	highway[0]=currentCity.index;
	citiesList.pop_front(); //az autopalya kezdete a lista elso eleme	
	if (cities.size()<=50000)
	{
	for (int i=1;i<K;i++){
		auto closestCity=citiesList.begin();
		long long dist=2000000000;
		for (auto it=citiesList.begin();it!=citiesList.end(); it++){
			long long d= (it->x-currentCity.x)*(it->x-currentCity.x)+(it->y-currentCity.y)*(it->y-currentCity.y);
			if ( d<dist ){
				dist=d;
				closestCity=it;
			}
		}
		currentCity=(*closestCity);
		highway[i]=currentCity.index;
		citiesList.erase(closestCity);
	}
	for (int i=0;i<K;i++) cout << names[highway[i]] << endl;
	}
	else if (K<=95000){
	for (int i=1;i<K;i++){
		auto closestCity=citiesList.begin();
		long long dist=2000000000;
		double m=0;
		for (auto it=citiesList.begin(); size_t(m)<(citiesList.size()-2); (it++)++){
			m+=2;
			long long d= (it->x-currentCity.x)*(it->x-currentCity.x)+(it->y-currentCity.y)*(it->y-currentCity.y);
			if ( d<dist ){
				dist=d;
				closestCity=it;
			}
		}
		currentCity=(*closestCity);
		highway[i]=currentCity.index;
		citiesList.erase(closestCity);
	}
	for (int i=0;i<K;i++) cout << names[highway[i]] << endl;
	}
	else{
		for (int i=1;i<K;i++){
		auto closestCity=citiesList.begin();
		long long dist=2000000000;
		double m=0;
		for (auto it=citiesList.begin(); size_t(m)<(citiesList.size()-3); ((it++)++)++){
			m+=3;
			long long d= (it->x-currentCity.x)*(it->x-currentCity.x)+(it->y-currentCity.y)*(it->y-currentCity.y);
			if ( d<dist ){
				dist=d;
				closestCity=it;
			}
		}
		currentCity=(*closestCity);
		highway[i]=currentCity.index;
		citiesList.erase(closestCity);
	}
	for (int i=0;i<K;i++) cout << names[highway[i]] << endl;	
	}
	
	
	
	delete[] names;
	return 0;	
}