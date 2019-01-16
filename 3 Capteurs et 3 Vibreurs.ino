//Définir Les Pins pour les capteurs de la ceinture.

//Un PIN sert à configurer une broche spécifiée grâce à un numéro qu'on lui attribue.

//#define sert à définir une variable constante avant que le programme soit compilé.

//Capteur de Gauche
#define trigPinLeft 2
#define echoPinLeft 3
//Capteur de Droite
#define trigPinRight 4
#define echoPinRight 5
//Capteur Frontal
#define trigPinFront 6
#define echoPinFront 7

//Définir Les Pins pour les vibreurs.

//Vibreur de Gauche
#define motorPinLeft 10
//Vibreur de Droite
#define motorPinRight 9
//Vibreur Frontal
#define motorPinFront 8

//Définir les durées et les distances pour chaque capteur.
//La "durée" correspond au temps que met un ultrason pour revenir sur l'émetteur à ultrasons de la ceinture.
//La "distance" correspond à la distance qui sépare l'obstacle du capteur, de l'utilisateur. 

//Une variable FLOAT est une variable qui permet de stocker des nombres décimaux.

float durationLeft, distanceLeft, durationRight, distanceRight, durationFront, distanceFront;

//Définir le nom du capteur.

//Une variable CHAR permet de stocker une lettre.

//Capteur Frontal
char Front = 'F';
//Capteur de Gauche
char Left = 'L';
//Capteur de Droite
char Right = 'R';

//void est un mot clé utilisé pour déclarer une function.
//void setup est une fonction qui est appelée au démarrage de la carte arduino.

void setup() {
  
  //Serial.begin() permet de paramétrer le nombre de donnée envoyée par seconde en bit.
  Serial.begin (9600);
  
  //Configuration des pins en sortie ou entrée.
  
  //pinMode() permet de configurer un pin soit en entrée, soit en sortie.
  
  //Capteur de Gauche
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  //Capteur de Droite
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  //Capteur Frontal
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  
  //Vibreur de Gauche
  pinMode(motorPinLeft, OUTPUT);
  //Vibreur de Droite
  pinMode(motorPinRight, OUTPUT);
  //Vibreur Frontal
  pinMode(motorPinFront, OUTPUT);
}
 
//void loop est une fonction qui est exécutée en boucle sans fin par la carte arduino.

void loop() {
  //Partie de programme qui va tourner en boucle tant que le système est en marche.
  
  //EmissionUltrasons permet de :
  //Choisir le pin "trig", qui est celui qui va reçevoir les ultrasons précédemment envoyé par l'éméteur/recépteur d'ultrasons.
  //Choisir le pin "echo", qui est celui qui va envoyer l'impulsion à l'éméteur/recépteur d'ultrasons pour émétre des ultrasons.
  //Choisir le pin "motor", qui correspond au vibreur choisi.
  //Choisir la variable float, qui va permettre de stocker la durée que mettent les ultrasons à revenir.
  //Choisir la variable float, qui va permettre de stocker la distance qu'on parcouru les ultrasons avant de toucher un obstacle.
  //Choisir la lettre à afficher lorsque le résultat apparé pour être sûr de savoir de quel capteur on parle pour une personne extérieur.
  
  //Configuration pour le capteur frontal et le vibreur frontal.
  EmissionUltrasons(trigPinFront, echoPinFront, motorPinFront, durationFront, distanceFront, Front); 
  
  //Configuration pour le capteur de gauche et le vibreur de gauche.
  EmissionUltrasons(trigPinLeft, echoPinLeft, motorPinLeft, durationLeft, distanceLeft, Left);
  
  //Configuration pour le capteur de droite et le vibreur de droite.
  EmissionUltrasons(trigPinRight, echoPinRight, motorPinRight, durationRight, distanceRight, Right);
  
  //delay permet de mettre en pause le programme pendant une période en milliseconde et donc d'éviter des erreur dans le programme.
  delay(500);
}

//void EmissionUltrasons est une function qui est exécutée sur demande du code.

void EmissionUltrasons(int trig, int echo, int motor, float duration, float distance, char name)
{
  //On envoie au capteur ultrasons de ne pas envoyer d'ultrasons.
  digitalWrite(trig, LOW);
  //On fait une pause dans le programme de plusieurs microseconds.
  delayMicroseconds(2);
  //On envoie au capteur ultrasons d'envoyer des ultrasons.
  digitalWrite(trig, HIGH);
  //On fait une pause dans le programme de plusieurs microseconds.
  delayMicroseconds(10);
  //On envoie au capteur ultrasons de ne pas envoyer d'ultrasons.
  digitalWrite(trig, LOW);
 
  //Mesurer le temps de réponse de l'émetteur/recepteur d'ultrasons
  
  duration = pulseIn(echo, HIGH);
  
  //Déterminer la distance grâce à la durée
  //On utilise 343 mètres par secondes comme vitesse du son
  
  distance = (duration / 2) * 0.0343;
  
  //On écrit le nom du capteur utilisé dans la console.
  Serial.print(name);
  //On écrit cette phrase dans la console.
  Serial.print("_ La distance est egale a : ");
  
  //On test la distance pour voir si on doit faire en sorte d'écrire dans la console que l'objet est hors de portée.
  if (distance >= 400 || distance <= 2) {
    //On écrit cette phrase dans la console quand l'objet est hors de portée.
    Serial.println("Hors de portee.");
  }
  else {
    //On écrit dans la console pour afficher la distance du capteur à l'objet.
    Serial.print(distance);
    //On écrit dans la console pour montrer l'unité de mesure.
    Serial.println(" cm.");
    
    //On écrit cette phrase dans la console.
    Serial.print("Le temps de reponse est de : ");
    //On écrit dans la console pour afficher la durée pour que les ultrasons reviennent au capteur.
    Serial.print(duration);
    //On écrit dans la console pour montrer l'unité de mesure.
    Serial.println(" microsecondes.");
    
    //On test la distance pour voir si l'on doit faire vibrer le capteur.
    if(distance <= 200)
    {
      //On fait vibrer le vibreur.
      analogWrite(motor, 100);
    }
    else
    {
      //Le vibreur de vibre pas.
      analogWrite(motor, 0);
    }
    
    //delay permet de mettre en pause le programme pendant une période en milliseconde et donc d'éviter des erreur dans le programme.
    delay(500);
  }
}
