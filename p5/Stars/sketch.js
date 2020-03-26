let stars;

function setup() {
  // put setup code here
    createCanvas(400,400, WEBGL);
    
    stars = new StarsGroup(5);
    
}

function draw() {
  // put drawing code here
    
    background(240);
    stars.update();
    stars.render();
    
}

function mousePressed(){
    
}


// ----------------------------------------------------------
// ----------------------------------------------------------
function StarsGroup(numStars){
    this.starsGroup = [];
    
    let range = 100;
    let speedRange = 0.1;
    for (let i = 0; i < numStars; ++i){
        this.starsGroup.push(new Star(random(-range, range), random(-range, range), random(-range, range),
                            random(-speedRange, speedRange), random(-speedRange, speedRange), random(-speedRange, speedRange)));
    }
    this.starsGroup[0].mass = 100;
}

StarsGroup.prototype.render = function(){
    
    for (let i = 0; i < this.starsGroup.length; ++i){
        this.starsGroup[i].render();
    }
}

StarsGroup.prototype.update = function(){
    
    let g = 0.01;
    
    for (let i = 0; i < this.starsGroup.length; ++i){
        
        for (let j = i; j < this.starsGroup.length; ++j){
            let dir = p5.Vector.sub(this.starsGroup[i].position, this.starsGroup[j].position);
            dir.normalize();
            let dist = p5.Vector.dist(this.starsGroup[i].position, this.starsGroup[j].position);
            
            let forceMag = g*this.starsGroup[i].mass*this.starsGroup[j].mass/(dist*dist);
            
            this.starsGroup[i].applyForce(p5.Vector.mult(dir, -forceMag));
            this.starsGroup[j].applyForce(p5.Vector.mult(dir, forceMag));
    
        }
    }
    
    for (let i = 0; i < this.starsGroup.length; ++i){
        this.starsGroup[i].update();
    }
}


// ----------------------------------------------------------
// ----------------------------------------------------------
function Star(x, y, z, vx, vy, vz){
    this.mass = 10;
    this.position = createVector(x, y, z);
    this.velocity = createVector(vx, vy, vz);
    this.acceleration = createVector(0, 0, 0);
}

Star.prototype.render = function(){
    push();
    translate(this.position);
    let c1 = color(255, 204, 0);
    let c2 = color(255, 204, 0);
    if (this.mass > 50)  fill(c1);
    else fill(c2);
    sphere(10);
    pop();
}

Star.prototype.update = function(){
    this.velocity.add(this.acceleration);
    this.position.add(this.velocity);
    this.acceleration.mult(0);
}

Star.prototype.applyForce = function(force){
    this.acceleration.add(p5.Vector.div(force, this.mass));
}
