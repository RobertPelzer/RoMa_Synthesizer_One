#include "oscicontainer.h"

Oscicontainer::Oscicontainer(uint32_t fs) {
 	osciSine = new Sinusoid(440,0.0,0,fs);
	osciSaw = new Sawtoothwave(440,0.0,0,fs);
	osciSquare = new Squarewave(440,0.0,0,fs);
	osciNoise = new Noise(0.0);
	this->isLFO = false;

	// create release Note Object
	relNote = new releaseNote();

  envelope = new ADSR();
  ADSRStatus = false;

 	osciSineAmpl = 0.0;
	osciSawAmpl = 0.0;
	osciSquareAmpl = 0.0;
	osciNoiseAmpl = 0.0;

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
    thisVal = osciSine->getNextSample();
    thisVal = thisVal + osciSaw->getNextSample();
    thisVal = thisVal + osciSquare->getNextSample();
    thisVal = thisVal + osciNoise->getNextSample();
    if (this->ADSRStatus) {
      thisVal = thisVal * envelope->process();
    } else {
      thisVal = thisVal * relNote->process();
    }
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

/*double Oscicontainer::getCurrentAmpl() {
	return 	osciSine->getCurrentAmpl() +
			osciSaw->getCurrentAmpl() +
			osciSquare->getCurrentAmpl() + 
			osciNoise->getCurrentAmpl();
}*/

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

void Oscicontainer::phase(double phi) {
	osciSaw->phase(phi);
	osciSquare->phase(phi);
	osciSine->phase(phi);
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


void Oscicontainer::setReleaseNoteState(int status) {
	relNote->gate(status);
}

void Oscicontainer::setADSRState(int status) {
  envelope->gate(status);
}

void Oscicontainer::setADSRStatus(bool status) {
  this->ADSRStatus = status;
}

/*
float Oscicontainer::releaseNoteProcess() {
	return relNote->process();
}*/

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

void Oscicontainer::setADSRAttackTime(float t) {
  envelope->setAttackTime(t);
}

void Oscicontainer::setADSRDecayTime(float t) {
  envelope->setDecayTime(t);
}

void Oscicontainer::setADSRSustainLevel(float level) {
  envelope->setSustainLevel(level);
}

void Oscicontainer::setADSRReleaseTime(float t) {
  envelope->setReleaseTime(t);
}