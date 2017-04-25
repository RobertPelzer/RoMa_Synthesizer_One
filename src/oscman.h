#ifndef OSCMAN_H
#define OSCMAN_H

#include <lo/lo.h>
#include <iostream>
#include <vector>

#include "datatypes.h"

class OscMan {
private:

    // the port to be opened
    int port;

    lo_server_thread st;

    // for each OSC message we store its path, value and type
    // messages are only integers, at this point:
    std::vector<double> messages;
    std::vector<std::string> paths;
    std::vector<std::string> types;

    std::vector<dMess> dMessages;
    std::vector<iMess> iMessages;
    std::vector<sMess> sMessages;

    static int double_callback(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);

public:

    OscMan(int p);
    double getLastMessage();
    double getLastDouble();
    double getLastInt();
    double getLastChar();
    std::string getLastPath();
    std::string getLastType();
    int getNumberOfMessages();
    int getNumberOfdMess();

};

#endif
