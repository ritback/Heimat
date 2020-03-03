


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
    disapearingInc = 0.5;
    
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