#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "eos_delaunay.h"
#include "Stopwatch.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char *argv[])
{
	//==============================================
	// print welcome message
	cout << endl
	     << "========================================"
                "========================================" << endl;
	cout << "= Code:    Equation of state interpolator" << endl
             << "= Purpose: Performance and closure tests of Delaunay interpolator" << endl
             << "= Author:  Christopher Plumberg" << endl
             << "= Contact: plumberg@illinois.edu" << endl
             << "= Date:    April 28, 2022" << endl
             << "========================================"
                "========================================" << endl << endl;

	//==============================================
	// check input first
	if (argc < 2)
	{
		cerr << "Usage: ./interpolate_ebsq [filename of EoS table]\n";
		exit(-1);
	}

	Stopwatch sw, swLoop;
	sw.Start();

	//==============================================
	// read path to input file from command line
	string path_to_file = string(argv[1]);

	//==============================================
	// set up EoS object
	cout << "Initializing equation of state "
                "interpolator:" << endl;
	cout << "  --> reading in equation of state "
                "table from: " << path_to_file << endl;
	eos_delaunay EoS( path_to_file );

	//==============================================
	// vectors to store input densities and
	// interpolated result for (T,muB,muQ,muS)
	vector<double> result(4, 0.0);
	vector<double> point({ 5754.35,  0.00231029,
                               0.351709, 0.378919   });

	//==============================================
	// time the interpolation itself
	swLoop.Start();
	cout << endl;

	//==============================================
	// call the interpolator
	const size_t n_repeat = 200000;
	cout << "Calling the interpolator "
	     << n_repeat << " times for test point: \n"
                "  --> {e,B,S,Q} = {"
             << point[0] << " MeV/fm^3," << point[1] << " 1/fm^3, "
             << point[2] << " 1/fm^3, " << point[3] << " 1/fm^3}" << endl;
	

	for (size_t i = 0; i < n_repeat; i++)
		EoS.interpolate(point, result);

	//==============================================
	// output result and compare with exact solution
	cout << "  --> exact result (units MeV):          "
	     << "252.5   52.5   52.5   52.5\n"
                "  --> interpolated result (units MeV):";
        for (const double & elem : result) cout << "   " << elem;
	cout << "\n";

	//==============================================
	// output timing results
	swLoop.Stop();
	sw.Stop();
	cout << endl;
	cout << "Average time to interpolate: " << swLoop.printTime()/n_repeat << " s." << endl;
	cout << "Total runtime: " << sw.printTime() << " s." << endl;

	return 0;
}
