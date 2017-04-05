#include "adsr.h"
#include <math.h>


ADSR::ADSR(void) {
    reset();
}

ADSR::~ADSR(void) {
}


void ADSR::gate(int gate) {
    if (gate == 0)
        state = note_off;
    else if (gate == 1)
        state = attack;
    else if (gate == 4)
        state = release;
}

int ADSR::getState() {
    return this->state;
}

void ADSR::reset() {
    state = note_off;
    output = 0.0;

    attack_time = 0.05;
    decay_time = 0.999;
    sustain_level = 1.0;
    release_time = 0.999;
}

float ADSR::getOutput() {
    return output;
}

void ADSR::setAttackTime(float t) {
    attack_time = t;
}

void ADSR::setDecayTime(float t) {
    decay_time = t;
}

void ADSR::setReleaseTime(float t) {
    release_time = t;
}

void ADSR::setSustainLevel(float level) {
    sustain_level = level;
}