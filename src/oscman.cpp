#include "oscman.h"


///////////////////////////////////////////////////////////////////////
/// \brief Constructor
/// \param Port
/////////////////////////////////////////////////////////////////////////

void error(int num, const char *m, const char *path);

OscMan::OscMan(int p)
{

	//std::string port = string(p);


	lo_server_thread st = lo_server_thread_new("50000", error);

    /// Add the example handler to the server!
    lo_server_thread_add_method(st, NULL, NULL, generic_handler, NULL);

    
	lo_server_thread_start(st);

    std::cout << "Started Server!" << std::endl;
}


void error(int num, const char *msg, const char *path)
{
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
    fflush(stdout);
}

///////////////////////////////////////////////////////////////////////
/// \brief The callback function: 
///  On each incoming message, we push it into the vectors!
/// \param void
/// \return void
/////////////////////////////////////////////////////////////////////////
int OscMan::generic_handler(const char *path, const char *types, lo_arg ** argv,
		int argc, void *data, void *user_data)
{
	int i;
	
	printf("path: <%s>\n", path);
	for (i = 0; i < argc; i++) {
		printf("arg %d '%c' ", i, types[i]);
		lo_arg_pp((lo_type)types[i], argv[i]);
		printf("\n");
	}
	printf("\n");
	fflush(stdout);
	
	return 1;
}




int OscMan::double_callback(const char *path, const char *types, lo_arg ** argv,
                            int argc, void *data, void *user_data )
{



    /// Do a static cast
    // This is bad Style ...
    // better ways mightbe 'std::function' and 'std::bind
    OscMan* statCast = static_cast<OscMan*>(user_data);

    if (std::string(types)=="f")
    {


        std::cout << "GOT FLOAT" << std::endl;

        /// assemble the struct
        dMess tmpD;
        tmpD.type =types;
        tmpD.path =path;
        tmpD.val = argv[0]->f;


        statCast->dMessages.push_back(tmpD);
    }
    else if (std::string(types)=="i")
    {

        std::cout << "GOT INT" << std::endl;


        /// assemble the struct
        iMess tmp;
        tmp.type =types;
        tmp.path =path;
        tmp.val = argv[0]->i;


        statCast->iMessages.push_back(tmp);
    }
    /// store all information
    //statCast->paths.push_back(path);
    //statCast->types.push_back(types);
    //statCast->messages.push_back(argv[0]->f);

}


///////////////////////////////////////////////////////////////////////
/// \brief Example of use: Prints all collected messages and clears them.
/// \param void
/// \return void
/////////////////////////////////////////////////////////////////////////
void OscMan::printAllMessages()
{

    std::cout <<  "All Messages:   " << std::endl;

    int i = 0;
    for(std::vector<dMess>::iterator it = dMessages.begin(); it != dMessages.end(); ++it)
    {
        //std::cout << paths[i] << " of type "<< types[i] << ": " << messages[i] << std::endl;
        std::cout << dMessages[i].path << " of type "<< dMessages[i].type << ": " << dMessages[i].val << std::endl;
        i++;
    }

    i = 0;
    for(std::vector<iMess>::iterator it = iMessages.begin(); it != iMessages.end(); ++it)
    {
        //std::cout << paths[i] << " of type "<< types[i] << ": " << messages[i] << std::endl;
        std::cout << iMessages[i].path << " of type "<< iMessages[i].type << ": " << iMessages[i].val << std::endl;
        i++;
    }

    messages.clear();
    paths.clear();


    iMessages.clear();
    dMessages.clear();

}



///////////////////////////////////////////////////////////////////////
/// \brief Example of use:
/// \param void
/// \return void
/////////////////////////////////////////////////////////////////////////
 dMess OscMan::getLast_dMess()
{

    dMess tmp = dMessages[0];

    //std::cout << paths[i] << " of type "<< types[i] << ": " << messages[i] << std::endl;
   // std::cout << dMessages[i].path << " of type "<< dMessages[i].type << ": " << dMessages[i].val << std::endl;

    dMessages.clear();

    return tmp;


}

///////////////////////////////////////////////////////////////////////
/// \brief Just return the path of the last message and delete the vector!
/// \param void
/// \return void
///////////////////////////////////////////////////////////////////////
std::string OscMan::getLastPath()
{

    if(messages.size()>0)
    {
        std::string s = paths[0];

        paths.clear();

        return s;
    }
    else
        return "No messages received!";
}


///////////////////////////////////////////////////////////////////////
/// \brief Just return the type of the last message and delete the vector!
/// \param void
/// \return void
///////////////////////////////////////////////////////////////////////
std::string OscMan::getLastType()
{

    if(types.size()>0)
    {

        std::string s = types[0];

        types.clear();

        return s;
    }
    else
        return "No messages received!";}



///////////////////////////////////////////////////////////////////////
/// \brief Works only for integers!
/// \param void
/// \return void
///////////////////////////////////////////////////////////////////////
double OscMan::getLastMessage()
{

    double d = messages[0];

    messages.clear();
    paths.clear();

    return d;
}


///////////////////////////////////////////////////////////////////////
/// \brief Return information on the number of buffered messages.
/// \param void
/// \return void
///////////////////////////////////////////////////////////////////////
int OscMan::getNumberOfMessages()
{
    return  messages.size();
}



int OscMan::getNumberOfdMess()
{
    return  dMessages.size();
}
