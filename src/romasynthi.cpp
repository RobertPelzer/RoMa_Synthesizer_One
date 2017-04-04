#include "romasynthi.h"
//#include <fstream>

RoMaSynthi::RoMaSynthi() : JackCpp::AudioIO("RoMaSynthi", 0,1) {
	reserveInPorts(2);
	reserveOutPorts(2);

	fs = getSampleRate();
	nframes = getBufferSize();

	std::cout << "fs: " << fs << " Hz";
	std::cout << " || buffer size: " << nframes << " samples" << endl;

	osci = new Oscicontainer *[7];

	osci[0] = new Oscicontainer(fs);
	osci[1] = new Oscicontainer(fs);
	osci[2] = new Oscicontainer(fs);
	osci[3] = new Oscicontainer(fs);
	osci[4] = new Oscicontainer(fs);
	osci[5] = new Oscicontainer(fs);
	osci[6] = new Oscicontainer(fs);

	osc = new OscMan(50000);
	midi = new MidiMan();
	//filter= new Biquad();
	filter= new Biquad(0, 0.3, 0.2, 1.0);
	lfo= new Oscicontainer(0, 1);
	distortion = new Distortion();

	midi->flushProcessedMessages();

	t_tracking = 0;
	counter = 0;


	//int midi_buffer;

	Noten = {-1, -1, -1, -1, -1, -1, -1} ;
	freeOsci = { 6, 5, 4, 3, 2, 1, 0};
	timetracker = { -1, -1, -1, -1, -1, -1, -1};
    
    //maximale Anzahl der Oszillator
	maxAnzahl_Osci = Noten.size();

	valOld = 0.0;
	typeOld = "";
	pathOld = "";
	bool distortion_on = false;

}



    /// Audio Callback Function:
    /// - the output buffers are filled here
int RoMaSynthi::audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs) {

        /// LOOP over all output buffers
    for(unsigned int i = 0; i < 1; i++) {

    	for(int frameCNT = 0; frameCNT  < nframes; frameCNT++) {
            
               
                
                outBufs[0][frameCNT] = (osci[0]->getNextSample() +
										osci[1]->getNextSample() + 
										osci[2]->getNextSample() +
										osci[3]->getNextSample() +
										osci[4]->getNextSample() +
										osci[5]->getNextSample() +
										osci[6]->getNextSample()) / 7;

				outBufs[0][frameCNT] = filter->process(outBufs[0][frameCNT]); //hand over to filter

				if(distortion_on) outBufs[0][frameCNT] = distortion->process(outBufs[0][frameCNT]); //hand over to distortion
		
				lfo->getNextSample();
		}
    }

        ///return 0 on success
         
    return 0;
}



void RoMaSynthi::midiHandler() {


      /// process midi messages
        
        // In RT Midi werden definierte Note On und Note off Werte ausgeggeben
        // val1 : 144 -> Note on, 128 -> Note off
        //val2 : Tonhöhe von 0 bis 127 - > Tonhöhe wird bei Note On und Note Off ausgegeben
        //val3 : Velocity - bei Note On wird Wert zwischen 0 un 126 ausgegeben, bei Note Off: 127
        
		midiMessage info = midi->get_rtmidi();
		// int val = midiMan->get_rtmidi;
		int val1 = info.byte1;
		int val2 = info.byte2;
		double val3 = info.byte3;
		double delta_time = info.stamp; // get time information
      
		t_tracking = t_tracking + delta_time; //akkumuliere Zeit
       
		//int n   = midiMan->getNumFaderMessages();
		int osci_nummer = 0;
		int position = 0;
		
		// Prezedur bei Note-On
        if(val1==144) {
             //wenn alle Oszillatoren benutzte werden, kill oldest
            if(counter==7) {
				int min = timetracker[0];
				int index = 0;
				//finde den aeltesten Wert == kleinste Zeit
				for(int i=1; i<timetracker.size(); i++) {
					if(timetracker[i]<min) {
						min = timetracker[i];
						index = i;
					}
				}
				//kill oldest Oszi und

				osci[index]->setReleaseNoteState(2);
				//osci[index]->amplitude(0);
				//value im Notenarray loeschen
				Noten[index] = -1;
				//freigewordenen Oszi zurueckgeben
				freeOsci.push_back(index);
				  
				//Zeitinstanz löschen
				timetracker[index] = -1;
				   
				counter--;
			}


			//Berechnung der Frequnenz aus der Midi Note
			double f0 = std::pow(double (2), (val2-double(69))/double(12))*440;
				  
			//freien Oszi finden
			osci_nummer = freeOsci.back();
			//std::cout << oszi_nummer<<" benutzt"<<endl;
				  
			//verwendeten Oszi loeschen
			freeOsci.pop_back();
			//std::cout << freeOszi.back()<<" ware der nachste"<<endl;
			osci[osci_nummer]->frequency(f0);
				  
				 
			//Amplitude aus der Midi-Info uebergeben 
			osci[osci_nummer]->setReleaseNoteState(1);
			osci[osci_nummer]->amplitude(val3/126);
			osci[osci_nummer]->phase(0);
				  
			//Notenwert zwischenspeichern
			Noten[osci_nummer] = val2;
				  
			//Zeit zwischenspeichern
			timetracker[osci_nummer] = t_tracking;
			

			// at some point, by MIDI perhaps, the envelope is gated "on"
			//env->gate(true);
				  
			counter++;
        }
            
        //Note off bei Note off Befehl (128)
        if(val1==128 ) {

           //finde Oszillator
           //std::cout << val2<<" Ton aus"<<endl;
            position = find(Noten.begin(), Noten.end(), val2) - Noten.begin();
            
            //Sicherheitsabfrage - wenn bei find nichts gefunden wird, wird hinter das letzte gezeigt und des kommt zu stackdump
            if(position<maxAnzahl_Osci) {
              	osci[position]->setReleaseNoteState(2);
              	//osci[position]->amplitude(0);
              
              	//value im Notenarray loeschen
              	Noten[position]= -1;
              	//freigewordenen Oszi zurueckgeben
              	freeOsci.push_back(position);
              
                //Zeitinstanz löschen
               	timetracker[position]= -1;
               
               	counter--;
              	}  
              // and some time later, it's gated "off"
			//env->gate(false); 
            }
            
         //Kontrollsausgabe
        if (val1>=0) {
         //std::cout << "Frei: " << freeOsci.size() << " Zeit: " << t_tracking << "Counter: " << counter << endl;
       }
}


void RoMaSynthi::oscHandler() {

  	double val;
	string type = osc->getLastType();
	
	if (type != "empty")
	{

	  	if (type== "f") val =  osc->getLastDouble();

	  	else if (type== "i") val =  osc->getLastInt();

	  	else if  (type== "s") val =  osc->getLastChar();

	  	string path = osc->getLastPath();

		typeOld = type;
		pathOld = path;
		valOld = val;
		cout<<val<<path<<"Type:"<<type<<endl;
		if (path.compare("/SineAmpl") == 0) {
			osci[0]->setSineAmpl(val);
			osci[1]->setSineAmpl(val);
			osci[2]->setSineAmpl(val);
			osci[3]->setSineAmpl(val);
			osci[4]->setSineAmpl(val);
			osci[5]->setSineAmpl(val);
			osci[6]->setSineAmpl(val);
			//cout << "OSC01 Ampl: " << val	<< endl;
		}
		
		if (path.compare("/SawAmpl") == 0) {
			//cout << "OSC02 Ampl: " << val	<< endl;
			osci[0]->setSawAmpl(val);
			osci[1]->setSawAmpl(val);
			osci[2]->setSawAmpl(val);
			osci[3]->setSawAmpl(val);
			osci[4]->setSawAmpl(val);
			osci[5]->setSawAmpl(val);
			osci[6]->setSawAmpl(val);
		}
		if (path.compare("/SquareAmpl") == 0) {
			//cout << "Harm: " << val << endl;
			osci[0]->setSquareAmpl(val);
			osci[1]->setSquareAmpl(val);
			osci[2]->setSquareAmpl(val);
			osci[3]->setSquareAmpl(val);
			osci[4]->setSquareAmpl(val);
			osci[5]->setSquareAmpl(val);
			osci[6]->setSquareAmpl(val);
		}
		if (path.compare("/NoiseAmpl") == 0) {
			//cout << "NoiseLevel: " << val << endl;
			osci[0]->setNoiseAmpl(val);
			osci[1]->setNoiseAmpl(val);
			osci[2]->setNoiseAmpl(val);
			osci[3]->setNoiseAmpl(val);
			osci[4]->setNoiseAmpl(val);
			osci[5]->setNoiseAmpl(val);
			osci[6]->setNoiseAmpl(val);
		}
		
	    if (path.compare("/LFO_Q") == 0) {
	      	filter->setQ(val);
		}
			
		if (path.compare("/Filter_Type") == 0) {
	      	filter->setType((int)val);
		}
			
		if (path.compare("/Filter_Gain") == 0) {
	      	filter->setPeakGain(val);
		}
			
		if (path.compare("/LFO_Freq") == 0) {
	    	lfo->frequency(val);
	    }

	    if (path.compare("/LFO_Type") == 0) {
	      	lfo->setLFOtype((int)val);
		}

		if (path.compare("/Distortion_Gain") == 0) {
	      	distortion->setGain((int)val);
		}

		if (path.compare("/Dist_On") == 0) {
	      	distortion_on=(int)val;
		}

	}
	
	
	usleep(500);
}


void RoMaSynthi::lfoHandler() {

	  //limits LFO Signal to 6- Bit 
	 double lfo_step = 0.0078125;

	 double lfo_value=((lfo->getCurrentAmpl()+1.0)/2)*0.5; //make value positiv, skaliere mit FC=0.5
	 if (lfo_value<0) lfo_value=0;//no negative values - dirty workaround in case amplitude is higher than 1

	 if (lfo_value > (lfo_oldValue + lfo_step) || lfo_value < (lfo_oldValue - lfo_step) ) {
      	//change Cutoff of Filter when lfo_value changes
     	filter->setFc(lfo_value);
      	lfo_oldValue=lfo_value;
      
	 }

}
  