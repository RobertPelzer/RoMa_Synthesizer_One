#ifndef SAWTOOTHWAVE_H
#define SAWTOOTHWAVE_H

#define _USE_MATH_DEFINES

#include<vector>
#include<cmath>

class Sawtoothwave {
private:

    // PURE SAWTOOTH STATE
    double freq;
    double amp;
    double phi;
	int harm;		// number of harmonics

    // SYSTEM RELATED
    int nframes;
    int fs;

    double *t;


public:
    Sawtoothwave(double f, double a, double p, int fS, int harm);
    void proceed(double ms);

    /// getters
    double frequency();
    double amplitude();
    double phase();
	int harmonics();
    /// setters (override)
    void frequency(double f);
    void amplitude(double a);
    void phase(double p);
	void harmonics(int N);

    double getNextSample();

};

#endif // SQUAREWAVE_H
