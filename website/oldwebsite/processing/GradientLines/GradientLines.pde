
float r = sqrt(2)*(256/2);
float angleStart = 0;
float angleInc = 0.7;
int lineNbr = 36;
float time = 0;
float timeInc = 1;
int endX, endY;

void setup ()
{
  size(256, 256);
  frameRate(60);
  background(0);
}

void draw()
{
  translate(width/2, height/2);
  
  colorMode(HSB, 100);
  float angle = angleStart;
  while(angle < angleStart+360)
  {
    stroke(angle*100/360, mouseX*40/width + 60, mouseY*40/height + 60);
    
    endX = (int) (r * cos(radians(angle)));
    endY = (int) (r * sin(radians(angle)));
    
    strokeWeight(2);
    line(0, 0, endX, endY);
    angle += 360/lineNbr;
  }
  angleStart = angleStart>(360/lineNbr) ? 0 : angleStart+angleInc;
  
}