const int pins[7] = {3,5,6,7,9,11,12};
const int BP=2; // broche du bouton poussoir
int i;
int lancer=0;
const int APPUI=0; // etat du BP
int ETAT_BP=0;
byte light [7] [7] = {
{0,0,0,0,0,0,0},
{0,0,0,1,0,0,0},
{1,0,0,0,0,0,1},
{1,0,0,1,0,0,1},
{1,0,1,0,1,0,1},
{1,0,1,1,1,0,1},
{1,1,1,0,1,1,1}
};
void setup ()
{
//configuration des broches en sortie
for (int i=0;i<7;i++)
{
pinMode(pins[i], OUTPUT);
}
pinMode(BP,INPUT);
// broche en entree
digitalWrite(BP,HIGH); // active le rappel au plus interne
}
void loop ()

{
ETAT_BP=digitalRead(BP); // lit et memorise la valeur du bp
if (ETAT_BP==APPUI) // SI ON APPUIE SUR LE BP
{
for (int i=0; i<7; i++)
{
digitalWrite(pins[i],light [0][i]);
}
lancer = random(1,7);
for (int j=0; j<7; j++)
{
digitalWrite(pins[j],light [lancer][j]);
}
delay(1000);
}
}