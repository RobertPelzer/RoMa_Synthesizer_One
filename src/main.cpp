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
#include <vector>
#include <algorithm>

#include "sawtoothwave.h"
#include "sinusoid.h"
#include "midiman.h"

using namespace std;
int midi_buffer;

    //vector<Sawtoothwave*> Oszi;
    Sawtoothwave ** oszi=new  Sawtoothwave *[5];
    vector<int> Noten= {-1, -1, -1, -1, -1} ;
    //vector<int> freeOszi={9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    vector<int> freeOszi={ 4, 3, 2, 1, 0};
    vector<double> timetracker={ -1, -1, -1, -1, -1};
    
    //maximale Anzahl der Oszillator
    int maxAnzahl_Oszi=Noten.size();

        
class SimpleSaw: public JackCpp::AudioIO {

private:
// hier muss eine allgemeine Oszillatorklasse her, indem die verschiedenen Typen aufgerufen werden
// die zehn Instanzen sind fuer das polyphone Spielen





public:
    MidiMan *midiMan;
    /// Audio Callback Function:
    /// - the output buffers are filled here
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs){


        
        /// LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {

            for(int frameCNT = 0; frameCNT  < nframes; frameCNT++)
            {

                outBufs[0][frameCNT] = (oszi[0]->getNextSample() +oszi[1]->getNextSample()+oszi[2]->getNextSample() +oszi[3]->getNextSample() +oszi[4]->getNextSample() )*0.3; /*+oszi[5]->getNextSample() +oszi[6]->getNextSample() +oszi[7]->getNextSample() +oszi[8]->getNextSample() +oszi[9]->getNextSample())*0.3 ;*/
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
        
        oszi[0]        = new Sawtoothwave(f1,a,1,44100,2);
        oszi[1]        = new Sawtoothwave(f1,a,1,44100,2);
        oszi[2]        = new Sawtoothwave(f1,a,1,44100,2);
        oszi[3]        = new Sawtoothwave(f1,a,1,44100,2);
        oszi[4]        = new Sawtoothwave(f1,a,1,44100,2); // bei mehr als 5 Oszis entstehen Artefakte
        /*oszi[5]        = new Sawtoothwave(f1,a,1,44100,2);
        oszi[6]        = new Sawtoothwave(f1,a,1,44100,2);
        oszi[7]        = new Sawtoothwave(f1,a,1,44100,2);
        oszi[8]        = new Sawtoothwave(f1,a,1,44100,2);
        oszi[9]        = new Sawtoothwave(f1,a,1,44100,2);*/
        


    }

};

///
///
///
int main(int argc, char *argv[]){


    double f1 = 400.0;
	  double a = 0;
	  double t_tracking=0; //Zeit Counter
	  int counter=0; //counter fue die Anzahl benutzer Oszillatoren
    /// initial ports from constructor created here.
    
    
    SimpleSaw * t = new SimpleSaw(f1, a);

     /// allocate a new midi manager
    MidiMan *midiMan = new MidiMan();

    /// activate the client
    t->start();

    /// connect sine ports to stereo ports
    t->connectToPhysical(0,0);		// connects this client out port 0 to physical destination port 0
    t->connectToPhysical(0,1);		// connects this client out port 1 to physical destination port 1

    ///print names
    cout << "outport names:" << endl;
    for(unsigned int i = 0; i < t->outPorts(); i++)
        cout << "\t" << t->getOutputPortName(i) << endl;

    /// flush all messages
    midiMan->flushProcessedMessages();
    
    
    /// run for EVER

    
    while(1) {

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
       double delta_time=Info.stamp; // get time information
      
       t_tracking=t_tracking+delta_time; //akkumuliere Zeit
       
       //int n   = midiMan->getNumFaderMessages();
       int oszi_nummer=0;
       int position=0;
       
        
       // Prezedur bei Note-On
        if(val1==144)
            {
             //wenn alle Oszillatoren benutzte werden, kill oldest
            if(counter==5){
              
              int min=timetracker[0];
              int index=0;
              //finde den aeltesten Wert == kleinste Zeit
              for(int i=1; i<timetracker.size(); i++) {
              
                if(timetracker[i]<min) {
                 min=timetracker[i];
                 index=i;
                 }
              }
                   //kill oldest Oszi und 
                   oszi[index]->amplitude(0);
                  //value im Notenarray loeschen
                  Noten[index]= -1;
                  //freigewordenen Oszi zurueckgeben
                  freeOszi.push_back(index);
                  
                    //Zeitinstanz löschen
                   timetracker[index]= -1;
                   
                   counter--;
               }
              //Berechnung der Frequnenz aus der Midi Note
              double f0 = std::pow(double (2), (val2-double(69))/double(12))*440;
              
              //freien Oszi finden
              oszi_nummer= freeOszi.back();
              //std::cout << oszi_nummer<<" benutzt"<<endl;
              
              //verwendeten Oszi loeschen
              freeOszi.pop_back();
              //std::cout << freeOszi.back()<<" ware der nachste"<<endl;
              oszi[oszi_nummer]->frequency(f0);
              
             
              //Amplitude aus der Midi-Info uebergeben 
              oszi[oszi_nummer]->amplitude(val3/126);
              
             //Notenwert zwischenspeichern
              Noten[oszi_nummer]=val2;
              
              //Zeit zwischenspeichern
              timetracker[oszi_nummer]=t_tracking;
              
              counter++;
           }
            
        //Note off bei Note off Befehl (128)
        if(val1==128 ) {

           //finde Oszillator
           //std::cout << val2<<" Ton aus"<<endl;
            position = find(Noten.begin(), Noten.end(), val2) - Noten.begin();
            
            //Sicherheitsabfrage - wenn bei find nichts gefunden wird, wird hinter das letzte gezeigt und des kommt zu stackdump
            if(position<maxAnzahl_Oszi) {
              //std::cout<<" Das ist Oszi" << position<<endl;
              oszi[position]->amplitude(0);
              
              //value im Notenarray loeschen
              Noten[position]= -1;
              //freigewordenen Oszi zurueckgeben
              freeOszi.push_back(position);
              
                //Zeitinstanz löschen
               timetracker[position]= -1;
               
               counter--;
              }   
            }
            
         //Kontrollsausgabe
        if (val1>=0) {
         std::cout << "Frei: "<<freeOszi.size()<<" Zeit: "<<t_tracking<<"Counter: "<<counter<<endl;
       }

    }

    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
    
    cout<<"ende"<<endl;
}

