
//class Sawtoothwave



#include "sawtoothwave.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
Sawtoothwave::Sawtoothwave(double f, double a, double p,  int fS)
{
    freq    = f;
    amp     = a;
    phi     = p;
    fs      = fS;
}

double Sawtoothwave::getNextSample() {

    /// This method gets the next sample of the Sawtoothwave.
    /// The amplitude is applied and the angle of the
    /// Sawtoothwave is increased, according to the sample rate.


    double n=2.0*M_PI * freq * (1.0/fs);
    
    //double thisVal=amp*((phi-fs/freq*n)   -(long)(phi-fs/freq*n));
    double thisVal=phi;
    
    // apply amplitude
    thisVal = amp*(thisVal-M_PI)/M_PI;
    
     // rotate to next step
    phi += n;
    if (phi>=2.0*M_PI) phi=0;

    return thisVal;

}


double Sawtoothwave::frequency() {
    return freq;
}

double Sawtoothwave::amplitude() {
    return amp;
}

double Sawtoothwave::phase() {
    return phi;
}


void Sawtoothwave::frequency(double f) {
    freq = f;
}

void Sawtoothwave::amplitude(double a) {
    amp = a;
}

void Sawtoothwave::phase(double p) {
    phi = p;
}

