#include "oscman.h"
#include <fstream>
#include <string>
using namespace std;

/* Error handler
 */
void error(int num, const char *msg, const char *path) {
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
    fflush(stdout);
}

/* Constructor
 * initialize and start osc server thread
 */
OscMan::OscMan(int p) {

    // osc server thread object
	lo_server_thread st = lo_server_thread_new("50000", error);
    // Add the callback handler to the server!
	lo_server_thread_add_method(st, NULL, NULL, double_callback, this);
	// start server thread
    lo_server_thread_start(st);
    std::cout << "Started OSC Server!" << std::endl;
}

/* Callback Handler
 * process osc messages
 */
int OscMan::double_callback(const char *path, const char *types, lo_arg ** argv,
                            int argc, void *data, void *user_data ) {
    // Converts between types using a combination of implicit and user-defined conversions
    OscMan* statCast = static_cast<OscMan*>(user_data);

    // message double (float)
    if (std::string(types)=="f") {
    	dMess tmpD;
      	tmpD.type = types;
      	tmpD.path = path; 
      	tmpD.val = argv[0]->f;
      	statCast->dMessages.push_back(tmpD);
    // message integer
    } else if (std::string(types)=="i") {
        iMess tmp;
        tmp.type = types;
        tmp.path = path;
        tmp.val = argv[0]->i;
        statCast->iMessages.push_back(tmp);
    // message char
    }	else if (std::string(types)=="s") {
        sMess tmps;
        tmps.type = types;
        tmps.path = path;
        tmps.val = argv[0]->s;
        statCast->sMessages.push_back(tmps);         
    }

    // store all information
    statCast->paths.push_back(path);
    statCast->types.push_back(types);  
    //statCast->messages.push_back(argv[0]->f);
}

/* get last double value from double value vector
 */
double OscMan::getLastDouble() {
	if(dMessages.size()>0) {
	    dMess tmp = dMessages[0];
	    dMessages.clear();
		return tmp.val;
	} else
      	return 0.0;
}

/* get last integer value from integer value vector
 */
double OscMan::getLastInt() {
	iMess tmp = iMessages[0];
	iMessages.clear();
    return (double)tmp.val;
}

/* get last char value from char value vector
 */
double OscMan::getLastChar() { 
    if(sMessages.size()>0) {
        sMess tmp = sMessages[0];
        sMessages.clear();
        //ASCII recalculation
        return (double)tmp.val-48;
    } else
        return 0.0;
}

/* get last osc message path
 */
std::string OscMan::getLastPath() {
    if(paths.size()>0) {
        std::string s = paths[0];
        paths.clear();
        return s;
    } else
        return "No messages received!";
}

/* get last osc message type
 */
std::string OscMan::getLastType() {
    if(types.size()>0) {
        std::string s = types[0];
        types.clear();
        return s;
    } else
        return "empty";
}