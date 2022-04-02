const byte nb_face = 9;
const byte nb_dos = 3;
const byte pin_face [nb_face] = {1,2,3,4,5,6,7,8,14};
const byte pin_dos [nb_dos] = {9,10,11};


void setup() {   

  for(int i = 0;i<nb_face;i++) {pinMode(pin_face[i], OUTPUT);}
  for(int i = 0;i<nb_dos;i++) {pinMode(pin_dos[i], OUTPUT);}

  for(int i = 0;i<nb_face;i++) {digitalWrite(pin_face[i],1);}
  delay(1000);
  for(int i = 0;i<nb_face;i++) {digitalWrite(pin_face[i],0);}

  
  for(int i = 0;i<nb_dos;i++) {digitalWrite(pin_dos[i],1);}
  delay(1000);
  for(int i = 0;i<nb_dos;i++) {digitalWrite(pin_dos[i],0);}

  
}//fin setup


void loop() {
  
  int led_dos = random(0,3);
  int led_face1 = random(0,9);
  int led_face2 = random(3,6);
  int led_face3 = random(6,9);  
  int delai = random(80,350);

  
  
  digitalWrite(pin_dos[led_dos],HIGH);
  digitalWrite(pin_face[led_face1],HIGH);
  digitalWrite(pin_face[led_face2],HIGH);  
  digitalWrite(pin_face[led_face3],HIGH);
  delay(delai);
  digitalWrite(pin_dos[led_dos],LOW);
  digitalWrite(pin_face[led_face1],LOW);
  digitalWrite(pin_face[led_face2],LOW);  
  digitalWrite(pin_face[led_face3],LOW);
  delay(delai);
  
  
  
  /*int b2 = random(6,9);
  int b3 = random(10,13);
  int delai = random(100,400);

  for(int i=0;i<5;i++) {
    
  digitalWrite(b1, HIGH);                      
  digitalWrite(b2, HIGH);
  digitalWrite(b3, HIGH);
  
  delay(delai);
  
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(b3, LOW);

  delay(delai);



  }//fin for
  */
}//fin loop


