#ifndef DEMOFILE_H
#define DEMOFILE_H

#include <fstream>
#include <string>

#include <cstddef>

#if !defined(MAX_OSPATH)
#define MAX_OSPATH 260 // max length of a filesystem pathname
#endif

#define DEMO_HEADER_ID "HL2DEMO"
#define DEMO_PROTOCOL 4

struct demoheader_t {
    char demofilestamp[8]; // Should be HL2DEMO
    int32_t demoprotocol; // Should be DEMO_PROTOCOL
    int32_t networkprotocol; // Network protocol
    char servername[MAX_OSPATH]; // Name of server
    char clientname[MAX_OSPATH]; // Name of client who recorded the game
    char mapname[MAX_OSPATH]; // Name of map
    char gamedirectory[MAX_OSPATH]; // Name of game directory (com_gamedir)
    float playback_time; // Time of track
    int32_t playback_ticks; // # of ticks in track
    int32_t playback_frames; // # of frames in track
    int32_t signonlength; // length of sigondata in bytes
};

class Demofile {
public:
    Demofile(std::string fn);
    ~Demofile();
    void print_game_details();

private:
    void read_header();
    void check_header();

private:
    std::string filename;
    std::ifstream fileHandle;
    demoheader_t header;
    std::string file_cont;
};

#endif // DEMOFILE_H
