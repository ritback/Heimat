
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