
boolean running = false;


Circles mCircles;
int config;
float rotationAngle;
float rotationAngleInc;

void setup ()
{
  size(512, 512);
  background(255);
  frameRate(60);
  
  rotationAngle = 0;
  rotationAngleInc = 0.01;
  
  mCircles = new Circles(400, 400, 40, 10, 8);
  mCircles.changeConfig(ALIGN_DEMI);
  mCircles.rotateCircles(PI/4);
  
  /*gui();*/
}

void draw ()
{
  if(running)
  {
    background(255);
    pushMatrix();
    translate(50, 50);
    mCircles.rotateCircles(rotationAngle);
    mCircles.render();
    popMatrix();
    
    rotationAngle += rotationAngleInc;
  }
  else
  {
    pushStyle();
    fill(150, 150, 150, 50);
    noStroke();
    rect(0, 0, width, height);
    
    pushMatrix();
    translate(width/2, height/2);
    fill(255, 67, 68);
    float rectSize = width/25;
    rect(-1.5*rectSize, -rectSize,
         3*rectSize, 2*rectSize, width/30);
    fill(255);
    rectSize -= 10;
    translate(-rectSize, 0);
    triangle(0, rectSize, 0, -rectSize, 2*rectSize, 0);
    popMatrix();
    popStyle();
    noLoop();
  }
  
}

void mousePressed() {
  if (!running)
  {
    loop();
  }
  running = !running;
  
}


class Circle
{
  float radius;
  float pointsRadius;
  public int pointsNbr;
  public float xCenter, yCenter;
  public float rotationAngle = 0;
  
  boolean renderConstruction = false;
  boolean renderPointsLinking = false;
  
  public Circle ()
  {
    
  }
  
  public Circle (float x, float y, float r, float pointsSize, int inPointsNbr)
  {
    xCenter = x;
    yCenter = y;
    radius = r;
    pointsRadius = pointsSize;
    pointsNbr = inPointsNbr;
  }
  
  public void render ()
  {
    pushMatrix();
    translate(xCenter, yCenter);
    
    rotate(rotationAngle);
    
    // render construction
    if (renderConstruction)
    {
      stroke (0);
      fill (0,0,0,0);
      ellipse (0, 0, 2*radius, 2*radius);
    }
    
    // render Points linking
    if (renderPointsLinking)
      beginShape();
    
    float pointX, pointY;
    for (int i = 0; i<pointsNbr; i++)
    {
      pointX = radius * cos(radians(90+ i * 360/pointsNbr));
      pointY = radius * sin(radians(90+ i * 360/pointsNbr));
      
      noStroke();
      fill(0);
      ellipse (pointX, pointY, pointsRadius, pointsRadius);
      
      if (renderPointsLinking)
      {
        stroke(0);
        strokeWeight(1);
        noFill();
        vertex(pointX,pointY);
      }
    }
    
    if (renderPointsLinking)
      endShape(CLOSE);
    
    popMatrix();
  }
    
}



// configuration d'alignement des cercles
static final int ALIGN = 1;
static final int ALIGN_DEMILINE = 2;
static final int ALIGN_DEMICOLON = 3;
static final int ALIGN_DEMI = 4;


class Circles
{
  ArrayList<Circle> circles = new ArrayList<Circle> ();
  float dimensionX, dimensionY;
  float circlesRadius;
  float circlesPointsWeight;
  int circlesPointsNbr;
  
  public Circles (float newWidth, float newHeight, float inCirclesRadius, float inPointsWeight, int inCirclesPointsNbr)
  {
    dimensionX = newWidth;
    dimensionY = newHeight;
    circlesRadius = inCirclesRadius;
    circlesPointsWeight = inPointsWeight;
    circlesPointsNbr = inCirclesPointsNbr;
  }
  
  public void changeConfig(int configNbr)
  {
    circles.clear();
    fillWithConfig(configNbr);
  }
  
  private void fillAlign()
  {
    int nbrColon = floor(dimensionX/(2*circlesRadius));
    int nbrLine = floor(dimensionY/(2*circlesRadius));
    for (int line = 0; line<nbrLine; line++) {
      for (int colon = 0; colon<nbrColon; colon++)
      {
        circles.add(new Circle((2*colon+1)*circlesRadius, (2*line+1)*circlesRadius, circlesRadius, circlesPointsWeight, circlesPointsNbr));
      }
    }
  }
  
  private void fillAlignDemiLine()
  {
    int nbrColon = floor(dimensionX/(2*circlesRadius));
    int nbrLine = floor(dimensionY/(circlesRadius)) - 1;
    for (int line = 0; line<nbrLine; line++) {
      for (int colon = 0; colon<nbrColon; colon++)
      {
        circles.add(new Circle((2*colon+1)*circlesRadius, (line+1)*circlesRadius, circlesRadius, circlesPointsWeight, circlesPointsNbr));
      }
    }
  }
  
  private void fillAlignDemiColon()
  {
    int nbrColon = floor(dimensionX/(circlesRadius)) - 1;
    int nbrLine = floor(dimensionY/(2*circlesRadius));
    for (int line = 0; line<nbrLine; line++) {
      for (int colon = 0; colon<nbrColon; colon++)
      {
        circles.add(new Circle((colon+1)*circlesRadius, (2*line+1)*circlesRadius, circlesRadius, circlesPointsWeight, circlesPointsNbr));
      }
    }
  }
  
  private void fillAlignDemi()
  {
    int nbrColon = floor(dimensionX/(circlesRadius)) -1;
    int nbrLine = floor(dimensionY/(circlesRadius)) -1;
    for (int line = 0; line<nbrLine; line++) {
      for (int colon = 0; colon<nbrColon; colon++)
      {
        circles.add(new Circle((colon+1)*circlesRadius, (line+1)*circlesRadius, circlesRadius, circlesPointsWeight, circlesPointsNbr));
      }
    }
  }
  
  private void fillWithConfig(int configNbr)
  {
    switch (configNbr)
    {
      case ALIGN:
        fillAlign();
        break;
      case ALIGN_DEMILINE:
        fillAlignDemiLine();
        break;
      case ALIGN_DEMICOLON:
        fillAlignDemiColon();
        break;
      case ALIGN_DEMI:
        fillAlignDemi();
        break;
    }
  }
  
  public void rotateCircles(float angleRad)
  {
    for (Circle c : circles)
    {
      c.rotationAngle = angleRad;
    }
  }
  
  public void render ()
  {
    /*pushStyle();
    noFill();
    strokeWeight(1);
    stroke(0);
    rect(0, 0, dimensionX, dimensionY);
    popStyle();*/
    for (Circle c : circles)
    {
      c.render();
    }
  }
}