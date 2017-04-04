//
//  distortion.h


#ifndef distortion_h
#define distortion_h

#include <iostream>
#include <math.h>

using namespace std;

class Distortion {
public:
    Distortion();
    Distortion(int gain);
    ~Distortion();

    void setGain(int gain);

    float process(float in);

    
protected:

    int gain;

};

inline float Distortion::process(float in) {
    float out = in;
    

    out=(out/abs(out))*(1-exp(gain*out*out/abs(out))); //Distortion Schetzen Formula  

    return out;
}

#endif // distortion_h