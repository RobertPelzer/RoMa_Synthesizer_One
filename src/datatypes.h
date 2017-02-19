#ifndef DATATYPES_H
#define DATATYPES_H


struct noteMessage {
    int noteNumber;    /// @var noteNumber The note number
    double velocity;
    bool hasBeenProcessed;

};


struct ctlMessage{
    int ctlNumber;    /// @var noteNumber The note number
    double value;
    bool hasBeenProcessed;

};


struct midiMessage{
	int byte1;
	int byte2;
	double byte3;
	double stamp;
	bool hasBeenProcessed;

};

#endif // DATATYPES_H
