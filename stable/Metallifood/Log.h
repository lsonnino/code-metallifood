// ============================================================================
// Log.h
// 
//
// ============================================================================
#ifndef Log
#define Log

#include <EEPROM.h>

// Atmel guarantees at least 100,000 write cycles
// protect the memory from excessive writing
//#define WRITE_DISABLE

// methodes
void setupAddress();
void writeAddress();
void next();
void write(int value);
void log();
void clear();


#endif // Log
