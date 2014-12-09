#include "Protocol.h"

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
    for (size_t i = 0; i < length; i++)
    {
        _PutChar(carr[i]);
    }
}
#else
#error Protocol cannot be compiled under this environment.
#endif

void Protocol::_GetCharCallback(const char c)
{
  //_PutChar('\n');
  //_PutChar(c);
    if (c == _MagicNumber)
    {
  //_PutChar('2');
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
    *(buffptr++) = c;
    if (buffptr - buff == sizeof(uint16_t))
    {
  //_PutChar('3');
        _MessageReceived(*(reinterpret_cast<uint16_t *>(buff)));
        recv = false;
    }
#elif defined(PROTOCOL_ARDUINO)
    if (0 == targetstage)
    {
  //_PutChar('4');
        *(buff+buffoffset) = c;
        buffoffset++;
        //_PutChar('0' + buffoffset);
        if (buffoffset == sizeof(uint16_t))
        {
  //_PutChar('6');
            targetsize = *(reinterpret_cast<uint16_t *>(buff));
            targetstage = 1;
            delete[] buff;
            buff = new char[targetsize];
            buffoffset = 0;
        }
    }
    else if (1 == targetstage)
    {
  //_PutChar('5');
        *(buff+buffoffset) = c;
        buffoffset++;
        if (buffoffset == targetsize)
        {
            _MessageReceived(buff, targetsize);
        }
    }
#else
#error Protocol cannot be compiled under this environment.
#endif
}

char *Protocol::buff = 0;
int Protocol::buffoffset = 0;
bool Protocol::recv = false;

#if defined(PROTOCOL_ARDUINO)
uint16_t Protocol::targetsize = 0;
int Protocol::targetstage = 0;
#endif

EntryGetChar Protocol::_GetChar;
EntryPutChar Protocol::_PutChar;
OnMessageReceived Protocol::_MessageReceived;
