/**
 *  ===================
 *  === METALLIFOOD === 
 *  ===================
 *  
 *  Ce code est le code de l'Adruino contenu dans le paquet Metallifood
 *  
 *  Role:
 *      Lorsque le bouton est appuye, commence la detection. La phase de detection dure (par default) deux secondes.
 *      Si pendant cette phase un metal est detecte, le LED rouge s'allume tant qu'un metal est a portee (ce LED attend (par default) une seconde avant de s'eteindre).
 *      Si le bouton est appuye de nouveau, relance la phase de detection.
 *      Si pendant ce temps aucun metal n'a ete detecte, le LED vert s'allume et attend (par default) une seconde avant de s'eteindre.
 *      
 *  Fonctionnement:
 *      Lorsque un metal est detecte, un battement est produit.
 *      Si aucun metal est detecte, une tesion proche de O[V] est detectee.
 *      Cette tension n'est pas exactement de 0[V] car il reste un bruit generant une legere tension (inferieure a 0.5[V])
 *      Lo battement est produit lorque un metal est detecte a une amplitude de l'ordre de 2[V]
 *      Le programme detecte donc une tension superieure a 0.5[V] (configurable). Si c'est le cas, il allume la LED. Sinon, il l'eteint
 *      Enfin, lorsque le bouton n'est appuye pas, les pattes du bouton sont en circuit ouvert. Lorsque le bouton est appuye, ces pattes passent en court circuit
 *      
 *  Configuration:
 *      La marge de detection est stockee dans la variable globale {THRESHOLD} (par default 0.5[V])
 *      
 *      Le LED rouge est branchee sur le pin {redLedPin} (par default PIN 2)
 *      Le LED vert est branchee sur le pin {greenLedPin} (par default PIN 3)
 *      Le pin de detection est le pin {sensorPin} (par default PIN A0)
 *      Le bouton est branche sur le le pin {buttonPin} (par default PIN 4)
 *      
 *      Le temps a attendre entre deux analyses du signal est stocke dans la variable globale {WAIT_TIME} (par default egal a 50[ms])
 *      Le temps pendant laquelle un LED reste allumee est stocke dans la variable globale
 *          {DETECTED_WAIT_TIME} (par default egal a 1[s])
 *      La duree de la phase de detection est stoquee dans la variable {DETECTION_TIME} (par default egal a 2[s])
 *  
 */

// =========================================================
// =                       VARIABLES                       =
// =========================================================
 
// GPIO
const byte sensorPin = A0; // La ou on lis la tension
const byte buttonPin = 4; // Le bouton
const byte redLedPin = 2; // Le LED rouge
const byte greenLedPin = 3; // Le LED vert

// analogRead donne une valeur entre 0 et 1023 (0 = 0V et 1023 = 5V)
const short THRESHOLD = 100; // = 0.5 V

// Durees
const int WAIT_TIME = 50; // Temps a attendre avant de recommencer (en millisecondes)
const int DETECTED_WAIT_TIME = 1000; // Temps a attendre apres qu'un metal aie ete detecte (en millisecondes)
const int DETECTION_TIME = 2000; // La duree de la phase de detection (en millisecondes)
const int MAX_DETECTION_ITERATIONS = DETECTION_TIME / WAIT_TIME; // Le nombre de fois que la fonction {loop()} est appellee avant de considerer la phase de detection finie

// Consignes pour la phase de detection
const byte RESTART_ITERATIONS = 1; // Recommencer la phase de detection
const byte CONTINUE = 0; // Continuer la phase de detection
const byte NONE = -1; // Ne rien faire

// Variables
int sensorValue = 0; // Tension (entre 0 et 1023 correspondant a une tension entre 0V et 5V)
int detectionIterations = 0; // Le nombre de fois que la fonction {loop()} est appellee
boolean pressedButton = false; // Si on est en phase de detection

// Variables necessaires pour lire l'etat du bouton
// Necessaires pour corriger l'effet "debounce" des bouttons
// Pour plus d'informations, lire ici: https://www.arduino.cc/en/Tutorial/Debounce
int buttonState;             // L'etat du bouton
int lastButtonState = LOW;   // L'etat du bouton lors de la derniere alanyse
// Ces temps risquent de vite prendre des grandes valeurs
unsigned long lastDebounceTime = 0;  // La derniere fois que le bouton a ete appuye
unsigned long debounceDelay = 70;    // Le temps de "debounce"

// =========================================================
// =                        METHODES                       =
// =========================================================

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
 * Analyse le signal recupere
 */
void loop() {
  byte currentInstruction = instruction(); // Regarde ce qu'il doit faire
  if(currentInstruction == NONE){ // Si il ne doit rien faire, ne fait rien
    //wait();
    return;
  }
  else if(currentInstruction == RESTART_ITERATIONS){ // Recommence les iterations a 0
    resetIterations();
    pressedButton = true;
  }
  else { // if iteration == CONTINUE
        // Augmente les iterations et continue
    detectionIterations++;
  }
  
  // Analyser la detection
  if(detected()){ // Si elle est au dessus de {threshold}
    digitalWrite(redLedPin, HIGH); // Allumer le LED rouge
    
    while(detected()){ // Tant qu'un metal est detecte
      // Attend un certain temps avant de continuer
      delay(DETECTED_WAIT_TIME);
    }

    // Recommence les iterations
    resetIterations();
  }
  else if(detectionIterations == MAX_DETECTION_ITERATIONS){ // Si aucun metal n'a ete detecte pendant la phase de detection
    digitalWrite(greenLedPin, HIGH); // Allumer le LED vert
    // Attend un certain temps avant de continuer
    delay(DETECTED_WAIT_TIME);
    // Recommence les iterations
    resetIterations();
  }

  // Attendre un certain temps avant de recommencer
  wait();
}

/**
 * Renvoie {true} si le bouton a ete appuye.
 * 
 * Pour des raisons mecaniques, lorsque le bouton est appuye, un signal impropre est parfois renvoye.
 * Cette methode corrige ce probleme
 * 
 * Ce code est une version adaptee du code disponible ici: https://www.arduino.cc/en/Tutorial/Debounce
 */
boolean isButtonPressed(){
  // Lis la valeur renvoyee par le bouton
  int reading = digitalRead(buttonPin);

  // Regarde si le boutton a ete presse et ignore le bruit genere par le bouton

  // Si l'etat du bouton change a cause du bruit genere par le bouton:
  if (reading != lastButtonState) {
    lastButtonState = reading;
    // Reset le timer
    lastDebounceTime = millis();
    return false;
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si le bouton n'a pas change d'etat depuis un certain temps,
    // prend cette valeur comme etat l'etat du bouton
    buttonState = reading;
  }

  return buttonState == HIGH;
}

/**
 * Regarde ce qu'il doit faire
 * Renvoie
 *    {RESTART_ITERATIONS} si la phase de detection doit recommencer
 *    {CONTINUE} si les iterations doivent continuer
 *    {NONE} si rien ne doit etre  fait
 */
byte instruction(){
  // Si le boutin est appuye, recommence la phase de detection
  if(isButtonPressed()){
    return RESTART_ITERATIONS;
  }
  // Sinon,
  // Si le bouton a deja ete appuye, continue la detection
  else if(pressedButton){
    return CONTINUE;
  }
  // Sinon,
  // Ne fait rien
  return NONE;
}

/**
 * Recommence les iterations a 0
 */
void resetIterations(){
  // Recommence les iterations
  pressedButton = false;
  detectionIterations = 0;
  // Eteint les LED
  digitalWrite(redLedPin, LOW); // Eteindre le led
  digitalWrite(greenLedPin, LOW); // Eteindre le led
}

/**
 * Detecte un metal
 * Renvoie {true} si un metal est detecte, renvoie {false sinon}
 */
boolean detected(){
  // Prends la difference de tension entre le pin {sensorPin} et le ground de l'Adruino
  // analogRead donne une valeur entre 0 et 1023 (0 = 0V et 1023 = 5V)
  sensorValue = analogRead(sensorPin);

  // Si cette valeur est superieure a la marge, un metal est detecte
  return sensorValue > THRESHOLD;
}

/**
 * Attend un certain temps avant de recommencer la methode {loop()}
 */
void wait(){
  // Ce temps peut etre optimise dans cette methode
  delay(WAIT_TIME);
}

/**
 *  
 *  Donne la distance entre le capteur de proximite et l'obstacle le plus proche
 *  
 **/
int getDistance(int triggerPin, int echoPin){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  return duration*0.034/2;
}

/**
 *  
 *  Renvoie {true} si la distance entre le capteur de proximite et
 *  l'obstacle le plus proche est inferieure a {distance}
 *  
 **/
boolean isObstacle(int triggerPin, int echoPin, int distance){
  return getDistance(triggerPin, echoPin) <= distance;
}
