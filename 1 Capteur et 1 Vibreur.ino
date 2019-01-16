//Définir Les Pins pour les capteurs de la ceinture.

//Un PIN sert à configurer une broche spécifiée grâce à un numéro qu'on lui attribue.

//Capteur
#define trigPin 2
#define echoPin 3

//Définir Les Pins pour les vibreurs.

//Vibreur de Gauche
#define motorPin 10

//Définir les durées et les distances pour chaque capteur.
//La "durée" correspond au temps que met un ultrason pour revenir sur l'émetteur à ultrasons de la ceinture.
//La "distance" correspond à la distance qui sépare l'obstacle du capteur, de l'utilisateur. 

//Une variable FLOAT est une variable qui permet de stocker des nombres décimaux.

float duration, distance;

void setup() {
  
  //Serial.begin() permet de paramétrer le nombre de donnée envoyée par seconde en bit.
  Serial.begin (9600);
  
  //Configuration des pins en sortie ou entrée.
  
  //pinMode() permet de configurer un pin soit en entrée, soit en sortie.
  
  //Capteur
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //Vibreur
  pinMode(motorPin, OUTPUT);
}
 
void loop() {
  //Partie de programme qui va tourner en boucle tant que le système est en marche.
  
  //EmissionUltrasons permet de :
  //Choisir le pin "trig", qui est celui qui va reçevoir les ultrasons précédemment envoyé par l'éméteur/recépteur d'ultrasons.
  //Choisir le pin "echo", qui est celui qui va envoyer l'impulsion à l'éméteur/recépteur d'ultrasons pour émétre des ultrasons.
  //Choisir le pin "motor", qui correspond au vibreur choisi.
  //Choisir la variable float, qui va permettre de stocker la durée que mettent les ultrasons à revenir.
  //Choisir la variable float, qui va permettre de stocker la distance qu'on parcouru les ultrasons avant de toucher un obstacle.
  //Choisir la lettre à afficher lorsque le résultat apparé pour être sûr de savoir de quel capteur on parle pour une personne extérieur.
  
  //Configuration pour le capteur et le vibreur.
  EmissionUltrasons(trigPin, echoPin, motorPin, duration, distance); 
  
  //delay permet de mettre en pause le programme pendant une période en milliseconde et donc d'éviter des erreur dans le programme.
  delay(500);
}

void EmissionUltrasons(int trig, int echo, int motor, float duration, float distance)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
 
  //Mesurer le temps de réponse de l'émetteur/recepteur d'ultrasons
  
  duration = pulseIn(echo, HIGH);
  
  //Déterminer la distance grâce à la durée
  //On utilise 343 mètres par secondes comme vitesse du son
  
  distance = (duration / 2) * 0.0343;
  Serial.print("La distance est egale a : ");
  
  if (distance >= 400 || distance <= 2) {
     Serial.println("Hors de portee.");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm.");
    
    Serial.print("Le temps de reponse est de : ");
    Serial.print(duration);
    Serial.println(" microsecondes.");
    
    if(distance <= 100)
    {
      analogWrite(motor, 255);
    }
    else
    {
      analogWrite(motor, 0);
    }
    
    delay(500);
  }
}
