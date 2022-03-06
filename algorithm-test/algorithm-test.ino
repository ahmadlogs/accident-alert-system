//--------------------------------------------------------------
#define xPin A1
#define yPin A2
#define zPin A3
//--------------------------------------------------------------
// Take multiple samples to reduce noise
const int samples = 10;
//--------------------------------------------------------------

void setup() 
{
  Serial.begin(115200);
}


void loop() 
{
  //--------------------------------------------------------------
  //Read raw values
  int xRaw=0,yRaw=0,zRaw=0;
  for(int i=0;i<samples;i++)
  {
    xRaw+=analogRead(xPin);
    yRaw+=analogRead(yPin);
    zRaw+=analogRead(zPin);
  }
  xRaw/=samples;
  yRaw/=samples;
  zRaw/=samples;
  //--------------------------------------------------------------
  Serial.print(xRaw);
  Serial.print("\t");
  Serial.print(yRaw);
  Serial.print("\t");
  Serial.print(zRaw);
  Serial.println();
  //--------------------------------------------------------------
  delay(200);
}
