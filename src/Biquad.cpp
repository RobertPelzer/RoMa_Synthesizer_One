//
//  Biquad.cpp
//
//  Created by Nigel Redmon on 11/24/12
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the Biquad code:
//  http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code
//  for your own purposes, free or commercial.
////////////////////////////////////////////////////////////////////////

//  The Code was edited in certain areas by Robert Pelzer and Markus Wende
//  Where the Code was edited, comments were created

//The biquad filter class is the implementation of a digital biquad filter, 
// which is a second-order recursive linear filter, containing two poles and two zeros. 
// The source code was taken from the following website: http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
// Some changes were made to the filter to make it fit our needs. 
// The Biquad has seven different selectable filters (lowpass, high pass, band pass, notch, peak, low shelf, high shelf). 
// For each filter a set of formulas is implemented which calculate the filter coefficients. 
// The advantage of using this biquad filter is, that it is a pretty flexible solution, 
// however on the downside of is the fact that every little parameter change of the filter leads to a re-calculation of the coefficients. 
// Fortunately, this doesn´t create any processing problems.
// The lowpass, high pass, band pass and the peak filter respond to a Q value which determines bandwidth for the band pass filter, 
// a steepness for low and high pass filters and the width of the peak filter. The low shelf, high shelf and peak filter don´t respond to Q value, but to a peak Gain. 
// A high gain additionally led to distortion, which in some cases wwas very nice sounding. 
// However, we undid this rise of gain to be able to implement a general distortion class. 
// This had the effect that the peak gain didn´t increase the signals volume, but in praxis has a similar effect as Q for the other filters.



#include "Biquad.h"
#include <iostream> 
#include <unistd.h>

Biquad::Biquad() {
    type = bq_type_lowpass;//bq_type_lowpass;
    a0 = 1.0;
    a1 = a2 = b1 = b2 = 0.0;
    Fc = 0.50;
    Q = 0.707;
    peakGain = 0.0;
    z1 = z2 = 0.0;
}

Biquad::Biquad(int type, double Fc, double Q, double peakGainDB) {
    setBiquad(type, Fc, Q, peakGainDB);
    z1 = z2 = 0.0;
}

Biquad::~Biquad() {
}

void Biquad::setType(int type) {
    this->type = type;
    calcBiquad();

    //  reduce gain for peak, highshelf and lowshelf
    //  This leads to a reduction of the volume, however a high peakGain then works similar to the Q factor
    if(type==bq_type_peak || type==bq_type_lowshelf || type==bq_type_highshelf) setGainReduce(1); 
    else setGainReduce(0);
}

void Biquad::setQ(double Q) {
    this->Q = Q;
    calcBiquad();
}

void Biquad::setFc(double Fc) {
    this->Fc = Fc;
    calcBiquad();
}

void Biquad::status() {

    std::cout<<"Filter Type: "<<type<<std::endl;
}

void Biquad::setPeakGain(double peakGainDB) {
    this->peakGain = peakGainDB;
    calcBiquad();
}
    
void Biquad::setBiquad(int type, double Fc, double Q, double peakGainDB) {
    this->type = type;
    this->Q = Q;
    this->Fc = Fc;
    setPeakGain(peakGainDB);
}

// turn on the gain reduction for applicable filter types
void Biquad::setGainReduce(int on) {

    if (on==1) {
      gain_reduce=true;  
    }
    else gain_reduce=false;
}

void Biquad::calcBiquad(void) {
    double norm;
    double V = pow(10, fabs(peakGain) / 20.0);
    double K = tan(M_PI * Fc);
    switch (this->type) {
        case bq_type_lowpass:
            norm = 1 / (1 + K / Q + K * K);
            a0 = K * K * norm;
            a1 = 2 * a0;
            a2 = a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / Q + K * K) * norm;
            break;
            
        case bq_type_highpass:
            norm = 1 / (1 + K / Q + K * K);
            a0 = 1 * norm;
            a1 = -2 * a0;
            a2 = a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / Q + K * K) * norm;
            break;
            
        case bq_type_bandpass:
            norm = 1 / (1 + K / Q + K * K);
            a0 = K / Q * norm;
            a1 = 0;
            a2 = -a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / Q + K * K) * norm;
            break;
            
        case bq_type_notch:
            norm = 1 / (1 + K / Q + K * K);
            a0 = (1 + K * K) * norm;
            a1 = 2 * (K * K - 1) * norm;
            a2 = a0;
            b1 = a1;
            b2 = (1 - K / Q + K * K) * norm;
            break;
            
        case bq_type_peak:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + 1/Q * K + K * K);
                a0 = (1 + V/Q * K + K * K) * norm;
                a1 = 2 * (K * K - 1) * norm;
                a2 = (1 - V/Q * K + K * K) * norm;
                b1 = a1;
                b2 = (1 - 1/Q * K + K * K) * norm;
            }
            else {    // cut
                norm = 1 / (1 + V/Q * K + K * K);
                a0 = (1 + 1/Q * K + K * K) * norm;
                a1 = 2 * (K * K - 1) * norm;
                a2 = (1 - 1/Q * K + K * K) * norm;
                b1 = a1;
                b2 = (1 - V/Q * K + K * K) * norm;
            }
            break;
        case bq_type_lowshelf:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + sqrt(2) * K + K * K);
                a0 = (1 + sqrt(2*V) * K + V * K * K) * norm;
                a1 = 2 * (V * K * K - 1) * norm;
                a2 = (1 - sqrt(2*V) * K + V * K * K) * norm;
                b1 = 2 * (K * K - 1) * norm;
                b2 = (1 - sqrt(2) * K + K * K) * norm;
            }
            else {    // cut
                norm = 1 / (1 + sqrt(2*V) * K + V * K * K);
                a0 = (1 + sqrt(2) * K + K * K) * norm;
                a1 = 2 * (K * K - 1) * norm;
                a2 = (1 - sqrt(2) * K + K * K) * norm;
                b1 = 2 * (V * K * K - 1) * norm;
                b2 = (1 - sqrt(2*V) * K + V * K * K) * norm;
            }
            break;
        case bq_type_highshelf:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + sqrt(2) * K + K * K);
                a0 = (V + sqrt(2*V) * K + K * K) * norm;
                a1 = 2 * (K * K - V) * norm;
                a2 = (V - sqrt(2*V) * K + K * K) * norm;
                b1 = 2 * (K * K - 1) * norm;
                b2 = (1 - sqrt(2) * K + K * K) * norm;
            }
            else {    // cut
                norm = 1 / (V + sqrt(2*V) * K + K * K);
                a0 = (1 + sqrt(2) * K + K * K) * norm;
                a1 = 2 * (K * K - 1) * norm;
                a2 = (1 - sqrt(2) * K + K * K) * norm;
                b1 = 2 * (K * K - V) * norm;
                b2 = (V - sqrt(2*V) * K + K * K) * norm;
            }
            break;
    }
    usleep(500);
    return;
}
