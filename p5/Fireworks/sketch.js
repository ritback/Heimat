

let fire = [];

// ==================================================
// setup() & draw()
// ==================================================
function setup()
{
  // Size of applet
  createCanvas(512, 512);//createCanvas(640, 480);
  frameRate(60);
  background(0);
  
    fire.add(new Explosion (0, 0));
}

function draw()
{
  background(25);
  drawAllExplosion();
}

// ==================================================
// draw All the explosion in the vector.
// ==================================================
function drawAllExplosion () {
  let i;
  for (i = 0; i < fire.length; i++) {
    var explosion = fire[i];
    if (explosion.isLinesVisible())
    {
      explosion.drawOneLoopExplosion ();
      if (!explosion.isStillActive()) // diminue la vitesse..
        explosion.makeLinesDisapear ();
    }
  }
  
  // remove all object that are unvisible
  for (i = 0; i<fire.length; i++){
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
function mouseClicked()
{
    fire.add(new Explosion (mouseX, mouseY));
}



























// -----------------------------------------
// -----------------------------------------
// Class declaration & implemantation
// -----------------------------------------
function ELine (_centerX, _centerY)
  {

  
    // line position
    this.centerX = _centerX;
    this.centerY = _centerY;

    // line Size
    this.maxRadiusHeadAtStart = 35;
    this.minRadiusTailAtStart = 0;
    this.lineRadiusHead = random (this.maxRadiusHeadAtStart/2, this.maxRadiusHeadAtStart);
    this.lineRadiusTail = random (this.minRadiusTailAtStart, this.maxRadiusHeadAtStart/3);
    
    this.lineDirectionRangeMax = 0;  /// random at setup or choose by user
    this.lineDirectionRangeMin = 0; /// random at setup or choose by user
    this.lineTetaDirection = 0;  /// can be fix independantly by user
    // line activity
    this.stillActive = true;
    
    // line evolution
    this.speedAtStart = random (0, 15);
    this.speedOfHead = random (this.speedAtStart/2, this.speedAtStart);
    this.speedOfTail = random (0, this.speedAtStart/2);
    this.accelerationOfHead = - 0.09; // la vitesse doit ralentir à chaque tour
    this.accelerationOfTail = 0.1;
    
    // line appearance
    this.lineWidth = random(1, 4);
    this.lineWidthInc = random(0.5);
    this.alpha = 255;
    this.alphaInc = -this.speedAtStart/2;
    this.lineColor = color (random(0,255), random(0,255), random(0,255), this.alpha);
  
  
  // -----------------------------------------
    this.drawOneLoopELine = function()
  {
    // mouvement de la tête
    // --------------------
    // évolution de la vitesse
    // la vitesse doit évoluer même si la vitesse est nul
    if (this.speedOfHead >= 0)
      this.speedOfHead += this.accelerationOfHead;
    // on ne veux pas reculer.
    if (this.speedOfHead > 0)
    {
      // évolution de la position
      this.lineRadiusHead += this.speedOfHead;
    }
    else this.speedOfHead = -1;
    
    
    // mouvement de la queue
    // ---------------------
    // évolution de la vitesse
    // la vitesse doit évoluer même si la vitesse est nul
    if (this.speedOfTail >= 0)
      this.speedOfTail += this.accelerationOfTail;
    if (this.speedOfTail > 0)
    {
      if (this.lineRadiusTail < this.lineRadiusHead)
      {
        // évolution de la position
        this.lineRadiusTail += this.speedOfTail;
        this.lineWidth += this.lineWidthInc; // évolution de l'apparence
        this.alpha += this.alphaInc;
      }
      // éviter les dépassements :
      if (this.lineRadiusTail > this.lineRadiusHead) // pas else parce qu'il faut faire le controle après avoir incrémenté la position de la queue
      {
        this.lineRadiusTail = this.lineRadiusHead;
      }
    }
    else this.speedOfTail = -1;
    
    // line activity
    if (this.speedOfHead == -1)
      if (this.lineRadiusTail == this.lineRadiusHead)
        this.stillActive = false;
    
    // dessin réel
    smooth();
    stroke(this.lineColor);
    strokeWeight(1 + this.lineWidth);
    
    // convertion coordonées polaire / cartésienne
    let lineHeadX = this.centerX + this.lineRadiusHead*cos(this.lineTetaDirection);
    let lineHeadY = this.centerY + this.lineRadiusHead*sin(this.lineTetaDirection);
    let lineTailX = this.centerX + this.lineRadiusTail*cos(this.lineTetaDirection);
    let lineTailY = this.centerY + this.lineRadiusTail*sin(this.lineTetaDirection);
    
    line(this.lineHeadX, this.lineHeadY, this.lineTailX, this.lineTailY);
    
  };
  
  
  // -----------------------------------------
  // -----------------------------------------
  // Parameters Acessors
  
  // -----------------------------------------
  // to be call before creation
this.setDirectionRange = function ( minRad,  maxRad)
  {
    this.lineDirectionRangeMax = maxRad;
    this.lineDirectionRangeMin = minRad;
    this.lineTetaDirection = random(this.lineDirectionRangeMin, this.lineDirectionRangeMax);
  };
  
    // line direction
    this.setDirectionRange(0, 2*PI);
    
  // -----------------------------------------
  // to be call before creation
this.setMaxRadiusHeadAtStart = function ( maxRadius)
  {
    this.maxRadiusHeadAtStart = maxRadius;
    this.lineRadiusHead = random (this.maxRadiusHeadAtStart/2, this.maxRadiusHeadAtStart);
    this.lineRadiusTail = random (0, this.maxRadiusHeadAtStart/3);
  };
  
  // -----------------------------------------
  // to be call before creation
this.setMaxHeadRadius = function ( headRadius)
  {
    this.maxRadiusHeadAtStart = headRadius;
    this.lineRadiusTail = random (this.minRadiusTailAtStart, this.maxRadiusHeadAtStart/3);
  };
  
this.setMinTailRadius = function ( tailRadius)
  {
    this.minRadiusTailAtStart = tailRadius;
    this.lineRadiusTail = random (this.minRadiusTailAtStart, this.maxRadiusHeadAtStart/3);
  };
  
  // -----------------------------------------
this.setAlpha = function ( newAlpha)
  {
     this.alpha = newAlpha;
     this.lineColor = color (red(lineColor),green(lineColor),blue(lineColor),alpha);
  };
  
this.isStillActive = function  ()
  {
    if (this.stillActive)
       return true;
    return false; 
  };
}






// -----------------------------------------
// -----------------------------------------
// Class declaration & implemantation
// -----------------------------------------
function Explosion (_centerX, _centerY)
{
  
     let liiines = {};
  
    this.lineNumber = random(360,450);
    this.disapearingInc = 2.5;

    for (let i = 0; i < this.lineNumber; i++)
    {
      let newLine = new ELine (_centerX, _centerY);
        
      // réglage de nos lignes. (les paramêtre standards rendent très bien).
      
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
        
        liiines.add(newLine);
    }
    this.lines = liiines;

this.drawOneLoopExplosion = function  ()
  {
    for (let i = 0; i < this.lines.length; i++) {
      this.lines[i].drawOneLoopELine();
    }
  };
  
this.makeLinesDisapear = function  ()
  {
   for (let i = 0; i < this.lines.length; i++)  {
      this.lines[i].setAlpha(alpha(lines[i].lineColor) - this.disapearingInc);
    }
  };
  
this.isLinesVisible = function  ()
  {
    let isLineVisible = false;
    for (let i = 0; i < this.lines.length; i++) {
        if (!isLineVisible)
            {
                if (alpha(this.lines[i].lineColor) != 0)
                isLineVisible = true;
            }
        else {break;}
    }
    return isLineVisible;
  };
  
this.isStillActive = function  ()
  {
    // la fin d'activité est quand toutes les lignes sont arrétées
    let isLinesActive = true;
    for (let i = 0; i < this.lines.length; i++) {
        if(isLinesActive) {
        isLinesActive = isLinesActive && this.lines[i].isStillActive();
        }
        else {break;}
    }
    return isLinesActive;
  };
  
  
  
}
