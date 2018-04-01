#include <iostream>
#include <string>

#include "protobuffs/netmessages_public.pb.h"

#include "demofile.h"

const std::string HELP_STR = "Usage:\n"
                             "       ./csgoprs filename\n";

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << HELP_STR;
        return 1;
    }

    Demofile df(argv[1]);
    df.print_game_details();

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
