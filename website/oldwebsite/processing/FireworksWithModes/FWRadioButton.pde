

class FWRadioButtons
{
  float mPosX, mPosY;
  float mWidth, mHeight;
  FWRadioButton mButton1;
  FWRadioButton mButton2;
  FWRadioButton mButton3;
  FWRadioButton mButton4;
  FWRadioButton mButton5;
  
  public FWRadioButtons(float inPosX, float inPosY, float inWidth, float inHeight)
  {
    mPosX = inPosX;
    mPosY = inPosY;
    mWidth = inWidth;
    mHeight = inHeight;
    
    float buttonSize = inWidth/5;
    mButton1 = new FWRadioButton((int)(0*buttonSize) + mPosX, mPosY, buttonSize, mHeight);
    mButton2 = new FWRadioButton((int)(1*buttonSize) + mPosX, mPosY, buttonSize, mHeight);
    mButton3 = new FWRadioButton((int)(2*buttonSize) + mPosX, mPosY, buttonSize, mHeight);
    mButton4 = new FWRadioButton((int)(3*buttonSize) + mPosX, mPosY, buttonSize, mHeight);
    mButton5 = new FWRadioButton((int)(4*buttonSize) + mPosX, mPosY, buttonSize, mHeight);
    
    mButton1.mIsSelected = true;
  }
  
  public void render()
  {
    mButton1.render();
    mButton2.render();
    mButton3.render();
    mButton4.render();
    mButton5.render();
  }
  
  public boolean onClick(int inX, int inY)
  {
    if (mButton1.isIn(inX, inY)) {modeSelected = 1; unselectAll(); mButton1.mIsSelected = true; return true;}
    else if (mButton2.isIn(inX, inY)) {modeSelected = 2; unselectAll(); mButton2.mIsSelected = true; return true;}
    else if (mButton3.isIn(inX, inY)) {modeSelected = 3; unselectAll(); mButton3.mIsSelected = true; return true;}
    else if (mButton4.isIn(inX, inY)) {modeSelected = 4; unselectAll(); mButton4.mIsSelected = true; return true;}
    else if (mButton5.isIn(inX, inY)) {modeSelected = 5; unselectAll(); mButton5.mIsSelected = true; return true;}
    return false;
  }
  
  public void unselectAll()
  {
    mButton1.mIsSelected = false;
    mButton2.mIsSelected = false;
    mButton3.mIsSelected = false;
    mButton4.mIsSelected = false;
    mButton5.mIsSelected = false;
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