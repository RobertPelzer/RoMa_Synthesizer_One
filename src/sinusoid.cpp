#include "sinusoid.h"

Sinusoid::Sinusoid(double f, double a, double p,  int fS) {
    freq    = f;
    amp     = a;
    phi     = p;
    fs      = fS;
    curr_ampl = 0.0;
    midiNoteOff = false;
}

double Sinusoid::getNextSample() {

    /// This method gets the next sample of the sinusoid.
    /// The amplitude is applied and the angle of the
    /// sinusoid is increased, according to the sample rate.

    // get sinusoidal value
    double thisVal = sin(phi);

    // apply amplitude
    thisVal = thisVal*amp;

    // rotate to next step
    phi += 2.0*M_PI * freq * (1.0/fs);

    // wrap to 2 pi
    if(phi>=2*M_PI)
        phi=0;

    curr_ampl = thisVal;

    return thisVal;

}


double Sinusoid::frequency() {
    return freq;
}

double Sinusoid::amplitude() {
    return amp;
}

double Sinusoid::phase() {
    return phi;
}

void Sinusoid::frequency(double f) {
    freq = f;
}

void Sinusoid::amplitude(double a) {
    amp = a;
}

void Sinusoid::phase(double p) {
    phi = p;
}

double Sinusoid::getCurrentAmpl() {
<<<<<<< HEAD
    return curr_ampl;
=======
return curr_ampl;
>>>>>>> biquad_lfo
}