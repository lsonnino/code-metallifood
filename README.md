
# Metallifood
Ce code est le code de l'Adruino contenu dans le paquet Metallifood


## Role:
Lorsque le bouton est appuyé, commence la détection. La phase de détection dure (par default) deux secondes.
Si pendant cette phase un métal est détécté, le LED rouge s'allume tant qu'un métal est à portée (ce LED attend (par default) une seconde avant de s'éteindre).
Si le bouton est appuyé de nouveau, relance la phase de détection.
Si pendant ce temps aucun métal n'à été détécté, le LED vert s'allume et attend (par default) une seconde avant de s'éteindre.
Un son est également joué pour appuyer les signaux lumineux.
Un historique peut etre retrouve dans la EEPROM (memoire a long therme) de l'Arduino et sera affiche au demarrage.

## Fonctionnement:
Lorsque un métal est détecté, un battement est produit.
Si aucun métal n'est détecté, une tesion proche de **0[V]** est détectée.
Cette tension n'est pas exactement de **0[V]** car il reste un bruit générant une légère tension (inférieure à **0.5[V]**).
Un battement est produit lorque un métal est détecté a une amplitude de l'ordre de **2[V]**.
Le programme détecte donc une tension supérieure à **0.5[V]** (configurable). Si c'est le cas, il allume la LED. Sinon, il l'éteint.
Enfin, lorsque le bouton n'est appuyé pas, les pattes du bouton sont en circuit ouvert. Lorsque le bouton est appuyé, ces pattes passent en court circuit

## Configuration:
* La marge de détection est stockée dans la variable globale ```THRESHOLD``` (par default **0.5[V]**).
* La LED rouge est branchée sur le pin ```redLedPin``` (par default **PIN 2**)
* La LED vert est branchée sur le pin ```greenLedPin``` (par default **PIN 3**)
* Le pin de détection est le pin ```sensorPin``` (par default **PIN A0**)
* Le bouton est branché sur le pin ```buttonPin``` (par default **PIN A4**)
* Le buzzer est branché sur le pin ```buzzerPin``` (par default **PIN 8**)
* Le temps à attendre entre deux analyses du signal est stocké dans la variable globale ```WAIT_TIME``` (par default egal a **50[ms]**)
* Le temps pendant lequel un LED est reste allumé en cas de détéction est stocké dans la variable globale ```DETECTED_WAIT_TIME``` (par default egal a **1[s]**)
* La durée de la phase de détection  est stoquée dans la variable ```DETECTION_TIME``` (par default égal à **2[s]**)
* Les mélodies jouées sont stoquées dans des variables également configurables

## Code:
La version stable du code est disponible [ici](https://github.com/lsonnino/code-metallifood/tree/master/v1.0)

# Versions

## 2.2
* L'historique de détection est sauvegardée dans la mémoire à long terme de l'Arduino

## 2.1
* Un son est joué pour appuyer les signaux lumineux

## 2.0
* Utilisation d'un bouton pour démarrer la phase de détection
* Ajout du support d'un LED lorsque aucun métal n'est détécté
* Code optimisé

## 1.0
* Un LED s'allume lorsque un métal est détécté

# Sponsorship

**Metallifood**  est open source.

# Credits

- Adam Abazi
- Lionel Boils
- Jean-Baptiste Della Faille
- [Maxime Lemerle](https://github.com/maxIem)
- [Lorenzo Sonnino](https://github.com/lsonnino)
- Corentin Thaon

# License

[The GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.en.html)
