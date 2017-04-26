////////////////////////////////////////////////////////////////////////

//  The Code was edited in certain areas by Robert Pelzer and Markus Wende

#ifndef MIDIMAN_H
#define MIDIMAN_H

#include "datatypes.h"
#include <rtmidi/RtMidi.h>
#include <unistd.h>

class MidiMan {
public:


    MidiMan();
    ~MidiMan();

    std::vector<std::string> returnAllNames();

    void updateMidiMessages(void *port_buf);
    void parseMidiMessages();

    void addNoteOnMessage(int in[3]);
    std::vector<noteMessage> getNoteOnMessages();
    void clearNoteOnMessages();

    void addNoteOffMessage(int in[3]);
    std::vector<noteMessage> getNoteOffMessages();
    void clearNoteOffMessages();

    void eraseNoteOnMessage(int position);

    void addFaderMessage(ctlMessage m);

    void markOnMessageProcessed(int pos);
    void markOffMessageProcessed(int pos);

    void flushProcessedMessages();

    ctlMessage getLastFaderMessage();

    int getNumFaderMessages();

    static void finish(int ignore);

    midiMessage get_rtmidi();

    void setVerbose();

private:
    // rtmidi
    static bool done;
    RtMidiIn *midiin;
    int nBytes, i;
    double stamp;
    bool isVerbose;

    std::vector<int>     val;


    noteMessage *tmpNote;

    void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData );

};

#endif // MIDIMAN_H
