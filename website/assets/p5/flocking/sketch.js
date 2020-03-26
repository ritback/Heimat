// https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects

// Original code from :
// 
// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com


let flock;

let obstacles = [];

  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------

function  setup() {
  createCanvas(windowWidth, windowHeight);
    frameRate(30);
    
  flock = new Flock();
    
  // Add an initial set of boids into the system
  for (let i = 0; i < 150; i++) {
    flock.addBoid(new Boid());
  }
  
  // obstacle à l'intérieur de la vue
  obstacles.push(new Obstacle(createVector(width/2, height/2), width, height, IN));
  background(50);
}

function draw() {
    
    //background(255, 255, 255, 255);
    
    clear();
    
    flock.run(obstacles);
    
    for (let i = 0; i < obstacles.length; ++i) {
      obstacles[i].render();
    }
    
    //console.log(frameRate());
}

// ----------------------------------------------------------------------
// Add a new boid into the System
function mousePressed() {
  
  flock.addBoid(new Boid(mouseX,mouseY));
  
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
    obstacles[0].center.x = width / 2;
    obstacles[0].center.y = height / 2;
    obstacles[0].shapeWidth = width;
    obstacles[0].shapeHeight = height;
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

// The Flock (a list of Boid objects)
// ----------------------------------

function Flock() {
        this.boids= [];
    }

Flock.prototype.run = function(obstacles) {
    for (let i = 0; i < this.boids.length; ++i) {
      this.boids[i].run(this.boids, obstacles);
    }
  }

Flock.prototype.addBoid = function(b) {
    this.boids.push(b);
  }



// The Boid class
// --------------


function Boid(x, y) {
    // dynamics
    // --------
    this.location =  createVector(random(0, width), random(0, height));
    let angle = random(TWO_PI);
    this.velocity = createVector(cos(angle), sin(angle));;
    this.acceleration = createVector(0, 0);;
    
      
    this.maxspeed = /*2;//*/random(1.5,2.5);
    this.maxforce = 0.05; // limitation des forces (pour pas que l'une écrase les autres)
    
    // shapes and rendering
    // --------------------
    //float r = /*3.0;//*/random(2, 5);; // radius
    this.maxHeight = 20.0;
    this.boidHeight = random(this.maxHeight/2, this.maxHeight);
    this.boidWidth = random(this.maxHeight/4, this.maxHeight/3);
    this.decHeight = random(1, this.boidWidth/3);
    
    this.colorFish = color (random(200,255), random(60,255), random(80,120));
    this.currentColor = color(this.colorFish);
    this.colorPhase = 0;
    this.colorPhaseInc = random(1);
    
  }
  
  // mouvement of the boid
  // ---------------------
Boid.prototype.run = function(boids, obstacles) {
    this.flock(boids); // add flock forces
    this.interactWithObstacles(obstacles);
    this.update(); // update the boid location
    this.borders(); // teleport the boid if he reach a border
    this.render(); // render the boid
  }
  
  // -----------------------------------------------------------------------------------
  // add a force into the systeme
  // Forces
Boid.prototype.applyForce = function(force) {
    // We could add mass here if we want A = F / M
    this.acceleration.add(force);
  }

  
  
  // -----------------------------------------------------------------------------------
  // Method to update location
  // -------------------------
Boid.prototype.update = function() {
    // Update velocity
      this.velocity.add(this.acceleration);
    // Limit speed
      //this.velocity.limit(this.maxspeed);
      this.location.add(this.velocity);
    // Reset accelertion to 0 each cycle
      this.acceleration.mult(0);
  }



  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // rendering of the boid (draw)
  // ----------------------------
Boid.prototype.render = function() {
    // Draw a triangle rotated in the direction of velocity
      let theta = this.velocity.heading() + radians(90);
    // heading2D() above is now heading() but leaving old syntax until Processing.js catches up
    
    fill(200, 100);
    stroke(255);
    push();
    translate(this.location.x, this.location.y);
    rotate(theta);
    
    this.updateColor ();
    fill(this.currentColor);
    noStroke();
    
    
    beginShape(QUADS);
    
    vertex(0, -this.boidHeight/2+this.decHeight);
    vertex(- this.boidWidth/2, 0);
    vertex(0, this.boidHeight/2+this.decHeight);
    vertex(+this.boidWidth/2, 0);
    
    
    endShape(CLOSE);
    
    
    
    pop();
  }
  
  
  // ------------------------------------------
Boid.prototype.updateColor = function() {
    let inc = 50*sin (this.colorPhase);
    this.colorPhase += this.colorPhaseInc;
    
    this.currentColor = color (red(this.colorFish) + inc, green(this.colorFish) + inc, blue(this.colorFish) + inc);
  }
  
  
  
  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // Wraparound
  // Les poissons qui sortent du cadre, apparaisse de l'autre coté
  // -------------------------------------------------------------
Boid.prototype.borders = function() {
    
    if (this.location.x < -this.boidHeight) this.location.x = width+this.boidHeight;
    if (this.location.y < -this.boidHeight) this.location.y = height+this.boidHeight;
    if (this.location.x > width+this.boidHeight) this.location.x = -this.boidHeight;
    if (this.location.y > height+this.boidHeight) this.location.y = -this.boidHeight;
    
    
    // this.boidHeight environ = 15 / 20
    /*
    let padding = -50;
    if (this.location.x < padding) this.location.x = width-padding;
    if (this.location.y < padding) this.location.y = height-padding;
    if (this.location.x > width-5) this.location.x = padding;
    if (this.location.y > height-5) this.location.y = padding;
    */
  }
  
  
  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // Forces for Flock, part. 1
  // -----------------------------------------------------------------------------------
  // We accumulate a new acceleration each time based on three rules
  // add and calculate all the forces that'll make the flock
  // ---------------------------------------------------------------
Boid.prototype.flock = function(boids) {
    // flock forces
    let sep = this.separate(boids);   // Separation
    let ali = this.align(boids);      // Alignment
    let coh = this.cohesion(boids);   // Cohesion
    
    // Arbitrarily weight these forces
    sep.mult(1.5);
    ali.mult(1.0);
    coh.mult(1.0);
    
    // Add the force vectors to acceleration
    this.applyForce(sep);
    this.applyForce(ali);
    this.applyForce(coh);
  }
  
  
  
  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // Forces for Flock, part 2.s
  // -----------------------------------------------------------------------------------
  // Separation
  // Method checks for nearby boids and steers away
Boid.prototype.separate = function(boids) {
    
    let desiredseparation = 30.0; // séparation de chaque éléments
    let steer = createVector(0, 0, 0);
    let count = 0;
    
    // For every boid in the system, check if it's too close
    for (let i = 0; i < boids.length; ++i) {
      let d = p5.Vector.dist(this.location, boids[i].location);
      
      // If the distance is greatethis.r than 0 and less than an arbitrary amount (0 when you are yourself)
      if ((d > 0) && (d < desiredseparation)) {
        // Calculate vector pointing away from neighbor
        let diff = p5.Vector.sub(this.location, boids[i].location);
        diff.normalize();
        diff.div(d);        // Weight by distance
        steer.add(diff);
        count++;            // Keep track of how many
      }
    }
    
    // Average -- divide by how many
    if (count > 0) {
      steer.div(count);
    }

    // As long as the vector is greater than 0
    if (steer.mag() > 0) {
      steer.normalize();
      steer.mult(this.maxspeed);
      // First two lines of code below could be condensed with new p5.Vector setMag() method
      // Not using this method until Processing.js catches up
      // steer.setMag(maxspeed);

      // Implement Reynolds: Steering = Desired - Velocity
      //steer.normalize();
      //steer.mult(maxspeed);
      steer.sub(this.velocity);
      steer.limit(this.maxforce);
    }
    
    
    return steer;
  }


  // -----------------------------------------------------------------------------------
  // Alignment
  // For every nearby boid in the system, calculate the average velocity
  
Boid.prototype.align = function(boids) {
    
    let neighbordist = 50;
    
    let sum = createVector(0, 0);
    let count = 0;
    
    for (let i = 0; i < boids.length; ++i) {
      let d = p5.Vector.dist(this.location, boids[i].location);
      if ((d > 0) && (d < neighbordist)) {
        sum.add(boids[i].velocity);
        count++;
      }
    }
    
    if (count > 0) {
      sum.div(count);
      sum.normalize();
      sum.mult(this.maxspeed);
      // First two lines of code below could be condensed with new p5.Vector setMag() method
      // Not using this method until Processing.js catches up
      // sum.setMag(maxspeed);

      // Implement Reynolds: Steering = Desired - Velocity
      //sum.normalize();
      //sum.mult(maxspeed);
      steer = p5.Vector.sub(sum, this.velocity);
      steer.limit(this.maxforce);
      return steer;
    } 
    else {
      return createVector(0, 0);
    }
  }



  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // A method that calculates and applies a steering force towards a target
  // (steer = control) (mouvement ordonée du troupeau)
  // STEER = DESIRED MfalseUS VELOCITY
Boid.prototype.seek = function(target) {
    let desired = p5.Vector.sub(target, this.location);  // A vector pointing from the location to the target
    // Scale to maximum speed
    desired.normalize();
    desired.mult(this.maxspeed);

    // Above two lines of code below could be condensed with new p5.Vector setMag() method
    // Not using this method until Processing.js catches up
    //desired.setMag(maxspeed);

    // Steering = Desired minus Velocity
    let steer = p5.Vector.sub(desired, this.velocity);
    steer.limit(this.maxforce);  // Limit to maximum steering force
    return steer;
  }
  
  
  
  // -----------------------------------------------------------------------------------
  // Cohesion
  // For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
Boid.prototype.cohesion = function(boids) {
    // somme de la position de tout les voisins
    // ----------------------------------------
    let neighbordist = 50; // seuil de voisinage
    let sum = createVector(0, 0);   // Start with empty vector to accumulate all locations
    let sumCoeff = 0; // utilisation de coefficient d'interaction pour chaque voisin
    let count = 0; // voisin de poids uniformes
    for (let i = 0; i < boids.length; ++i) {
      let d = p5.Vector.dist(this.location, boids[i].location);
      if ((d > 0) && (d < neighbordist)) {
        sum.add(p5.Vector.mult(boids[i].location, boids[i].boidHeight)); // somme des locations de tout les voisins
        sumCoeff += boids[i].boidHeight; // utilisation de coefficient d'interaction pour chaque voisin
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
      return this.seek(sum);  // Steer towards the location
    } 
    else {
      return createVector(0, 0);
    }
  }
  
  
  // -----------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------
  // Forces
  // -----------------------------------------------------------------------------------
Boid.prototype.interactWithObstacles = function(obstacles) {
  {
    let steerObstacle = createVector(0, 0, 0);
    for (let i = 0; i < obstacles.length; ++i)
    {
      this.applyForce(obstacles[i].calculateObstacleForce(this));
    }
  }
  
  
  
}

// Macro
// -----
let IN = true;  //attractive force of the object (retain the in of the shape)
let OUT = false;  //repuslsive force of the object (retain the out of the shape)



// The Obstacle class
// ------------------


  // --------------------------------------------
function Obstacle(location, newWidth, newHeight, inOrOut) {
  {
    this.inOrOut = inOrOut;
    this.center = location;
    
    this.shapeWidth = newWidth;
    this.shapeHeight = newHeight;
      
      this.borderWidth = newWidth/100;
    
  }
  
  
  
  // -----------------------------------------------------
  // retour visuel de l'obstacle
Obstacle.prototype.render = function() {
    if (0)
        {
    stroke (0);
    strokeWeight(5);
    noFill ();
    
    rect(this.center.x - this.shapeWidth/2,
         this.center.y - this.shapeHeight/2,
         this.shapeWidth,
         this.shapeHeight);
            
    strokeWeight(1);
    rect(this.center.x - this.shapeWidth/2 + this.borderWidth,
         this.center.y - this.shapeHeight/2 + this.borderWidth,
         this.shapeWidth - 2*this.borderWidth,
         this.shapeHeight - 2*this.borderWidth);
    
    }
  }
  
  
  // --------------------------------------------------------
  // calcul de la force de l'objet sur un élément du troupeau
Obstacle.prototype.calculateObstacleForce = function(boid) {
      return this.calculateForceFromRect (boid);
  }
  
  
  // --------------------------------------------------------
Obstacle.prototype.calculatePointForce = function(boid,  point, desiredRange) {
    let steer = createVector(0, 0, 0);
    
    let d = p5.Vector.dist(point, boid.location);
    
    if ((d > 0) && (d < desiredRange))
    {
      let diff = p5.Vector.sub(point, boid.location);
      if (this.inOrOut == OUT)
        diff.mult(-1);
      diff.normalize();
      diff.div(d);        // Weight by distance
      steer.add(diff);
    }

    // As long as the vector is greater than 0
    if (steer.mag() > 0) {
      steer.normalize();
      steer.mult(boid.maxspeed);
      // First two lines of code below could be condensed with new p5.Vector setMag() method
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

Obstacle.prototype.calculateForceFromRect = function(boid)  {
    let steer = createVector(0, 0, 0);
    
    if (this.inOrOut == OUT){
      // si l'élément appartient au rectangle
      if (boid.location.x > (this.center.x - this.shapeWidth/2) && boid.location.x < (this.center.x + this.shapeWidth/2)) {
        if (boid.location.y > (this.center.y - this.shapeHeight/2) && boid.location.y < (this.center.y + this.shapeHeight/2)) {
          
          let d = p5.Vector.dist(this.center, boid.location);
          
          let diff = p5.Vector.sub(this.center, boid.location);
          if (this.inOrOut == OUT)
            diff.mult(-1);
          diff.normalize();
          diff.div(d);        // Weight by distance
          steer.add(diff);
        
        }
      }
    }
    // situation d'attraction
    else {
        // 3 scénario:
        // - le boid est dans le rectangle
        // -- sur une zone en bordure du rectangle -> force vers le centre
        // -- a l'interieur du rectangle...  -> pas de force
        // - le boid est en dehors du rectangle -> force vers le centre
        
        /*
      if (
          
            ((// si le boid est situé sur la zone de bord gauche
                boid.location.x > (this.center.x - this.shapeWidth/2) &&
                boid.location.x < (this.center.x - this.shapeWidth/2 + this.borderWidth))
              || ( // si le boid est situé sur la zone de bord droite
                boid.location.x < (this.center.x + this.shapeWidth/2) &&
                boid.location.x > (this.center.x + this.shapeWidth/2 - this.borderWidth))
            ) // et que le boid appartient au rectangle
            && (boid.location.y > (this.center.y - this.shapeHeight/2))
            && (boid.location.y < (this.center.y + this.shapeHeight/2))
          ||
          
            ((// si le boid est situé sur la zone de bord haute
                boid.location.y > (this.center.y - this.shapeHeight/2) &&
                boid.location.y < (this.center.y - this.shapeHeight/2 + this.borderWidth))
              || (// si le boid est situé sur la zone de bord basse
                boid.location.y < (this.center.y + this.shapeHeight/2) &&
                boid.location.y > (this.center.y + this.shapeHeight/2 - this.borderWidth))
            ) // et que le boid appartient au rectangle
            && (boid.location.x > (this.center.x - this.shapeWidth/2))
            && (boid.location.x < (this.center.x + this.shapeWidth/2))
              
          ) */
        
        // si le boid est or de la zone => force vers le centre
      if (boid.location.x < (this.center.x - this.shapeWidth/2 + this.borderWidth) ||
          boid.location.x > (this.center.x + this.shapeWidth/2 - this.borderWidth) ||
          boid.location.y < (this.center.y - this.shapeHeight/2 + this.borderWidth) ||
          boid.location.y > (this.center.y + this.shapeHeight/2 - this.borderWidth))
        {
              let d = p5.Vector.dist(this.center, boid.location);
          
              let diff = p5.Vector.sub(this.center, boid.location);
              if (this.inOrOut == OUT)
                diff.mult(-1);
              diff.normalize();
              diff.div(d);        // Weight by distance
              steer.add(diff);
          } // fin d'appartenance à la barrière
        
        
    // As long as the vector is greater than 0 just set a steering force to feel more natural.
      if (steer.mag() > 0) {
        steer.normalize();
        steer.mult(boid.maxspeed);
        steer.sub(boid.velocity);
          steer.limit(1.2*boid.maxforce);
          
        
      } // fin controle magnitude
        
    } // fin if in/Out 
      
    
    return steer; 
  }
  
  
  
  
  
}