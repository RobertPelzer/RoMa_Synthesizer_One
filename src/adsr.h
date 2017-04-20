#ifndef adsr_h
#define adsr_h

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

        output = output + output * attack_time;
        oldState = state;
        if (output >= 0.99) {
            output = 1.0;
            state = decay;
        }
    } else if (state == decay) {
        output = output * decay_time;
        oldState = state;
        if (output <= sustain_level) {
            state = sustain;
        }
    } else if (state == sustain) {
        output = sustain_level;
    } else if (state == release) {
        output = output * release_time;
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