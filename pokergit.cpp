// pokerfinal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>


using namespace std;
double p30, p32, p12, p10;

double evp(double  bb2c, double b0r, double b2r, double a1r, double aa1r) {
	double ev = p30*((1 - b0r) + b0r * 3);
	ev += p10*((1 - a1r)*-1 + a1r*((1 - b0r) + b0r*((1 - aa1r)*-3 + aa1r * 3)));
	ev += p32*((1 - b2r) + b2r*(bb2c * 9 + ((1 - bb2c) * 3)));
	ev += p12*((1 - a1r)*-1 + a1r*((1 - b2r) + b2r*((1 - aa1r)*-3 + aa1r*((1 - bb2c) * 3 + bb2c*-9))));
	return ev;

}

int main()
{

	//double p3 = 0.4, p2 = 0.5;
	//double p3 = 0.4, p2 = 1; =LOL= double p3 = 0.4, p2 = 0.25; 
	//double p3 = 0.0, p2 = 0.3;
	//double p3 = 0.0, p2 = 0.2;
	double p3 = 0.02, p2 = 0.015;
	p32 = p3*p2;
	p30 = p3*(1 - p2);
	p12 = (1 - p3)*p2;
	p10 = (1 - p3)*(1 - p2);
	cout << fixed << setprecision(4);
	double  bb2c = 0.5, b0r = 0.5, b2r = 0.5;
	double a1r = 1, aa1r = 1;

	for (int i = 0; i < 10000; i++) {
		//B
		if (p32 * 9 - p12 * 9 * a1r*aa1r > p32 * 3 + p12 * 3 * a1r*aa1r) bb2c = 0;
		else bb2c = 1;

		if (a1r*p12*((1 - aa1r)*-3 + aa1r*(bb2c*-9 + (1 - bb2c) * 3)) + p32*(bb2c * 9 + (1 - bb2c) * 3) > a1r*p12 + 1 * p32) b2r = 0;
		else b2r = 1;

		//cout << "a=" << a1r*((1 - aa1r)*(-3) + aa1r * 3) + 3 << " b=" << a1r + 1 << endl;
		if (a1r*p10*((1 - aa1r)*(-3) + aa1r * 3) + p30 * 3 > p10*a1r + p30 * 1) b0r = 0;
		else b0r = 1;
		if (i>9990) cout << "bb2c=" << bb2c << " b2r=" << b2r << " b0r=" << b0r << " evp=" << evp(bb2c, b0r, b2r, a1r, aa1r) << " : ";

		//A
		aa1r += 0.001*a1r*(p10*b0r * 3 + p12*b2r*(bb2c*(-9) + (1 - bb2c) * 3) - (p10*b0r*(-3) + p12*b2r*(-3)));
		if (aa1r < 0) aa1r = 0;
		if (aa1r > 1) aa1r = 1;
		a1r += 0.001*(p10*(1 - b0r) + p10*b0r*((1 - aa1r)*(-3) + aa1r*(3)) + p12*(1 - b2r) + p12*b2r*((1 - aa1r)*(-3) + aa1r*(bb2c*(-9) + (1 - bb2c) * 3)) - (-p10 - p12));
		if (a1r < 0) a1r = 0;
		if (a1r > 1) a1r = 1;
		if (i > 9990) cout << "aa1r=" << aa1r << " a1r=" << a1r << " ev=" << evp(bb2c, b0r, b2r, a1r, aa1r);
		if (i > 9990) {
			cout << " 30=" << p30*((1 - b0r) + b0r * 3);
			cout << " 10=" << p10*((1 - a1r)*-1 + a1r*((1 - b0r) + b0r*((1 - aa1r)*-3 + aa1r * 3)));
			cout << " 32=" << p32*((1 - b2r) + b2r*(bb2c * 9 + ((1 - bb2c) * 3)));
			cout << " 12=" << p12*((1 - a1r)*-1 + a1r*((1 - b2r) + b2r*((1 - aa1r)*-3 + aa1r*((1 - bb2c) * 3 + bb2c*-9)))) << endl;
		}
	}

	//cout << "evp=" << evp(bb2c, b0r, b2r, a1r, aa1r) << endl;

	//bb2c = 0, b0r = 0, b2r = 0;
	double a1rL = a1r, aa1rL = aa1r;
	bb2c = 0.51, b0r = 0.51, b2r = 0.51;
	a1r = 0.51, aa1r = 0.51;

	for (int i = 0; i < 10000; i++) {
		//A
		if (p10*b0r * 3 + p12*b2r*(bb2c*(-9) + (1 - bb2c) * 3) > p10*b0r*(-3) + p12*b2r*(-3)) {
			aa1r = 1;
		}
		else {
			aa1r = 0;
		}

		if (p10*(1 - b0r) + p10*b0r*((1 - aa1r)*(-3) + aa1r*(3)) + p12*(1 - b2r) + p12*b2r*((1 - aa1r)*(-3) + aa1r*(bb2c*(-9) + (1 - bb2c) * 3)) > -p10 - p12) {
			a1r = 1;
		}
		else {
			a1r = 0;
		}
		//////////////////////////
		if (i>9990) cout << "aa1r=" << aa1r << " a1r=" << a1r << " evp=" << evp(bb2c, b0r, b2r, a1r, aa1r) << " : ";

		//B
		bb2c -= 0.001*b2r*(p32 * 9 - 9 * p12*a1r*aa1r - (p32 * 3 + p12 * 3 * a1r*aa1r));
		if (bb2c < 0) bb2c = 0;
		if (bb2c > 1) bb2c = 1;
		b2r -= 0.001*(p12*a1r*((1 - aa1r)*(-3) + aa1r*(bb2c*(-9) + (1 - bb2c) * 3)) + p32*(bb2c * 9 + (1 - bb2c) * 3) - (p12*a1r + p32 * 1));
		if (b2r < 0) b2r = 0;
		if (b2r > 1) b2r = 1;
		b0r -= 0.001*(p10*a1r*((1 - aa1r)*(-3) + aa1r * 3) + p30 * 3 - (p10*a1r + p30 * 1));
		if (b0r < 0) b0r = 0;
		if (b0r > 1) b0r = 1;
		//////////////////////////
		if (i>9990) cout << "bb2c=" << bb2c << " b2r=" << b2r << " b0r=" << b0r << " ev=" << evp(bb2c, b0r, b2r, a1r, aa1r);
		if (i>9990) cout << " 30=" << (1 - b0r) + b0r * 3 << " 10=" << (1 - a1r)*-1 + a1r*((1 - b0r) + b0r*((1 - aa1r)*-3 + aa1r * 3)) << " 32=" << (1 - b2r) + b2r*(bb2c * 9 + ((1 - bb2c) * 3)) << " 12=" << (1 - a1r)*-1 + a1r*((1 - b2r) + b2r*((1 - aa1r)*-3 + aa1r*((1 - bb2c) * 3 + bb2c*-9))) << endl;

	}


	cout << "EV=" << evp(bb2c, b0r, b2r, a1rL, aa1rL) << endl;

	cout << "hello" << endl;
	return 0;
}

