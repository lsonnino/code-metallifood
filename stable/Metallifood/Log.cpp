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
#include <Arduino.h>

// =========================================================
// =                       VARIABLES                       =
// =========================================================
byte address = 0; // La derniere valeur stoquee dans la EEPROM

// =========================================================
// =                        METHODES                       =
// =========================================================

/**
 * 
 * Trouve le premier address
 * 
 */
void setupAddress(){
  address = EEPROM.read(0);
}
/**
 * 
 * Sauvegarde l'address actuelle
 * 
 */
void writeAddress(){
  #ifdef WRITE_DISABLE
    EEPROM.write(0, address);
  #endif
}

/**
 *  
 *  Si necessaire, oublie le dernier therme pour se souvenir du nouveau
 *  
 **/
void next(){
  if(address < EEPROM.length() - 1){
    address++;
  }
  else {
    for(int i=2 ; i < EEPROM.length() - 1 ; i++){
      #ifdef WRITE_DISABLE
        EEPROM.write(i, EEPROM.read(i + 1));
      #endif
    }
  }

  writeAddress();
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
  
  // Passe a l'adresse suivant
  next();
  
  // Ecrit la valeur dans la EEPROM
  #ifdef WRITE_DISABLE
    EEPROM.write(address, val);
  #endif
}

/**
 * 
 * Affiche toute la memoire
 * 
 */
void log(){
  setupAddress();
  Serial.print("Address is ");
  Serial.println(address, DEC);

  for(int i=1 ; i <= address ; i++){
    byte value = EEPROM.read(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(value*4, DEC);
    Serial.println();
  }
}

/**
 * 
 * Efface completement l'historique
 * 
 */
void clear(){
  address = 0;

  for(int i=1 ; i < EEPROM.length() ; i++){
     write(0);
  }
  
  address = 0;
  writeAddress();
}

