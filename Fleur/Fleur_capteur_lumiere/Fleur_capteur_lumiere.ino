// Programme Arduino : Fleur commandee par photoresistance


//---- inclusion de librairie
#include <Servo.h> // inclut la librairie Servo

//--- entete déclarative = variables et constantes globales

int mesureBrute=0;// Variable pour acquisition résultat brut de conversion analogique numérique
int seuil=800; // Variable fixant le seuil de détection de l'obscurité - à adapter

const int photoR=A0; //declaration constante de broche analogique

//----- constantes de paramétrage du servomoteur

const int posMin=550; // largeur impulsion en μs correspondant à la position 0° du servomoteur
const int posMax=2350; // largeur impulsion en μs correspondant à la position 180° du servomoteur

const int brocheServo=2; // broche du servomoteur
Servo servo; // déclaration d'un objet servomoteur
int angleServo=0; // variable de position du servomoteur
int angleServo0=0; // variable pour mémoriser la dernière position du servomoteur
int vitesse=50; // vitesse de positionnement entre 2 pas - en ms - entre 5 et 100ms

void setup() {//--- la fonction setup() : exécutée au début et 1 seule fois
//Serial.begin(115200); // initialise la vitesse de la connexion série

//-- utilise la meme vitesse dans le Terminal Série
servo.attach(brocheServo, posMin, posMax); // attache le servomoteur à la broche

// et initialisation des positions extremes
servo.write(angleServo); // positionne le servomoteur à l'angle voulu - initial =0°
angleServo0=angleServo; // mémorise la position courante du servomoteur

} // fin de la fonction setup()

void loop() { //--- la fonction loop() : exécutée en boucle sans fin

        // acquisition conversion analogique-numerique (CAN) sur la voie analogique
	mesureBrute=analogRead(photoR);

if (mesureBrute <= 200) {
    angleServo=50;


	servoTo(servo, angleServo0, angleServo, vitesse);
	angleServo0=angleServo; // mémorise la nouvelle position
	delay(100); // pause

	
	} // fin if

	else { 
                 angleServo=135;
                 
                 servoTo(servo, angleServo0, angleServo, vitesse);
	angleServo0=angleServo; // mémorise la nouvelle position

	delay(100); // laisse le temps au caractères d'arriver

		} // fin else
	
} // fin de la fonction loop()

//--- fonction de positionnement progressif du servomoteur par pas fixe de n degrés-----

void servoTo( Servo toServo, int fromAngle, int toAngle, int toVitesse ) {

	int delta=toAngle-fromAngle; // variation d'angle
	Serial.print(F("delta = ")), Serial.println(delta);
	
	if (delta>=0) { // si variation positive
	for (int i=0; i<delta; i++) { // defile n positions pour atteindre angle final dans sens positif

	fromAngle=fromAngle+1; // ajoute cran
	toServo.write(fromAngle); // crée impulsion à partir valeur angle - plus précis que write()
	Serial.print("angle courant servo = "),
	Serial.println(fromAngle);
	delay(toVitesse); // pause entre chaque positionnement
	
	}// fin for
	} // fin if

	else { // si variation négative
	for (int i=-delta; i>0; i--) { // defile n positions pour atteindre angle final dans sens négatif
	fromAngle=fromAngle-1; // ajoute cran
	toServo.write(fromAngle); // crée impulsion à partir valeur angle - plus précis que write()
	Serial.print("angle courant servo = "),
	Serial.println(fromAngle);
	delay(toVitesse); // pause entre chaque positionnement
	
	} // fin for
	} // fin else
} // fin fonction servoTo
