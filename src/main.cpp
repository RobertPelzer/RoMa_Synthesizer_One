/**
 * \file
 *
 * \brief This is an example of creating a sawtoothwave.
 *
 *
 * \todo Use interpolation!
 *
 * \author
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/18$
 *
 * Contact: von_coler@tu-berlin.de
 *
 */



#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <jackaudioio.hpp>

#include "sawtoothwave.h"
#include "sinusoid.h"
#include "midiman.h"

using std::cout;
using std::endl;
int midi_buffer;


class SimpleSaw: public JackCpp::AudioIO {

private:

    Sawtoothwave *saw1;
    Sawtoothwave *saw2;
    MidiMan *midiMan;

public:
    /// Audio Callback Function:
    /// - the output buffers are filled here
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs){


        /// process midi messages
        
        // In RT Midi werden definierte Note On und Note off Werte ausgeggeben
        // val1 : 144 -> Note on, 128 -> Note off
        //val2 : Tonhöhe von 0 bis 127 - > Tonhöhe wird bei Note On und Note Off ausgegeben
        //val3 : Velocity - bei Note On wird Wert zwischen 0 un 126 ausgegeben, bei Note Off: 127
        
        midiMessage Info = midiMan->get_rtmidi();
       // int val = midiMan->get_rtmidi;
       int val1 = Info.byte1;
       int val2 = Info.byte2;
       double val3 = Info.byte3;
        int n   = midiMan->getNumFaderMessages();
        
        
        //Kontrollsausgabe
       // if (val1>=0) {
         //std::cout << midi_buffer<<endl;
       // }

          if(val1==144)
            {
              //Berechnung der Frequnenz aus der Midi Note
              double f0 = std::pow(double (2), (val2-double(69))/double(12))*440;
              
             //alte und ungenaue Berechnung - nicht mehr benutzen!//////
             //double f0 = std::pow((double) val2 / 126.0,4.0) * 10000.0; 
               //std::cout <<std::setprecision (4) <<f0<<std::endl;
               /// flush all messages
               
              midiMan->flushProcessedMessages();

              saw1->frequency(f0);
              saw2->frequency(440);
              //buffer zum Zwischenspeichern und Ausschalten des Tons
             midi_buffer=val2;
             
             //std::cout << "Val1 "<<val1<<" Val2 "<<val2<<" Val3 "<<val3<<" Midi"<<midi_buffer<<std::endl;
             
              //Amplitude aus der Midi-Info uebergeben 
              saw1->amplitude(val3/126);
              saw2->amplitude(val3/126);
              }
            
        //Note off bei Note off Befehl (128) und wenn dies den aktuell bespielen Ton betrifft  
        if(val1==128 && val2==midi_buffer) {
          saw1->amplitude(0);
          saw2->amplitude(0);
          }


        /// LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {

            for(int frameCNT = 0; frameCNT  < nframes; frameCNT++)
            {

                outBufs[0][frameCNT] = saw1->getNextSample() + saw2->getNextSample();
            }
        }

        ///return 0 on success
        return 0;
    }

    /// Constructor
    SimpleSaw(double f1, double a) :
        JackCpp::AudioIO("sawtoothwave_example", 0,1){

        reserveInPorts(2);
        reserveOutPorts(2);




        saw1        = new Sawtoothwave(f1,a,1,44100,2);
        saw2       = new Sawtoothwave(440,a,1,44100,2);

        /// allocate a new midi manager
        midiMan = new MidiMan();

    }

};

///
///
///
int main(int argc, char *argv[]){


    double f1 = 400.0;
	double a = 0;

    /// initial ports from constructor created here.
    SimpleSaw * t = new SimpleSaw(f1, a);



    /// activate the client
    t->start();

    /// connect sine ports to stereo ports
    t->connectToPhysical(0,0);		// connects this client out port 0 to physical destination port 0
    t->connectToPhysical(0,1);		// connects this client out port 1 to physical destination port 1

    ///print names
    cout << "outport names:" << endl;
    for(unsigned int i = 0; i < t->outPorts(); i++)
        cout << "\t" << t->getOutputPortName(i) << endl;

    /// run for EVER
    sleep(-1);

    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}

