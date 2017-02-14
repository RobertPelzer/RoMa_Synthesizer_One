#ifndef NOISE_H
#define NOISE_H

#define _USE_MATH_DEFINES

#include<vector>
#include<cmath>
#include <stdlib.h>     /* srand, rand */

class Noise {
public:
    Noise(double a);
    void proceed(double ms);

    /// getters
    double amplitude();
    /// setters (override)
    void amplitude(double a);

    double getNextSample();



private:

    // PURE SAWTOOTH STATE
    double amp;

    // SYSTEM RELATED
    int nframes;
    int fs;

    double *t;


};

#endif // NOISE_H
