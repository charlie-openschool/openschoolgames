OvalAnimation ovalAnimation;
float xpos;
float ypos;
float drag = 30.0;

void setup() {
  size(640, 360);
  background(53, 0, 100);
  frameRate(24);
  ovalAnimation = new OvalAnimation(PI/16, 150, 150);
  ypos = height * 0.25;
}

void draw() { 
  float dx = mouseX - xpos;
  xpos = xpos + dx/drag;
  float dy = mouseY - ypos;
  ypos = ypos + dy/drag;

  background(53, 0, 100);
  ovalAnimation.display((int)xpos, (int)ypos);
}

class OvalAnimation {
  double theta = 0.0;
  double incrementAngle = 0.0;
  int maxHeight;
  int maxWidth;
  
  OvalAnimation(double incrementAngle, int maxHeight, int maxWidth) {
    this.incrementAngle = incrementAngle;
    this.maxHeight = maxHeight;
    this.maxWidth = maxWidth;
  }

  void display(int xpos, int ypos) {
    if (theta < 2 *PI){
      theta += incrementAngle;
    } else {
      theta = 0; 
    }
      double xFactor = cos((float)theta);
      double yFactor = sin((float)theta);
      int currentWidth = (int)(xFactor * maxWidth);
      int currentHeight = (int)(yFactor * maxHeight);
      if (currentWidth < 50){
        currentWidth = 50;  
     }
     if (currentHeight < 50){
       currentHeight = 50;
     }
      ellipse(xpos, ypos, currentWidth, currentHeight);
  }
}
