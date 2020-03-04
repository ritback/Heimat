

Flock flock;

ArrayList<Obstacle> obstacles;

  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------

void setup() {
  size(512, 256);
  frameRate(60);
  
  
  flock = new Flock();
  // Add an initial set of boids into the system
  for (int i = 0; i < 150; i++) {
    flock.addBoid(new Boid(width/2,height/2));
  }
  
  obstacles = new ArrayList <Obstacle> ();
  // obstacle à l'intérieur de la vue
  obstacles.add (new Obstacle(new PVector(width/2, height/2), RECT, width, height, IN));
  background(50);
}

void draw() {
    background(50);
    flock.run(obstacles);
  
    for (Obstacle ob : obstacles) {
      ob.render();
    }
}

// Add a new boid into the System
void mousePressed() {
  flock.addBoid(new Boid(mouseX,mouseY));
  
}




// The Flock (a list of Boid objects)
// ----------------------------------

class Flock {
  ArrayList<Boid> boids; // An ArrayList for all the boids

  Flock() {
    boids = new ArrayList<Boid>(); // Initialize the ArrayList
  }

  void run(ArrayList<Obstacle> obstacles) {
    for (Boid b : boids) {
      b.run(boids, obstacles);  // Passing the entire list of boids to each boid individually
    }
  }

  void addBoid(Boid b) {
    boids.add(b);
  }

}


// The Boid class
// --------------


class Boid {

  // dynamics
  // --------
  public PVector location;
  public PVector velocity;
  public PVector acceleration;
  
  public float maxforce;    // Maximum steering force
  public float maxspeed;    // Maximum speed
  
  // shapes and rendering
  // --------------------
  //float r = /*3.0;//*/random(2, 5);; // radius
  public float maxHeight = 20;
  public float boidHeight = random(maxHeight/2, maxHeight);
  public float boidWidth = random(maxHeight/4, maxHeight/3);
  public float decHeight = random(1, boidWidth/3);
  
  public color colorFish = color ((int)random(200,255), (int)random(60,255), (int)random(80,120));
  public color currentColor = color(colorFish);
  public float colorPhase = 0;
  public float colorPhaseInc = random(1);
  
  // constructor
  // -----------
  Boid(float x, float y) {
    acceleration = new PVector(0, 0);

    float angle = random(TWO_PI);
    velocity = new PVector(cos(angle), sin(angle));

    location = new PVector(x, y);
    maxspeed = /*2;//*/random(1.5,2.5);
    maxforce = 0.05; // limitation des forces (pour pas que l'une écrase les autres)
    
  }
  
  // mouvement of the boid
  // ---------------------
  void run(ArrayList<Boid> boids, ArrayList<Obstacle> obstacles) {
    flock(boids); // add flock forces
    interactWithObstacles(obstacles);
    update(); // update the boid location
    borders(); // teleport the boid if he reach a border
    render(); // render the boid
  }
  
  // -----------------------------------------------------------------------------------
  // add a force into the systeme
  // Forces
  void applyForce(PVector force) {
    // We could add mass here if we want A = F / M
    acceleration.add(force);
  }

  
  
  // -----------------------------------------------------------------------------------
  // Method to update location
  // -------------------------
  void update() {
    // Update velocity
    velocity.add(acceleration);
    // Limit speed
    velocity.limit(maxspeed);
    location.add(velocity);
    // Reset accelertion to 0 each cycle
    acceleration.mult(0);
  }



  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // rendering of the boid (draw)
  // ----------------------------
  void render() {
    // Draw a triangle rotated in the direction of velocity
    float theta = velocity.heading2D() + radians(90);
    // heading2D() above is now heading() but leaving old syntax until Processing.js catches up
    
    fill(200, 100);
    stroke(255);
    pushMatrix();
    translate(location.x, location.y);
    rotate(theta);
    
    updateColor ();
    fill(currentColor);
    noStroke();
    
    
    beginShape(QUADS);
    
    vertex(0, -boidHeight/2+decHeight);
    vertex(- boidWidth/2, 0);
    vertex(0, boidHeight/2+decHeight);
    vertex(+boidWidth/2, 0);
    
    
    endShape();
    
    
    /*  
    for (PVector i : previousLocations) {
      ellipse(i.x, i.y, boidWidth, boidWidth);
    }
    */
    
    
    popMatrix();
  }
  
  
  // ------------------------------------------
  protected void updateColor () {
    float inc = 50*sin (colorPhase);
    colorPhase += colorPhaseInc;
    
    currentColor = color (red(colorFish) + inc, green(colorFish) + inc, blue(colorFish) + inc);
  }
  
  
  
  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // Wraparound
  // Les poissons qui sortent du cadre, apparaisse de l'autre coté
  // -------------------------------------------------------------
  void borders() {
    if (location.x < -boidHeight) location.x = width+boidHeight;
    if (location.y < -boidHeight) location.y = height+boidHeight;
    if (location.x > width+boidHeight) location.x = -boidHeight;
    if (location.y > height+boidHeight) location.y = -boidHeight;
  }
  
  
  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // Forces for Flock, part. 1
  // -----------------------------------------------------------------------------------
  // We accumulate a new acceleration each time based on three rules
  // add and calculate all the forces that'll make the flock
  // ---------------------------------------------------------------
  void flock(ArrayList<Boid> boids) {
    // flock forces
    PVector sep = separate(boids);   // Separation
    PVector ali = align(boids);      // Alignment
    PVector coh = cohesion(boids);   // Cohesion
    
    // Arbitrarily weight these forces
    sep.mult(1.5);
    ali.mult(1.0);
    coh.mult(1.0);
    
    // Add the force vectors to acceleration
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
  }
  
  
  
  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // Forces for Flock, part 2.s
  // -----------------------------------------------------------------------------------
  // Separation
  // Method checks for nearby boids and steers away
  PVector separate (ArrayList<Boid> boids) {
    
    float desiredseparation = 25.0f; // séparation de chaque éléments
    PVector steer = new PVector(0, 0, 0);
    int count = 0;
    
    // For every boid in the system, check if it's too close
    for (Boid other : boids) {
      float d = PVector.dist(location, other.location);
      
      // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
      if ((d > 0) && (d < desiredseparation)) {
        // Calculate vector pointing away from neighbor
        PVector diff = PVector.sub(location, other.location);
        diff.normalize();
        diff.div(d);        // Weight by distance
        steer.add(diff);
        count++;            // Keep track of how many
      }
    }
    
    // Average -- divide by how many
    if (count > 0) {
      steer.div((float)count);
    }

    // As long as the vector is greater than 0
    if (steer.mag() > 0) {
      steer.normalize();
      steer.mult(maxspeed);
      // First two lines of code below could be condensed with new PVector setMag() method
      // Not using this method until Processing.js catches up
      // steer.setMag(maxspeed);

      // Implement Reynolds: Steering = Desired - Velocity
      //steer.normalize();
      //steer.mult(maxspeed);
      steer.sub(velocity);
      steer.limit(maxforce);
    }
    
    
    return steer;
  }


  // -----------------------------------------------------------------------------------
  // Alignment
  // For every nearby boid in the system, calculate the average velocity
  
  PVector align (ArrayList<Boid> boids) {
    
    float neighbordist = 50;
    
    PVector sum = new PVector(0, 0);
    int count = 0;
    
    for (Boid other : boids) {
      float d = PVector.dist(location, other.location);
      if ((d > 0) && (d < neighbordist)) {
        sum.add(other.velocity);
        count++;
      }
    }
    
    if (count > 0) {
      sum.div((float)count);
      sum.normalize();
      sum.mult(maxspeed);
      // First two lines of code below could be condensed with new PVector setMag() method
      // Not using this method until Processing.js catches up
      // sum.setMag(maxspeed);

      // Implement Reynolds: Steering = Desired - Velocity
      //sum.normalize();
      //sum.mult(maxspeed);
      PVector steer = PVector.sub(sum, velocity);
      steer.limit(maxforce);
      return steer;
    } 
    else {
      return new PVector(0, 0);
    }
  }



  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // A method that calculates and applies a steering force towards a target
  // (steer = control) (mouvement ordonée du troupeau)
  // STEER = DESIRED MfalseUS VELOCITY
  public PVector seek(PVector target) {
    PVector desired = PVector.sub(target, location);  // A vector pointing from the location to the target
    // Scale to maximum speed
    desired.normalize();
    desired.mult(maxspeed);

    // Above two lines of code below could be condensed with new PVector setMag() method
    // Not using this method until Processing.js catches up
    //desired.setMag(maxspeed);

    // Steering = Desired minus Velocity
    PVector steer = PVector.sub(desired, velocity);
    steer.limit(maxforce);  // Limit to maximum steering force
    return steer;
  }
  
  
  
  // -----------------------------------------------------------------------------------
  // Cohesion
  // For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
  PVector cohesion (ArrayList<Boid> boids) {
    // somme de la position de tout les voisins
    // ----------------------------------------
    float neighbordist = 50; // seuil de voisinage
    PVector sum = new PVector(0, 0);   // Start with empty vector to accumulate all locations
    float sumCoeff = 0; // utilisation de coefficient d'interaction pour chaque voisin
    int count = 0; // voisin de poids uniformes
    for (Boid other : boids) {
      float d = PVector.dist(location, other.location);
      if ((d > 0) && (d < neighbordist)) {
        sum.add(PVector.mult(other.location, other.boidHeight)); // somme des locations de tout les voisins
        sumCoeff += other.boidHeight; // utilisation de coefficient d'interaction pour chaque voisin
        count++; // voisin de poids uniformes
      }
    }
    
    // calcul de la force de chaque voisins
    // ------------------------------------
    // Si il y a effectivement des voisins :
    if (count > 0) {
      // normalize the neighgboors location
      sum.div(sumCoeff);// utilisation de coefficient d'interaction pour chaque voisin
      //sum.div(count); // voisin de poids uniformes
      return seek(sum);  // Steer towards the location
    } 
    else {
      return new PVector(0, 0);
    }
  }
  
  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // Forces
  // -----------------------------------------------------------------------------------
  
  void interactWithObstacles (ArrayList<Obstacle> obstacles) 
  {
    PVector steerObstacle = new PVector(0, 0, 0);
    for (Obstacle ob : obstacles)
    {
      applyForce(ob.calculateObstacleForce(this));
    }
  }
  
  
  
}

// Macro
// -----
boolean IN = true;  //attractive force of the object (retain the in of the shape)
boolean OUT = false;  //repuslsive force of the object (retain the out of the shape)



// The Obstacle class
// ------------------


class Obstacle {
  // location and shape
  PVector center;
  
  int shape = ELLIPSE;
  float shapeWidth;
  float shapeHeight;
  
  
  
  // attraction or répusion
  boolean inOrOut = OUT;
  
  
  
  // --------------------------------------------
  Obstacle (PVector location, int newShape, float newWidth, float newHeight)
  {
    center = location;
    
    shape = newShape;
    shapeWidth = newWidth;
    shapeHeight = newHeight;
    
  }
  
  // --------------------------------------------
  Obstacle (PVector location, int newShape, float newWidth, float newHeight, boolean sayItInOrOut)
  {
    center = location;
    
    shape = newShape;
    shapeWidth = newWidth;
    shapeHeight = newHeight;
    
    inOrOut = sayItInOrOut;
  }
  
  
  
  
  // -----------------------------------------------------
  // retour visuel de l'obstacle
  void render ()
  {
    stroke (0);
    strokeWeight(0);
    noFill ();
    
    if (shape == ELLIPSE)
    {
      ellipse(center.x, center.y, shapeWidth, shapeHeight);
    }
    else if (shape == RECT)
    {
      rect(center.x - shapeWidth/2, center.y - shapeHeight/2, shapeWidth, shapeHeight);
    }
    
  }
  
  
  // --------------------------------------------------------
  // calcul de la force de l'objet sur un élément du troupeau
  PVector calculateObstacleForce (Boid boid)
  {
    if (shape == RECT){
      return calculateForceFromRect (boid);
    }
    else if (shape == ELLIPSE) {
      
    }
    
    return calculatePointForce (boid, center, 50.f);
    
  }
  
  
  // --------------------------------------------------------
  PVector calculatePointForce (Boid boid, PVector point, float desiredRange)
  {
    PVector steer = new PVector(0, 0, 0);
    
    float d = PVector.dist(point, boid.location);
    
    if ((d > 0) && (d < desiredRange))
    {
      PVector diff = PVector.sub(point, boid.location);
      if (inOrOut == OUT)
        diff.mult(-1);
      diff.normalize();
      diff.div(d);        // Weight by distance
      steer.add(diff);
    }

    // As long as the vector is greater than 0
    if (steer.mag() > 0) {
      steer.normalize();
      steer.mult(boid.maxspeed);
      // First two lines of code below could be condensed with new PVector setMag() method
      // Not using this method until Processing.js catches up
      //steer.setMag(boid.maxspeed);

      // Implement Reynolds: Steering = Desired - Velocity
      //steer.normalize();
      //steer.mult(maxspeed);
      steer.sub(boid.velocity);
      steer.limit(2.75 * boid.maxforce);
    }
    
    return steer; 
  }
  
  
  
  // --------------------------------------------------------
  PVector calculateForceFromRect (Boid boid)
  {
    PVector steer = new PVector(0, 0, 0);
    
    if (inOrOut == OUT){
      // si l'élément appartient au rectangle
      if (boid.location.x > (center.x - shapeWidth/2) && boid.location.x < (center.x + shapeWidth/2)) {
        if (boid.location.y > (center.y - shapeHeight/2) && boid.location.y < (center.y + shapeHeight/2)) {
          
          float d = PVector.dist(center, boid.location);
          
          PVector diff = PVector.sub(center, boid.location);
          if (inOrOut == OUT)
            diff.mult(-1);
          diff.normalize();
          diff.div(d);        // Weight by distance
          steer.add(diff);
        
        }
      }
    }
    // situation d'attraction
    else {
      // si l'élément appartient au rectangle
      // si l'élément est sur les bords
      int border = 50;
      if (
            (
              (boid.location.x > (center.x - shapeWidth/2) && boid.location.x < (center.x - shapeWidth/2 + border))
              || (boid.location.x < (center.x + shapeWidth/2) && boid.location.x > (center.x + shapeWidth/2 - border))
            )
            && (boid.location.y > (center.y - shapeHeight/2))
            && (boid.location.y < (center.y + shapeHeight/2))
          ||
          
            (
              (boid.location.y > (center.y - shapeHeight/2) && boid.location.y < (center.y - shapeHeight/2 + border))
              || (boid.location.y < (center.y + shapeHeight/2) && boid.location.y > (center.y + shapeHeight/2 - border))
            )
            && (boid.location.x > (center.x - shapeWidth/2))
            && (boid.location.x < (center.x + shapeWidth/2))
              
          ) {
            
              float d = PVector.dist(center, boid.location);
          
              PVector diff = PVector.sub(center, boid.location);
              if (inOrOut == OUT)
                diff.mult(-1);
              diff.normalize();
              diff.div(d);        // Weight by distance
              steer.add(diff);
              
            } // fin d'appartenance à la barrière
    } // fin if in/Out 
      
    // As long as the vector is greater than 0
      if (steer.mag() > 0) {
        steer.normalize();
        steer.mult(boid.maxspeed);
        // First two lines of code below could be condensed with new PVector setMag() method
        // Not using this method until Processing.js catches up
        //steer.setMag(boid.maxspeed);
  
        // Implement Reynolds: Steering = Desired - Velocity
        //steer.normalize();
        //steer.mult(maxspeed);
        steer.sub(boid.velocity);
        steer.limit(1.5*boid.maxforce);
      } // fin controle magnitude
    
    
    return steer; 
  }
  
  
  
  
  
}