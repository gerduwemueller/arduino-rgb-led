//www.elegoo.com
//2016.12.8

// Definiere PINs
#define PIN_RED  6
#define PIN_GREEN 5
#define PIN_BLUE  3

// Helligkeit der LED
#define BRIGHTNESS 100

// Debug-Ausgabe
#define DEBUG true

// Delay zwischen Farbwechsel
#define delayTime 1000

// Delay beim Fading, 0 um Fading auszuschalten
#define fadingDelay 0

// Farben
int COLOR_RED[]     = {BRIGHTNESS,0,0};
int COLOR_MAGENTA[] = {BRIGHTNESS,0,BRIGHTNESS};
int COLOR_BLUE[]    = {0,0,BRIGHTNESS};
int COLOR_CYAN[]    = {0,BRIGHTNESS,BRIGHTNESS};
int COLOR_GREEN[]   = {0,BRIGHTNESS,0};
int COLOR_YELLOW[]  = {BRIGHTNESS,BRIGHTNESS,0};

// Farbfolge
int *colorChange[] = {
  COLOR_RED  
  ,COLOR_MAGENTA  
  ,COLOR_BLUE
  ,COLOR_CYAN
  ,COLOR_GREEN  
  ,COLOR_YELLOW  
};


/**
 * Setup
 */
void setup()
{

  // Initialisiere serielle Schnittstelle
  if (DEBUG) Serial.begin(9600);
  
  // PINs definieren
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);  
  
}

/**
 * Main Loop
 */
void loop()
{

  int numberOfColors = sizeof(colorChange) / sizeof(colorChange[0]) ; 

  printDebug(String ("=== ") + String("sizeof colorChange=") + String(numberOfColors));    

  if (fadingDelay != 0) {
    setColor(colorChange[0]);    
    delay(delayTime);
  }

  for (int i=0; i<numberOfColors; i++) {    

    printDebug(String("color no=") + String(i));  

    if (fadingDelay == 0) {
      
      setColor(colorChange[i]);    
      delay(delayTime);
      
    } else
    {
  
      if (i < numberOfColors-1 ) {
        setColor(colorChange[i],colorChange[i+1]);
      } else
      {
        setColor(colorChange[i],colorChange[0]);    
      }                            
  
      if (i != numberOfColors) delay(delayTime);
      
    }

  }

}

/**
 * setColor
 */
void setColor(int *color) {

  printDebug(String("Setting red=")
                  + String(color[0])
                  + String(", green=")
                  + String(color[1])
                  + String(", blue=")
                  + String(color[2]));                  

  analogWrite(PIN_RED, color[0]);
  analogWrite(PIN_GREEN, color[1]);
  analogWrite(PIN_BLUE, color[2]);  
  
}


void setColor(int *oldColor, int *newColor) {
  
  printDebug(String("Changing red=")
                  + String(oldColor[0])
                  + String("->")
                  + String(newColor[0])
                  + String(", green=")
                  + String(oldColor[1])
                  + String("->")
                  + String(newColor[1])
                  + String(", blue=")
                  + String(oldColor[2])
                  + String("->")        
                  + String(newColor[2]));        

  int redValue   = oldColor[0];                  
  int greenValue = oldColor[1];                  
  int blueValue = oldColor[2];                 

  for (int i=0; i<=BRIGHTNESS; i++) {

    if (redValue < newColor[0]) redValue++;
    if (redValue > newColor[0]) redValue--;

    if (greenValue < newColor[1]) greenValue++;
    if (greenValue > newColor[1]) greenValue--;

    if (blueValue < newColor[2]) blueValue++;
    if (blueValue > newColor[2]) blueValue--;

    analogWrite(PIN_RED, redValue);
    analogWrite(PIN_GREEN, greenValue);
    analogWrite(PIN_BLUE, blueValue);          
    delay(fadingDelay);
    
  }                 
    
}


void printDebug(String s) {

  if (!DEBUG) return;

  Serial.println(s);  
  
}
