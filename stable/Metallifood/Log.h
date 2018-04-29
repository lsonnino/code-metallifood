// ============================================================================
// Log.h
// 
//
// ============================================================================
#ifndef Log
#define Log

#include <EEPROM.h>

// methodes
void setupAddress();
void writeAddress();
void next();
void write(int value);
void log();
void clear();


#endif // Log
