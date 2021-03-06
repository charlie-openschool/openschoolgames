void setup() {
  size(800, 600);
  background(255);
  smooth();  
}

float scaleFactor = 2.0;
int colorCount = 50;
boolean colorUp = true;
boolean scaleUp = true;
boolean stop = false;
int count = 0;

void draw(){
  if (frameCount % 10 == 0){
    if (!stop){
      count += 1;
      pushMatrix();
      if (colorCount == 255){
        colorUp = false;
      }
      if (colorCount == 50){
        colorUp = true;
      }
      if (colorUp){
        colorCount += 1;
      } else {
        colorCount -=1;
      }
      fill(colorCount, 0, 0)
      translate(350 + cos(count) * 100, 310 + sin(count) * 100);
      rotate(radians(30 + frameCount));
      scale(scaleFactor);
      rect(0, 0, 20, 20);
      popMatrix();
    }
    if (frameCount % 100 == 0){
      if (scaleFactor > 7.0){
        scaleUp = false;
      }
      if (0.50 > scaleFactor){
        stop = true;
      }
      if (scaleUp){
        scaleFactor += .15;
      } else {
        scaleFactor -= .15;
      }
    }
  }
}