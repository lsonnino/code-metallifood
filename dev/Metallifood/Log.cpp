/**
 *  ===================
 *  === METALLIFOOD === 
 *  ===================
 *  
 *  Ce code ecrit dans les valeures lues par le detecteur dans la memoire EEPROM (memoire a long terme) de l'Arduino
 *  et les affiches a l'ecran pour debug.
 *  
 */

#include <EEPROM.h>

// =========================================================
// =                       VARIABLES                       =
// =========================================================
int address = 0; // La derniere valeur stoquee dans la EEPROM
const int SEPARATOR = 0; // Derniere valeur stoquee dans la EEPROM
const int SEPARATOR_MULTIPLIER = 8; // Nombre de fois ou le {SEPARATOR} est ecrit

// =========================================================
// =                        METHODES                       =
// =========================================================

/**
 *  Passe a l'adresse suivante
 **/
void nextAddress(){
  // La prochaine fois, ecrire la valeur dans la case d'apres
  address++;

  // Si {address} est arrivee au bout, recommencer
  if (address == EEPROM.length()) {

    address = 0;
  }
}

/**
 *  
 *  Ecrit la valeur {value} dans la EEPROM
 *  value est une valeur entre 0 et 1023
 *  
 **/
void write(int value) {
  /*
   * {value} est une valeur comprise entre 0 et 1023. Or, dans la EEPROM on ne peut ecrire que une valeur
   * comprise entre 0 et 255
   */
  int val = value / 4;
  // Ecrit la valeur dans la EEPROM
  EEPROM.write(address, val);
  // Passe a l'adresse suivant
  nextAddress();

  // Ecrit les separateurs
  int i = 0;
  while(i < SEPARATOR_MULTIPLIER){
    EEPROM.write(address, SEPARATOR);

    // Passe a l'adresse suivant
    nextAddress();
  }

  address = address - SEPARATOR_MULTIPLIER;
  if(address < 0){
    address = address + EEPROM.length();
  }
}
