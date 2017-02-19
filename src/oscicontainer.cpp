#include "oscicontainer.h"

Oscicontainer::Oscicontainer() {
    osciSine = new Sinusoid(440,0.0,0,48000);
	osciSaw = new Sawtoothwave(440,0.0,0,48000,4);
	osciSquare = new Squarewave(440,0.0,0,48000);
	osciNoise = new Noise(0.0);

	osciSineAmpl = 0.0;
	osciSawAmpl = 0.0;
	osciSquareAmpl = 0.0;
	osciNoiseAmpl = 0.0;
}

double Oscicontainer::getNextSample() {

    double thisVal = osciSine->getNextSample();
	thisVal = thisVal + osciSaw->getNextSample();
	thisVal = thisVal + osciSquare->getNextSample();
	thisVal = thisVal + osciNoise->getNextSample();

    return thisVal;

}

void Oscicontainer::amplitude(double a) {
	osciSine->amplitude(osciSineAmpl*a);
	osciSaw->amplitude(osciSawAmpl*a);
	osciSquare->amplitude(osciSquareAmpl*a);
	osciNoise->amplitude(osciNoiseAmpl*a);
}

void Oscicontainer::frequency(double f) {
	osciSine->frequency(f);
	osciSaw->frequency(f);
	osciSquare->frequency(f);
}

void Oscicontainer::setSineAmpl(double a) {
	osciSineAmpl = a;
}

void Oscicontainer::setSawAmpl(double a) {
	osciSawAmpl = a;
}

void Oscicontainer::setSquareAmpl(double a) {
	osciSquareAmpl = a;
}

void Oscicontainer::setNoiseAmpl(double a) {
	osciNoiseAmpl = a;
}
