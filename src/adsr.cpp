#include "adsr.h"

/* constructor
 */
ADSR::ADSR(void) {
    reset();
}

/* set the state of the adsr
 */
void ADSR::gate(int gate) {
    if (gate == 0)
        state = note_off;
    else if (gate == 1)
        state = attack;
    else if (gate == 2)
        state = decay;
    else if (gate == 3)
        state = sustain;
    else if (gate == 4)
        state = release;
}

/* get the current state of the adsr
 */
int ADSR::getState() {
    return this->state;
}

/* reset the adsr with preset values for the envelope
 */
void ADSR::reset() {
    state = note_off;
    output = 0.0;

    attack_time = 1.0;
    decay_time = 1.0;
    sustain_level = 99;
    release_time = 1.0;
}

/* returns the output
 */
float ADSR::getOutput() {
    return output;
}

/* set the attack_time value
 * with an input range from 1 to 99
 */
void ADSR::setAttackTime(float t) {
    attack_time = t;
}

/* set the decay_time value
 * with an input range from 1 to 99
 */
void ADSR::setDecayTime(float t) {
    decay_time = t;
}

/* set the release_time value
 * with an input range from 1 to 99
 */
void ADSR::setReleaseTime(float t) {
    release_time = t;
}

/* set the sustain_level value
 * with an input range from 1 to 99
 */
void ADSR::setSustainLevel(float level) {
    sustain_level = level;
}