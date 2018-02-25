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

#define DEMO_RECORD_BUFFER_SIZE                                                \
    (2 * 1024 * 1024) // temp buffer big enough to fit both string tables and
                      // server classes
#define NET_MAX_PAYLOAD (262144 - 4) // largest message we can send in bytes

#define FDEMO_NORMAL 0
#define FDEMO_USE_ORIGIN2 (1 << 0)
#define FDEMO_USE_ANGLES2 (1 << 1)
#define FDEMO_NOINTERP (1 << 2) // don't interpolate between this an last view

#define MAX_SPLITSCREEN_CLIENTS 2

// Demo messages
enum {
    // it's a startup message, process as fast as possible
    DEMO_SIGNON = 1,
    // it's a normal network packet that we stored off
    DEMO_PACKET,
    // sync client clock to demo tick
    DEMO_SYNCTICK,
    // console command
    DEMO_CONSOLECMD,
    // user input command
    DEMO_USERCMD,
    // network data tables
    DEMO_DATATABLES,
    // end of time.
    DEMO_STOP,
    // a blob of binary data understood by a callback function
    DEMO_CUSTOMDATA,

    DEMO_STRINGTABLES,

    // Last command
    DEMO_LASTCMD = DEMO_STRINGTABLES
};

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

struct QAngle {
    float x, y, z;
    void Init(void) { x = y = z = 0.0f; }
    void Init(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

struct Vector {
    float x, y, z;
    void Init(void) { x = y = z = 0.0f; }
    void Init(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

struct democmdinfo_t {
    democmdinfo_t(void) {}

    struct Split_t {
        int32_t flags;

        // original origin/viewangles
        Vector viewOrigin;
        QAngle viewAngles;
        QAngle localViewAngles;

        // Resampled origin/viewangles
        Vector viewOrigin2;
        QAngle viewAngles2;
        QAngle localViewAngles2;

        Split_t(void)
        {
            flags = FDEMO_NORMAL;
            viewOrigin.Init();
            viewAngles.Init();
            localViewAngles.Init();

            // Resampled origin/angles
            viewOrigin2.Init();
            viewAngles2.Init();
            localViewAngles2.Init();
        }

        Split_t &operator=(const Split_t &src)
        {
            if (this == &src)
                return *this;

            flags = src.flags;
            viewOrigin = src.viewOrigin;
            viewAngles = src.viewAngles;
            localViewAngles = src.localViewAngles;
            viewOrigin2 = src.viewOrigin2;
            viewAngles2 = src.viewAngles2;
            localViewAngles2 = src.localViewAngles2;

            return *this;
        }

        const Vector &GetViewOrigin(void)
        {
            if (flags & FDEMO_USE_ORIGIN2) {
                return viewOrigin2;
            }
            return viewOrigin;
        }

        const QAngle &GetViewAngles(void)
        {
            if (flags & FDEMO_USE_ANGLES2) {
                return viewAngles2;
            }
            return viewAngles;
        }
        const QAngle &GetLocalViewAngles(void)
        {
            if (flags & FDEMO_USE_ANGLES2) {
                return localViewAngles2;
            }
            return localViewAngles;
        }

        void Reset(void)
        {
            flags = 0;
            viewOrigin2 = viewOrigin;
            viewAngles2 = viewAngles;
            localViewAngles2 = localViewAngles;
        }
    };

    void Reset(void)
    {
        for (int i = 0; i < MAX_SPLITSCREEN_CLIENTS; ++i) {
            u[i].Reset();
        }
    }

    Split_t u[MAX_SPLITSCREEN_CLIENTS];
};

struct DemoData {
    int32_t tick;
    unsigned char cmd;
    unsigned char playerSlot;

    int32_t blob_size;
    char *blob;
};

class Demofile {
public:
    Demofile(std::string fn);
    ~Demofile(void);
    void print_game_details(void);

private:
    void read_header(void);
    void read_cmd_header(DemoData *);
    void read_cmd_info(democmdinfo_t &);
    void read_blob(DemoData *cmd, bool skip = false);
    DemoData *read_next_blob(void);
    void check_header(void);

private:
    std::string filename;
    std::ifstream fileHandle;
    demoheader_t header;
    std::string file_cont;
};

#endif // DEMOFILE_H
