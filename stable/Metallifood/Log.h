/*
 * Copyright 2018 Adam Abazi, Lionel Boils, Jean-Baptiste Della Faille,
 * Maxime Lemerle, Lorenzo Sonnino, Corentin Thaon
 * 
 * This file is part of METALIFOOD.
 * 
 * METALIFOOD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * METALIFOOD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LOG_H
#define LOG_H

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


#endif // LOG_H
