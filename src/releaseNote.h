#ifndef releaseNote_h
#define releaseNote_h

class releaseNote {
private:
    int state;
    float output;
    
public:
	releaseNote(void);
	~releaseNote(void);
	float process(void);
    float getOutput(void);
	void gate(int on);
    void reset(void);
    int getState(void);

    enum noteState {
        note_off = 0,
        note_on = 1,
        note_release = 2
    };
};

inline float releaseNote::process() {

    if(state == note_release) {
        output = output * 0.99;
        if (output <= 0.001) {
            output = 0.0;
            state = note_off;
        }
    } else if(state == note_on) {
        if (output == 0.0)
            output = 0.001;

        output = output + output * 0.01;
        if (output >= 0.99) {
            output = 1.0;
        }
    } else {
        output = 0.0;
        state = note_off;
    }

    return output;
}

#endif