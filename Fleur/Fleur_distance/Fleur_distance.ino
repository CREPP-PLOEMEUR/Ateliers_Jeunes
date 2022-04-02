// Programme Arduino: Fleur commandée par capteur de distance

//....Inclusion de librairie....

#include <Servo.h> // inclut la librairie Servo
#include <Utils.h> // inclut la librairie Utils, librairie personnelle avec plusieurs fonctions utiles
//__________________________________________________________
//....Entete déclarative = variables et constantes globales
//__________________________________________________________

//...Constantes de paramétrage du servomoteur

const int posMin=550; //largeur impulsion en µs correspondant à la position 0° du servomoteur
const int posMax=2350; // largeur impulsion en µs correspondant à la position 180° du servomoteur

const int brocheServo=2; // broche du servomoteur
Servo servo; // déclaration d'un objet servomoteur
int angleServo=0; //variable de position du servomoteur
int angleServo0=0; // variable pour mémoriser la dernière position du servomoteur
int vitesse=40; // vitesse de positionnement entre 2 pas - en ms - entre 5 et 100 ms

// Variables et constantes pour le GP2D12

const int GP2D12=A0; // déclaration constante de broche analogique
float MesureMv=0.0;// mesure broche en mVolts

//...déclaration des variables globales

int mesureBrute=0;  // variable pour acquisition résultat brut de conversion analogique-numérique






void setup()  {  // la fonction setup() exécutée au début et une seul fois

  
  angleServo=45;
  servo.attach(brocheServo,posMin,posMax); // attache le servomoteur à la broche et initialisation des positions extremes
  servo.write(angleServo); // positionne le servomoteur à l'angle voulu - initial=45°
  angleServo0=angleServo; // mémorise la position courante du servomoteur
  
} // fin de la fonction setup()



void loop()  {  // La fonction loop() éxécutée en boucle sans fin

    int nbmoy=50;
    long cumul=0;
    int moyenne =0;

  for(int i=0;i<=nbmoy;i++) {
  
    mesureBrute=analogRead(GP2D12);  // acquisition conversion analogique-numérique (CAN) sur la voie analogique
    MesureMv=mesureBrute*(5000/1023);
  
    delay (5);
  
    cumul = cumul +MesureMv;

} // fin de for

    moyenne =cumul/nbmoy;
   




    //positionnement du servo
  
  if (moyenne>2500)  {
    
    moyenne = 2500;
  } 
  else {
    if (moyenne<200) {
    
     moyenne=200 ;
      
    }
      else {
    angleServo= map (moyenne,200,2500,1,92);
    servoTo (servo,angleServo0,angleServo,vitesse);
  } // fin de else
    
  angleServo0=angleServo;
  }

  
}  // fin de la fonction loop



 







//... Fonction de positionnement progressif du servomoteur pas à pas fixe de n degrés...

void servoTo(Servo toServo, int fromAngle, int toAngle, int toVitesse)  {
  
    int delta=toAngle-fromAngle;  // variation d'angle
   // Serial.print(F("delta=")), Serial.println(delta);
    
    if (delta>=0)  {  // si variation positive
    for (int i=0; i<delta; i++) {  // défile n positions pour atteindre l'angle final dans sens positif
    
    fromAngle=fromAngle+1;  // ajoute 1 cran
    toServo.write(fromAngle); // crée une impulsion à partir valeur angle plus précis que write()
   // Serial.print("angle courant servo=");
    //Serial.println(fromAngle);
    delay(toVitesse); // pause entre chaque positionnement
    
    } // fin de for
    
  }  // fin de if
  
    else {  // si variation négative
    for (int i=-delta; i>0; i--)  {  // defile n positions pour atteindre angle final dans sens négatif
    fromAngle=fromAngle-1;  // ajoute 1 cran
    toServo.write(fromAngle);  // crée impulsion à partir valeur angle - plus précis que write()
    //Serial.print("angle courant servo=");
    //Serial.println(fromAngle);
    delay(toVitesse);  // pause entre chaque positionnement
    
    } // fin de for
    
  } // fin de else
  
} // fin de la fonction servoTo



