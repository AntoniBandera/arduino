#include <servo.h>
//TM4C123GPM    podlacz sterwoanie serva do pinu numer 7 - czyli PB4
//jesli chcesz podlaczyc LED Green jest on na 39 - czyli PF3
Servo serwomechanizm;  //Tworzymy obiekt, dzięki któremu możemy odwołać się do serwa 
int pozycja = 0; //Aktualna pozycja serwa 0-180
int zmiana = 6; //Co ile ma się zmieniać pozycja serwa?


void setup() 
{ 
      serwomechanizm.attach(7);  //Serwomechanizm podłączony do pinu 9
} 
 
 void loop() 
 {  
       if (pozycja < 180) { //Jeśli pozycja mieści się w zakresie
        serwomechanizm.write(pozycja); //Wykonaj ruch
       } else { //Jeśli nie, to powrót na początek
         pozycja = 0;
       }    
                         
       pozycja = pozycja + zmiana; //Zwiększenie aktualnej pozycji serwa
       delay(200); //Opóźnienie dla lepszego efektu                        
 }

