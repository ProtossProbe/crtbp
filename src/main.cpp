//
//  crtbp.cpp
//
//
//  Created by Protoss Probe on 2017/06/07.
//  Copyright � 2016-2017 probe. All rights reserved.
//

#include "crtbp.hpp"

using namespace std;
using namespace boost::math;
using namespace boost::numeric::odeint;
using namespace ProbeUtility;

int main(int argc, char *argv[]) {
    string inputstring(argv[1]);
    string infostring(argv[2]);
    auto input = readInputFromTxt(inputstring);
    auto info = readInfoFromTxt(infostring);
    int number = input.size();
    cout << "Total Number: " << number << endl;

    double endt = info[0] * pi2, dt = info[1] / year * pi2;
    int jump = info[2];

    crtbp system;
    orbit3d *orbits = new orbit3d[MAX_NUMBER];
    for (size_t i = 0; i < number; i++) {
        orbits[i].setInitial(input[i].first, dt, endt, to_string(i + 1));
    }
    double start = omp_get_wtime();
    system.inteNbody(orbits, number, endt, jump);
    cout << "Time: " << omp_get_wtime() - start << endl;
}