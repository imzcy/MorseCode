#include "Morse.h"

#define TIMEUNIT 50

EntryHigh _High;
EntryLow _Low;
EntryDelay _Delay;

void MorseEntry(EntryHigh high, EntryLow low, EntryDelay delay)
{
  _High = high;
  _Low = low;
  _Delay = delay;
}

void DASH()
{
  _High();
  _Delay(3 * TIMEUNIT);
  _Low();
  _Delay(TIMEUNIT);
}

void DOT()
{
  _High();
  _Delay(TIMEUNIT);
  _Low();
  _Delay(TIMEUNIT);
}

void CHAR()
{
  _Delay(2 * TIMEUNIT);
}

void WORD()
{
  _Delay(3 * TIMEUNIT);
}

void MorseExecute(const char c)
{
  switch(c)
  {
    case 'a': case 'A':
    DOT();DASH();CHAR();
    break;
    case 'b': case 'B':
    DASH();DOT();DOT();DOT();CHAR();
    break;
    case 'c': case 'C':
    DASH();DOT();DASH();DOT();CHAR();
    break;
    case 'd': case 'D':
    DASH();DOT();DOT();CHAR();
    break;
    case 'e': case 'E':
    DOT();CHAR();
    break;
    case 'f': case 'F':
    DOT();DOT();DASH();DOT();CHAR();
    break;
    case 'g': case 'G':
    DASH();DASH();DOT();CHAR();
    break;
    case 'h': case 'H':
    DOT();DOT();DOT();DOT();CHAR();
    break;
    case 'i': case 'I':
    DOT();DOT();CHAR();
    break;
    case 'j': case 'J':
    DOT();DASH();DASH();DASH();CHAR();
    break;
    case 'k': case 'K':
    DASH();DOT();DASH();CHAR();
    break;
    case 'l': case 'L':
    DOT();DASH();DOT();DOT();CHAR();
    break;
    case 'm': case 'M':
    DASH();DASH();CHAR();
    break;
    case 'n': case 'N':
    DASH();DOT();CHAR();
    break;
    case 'o': case 'O':
    DASH();DASH();DASH();CHAR();
    break;
    case 'p': case 'P':
    DOT();DASH();DASH();DOT();CHAR();
    break;
    case 'q': case 'Q':
    DASH();DASH();DOT();DASH();CHAR();
    break;
    case 'r': case 'R':
    DOT();DASH();DOT();CHAR();
    break;
    case 's': case 'S':
    DOT();DOT();DOT();CHAR();
    break;
    case 't': case 'T':
    DASH();CHAR();
    break;
    case 'u': case 'U':
    DOT();DOT();DASH();CHAR();
    break;
    case 'v': case 'V':
    DOT();DOT();DOT();DASH();CHAR();
    break;
    case 'w': case 'W':
    DOT();DASH();DASH();CHAR();
    break;
    case 'x': case 'X':
    DASH();DOT();DOT();DASH();CHAR();
    break;
    case 'y': case 'Y':
    DASH();DOT();DASH();DASH();CHAR();
    break;
    case 'z': case 'Z':
    DASH();DASH();DOT();DOT();CHAR();
    break;
    case '0':
    DASH();DASH();DASH();DASH();DASH();CHAR();
    break;
    case '1':
    DOT();DASH();DASH();DASH();DASH();CHAR();
    break;
    case '2':
    DOT();DOT();DASH();DASH();DASH();CHAR();
    break;
    case '3':
    DOT();DOT();DOT();DASH();DASH();CHAR();
    break;
    case '4':
    DOT();DOT();DOT();DOT();DASH();CHAR();
    break;
    case '5':
    DOT();DOT();DOT();DOT();DOT();CHAR();
    break;
    case '6':
    DASH();DOT();DOT();DOT();DOT();CHAR();
    break;
    case '7':
    DASH();DASH();DOT();DOT();DOT();CHAR();
    break;
    case '8':
    DASH();DASH();DASH();DOT();DOT();CHAR();
    break;
    case '9':
    DASH();DASH();DASH();DASH();DOT();CHAR();
    break;
    case '.':
    DOT();DASH();DOT();DASH();DOT();DASH();CHAR();
    break;
    case ',':
    DASH();DASH();DOT();DOT();DASH();DASH();CHAR();
    break;
    case ':':
    DASH();DASH();DASH();DOT();DOT();DOT();CHAR();
    break;
    case '?':
    DOT();DOT();DASH();DASH();DOT();DOT();CHAR();
    break;
    case '\'':
    DOT();DASH();DASH();DASH();DASH();DOT();CHAR();
    break;
    case '-':
    DASH();DOT();DOT();DOT();DOT();DASH();CHAR();
    break;
    case '/':
    DASH();DOT();DOT();DASH();DOT();CHAR();
    break;
    case '(': case ')':
    DASH();DOT();DASH();DASH();DOT();DASH();CHAR();
    break;
    case '"':
    DOT();DASH();DOT();DOT();DASH();DOT();CHAR();
    break;
    case '@':
    DOT();DASH();DASH();DOT();DASH();DOT();CHAR();
    break;
    case '=':
    DASH();DOT();DOT();DOT();DASH();CHAR();
    break;
    case '\n':
    DOT();DASH();DOT();DASH();CHAR();
    break;
    default:
    WORD();
  }
}
