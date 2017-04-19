//
//  distortion.cpp

#include "distortion.h"


Distortion::Distortion() {
    gain=0;

}

Distortion::Distortion(int gain) {
    setGain(gain);

}

Distortion::~Distortion() {
}


void Distortion::setGain(int gain) {
    this->gain = gain;
}

