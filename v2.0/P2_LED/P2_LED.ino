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
 *      Lo battement est produit lorque un metal est detecte a une amplitude de l'ordre de 2[V]
 *      Le programme detecte donc une tension superieure a 0.5[V] (configurable). Si c'est le cas, il allume la LED. Sinon, il l'eteint
 *      
 *  Configuration:
 *      La marge de detection est stockee dans la variable globale {THRESHOLD} (par default 0.5[V])
 *      La LED est branchee sur le pin {ledPin} (par default PIN 2)
 *      Le pin de detection est le pin {sensorPin} (par default PIN A0)
 *      Le temps a attendre entre deux analyses du signal est stocke dans la variable globale {WAIT_TIME} (par default egal a 50[ms])
 *      Le temps pendant laquelle la LED reste allumee en cas de detection d'un metal est stocke dans la variable globale
 *          {DETECTED_WAIT_TIME} (par default egal a 1[s])
 *  
 */
 
// GPIO
const byte sensorPin = A0; // La ou on lis la tension
const byte buttonPin = 4; // Le bouton
const byte redLedPin = 2; // Le LED rouge
const byte greenLedPin = 3; // Le LED vert

// analogRead donne une valeur entre 0 et 1023 (0 = 0V et 1023 = 5V)
const short THRESHOLD = 100; // = 0.5 V

const int WAIT_TIME = 50; // Temps a attendre avant de recommencer (en millisecondes)
const int DETECTED_WAIT_TIME = 1000; // Temps a attendre apres qu'un metal aie ete detecte (en millisecondes)
const int DETECTION_TIME = 1000;
const int MAX_DETECTION_ITERATIONS = DETECTION_TIME/WAIT_TIME;

const byte RESTART_ITERATIONS = 1;
const byte CONTINUE = 0;
const byte NONE = -1;

// Variables
int sensorValue = 0; // Tension (entre 0 et 1023 correspondant a une tension entre 0V et 5V)
int detectionIterations = 0;
boolean pressedButton = false;

/**
 * Methode lancee a l'allumage
 * Configure les pin
 */
void setup() {
  // Vitesse d'execution
  Serial.begin(9600);
  
  // Configure les GPIO
  pinMode(sensorPin, INPUT); // Le {sensorPin} est une entree
  pinMode(buttonPin, INPUT); // Le {buttonPin} est une entree
  pinMode(redLedPin, OUTPUT); // Le {redLedPin} est une sortie
  pinMode(greenLedPin, OUTPUT); // Le {greenLedPin} est une sortie
}

/**
 * Methode executee en continu
 * Analyse le signal recu
 */
void loop() {
  byte instruction = instruction();
  if(instruction == NONE){
    wait();
    return;
  }
  else if(instruction == RESTART_ITERARIONS){
    resetIterations();
    pressedButton = true;
  }
  else { // if iteration == CONTINUE
    detectionIterations++;
  }
  
  // Analyser cette valeur
  if(detected()){ // Si elle est au dessus de {threshold}
    digitalWrite(redLedPin, HIGH); // Allumer le LED
    
    while(detected(){
      // Attend un certain temps avant de continuer
      delay(DETECTED_WAIT_TIME);
    }
    
    resetIterations;
  }
  else if(detectionIterations == MAX_DETECTION_ITERATIONS){ // Sinon
    digitalWrite(greenLedPin, HIGH); // Allumer le LED
    // Attend un certain temps avant de continuer
    delay(DETECTED_WAIT_TIME);
    resetIterations;
  }

  // Attendre un certain temps avant de recommencer
  wait();
}

boolean detected(){
  // Prends la difference de tension entre le pin {sensorPin} et le ground de l'Adruino
  // analogRead donne une valeur entre 0 et 1023 (0 = 0V et 1023 = 5V)
  sensorValue = analogRead(sensorPin);

  return sensorValue > THRESHOLD;
}

void resetIterations(){
  pressedButton = false;
  detectionIterations = 0;
  digitalWrite(redLedPin, LOW); // Eteindre le led
  digitalWrite(greenLedPin, LOW); // Eteindre le led
}

int instruction(){
  if(digitalRead(buttonPin)){
    return RESTART_ITERATIONS;
  }
  else if(pressedButton){
    return CONTINUE;
  }
  return NONE;
}

void wait(){
  delay(WAIT_TIME);
}

