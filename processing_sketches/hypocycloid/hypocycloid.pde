Inputs inputs;

void setup()
{
  size(400, 400);
  background(255);
}

float theta = 0.0;
void draw() {
  if (this.inputs != null){
    if (this.inputs.getCanClear()){
      theta = 0.0;
      background(255);
    }
  
    theta = theta + .05;
    float a = this.inputs.getAValue();
    float b = this.inputs.getBValue();
    stroke(100,0,0);
    float x = (a-b)*cos(theta) + (b*cos(((a-b)/b)*theta));
    float y = (a-b)*sin(theta) - (b*sin(((a-b)/b)*theta));
    translate(150, 150);
    point(x, y);
  }
}

void bindInputsJS(Inputs inputs){
  this.inputs = inputs;
}