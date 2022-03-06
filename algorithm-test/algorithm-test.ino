#include <math.h>
//--------------------------------------------------------------
#define xPin A1
#define yPin A2
#define zPin A3
//--------------------------------------------------------------

byte updateflag;

int xaxis = 0, yaxis = 0, zaxis = 0;
int deltx = 0, delty = 0, deltz = 0;
int vibration = 0, magnitude = 0, sensitivity = 45, devibrate = 75;
double angle;
//Used to run impact routine every 2mS.
unsigned long time1;
//--------------------------------------------------------------



void setup()
{
  //--------------------------------------------------------------
  Serial.begin(9600);
  //--------------------------------------------------------------
  time1 = micros(); 
  //Serial.print("time1 = "); Serial.println(time1);
  //--------------------------------------------------------------
}

void loop()
{
  //--------------------------------------------------------------
  //call impact routine every 2mS
  if (micros() - time1 > 1999) Impact();
  //--------------------------------------------------------------
  if(updateflag > 0) 
  {
    updateflag=0;
    Serial.print("Impact detected!!");
    Serial.print("Magnitude:"); Serial.print(magnitude);
    Serial.print("\t Angle:"); Serial.print(angle, 2);
    Serial.print("\t Car Direction: NaN");
    Serial.println();
  }
  //--------------------------------------------------------------

}


void Impact()
{
  //--------------------------------------------------------------
  /* 
  //Calibration testing. Accelerometer is calibrated correctly x ~0 y ~0 z ~9.8
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");Serial.println("m/s^2 ");
  */
  //--------------------------------------------------------------
  time1 = micros(); // resets time value
  //--------------------------------------------------------------
  int oldx = xaxis; //store previous axis readings for comparison
  int oldy = yaxis;
  int oldz = zaxis;
  
  //Serial.print("current time = "); Serial.print(micros()); Serial.print("\toldx = "); Serial.print(oldx); Serial.print("\toldy = "); Serial.print(oldy); Serial.print("\toldz = "); Serial.println(oldz);
  //--------------------------------------------------------------
  vibration--; // loop counter prevents false triggering. Vibration resets if there is an impact. Don't detect new changes until that "time" has passed.
  //Serial.print("Vibration = "); Serial.println(vibration);
  if(vibration < 0) vibration = 0;                                
  //Serial.println("Vibration Reset!");
  //Serial.println("****************************");
  //--------------------------------------------------------------
  xaxis = analogRead(xPin);
  yaxis = analogRead(yPin);
  zaxis = analogRead(zPin);
  
  //Serial.print("current time = "); Serial.print(micros()); Serial.print("\txaxis = "); Serial.print(xaxis); Serial.print("\tyaxis = "); Serial.print(yaxis); Serial.print("\tzaxis = "); Serial.println(zaxis);
  //Serial.println("****************************");
  //--------------------------------------------------------------
  if(vibration > 0) return;
  //--------------------------------------------------------------
  deltx = xaxis - oldx;                                           
  delty = yaxis - oldy;
  deltz = zaxis - oldz;
  
  //Magnitude to calculate force of impact.
  magnitude = sqrt(sq(deltx) + sq(delty) + sq(deltz));
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  if (magnitude >= sensitivity) //impact detected
  {
    //Values that caused the impact
    Serial.print("Impact Time = "); Serial.print(micros()); Serial.print("\t\tCar Direction = "); 
    Serial.print("oldx = "); Serial.print(oldx); Serial.print("\toldy = "); Serial.print(oldy); Serial.print("\toldz = "); Serial.println(oldz);
    Serial.print("xaxis = "); Serial.print(xaxis); Serial.print("\tyaxis = "); Serial.print(yaxis); Serial.print("\tzaxis = "); Serial.println(zaxis);
    Serial.print("Mag = "); Serial.print(magnitude);
    Serial.print("\tdeltx = "); Serial.print(deltx);
    Serial.print("\tdelty = "); Serial.print(delty);
    Serial.print("\tdeltz = "); Serial.println(deltz);
    //--------------------------------------------------------------
    updateflag=1;
    //////impactDirection = getHeading(magEvent);

    //double X = xaxis - 512; // adjust xaxis reading to +/- 512
    //double Y = yaxis - 512; // adjust yaxis reading to +/- 512

    double X = acos((double) deltx / magnitude);
    double Y = acos((double) delty / magnitude);
    //--------------------------------------------------------------
    Serial.print("X = "); Serial.print(X); Serial.print("Y = "); Serial.println(Y);

    Serial.println("****************************");

    angle = (atan2(Y,X) * 180)/PI; // use atan2 to calculate angle and convert radians to degrees
    angle += 180;                                               
    //--------------------------------------------------------------
    // reset anti-vibration counter
    vibration = devibrate;
    //--------------------------------------------------------------
  }
  else
  {
    //if (magnitude > 15)
      //Serial.println(magnitude);
    //reset magnitude of impact to 0
    magnitude=0;
  }
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
}
