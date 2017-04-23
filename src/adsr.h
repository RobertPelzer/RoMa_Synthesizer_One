#ifndef adsr_h
#define adsr_h

#include <math.h>

class ADSR {
private:
    int state;
    int oldState;
    float output;
    float attack_time;
    float decay_time;
    float sustain_level;
    float release_time;
    
public:
	ADSR(void);
	~ADSR(void);
	float process(void);
    float getOutput(void);
	void gate(int on);
    void reset(void);
    int getState(void);

    void setAttackTime(float t);
    void setDecayTime(float t);
    void setReleaseTime(float t);
    void setSustainLevel(float level);

    enum noteState {
        note_off = 0,
        attack = 1,
        decay = 2,
        sustain = 3,
        release = 4
    };
};

inline float ADSR::process() {

    if (state == attack) {
        if (output == 0.0)
            output = 0.001;
        if (oldState >= 2)
            output = 0.001;
        // multiplicator goes from 0.04 to 0.00002
        // with release_time from 1 to 99
        output = output + output * (1 - (exp(-log10((1.0 + 10) / 10 ) / attack_time) + 0.0004));
        oldState = state;
        if (output >= 0.99) {
            output = 1.0;
            state = decay;
        }
    } else if (state == decay) {
        // multiplicator goes from 0.99924 to 0.999992
        // with release_time from 1 to 99
        output = output * (0.99 + (exp(-log10((2.0 + 10) / 10 ) / decay_time) / 100));
        oldState = state;
        if (output <= sustain_level / 100) {
            state = sustain;
        }
    } else if (state == sustain) {
        // sustain goes from 1 to 99
        output = sustain_level / 100;
    } else if (state == release) {
        // multiplicator goes from 0.99924 to 0.999992
        // with release_time from 1 to 99
        output = output * (0.99 + (exp(-log10((2.0 + 10) / 10 ) / release_time) / 100));
        oldState = state;
        if (output <= 0.001) {
            output = 0.0;
            state = note_off;
        }
      
    } else {
        output = 0.0;
        state = note_off;
    }

    return output;
}

#endif