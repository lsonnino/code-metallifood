/**
 *  ===================
 *  === METALLIFOOD === 
 *  ===================
 *  
 *  Ce code est le code de l'Adruino contenu dans le paquet Metallifood
 *  
 *  Role:
 *      Il allume une LED lorsque un metal est detecte
 *  Fonctionnement:
 *      Lorsque un metal est detecte, un battement est produit.
 *      Si aucun metal est detecte, une tesion proche de O[V] est detectee.
 *      Cette tension n'est pas exactement de 0[V] car il reste un bruit generant une legere tension (inferieure a 0.5[V])
 *      Lo battement produit lorque un metal est detecte a une amplitude de l'ordre de 2[V]
 *      Le programme detecte donc une tension superieure a 0.5[V] (configurable). Si c'est le cas, il allume le LED. Sinon, il l'eteint
 *      
 *  Configuration:
 *      La marge de detection est stoquee dans la variable globale {THRESHOLD} (par default 0.5[V])
 *      Le LED est branche sur le pin {ledPin} (par default PIN 2)
 *      Le pin de detection est le pin {sensorPin} (par default PIN A0)
 *      Le temps a attendre entre deux analyses du signal est stoque dans la variable globale {WAIT_TIME} (par default egal a 500[ms])
 *  
 */
 
// GPIO
int sensorPin = A0; // La ou on lis la tension
int ledPin = 2; // La LED

// analogRead donne une valeur entre 0 et 1023 (0 = 0V et 1023 = 5V)
float THRESHOLD = 100; // = 0.5 V

int WAIT_TIME = 500; // Temps a attendre avant de recommencer (en millisecondes)

// Variables
int sensorValue = 0; // Tension (entre 0 et 1023 correspondant a une tension entre 0V et 5V)

/**
 * Methode lancee a l'allumage
 * Configure les pin
 */
void setup() {
  // Configure les GPIO
  pinMode(sensorPin, INPUT); // Le {sensorPin} est une entree
  pinMode(ledPin, OUTPUT); // Le {ledPin} est une sortie
}

/**
 * Methode executee en continu
 * Analyse le signal recu
 */
void loop() {
  // Prends la difference de tension entre le pin {sensorPin} et le ground de l'Adruino
  // analogRead donne une valeur entre 0 et 1023 (0 = 0V et 1023 = 5V)
  sensorValue = analogRead(sensorPin);

  // Analyser cette valeur
  if(sensorValue > THRESHOLD){ // Si elle est au dessus de {threshold}
    digitalWrite(ledPin, HIGH); // Allumer le LED
  }
  else if(sensorValue < threshold){ // Sinon
    digitalWrite(ledPin, LOW); // Eteindre le led
  }

  // Attendre un certain temps avant de recommencer
  delay(WAIT_TIME);
}
