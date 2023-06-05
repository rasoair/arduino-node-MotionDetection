#define PIR_MOTION_SENSOR 3 // Use pin 3 to receive the signal from the module
#define SPEAKER 4
char trans[20];
int isDetect;
#define NOTE_A 440
#define NOTE_D 587
#define NOTE_E 659
#define NOTE_Fs 739
#define NOTE_A2 880

// 以下は某コンビニエンスストアやインターフォンでお馴染みのメロディーです
int melody[] = {NOTE_Fs, NOTE_D, NOTE_A, NOTE_D, NOTE_E, NOTE_A2, NOTE_A, NOTE_E, NOTE_Fs, NOTE_E, NOTE_A, NOTE_D};
float duration[] = {1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 4};

void setup()
{
  pinMode(PIR_MOTION_SENSOR, INPUT);
  pinMode(SPEAKER, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  if (digitalRead(PIR_MOTION_SENSOR))
  {
    Serial.println("Detected");
    isDetect = 1;
    delay(500); // for 500ms
    for (int x = 0; x < 12; x++)
    {
      tone(SPEAKER, melody[x]);
      delay(300 * duration[(x % 100)]);
      noTone(SPEAKER);
    }
  }
  else
  {
    Serial.println("Watching");
    isDetect = 0;
    delay(500);
  }
  memset(trans, 0, 20);
  char *json = &trans[0];
  sprintf(json, "{\"isDetected\":%d}", isDetect);
  Serial.println(json);
  delay(2000); // for 2000ms
}