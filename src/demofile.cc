#include <cstring>
#include <fstream>
#include <iostream>

#include "demofile.h"
#include "utils.h"

Demofile::Demofile(std::string fn)
    : filename(fn)
{
    fileHandle
        = std::ifstream(filename, std::ios_base::in | std::ios_base::binary);

    if (!fileHandle.is_open()) {
        throw std::ios_base::failure("unable to open file");
    }

    read_header();
}

Demofile::~Demofile() { fileHandle.close(); }

void Demofile::read_header()
{
    fileHandle.read((char *)&header, sizeof(demoheader_t));
    if (!fileHandle) {
        throw std::ios_base::failure("unable to read header");
    }
    check_header();
}

void Demofile::check_header()
{
    if (strcmp(DEMO_HEADER_ID, header.demofilestamp)) {
        throw std::runtime_error(std::string("wrong demo header ID: ")
                                 + std::string(header.demofilestamp));
    }

    if (header.demoprotocol != DEMO_PROTOCOL) {
        throw std::runtime_error(std::string("wrong demo header protocol: ")
                                 + std::string(header.demofilestamp));
    }
}

void Demofile::print_game_details()
{

    std::cout << "ID: " << header.demofilestamp
              << "; PROTOCOL: " << header.demoprotocol << std::endl
              << "========================" << std::endl
              << "Server name:       " << header.servername << std::endl
              << "Client name:       " << header.clientname << std::endl
              << "Map name:          " << header.mapname << std::endl
              << "Game lenght (min): " << header.playback_time / 60
              << std::endl;
}
