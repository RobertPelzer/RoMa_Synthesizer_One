/**
 * \struct noteMessage
 *
 *
 * \brief Structure for holding Note (on,off) messages.
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2005/04/14 14:16:20 $
 *
 * Contact: von_coler@intelligent-noise-solutions.de
 *
 *
 */

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
	bool hasBeenProcessed;

};

#endif // DATATYPES_H
