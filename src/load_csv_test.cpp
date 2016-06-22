#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "loadcsv.h"
#include "compression.h"

using namespace std;

int
main()
{
	string file_name, power_str;
	vector<float> power;
	float power_f;

	float test = 1.87;
	printf("Before: %f\n", test);
	mask(&test, (size_t)12);
	printf("After: %f\n", test);

	printf("Filename: \n");
	getline(cin, file_name);
	ifstream csvfile(file_name.c_str());
	while (csvfile.good()) {
		getline (csvfile, power_str);
		power_f = atof(power_str.c_str());
		mask(&power_f, 12);
		power.push_back(power_f);
	}

	create_test_files_from_arr(&power[0], power.size());
}
