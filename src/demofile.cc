#include <cstring>
#include <fstream>
#include <iostream>

#include "demofile.h"
#include "protobuffs/netmessages_public.pb.h"

Demofile::Demofile(std::string fn)
    : filename(fn)
{
    fileHandle
        = std::ifstream(filename, std::ios_base::in | std::ios_base::binary);

    if (!fileHandle.is_open()) {
        std::string errmsg = "unable to open file: '" + filename + "'";
        throw std::ios_base::failure(errmsg);
    }

    read_header();

    DemoData *demo_blob = read_next_blob();
    while (demo_blob->cmd != DEMO_STOP) {
        std::cerr << "CMD TYPE: " << (int32_t)demo_blob->cmd << std::endl;
        std::cerr << "CMD TICK: " << demo_blob->tick << std::endl;

        delete demo_blob->blob;
        delete demo_blob;

        demo_blob = read_next_blob();
    }

    delete demo_blob->blob;
    delete demo_blob;
}

Demofile::~Demofile(void) { fileHandle.close(); }

void Demofile::read_header(void)
{
    fileHandle.read((char *)&header, sizeof(demoheader_t));
    if (!fileHandle) {
        throw std::ios_base::failure("unable to read header");
    }
    check_header();
}

void Demofile::check_header(void)
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

void Demofile::read_cmd_header(DemoData *d)
{
    fileHandle.read((char *)&d->cmd, sizeof(unsigned char));
    if (d->cmd <= 0) {
        throw std::runtime_error("No end tag in demo file");
    }

    if (d->cmd > DEMO_LASTCMD) {
        throw std::runtime_error("Unknown command in demo file");
    }

    fileHandle.read((char *)&d->tick, sizeof(int32_t));
    fileHandle.read((char *)&d->playerSlot, sizeof(unsigned char));

    if (!fileHandle) {
        throw std::runtime_error("Couldn't read CMD header successfully");
    }
}

void Demofile::read_cmd_info(democmdinfo_t &info)
{
    fileHandle.read((char *)&info, sizeof(democmdinfo_t));

    if (!fileHandle) {
        throw std::runtime_error("Couldn't read CMD info successfully");
    }
}

void Demofile::read_blob(DemoData *cmd, bool skip)
{
    /* FIXME: if skip set, only use fseek to jump over a blob */
    fileHandle.read((char *)&cmd->blob_size, sizeof(int32_t));

    /* FIXME: take care of possible exceptions */
    cmd->blob = new char[cmd->blob_size];

    fileHandle.read(cmd->blob, cmd->blob_size);
    if (!fileHandle) {
        std::string reason;
        if (fileHandle.eofbit)
            reason = "reached eof";
        else if (fileHandle.badbit)
            reason = "memory shortage of ifstream except";
        else if (fileHandle.failbit)
            reason = "total crap";
        throw std::runtime_error(
            std::string("Couldn't read a blob successfully: ") + reason);
    }
}

DemoData *Demofile::read_next_blob(void)
{
    DemoData *blob = new DemoData;
    blob->blob = NULL;

    read_cmd_header(blob);

    switch (blob->cmd) {
    case DEMO_SYNCTICK:
    case DEMO_STOP:
        break;

    case DEMO_CONSOLECMD:
        read_blob(blob);
        break;

    case DEMO_DATATABLES:
        read_blob(blob);
        break;

    case DEMO_STRINGTABLES:
        read_blob(blob);
        break;

    case DEMO_USERCMD:
        int32_t dummy; // FIXME: use fseek later to skip dummy data
        fileHandle.read((char *)&dummy, sizeof(int32_t));
        read_blob(blob);
        break;

    case DEMO_SIGNON:
    case DEMO_PACKET: {
        int32_t dummy_seq;
        democmdinfo_t demoinfo;
        read_cmd_info(demoinfo);

        // TODO: read sequence function
        fileHandle.read((char *)&dummy_seq, sizeof(int32_t));
        fileHandle.read((char *)&dummy_seq, sizeof(int32_t));

        read_blob(blob);
    } break;

    default:
        break;
    }

    return blob;
}

void Demofile::print_game_details(void)
{
    std::cout << "ID: " << header.demofilestamp
              << "; PROTOCOL: " << header.demoprotocol << std::endl
              << "========================" << std::endl
              << "Server name:       " << header.servername << std::endl
              << "Client name:       " << header.clientname << std::endl
              << "Map name:          " << header.mapname << std::endl
              << "Game lenght (min): " << header.playback_time / 60 << std::endl
              << "------------------------" << std::endl
              << "networkprotocol:   " << header.networkprotocol << std::endl
              << "gamedirectory:     " << header.gamedirectory << std::endl
              << "playback_ticks:    " << header.playback_ticks << std::endl
              << "playback_frames:   " << header.playback_frames << std::endl
              << "signonlength:      " << header.signonlength << std::endl;
}
