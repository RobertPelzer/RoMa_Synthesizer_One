#include "oscicontainer.h"

Oscicontainer::Oscicontainer() {
  osciSine = new Sinusoid(440,0.0,0,48000);
	osciSaw = new Sawtoothwave(440,0.0,0,48000);
	osciSquare = new Squarewave(440,0.0,0,48000);
	osciNoise = new Noise(0.0);
	this->isLFO = false;

 osciSineAmpl = 1.0;
	osciSawAmpl = 1.0;
	osciSquareAmpl = 1.0;
	osciNoiseAmpl = 0.3;
}
//LFO Constructor: type and frequency selectable. Type 0 (and any other non-defined): Sinus, Type 1: Saw, Type 2: Square
Oscicontainer::Oscicontainer(int type, double f) {
 
  lfoSaw= new Sawtoothwave(f,1,0,48000);
  lfoSquare= new Squarewave(f,1,0,48000);
  lfoSin = new Sinusoid(f,1,0,48000);
  
   if(type ==1) {
     lfoSaw->amplitude(1);
     lfoSquare->amplitude(0);
     lfoSin->amplitude(0);
   }
  else if (type ==2) {
     lfoSaw->amplitude(0);
     lfoSquare->amplitude(1);
     lfoSin->amplitude(0);
     }
  else {
     lfoSaw->amplitude(0);
     lfoSquare->amplitude(0);
     lfoSin->amplitude(1);
     }

  this->isLFO = true;
}



double Oscicontainer::getNextSample() {
double thisVal;

  if (this->isLFO==true) {
    if(this->type ==1) thisVal= lfoSaw->getNextSample();
    else if (this->type ==2) thisVal = lfoSquare->getNextSample();
    else thisVal= lfoSin->getNextSample();
   
	}
	else {
     thisVal = osciSaw->getNextSample();
    thisVal = thisVal + osciSquare->getNextSample();
    thisVal = thisVal + osciNoise->getNextSample();
    thisVal = thisVal + osciSine->getNextSample();
}
    return thisVal;

}

void Oscicontainer::amplitude(double a) {

 if (this->isLFO==true) {
    if(this->type ==1) {
     lfoSaw->amplitude(1);
     lfoSquare->amplitude(0);
     lfoSin->amplitude(0);
   }
  else if (this->type ==2) {
      lfoSaw->amplitude(0);
     lfoSquare->amplitude(1);
     lfoSin->amplitude(0);
     }
  else {
      lfoSaw->amplitude(0);
     lfoSquare->amplitude(0);
     lfoSin->amplitude(1);
     }
     }
     
   else {
	osciSaw->amplitude(osciSawAmpl*a);
	osciSquare->amplitude(osciSquareAmpl*a);
	osciNoise->amplitude(osciNoiseAmpl*a);
	osciSine->amplitude(osciSineAmpl*a);
	}
}

void Oscicontainer::frequency(double f) {
  if (this->isLFO==true) {
     if(this->type ==1) lfoSaw->frequency(f);
    else if (this->type ==2) lfoSquare->frequency(f);
    else lfoSin->frequency(f);
    }
  else {
    osciSaw->frequency(f);
    osciSquare->frequency(f);
    osciSine->frequency(f);
	}
}

void Oscicontainer::setSineAmpl(double a) {
	osciSineAmpl = a;
}
void Oscicontainer::setSawAmpl(double a) {
	osciSawAmpl = a;
}

void Oscicontainer::setSquareAmpl(double a) {
	osciSquareAmpl = a;
}

void Oscicontainer::setNoiseAmpl(double a) {
	osciNoiseAmpl = a;
}

void Oscicontainer::setLFOtype(int Type) {
	this->type = Type;
	Oscicontainer::amplitude(0);
}


double Oscicontainer::getCurrentAmpl() {
  if (this->isLFO==true) {
     if(this->type ==1) return lfoSaw->getCurrentAmpl();
    else if (this->type ==2) return lfoSquare->getCurrentAmpl();
    else return lfoSin->getCurrentAmpl();
    }
  else {
    return 0; // osciSaw->getCurrentAmpl() + osciSquare->getCurrentAmpl() + osciSine->getCurrentAmpl();
    
    
	}
}