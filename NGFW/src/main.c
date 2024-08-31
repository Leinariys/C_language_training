#include "utility/string_replacement.h"
#include "net/server.h"


extern char* input_ip;
extern int input_port;
extern char* output_ip;
extern int output_port;


int main(int argc, char* argv[])
{
    readServerParametersFromArguments(argc, argv, &input_ip, &input_port, &output_ip, &output_port);

    int result = initServer();

    return result;
}
