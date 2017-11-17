#define CSV_IO_NO_THREAD
#include "fast-cpp-csv-parser/csv.h"
#include <iostream>
#include <set>
#include <map>
#include <time.h>
using namespace std;

// Split:
// function to split the string of coordinates into vector entries
vector<char*> split(char* coords, char delim) {
	vector<char*> splitter;
	char* splitCoords = strtok(coords, " ");
	while(splitCoords) {
		splitter.push_back(splitCoords);
		splitCoords = strtok(NULL, " ");
	}
	return splitter;
}

int main() {
	clock_t t;
	t = clock();
	// Map to store all of the zips in MD and map them to their coordinates
	// Key = ZIP
	// Value = vector of Coordinates
	map<char*, vector<char*>> zips;

	// Map to store all of the zips in MD and map them to their neighbors
	// Key = ZIP
	// Value = set of neighboring ZIPS
	map<char*, set<char*>> neighbors;

	// Column names for reading in the csv
	char* poname;
	char* zip;
	char* latitude;
	char* pop2001;
	char* state;
	char* area;
	char* longitude;
	char* sumblkpop;
	char* coords;

	// Read in the csv containing all the zips in MD
	io::CSVReader<9, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("data_filtered.csv");
	while(in.read_row(poname, zip, latitude, pop2001, state, area, longitude, sumblkpop, coords)) {
		vector<char*> coordString;
		coordString = split(coords, ',');
		zips[zip] = coordString;
	}

	// Iterate over the map of ZIPS
	for (auto it = zips.cbegin(); it != zips.cend(); ++it) {
		set<char*> neighbor_set;
		// Iterate over the map of ZIPS
		for (auto it2 = zips.cbegin(); it2 != zips.cend(); ++it2) {
			// If comparing the same ZIP, skip it
			if(it->first == it2->first) {
				continue;
			}
			// Iterate over the first ZIP's vector of coordinates
			for(unsigned int i = 0; i < it->second.size(); i++) {
				// Iterate over the second ZIP's vector of coordinates
				for (unsigned int j = 0; j < it2->second.size(); j++) {
					// If the coordinates are equal, then the ZIPs are neighbors
					if (strcmp(it->second[i],it2->second[j]) == 0) {
						neighbor_set.insert(it2->first);
					}
				}
			}
		}
		neighbors[it->first] = neighbor_set;
	}

	// Uncomment following section to output the neighbors to the console

	for (auto it = neighbors.cbegin(); it != neighbors.cend(); it++) {
		cout << it->first << ": ";
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}

	t = clock() - t;
	printf("Time %f\n", ((float)t)/CLOCKS_PER_SEC);

};
