#include "sawtoothwave.h"

Sawtoothwave::Sawtoothwave(double f, double a, double p,  int fS, int N) {
    freq    = f;
    amp     = a;
    phi     = p;
    fs      = fS;
	harm	= N;
}

double Sawtoothwave::getNextSample() {

    /// This method gets the next sample of the Sawtoothwave.
    /// The amplitude is applied and the angle of the
    /// Sawtoothwave is increased, according to the sample rate.

    // get Sawtoothwave value
	double thisVal = 0.0;
	for (int i = 1; i < harm+1; i++) {
		thisVal = thisVal + (pow(-1,i)*sin(phi*i)/i);
	}

    // apply amplitude
    thisVal = amp/2 - amp/2*thisVal;

    // rotate to next step
    phi += 2.0*M_PI * freq * (1.0/fs);

    // wrap to 2 pi
    if(phi>=2*M_PI)
        phi=0;

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

int Sawtoothwave::harmonics() {
	return harm;
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
void Sawtoothwave::harmonics(int N) {
	harm = N;
}
