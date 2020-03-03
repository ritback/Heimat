
import java.util.Iterator;

/*
// KeyBoard Control :

// 1 = mode1;
// 2 = mode2;
// 3 = mode3;
// 4 = mode4;
*/

protected ArrayList<Explosion> fire;

static final int mode1 = 1;
static final int mode2 = 2;
static final int mode3 = 3;
static final int mode4 = 4;
static final int mode5 = 5;

static int modeSelected = 1;

FWRadioButtons mRadioButtons;


// ==================================================
// setup() & draw()
// ==================================================
void setup()
{
  // Size of applet
  size(512, 512);//size(640, 480);
  frameRate(60);
  background(0);
  
  mRadioButtons = new FWRadioButtons(5, 5, width/4, height/20, 5);
  mRadioButtons.render();
  fire = new ArrayList<Explosion> ();
}

void draw()
{
  background(25);
  drawAllExplosion();
  pushStyle();
  mRadioButtons.render();
  popStyle();
}


// ==================================================
// draw All the explosion in the vector.
// ==================================================
void drawAllExplosion () {
  
  Iterator<Explosion> it = fire.iterator();
  while (it.hasNext()) {
    Explosion explosion = it.next ();
    if (explosion.isLinesVisible())
    {
      explosion.drawOneLoopExplosion ();
      if (!explosion.isStillActive()) // diminue la vitesse..
        explosion.makeLinesDisapear ();
    }
  }
  
  // remove all object that are unvisible
  for (int i = 0; i<fire.size(); i++){
    if (!(fire.get(i)).isLinesVisible())
    {
      fire.remove(i);
    }
  }
  
}

// -----------------------------------------
// -----------------------------------------
// Event
// -----------------------------------------
void mouseClicked()
{
  if (!mRadioButtons.onClick(mouseX, mouseY))
    fire.add(new Explosion (mouseX, mouseY));
}


void keyPressed()
{
  if (key == '1')
  {
    modeSelected = mode1;
  }
  else if (key == '2')
  {
    modeSelected = mode2;
  }
  else if (key == '3')
  {
    modeSelected = mode3;
  }
  else if (key == '4')
  {
    modeSelected = mode4;
  }
  else if (key == '5')
  {
    modeSelected = mode5;
  }
  
}






// -----------------------------------------
// -----------------------------------------
// Class declaration & implemantation
// -----------------------------------------
class Explosion
{
  
  protected int lineNumber;
  protected ArrayList<ELine> lines;
  protected float disapearingInc;
  
  // -----------------------------------------
  // -----------------------------------------
  public Explosion (int _centerX, int _centerY)
  {
    lineNumber = (int) random(360,450);
    lines = new ArrayList<ELine> ();
    disapearingInc = 2.5;
    
    for (int i = 0; i < lineNumber; i++)
    {
      ELine newLine = new ELine (_centerX, _centerY);
      // réglage de nos lignes. (les paramêtre standards rendent très bien).
      switch(modeSelected)
      {
      case mode1:
        // position and dinamics
        newLine.accelerationOfTail = 0.1;
        newLine.accelerationOfHead = -0.4;
        //newLine.speedAtStart = 15;
        newLine.speedOfTail = random (5,10);
        //newLine.setDirectionRange(-PI/2,PI/2);
        
        // new appearance
        //newLine.setAlpha(255.f);
        newLine.alphaInc = -1;
        newLine.lineWidth = random (0,5);
        newLine.lineWidthInc = 0.01;
        break;
        
      case mode2:
        break;
      
      case mode3:
        // position and dinamics
        newLine.accelerationOfTail = 0.3;
        newLine.accelerationOfHead = -0.4;
        newLine.speedOfTail = random(0,3);
        
        // new appearance
        newLine.setAlpha(255.f);
        break;
        
      case mode4 :
        // position and dinamics
        newLine.accelerationOfTail = 0.3;
        newLine.accelerationOfHead = -0.4;
        //newLine.speedAtStart = 15;
        newLine.speedOfTail = random(0,3);
        //newLine.setDirectionRange(-PI/2,PI/2);
        
        // new appearance
        newLine.setAlpha(150);
        newLine.alphaInc = -15;
        newLine.lineWidthInc = 7;
        break;
      
      case mode5 :
        // position and dinamics
        newLine.accelerationOfTail = 0.1;
        newLine.accelerationOfHead = -0.4;
        //newLine.speedAtStart = 15;
        newLine.speedOfTail = random (5,10);
        newLine.setDirectionRange(-PI/2,PI/2);
        
        // new appearance
        //newLine.setAlpha(255.f);
        newLine.alphaInc = -1;
        newLine.lineWidth = random (0,5);
        newLine.lineWidthInc = 0.01;
        break;
      }
      
      // add the new line
      lines.add(newLine);
    }
    
  }
  
  public void drawOneLoopExplosion ()
  {
    Iterator<ELine> it = lines.iterator();
    ELine lineIt;
    
    while (it.hasNext()) {
      lineIt = it.next();
      lineIt.drawOneLoopELine();
    }
  }
  
  public void makeLinesDisapear ()
  {
    Iterator<ELine> it = lines.iterator();
    ELine lineIt;
    while (it.hasNext()) {
      lineIt = it.next();
      lineIt.setAlpha(alpha(lineIt.lineColor) - disapearingInc);
    }
  }
  
  public boolean isLinesVisible ()
  {
    boolean isLineVisible = false;
    Iterator<ELine> it = lines.iterator();
    ELine lineIt;
    while (it.hasNext() && !isLineVisible) {
      lineIt = it.next();
      if (alpha(lineIt.lineColor) != 0)
        isLineVisible = true;
    }
    return isLineVisible;
  }
  
  public boolean isStillActive ()
  {
    // la fin d'activité est quand toutes les lignes sont arrétées
    boolean isLinesActive = true;
    Iterator<ELine> it = lines.iterator();
    ELine lineIt;
    while (it.hasNext() && isLinesActive) {
      lineIt = it.next();
      isLinesActive = isLinesActive && lineIt.isStillActive();
    }
    return isLinesActive;
  }
  
  
  
}



// -----------------------------------------
// -----------------------------------------
// Class declaration & implemantation
// -----------------------------------------
class ELine
{
  // line position
  // -------------
  // position du centre
  protected float centerX;  /// choose by user
  protected float centerY;  /// choose by user
  // taille de la ligne
  protected float maxRadiusHeadAtStart;
  protected float minRadiusTailAtStart; /// random at setup or choose by user
  protected float lineRadiusHead;
  protected float lineRadiusTail; /// can be fix independantly by user
  // direction
  protected float lineDirectionRangeMax;  /// random at setup or choose by user
  protected float lineDirectionRangeMin; /// random at setup or choose by user
  protected float lineTetaDirection;  /// can be fix independantly by user
  
  // line Activity
  // -------------
  protected boolean stillActive;
  
  // line evolution
  // --------------
  public float speedAtStart; /// random at setup or choose by user
  protected float speedOfHead; // Speed of the head of the line, random at setup
  public float speedOfTail; // Speed of the back of the line, random at setup
  public float accelerationOfHead; // have to be fix to have a cool effect  /// can be changed independantly by user in loop
  public float accelerationOfTail; // have to be fix to have a cool effect  /// can be changed independantly by user in loop
  
  // line appearance
  // ---------------
  public float lineWidth; /// random at setup or choose by user
  public float lineWidthInc; /// width will be incremented whith this incrementor
  protected float alpha;
  public float alphaInc; /// alpha will be incremented whith this incrementor
  public color lineColor; /// random at setup or choose by user
  
  
  
  
  // -----------------------------------------
  // -----------------------------------------
  public ELine (int _centerX, int _centerY)
  {
    // line position
    centerX = _centerX;
    centerY = _centerY;
    
    // line Size
    maxRadiusHeadAtStart = 35;
    minRadiusTailAtStart = 0;
    lineRadiusHead = random (maxRadiusHeadAtStart/2, maxRadiusHeadAtStart);
    lineRadiusTail = random (minRadiusTailAtStart, maxRadiusHeadAtStart/3);
    
    // line direction
    setDirectionRange (0, 2*PI);
    
    // line activity
    stillActive = true;
    
    // line evolution
    speedAtStart = random (0, 15);
    speedOfHead = random (speedAtStart/2, speedAtStart);
    speedOfTail = random (0, speedAtStart/2);
    accelerationOfHead = - 0.09; // la vitesse doit ralentir à chaque tour
    accelerationOfTail = 0.1;
    
    // line appearance
    lineWidth = random(1, 4);
    lineWidthInc = random(0.5);
    alpha = 255;
    alphaInc = -speedAtStart/2;
    lineColor = color ((int)random(0,255), (int)random(0,255), (int)random(0,255), alpha);
  }
  
  
  // -----------------------------------------
  public void drawOneLoopELine ()
  {
    // mouvement de la tête
    // --------------------
    // évolution de la vitesse
    // la vitesse doit évoluer même si la vitesse est nul
    if (speedOfHead >= 0)
      speedOfHead += accelerationOfHead;
    // on ne veux pas reculer.
    if (speedOfHead > 0)
    {
      // évolution de la position
      lineRadiusHead += speedOfHead;
    }
    else speedOfHead = -1;
    
    
    // mouvement de la queue
    // ---------------------
    // évolution de la vitesse
    // la vitesse doit évoluer même si la vitesse est nul
    if (speedOfTail >= 0)
      speedOfTail += accelerationOfTail;
    if (speedOfTail > 0)
    {
      if (lineRadiusTail < lineRadiusHead)
      {
        // évolution de la position
        lineRadiusTail += speedOfTail;
        lineWidth += lineWidthInc; // évolution de l'apparence
        alpha += alphaInc;
      }
      // éviter les dépassements :
      if (lineRadiusTail > lineRadiusHead) // pas else parce qu'il faut faire le controle après avoir incrémenté la position de la queue
      {
        lineRadiusTail = lineRadiusHead;
      }
    }
    else speedOfTail = -1;
    
    // line activity
    if (speedOfHead == -1)
      if (lineRadiusTail == lineRadiusHead)
        stillActive = false;
    
    // dessin réel
    lineColor = color (red(lineColor),green(lineColor),blue(lineColor),alpha);
    smooth();
    stroke(lineColor);
    strokeWeight(1 + lineWidth);
    
    // convertion coordonées polaire / cartésienne
    float lineHeadX = centerX + lineRadiusHead*cos(lineTetaDirection);
    float lineHeadY = centerY + lineRadiusHead*sin(lineTetaDirection);
    float lineTailX = centerX + lineRadiusTail*cos(lineTetaDirection);
    float lineTailY = centerY + lineRadiusTail*sin(lineTetaDirection);
    
    line(lineHeadX, lineHeadY, lineTailX, lineTailY);
    
  }
  
  
  // -----------------------------------------
  // -----------------------------------------
  // Parameters Acessors
  
  // -----------------------------------------
  // to be call before creation
  public void setDirectionRange (float minRad, float maxRad)
  {
    lineDirectionRangeMax = maxRad;
    lineDirectionRangeMin = minRad;
    lineTetaDirection = random(lineDirectionRangeMin, lineDirectionRangeMax);
  }
  
  // -----------------------------------------
  // to be call before creation
  public void setMaxRadiusHeadAtStart (float maxRadius)
  {
    maxRadiusHeadAtStart = maxRadius;
    lineRadiusHead = random (maxRadiusHeadAtStart/2, maxRadiusHeadAtStart);
    lineRadiusTail = random (0, maxRadiusHeadAtStart/3);
  }
  
  // -----------------------------------------
  // to be call before creation
  public void setMaxHeadRadius (float headRadius)
  {
    maxRadiusHeadAtStart = headRadius;
    lineRadiusTail = random (minRadiusTailAtStart, maxRadiusHeadAtStart/3);
  }
  
  public void setMinTailRadius (float tailRadius)
  {
    minRadiusTailAtStart = tailRadius;
    lineRadiusTail = random (minRadiusTailAtStart, maxRadiusHeadAtStart/3);
  }
  
  // -----------------------------------------
  public void setAlpha (float newAlpha)
  {
     alpha = newAlpha;
     lineColor = color (red(lineColor),green(lineColor),blue(lineColor),alpha);
  }
  
  public boolean isStillActive ()
  {
    if (stillActive)
       return true;
    return false; 
  }
  
}





class FWRadioButtons
{
  float mPosX, mPosY;
  float mWidth, mHeight;
  protected ArrayList<FWRadioButton> mButtons;
  
  public FWRadioButtons(float inPosX, float inPosY, float inWidth, float inHeight, int inNbrOfButton)
  {
    mPosX = inPosX;
    mPosY = inPosY;
    mWidth = inWidth;
    mHeight = inHeight;
    
    float buttonSize = inWidth/5;
    mButtons = new ArrayList<FWRadioButton>();
    
    for (int i=0; i<inNbrOfButton; ++i)
    {
      mButtons.add(new FWRadioButton(i*buttonSize + mPosX, mPosY, buttonSize, mHeight));
    }
    Iterator<FWRadioButton> it = mButtons.iterator();
    (it.next()).mIsSelected = true;
  }
  
  public void render()
  {
    Iterator<FWRadioButton> it = mButtons.iterator();
    while (it.hasNext())
    {
      FWRadioButton button = it.next ();
      button.render();
    }
  }
  
  public boolean onClick(int inX, int inY)
  {
    Iterator<FWRadioButton> it = mButtons.iterator();
    int i = 0;
    while (it.hasNext())
    {
      FWRadioButton button = it.next ();
      if (button.isIn(inX, inY))
      {
        modeSelected = i+1;
        unselectAll();
        button.mIsSelected = true;
        return true;
      }
      i++;
    }
    return false;
  }
  
  public void unselectAll()
  {
    Iterator<FWRadioButton> it = mButtons.iterator();
    while (it.hasNext())
    {
      FWRadioButton button = it.next ();
      button.mIsSelected = false;
    }
  }
}



class FWRadioButton
{
  float mPosX, mPosY;
  float mWidth, mHeight;
  boolean mIsSelected;
  color mSelectedColor;
  color mUnselectedColor;
  
  public FWRadioButton(float inPosX, float inPosY, float inWidth, float inHeight)
  {
    mPosX = inPosX;
    mPosY = inPosY;
    mWidth = inWidth;
    mHeight = inHeight;
    mIsSelected = false;
    mSelectedColor = color(255, 255, 255, 150);
    mUnselectedColor = color(255, 255, 255, 50);
  }
  
  public void render()
  {
    pushStyle();
    strokeWeight(1);
    stroke(255);
    if (mIsSelected)
    {
      fill(mSelectedColor);
    }
    else
    {
      fill(mUnselectedColor);
    }
    
    rect(mPosX, mPosY, mWidth, mHeight);
    popStyle();
  }
  
  public boolean isIn(int inX, int inY)
  {
    if (inX >= mPosX && inX <= mPosX+mWidth && 
        inY >= mPosY && inY <= mPosY+mHeight)
    {
        return true;
    }
    else
    {
      return false;
    }
  }
  
}