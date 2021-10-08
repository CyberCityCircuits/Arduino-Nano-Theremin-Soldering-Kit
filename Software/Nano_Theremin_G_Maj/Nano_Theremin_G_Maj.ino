
int col_5   =  2; //LED Matrix - Column 5
int col_4   =  3; //LED Matrix - Column 4
int col_3   =  4; //LED Matrix - Column 3
int speaker =  5; //Speaker
int trigPin =  6; //Ultrasonic Trig Pin
int echoPin =  7; //Ultrasonic Echo Pin
int col_2   = 14; //LED Matrix - Column 2
int col_1   = 15; //LED Matrix - Column 1
int row_4   = 16; //LED Matrix - Row 4
int row_3   = 17; //LED Matrix - Row 4
int row_2   = 18; //LED Matrix - Row 2
int row_1   = 19; //LED Matrix - Row 1

// defines variables
long duration; // variable for the duration of sound wave travel
float distance;  // variable for the distance measurement
float min_dist =  2.0;
float max_dist = 30.0;
float step_note = (max_dist-min_dist)/20;
int play_note;
int wait = 50;

int led_1[] = {col_1, row_1};

int leds[][2] = {{col_1, row_1},{col_1, row_2},{col_1, row_3},{col_1, row_4},
                 {col_2, row_1},{col_2, row_2},{col_2, row_3},{col_2, row_4},
                 {col_3, row_1},{col_3, row_2},{col_3, row_3},{col_3, row_4},
                 {col_4, row_1},{col_4, row_2},{col_4, row_3},{col_4, row_4},
                 {col_5, row_1},{col_5, row_2},{col_5, row_3},{col_5, row_4}};

//define notes
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319

int notes[] = {NOTE_A1,  NOTE_A1, NOTE_B1,  NOTE_C2,
               NOTE_C2, NOTE_D2,  NOTE_D2, NOTE_E2,
               NOTE_E2,  NOTE_FS2, NOTE_G2,  NOTE_G2, 
               NOTE_A2,  NOTE_A2, NOTE_B2,  NOTE_C3,
               NOTE_C3, NOTE_D3,  NOTE_D3, NOTE_E3};

void setup() {
  Serial.begin(9600);       //Start Serial Communication
  Serial.println("Aruino Nano Chromatic Theremin");
  
  pinMode(trigPin, OUTPUT); //Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  //Sets the echoPin as an INPUT

  pinMode(col_1, OUTPUT);
  pinMode(col_2, OUTPUT);
  pinMode(col_3, OUTPUT);
  pinMode(col_4, OUTPUT);
  pinMode(col_5, OUTPUT);
  pinMode(row_1, OUTPUT);
  pinMode(row_2, OUTPUT);
  pinMode(row_3, OUTPUT);
  pinMode(row_4, OUTPUT);

  digitalWrite(col_1, HIGH);
  digitalWrite(col_2, HIGH);
  digitalWrite(col_3, HIGH);
  digitalWrite(col_4, HIGH);
  digitalWrite(col_5, HIGH);
  digitalWrite(row_1, LOW);
  digitalWrite(row_2, LOW);
  digitalWrite(row_3, LOW);
  digitalWrite(row_4, LOW);

}

void loop() {
  ultrasonic();
  play_note = (distance/step_note) - 5;
  if (play_note > 20){
    play_note = 20;
  }
  if (play_note < 0){    play_note = 0;
  }
   play_tone();
  
}


void ultrasonic(){
  digitalWrite(trigPin, LOW); // Clears the trigPin condition
  delayMicroseconds(2);       // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //Displays the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm"); 
}

void light_led(int led){
  //To light - col = LOW, row = HIGH
  int row = leds[led][0];
  int col = leds[led][1];
  digitalWrite(col, LOW);
  digitalWrite(row, HIGH);
  delay(10);
  digitalWrite(col, HIGH);
  digitalWrite(row, LOW);
  delay(10);
}

void play_tone(){
  Serial.print(" Note Array Index: "); Serial.print(play_note);
  Serial.print(" Note Value: ");       Serial.print(notes[play_note]);
  Serial.print(" Distance: ");         Serial.println(distance);
  tone(speaker, notes[play_note], wait + 20);
  digitalWrite(leds[play_note][0], LOW);   digitalWrite(leds[play_note][1], HIGH); delay(wait);
  digitalWrite(leds[play_note][0], HIGH);  digitalWrite(leds[play_note][1], LOW);  //delay(wait);
  
}
