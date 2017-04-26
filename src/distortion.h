//
//  distortion.h


#ifndef distortion_h
#define distortion_h

#include <iostream>
#include <cmath>

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
    
	//Distortion Schetzen Formula
    out=(out/abs(out))*(1-exp(gain*out*out/abs(out)));   
    

    return out;
}

#endif // distortion_h
