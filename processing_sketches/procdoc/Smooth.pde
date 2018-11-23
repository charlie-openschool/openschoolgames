void setup() {
  size(150, 150);
  smooth();
  background(255);  
}

void draw(){
  pushMatrix();
  fill(100, 0, 0);
  scale(3.0);
  translate(30, 10);
  rotate(radians(45));
  rect(0, 0, 20, 20);
  popMatrix();
}