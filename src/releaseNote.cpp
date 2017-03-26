#include "releaseNote.h"
#include <math.h>


releaseNote::releaseNote(void) {
    reset();
}

releaseNote::~releaseNote(void) {
}


void releaseNote::gate(int gate) {
    if (gate == 0)
        state = note_off;
    else if (gate == 1)
        state = note_on;
    else if (gate == 2)
        state = note_release;
}

int releaseNote::getState() {
    return this->state;
}

void releaseNote::reset() {
    state = note_off;
    output = 0.0;
}

float releaseNote::getOutput() {
    return output;
}