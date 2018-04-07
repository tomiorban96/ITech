#include "value.hpp"

#include <istream>
#include <vector>

void intervals(std::istream& is, std::ostream& os) {
    std::size_t n, m;
    is >> n >> m;

	Value **intervals=new Value*[n];
	for (size_t i=0;i<n;i++) intervals[i]=new Value[2];

	Value *elements=new Value[m];

    for (size_t i=0;i<n;i++){
		is >> intervals[i][0] >> intervals[i][1];
	}
    for (size_t i=0;i<m;i++){
		is >> elements[i];
	}
	
	int *count=new int[m];
	int c=0;
	int index=0;
	
	for (size_t i=0;i<m;i++){
		c=0;
		for (size_t j=0;j<n;j++){
			if ( elements[i]<=intervals[j][1] && intervals[j][0]<=elements[i]) c++;
		}
		count[index]=c;
		index++;
	}

    // todo calculate result

    for (std::size_t i = 0; i < m; ++i){
        // todo write calculation result
	os << count[i] << std::endl;}
	
	for (size_t i=0;i<n;i++) delete[] intervals[i];
	delete[] elements;
	delete[] intervals;
	delete[] count;
}
