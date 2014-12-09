#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define PROTOCOL_ARDUINO

#if defined(PROTOCOL_PC)
#include <inttypes.h>
#endif
#include <inttypes.h>

//namespace NTUOSS { namespace TgifHacks {

typedef void (*EntryGetCharCallback)(const char c);
typedef void (*EntryGetChar)(EntryGetCharCallback GetCharCallback);
typedef void (*EntryPutChar)(const char c);

#if defined(PROTOCOL_ARDUINO)
typedef void (*OnMessageReceived)(const char *carr, const uint16_t length);
#elif defined(PROTOCOL_PC)
typedef void (*OnMessageReceived)(const uint16_t pos);
#else
#error Protocol cannot be compiled under this environment.
#endif 

class Protocol
{
public:
    static void Init(EntryGetChar GetChar, EntryPutChar PutChar, OnMessageReceived MessageReceived);

public:
#if defined(PROTOCOL_ARDUINO)
    static void Send(const uint16_t pos);
#elif defined(PROTOCOL_PC)
    static void Send(const char *carr, const uint16_t length);
#else
#error Protocol cannot be compiled under this environment.
#endif

private:
    static void _GetCharCallback(const char c);

    static EntryGetChar _GetChar;
    static EntryPutChar _PutChar;
    static OnMessageReceived _MessageReceived;
    static const char _MagicNumber = 0x1;

    static char *buff;
    static int buffoffset;
    static bool recv;

#if defined(PROTOCOL_ARDUINO)
    static uint16_t targetsize;
    static int targetstage;
#endif
};

//} }

#endif // _PROTOCOL_H_
