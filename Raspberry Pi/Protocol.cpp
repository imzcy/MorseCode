#include "Protocol.h"

using namespace NTUOSS::TgifHacks;

void Protocol::Init(EntryGetChar GetChar, EntryPutChar PutChar, OnMessageReceived MessageReceived)
{
    _GetChar = GetChar;
    _PutChar = PutChar;
    _MessageReceived = MessageReceived;
    GetChar(_GetCharCallback);
}

#if defined(PROTOCOL_ARDUINO)
void Protocol::Send(const uint16_t pos)
{
    int size = 1 + sizeof(uint16_t);
    char *buff = new char[size];
    *buff = _MagicNumber;
    *(reinterpret_cast<uint16_t *>(buff + 1)) = pos;
    for (int i = 0; i < size; i++)
    {
        _PutChar(buff[i]);
    }
    delete[] buff;
}
#elif defined(PROTOCOL_PC)
void Protocol::Send(const char *carr, const uint16_t length)
{
    _PutChar(_MagicNumber);
    char *tmp = new char[sizeof(uint16_t)];
    *(reinterpret_cast<uint16_t *>(tmp)) = length;
    for (int i = 0; i < sizeof(uint16_t); i++)
    {
        _PutChar(tmp[i]);
    }
    for (int i = 0; i < length; i++)
    {
        _PutChar(carr[i]);
    }
    delete[] tmp;
}
#else
#error Protocol cannot be compiled under this environment.
#endif

void Protocol::_GetCharCallback(const char c)
{
    if (c == _MagicNumber)
    {
        delete buff;
        buff = new char[sizeof(uint16_t)];
        buffoffset = 0;
        recv = true;
#if defined(PROTOCOL_ARDUINO)
        targetsize = 0;
        targetstage = 0;
#endif
        return;
    }
    if (false == recv)
    {
        return;
    }
#if defined(PROTOCOL_PC)
    // Receive next few characters
    *(buff + buffoffset) = c;
    buffoffset++;
    if (buffoffset == sizeof(uint16_t))
    {
        _MessageReceived(*(reinterpret_cast<uint16_t *>(buff)));
        recv = false;
    }
#elif defined(PROTOCOL_ARDUINO)
    if (0 == targetstage)
    {
        *(buffptr++) = c;
        if (buffptr - buff == sizeof(uint16_t))
        {
            targetsize = *(reinterpret_cast<uint16_t *>(buff));
            targetstage = 1;
            delete[] buff;
            buff = new char[targetsize];
            buffptr = buff;
        }
    }
    else if (1 == targetstage)
    {
        *(buffptr++) = c;
        if (buffptr - buff == targetsize)
        {
            _MessageReceived(buff, targetsize);
        }
    }
#else
#error Protocol cannot be compiled under this environment.
#endif
}

char *Protocol::buff = nullptr;
int Protocol::buffoffset = 0;
bool Protocol::recv = false;

#if defined(PROTOCOL_ARDUINO)
uint16_t Protocol::targetsize = 0;
int Protocol::targetstage = 0;
#endif

EntryGetChar Protocol::_GetChar;
EntryPutChar Protocol::_PutChar;
OnMessageReceived Protocol::_MessageReceived;