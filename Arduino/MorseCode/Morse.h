typedef void (*EntryHigh)(void);
typedef void (*EntryLow)(void);
typedef void (*EntryDelay)(const int);

void MorseEntry(EntryHigh high, EntryLow low, EntryDelay delay);
void MorseExecute(const char c);
