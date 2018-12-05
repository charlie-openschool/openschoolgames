Inputs inputs;

void setup()
{
  size(400, 400);
  background(255);
  stroke(100,0,0);
}

float theta = 0.0;
String currentDescription = "";
void draw() {
  if (this.inputs != null){
    if (this.inputs.getCanClear()){
      theta = 0.0;
      background(255);
    }
    theta = theta + .02;
    float a = this.inputs.getAValue();
    float b = this.inputs.getBValue();
    float h = this.inputs.getHValue();
    printDescription(a, b, h);
    float x = (a+b)*cos(theta) - (h*cos(((a+b)/b)*theta));
    float y = (a+b)*sin(theta) - (h*sin(((a+b)/b)*theta));
    translate(150, 150);
    point(x, y);
  }
}

void printDescription(float a, float b, float h){
    String description = "";
    if (a/b == 1.0){
      description = "a: " + a + " b: " + b + " h: "+ h + " Cardioid k: " + a/b;
    } else if (a % b == 0){
     description = "a: " + a + " b: " + b + " h: "+ h + " k: " + a/b;
   } else if (b % a == 0){
     description = "a: " + a + " b: " + b + " h: "+ h + " k: " + b/a;
   }
   if (currentDescription != description){
     currentDescription = description;
     println(description);
   }
}

void bindInputsJS(Inputs inputs){
  this.inputs = inputs;
}