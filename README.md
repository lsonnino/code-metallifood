
# Metallifood
Ce code est le code de l'Adruino contenu dans le paquet Metallifood

## Role:
Il allume une LED lorsque un metal est détecté.

## Fonctionnement:
Lorsque un métal est détecté, un battement est produit.
Si aucun métal n'est détecté, une tesion proche de **0[V]** est détectée.
Cette tension n'est pas exactement de **0[V]** car il reste un bruit générant une légère tension (inférieure à **0.5[V]**).
Un battement produit lorque un métal est détecté a une amplitude de l'ordre de **2[V]**.
Le programme détecte donc une tension supérieure à **0.5[V]** (configurable). Si c'est le cas, il allume le LED. Sinon, il l'éteint.

## Configuration:
* La marge de détection est stoquée dans la variable globale ```THRESHOLD``` (par default **0.5[V]**).
* Le LED est branche sur le pin ```ledPin``` (par default **PIN 2**)
* Le pin de détection est le pin ```sensorPin``` (par default **PIN A0**)
* Le temps à attendre entre deux analyses du signal est stoqué dans la variable globale ```WAIT_TIME``` (par default egal a **50[ms]**)
* Le temps pendant lequel la LED est gardée allumée en cas de détéction est stoqué dans la variable globale ```DETECTED_WAIT_TIME``` (par default egal a **1[s]**)

# Sponsorship

**Metallifood**  est open source.

# Credits

- Adam Abazi
- Lionel Boils
- Jean-Baptiste Della Faille
- [Maxime Lemerle](https://github.com/maxlem)
- [Lorenzo Sonnino](https://github.com/lsonnino)
- Corentin Thaon

# License

[The GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.en.html)
