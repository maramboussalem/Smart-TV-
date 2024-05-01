#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const byte ROWS = 4; // Quatre rangées
const byte COLS = 4; // Quatre colonnes

char keys[ROWS][COLS] = {
  {'1','2','3','F1'},
  {'4','5','6','F2'},
  {'7','8','9','0'},
  {'*',ESC,UP_ARROW,ENTER}
};

byte rowPins[ROWS] = {4, 3, 2, 1};
byte colPins[COLS] = {5, 6, 7, A0}; // Utilisez A0 pour la colonne F1 et A1 pour la colonne F2

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const char password[] = "123";
char enteredPassword[sizeof(password)] = ""; // Tampon pour stocker le mot de passe entré
int passwordIndex = 0; // Index pour suivre les caractères entrés

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  char key = keypad.getKey();
  
  if (key != NO_KEY) {
    if (key == ENTER || key == 'F1') { // Si Ent (Enter) ou F1 est pressé
      if (strcmp(enteredPassword, password) == 0) { // Comparer le mot de passe entré avec le mot de passe correct
        lcd.clear();
        lcd.print("Bonjour Eya");
      } else {
        lcd.clear();
        lcd.print("Mot de passe incorrect");
      }
      delay(1000); // Délai pour permettre la lecture du message sur l'écran LCD
      lcd.clear(); // Effacer l'écran LCD après l'affichage du message
      passwordIndex = 0; // Réinitialiser l'index du mot de passe
      memset(enteredPassword, 0, sizeof(enteredPassword)); // Effacer le tampon du mot de passe entré
    } else if (key == ESC || key == 'F2') { // Si ESC ou F2 est pressé
      lcd.clear();
      lcd.print("Erreur");
      delay(1000); // Délai pour permettre la lecture du message sur l'écran LCD
      lcd.clear(); // Effacer l'écran LCD après l'affichage du message
      passwordIndex = 0; // Réinitialiser l'index du mot de passe
      memset(enteredPassword, 0, sizeof(enteredPassword)); // Effacer le tampon du mot de passe entré
    } else if (passwordIndex < sizeof(password) - 1) { // Vérifier s'il y a de l'espace dans le tampon
      enteredPassword[passwordIndex++] = key; // Stocker la touche pressée dans le tampon
      lcd.print(key); // Afficher la touche pressée sur l'écran LCD
    }
  }
}
