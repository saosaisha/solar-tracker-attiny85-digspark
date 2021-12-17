/*
 * Solar tracker 2 LDR
 * ini untuk membuat solar panel mengikuti sinar matahari
 * arah timur ke barat atau sebaliknya
 * Rangkaian ini mengunakan Attiny85 Digspark
 * https://www.youtube.com/c/Radal05
 * 18 Desember 2021
 */

#include <SoftRcPulseOut.h>
#define NOW 1 
SoftRcPulseOut myservo; 
int pos = 90;   // Posisi awal solar cell
int sens1 = A2; // LRD 1 pin PB4
int sens2 = A3; //LDR 2 pin PB3
int tolerance = 2;// Toleransi bisa kalian setting
 
void setup() 
{ 
  myservo.attach(0);  // attaches the servo on pin PB0 
  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT);
  myservo.write(pos);
  delay(1000); // delay 1 seconds delay while we position the solar cell
  SoftRcPulseOut::refresh(NOW);
}  
 
void loop() 
{ 
  int val1 = analogRead(sens1); // Baca data sensor LDR1
  int val2 = analogRead(sens2); // Baca data sensor LDR2

  if((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
    /*
     * Tidak ada pergerakan bila selisih
     * data LDR1 dengan data LDR2 bila sama atau lebih kecil dari toleransi
     */
  } else {    
    if(val1 > val2)
    {
      pos = --pos;
    }
    if(val1 < val2) 
    {
      pos = ++pos;
    }
  }

  if(pos > 180) { pos = 180; } // reset bila pos melebihi 180
  if(pos < 0) { pos = 0; } // reset bila pos dibawah 0 
  
  myservo.write(pos); // Lakukan penyesuaiya solar cell
  delay(10);//menentukan kecepatan pergerakan per 1 derajat
   SoftRcPulseOut::refresh(NOW);

}
