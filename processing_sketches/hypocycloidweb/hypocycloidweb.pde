
void setup()
{
  size(600, 600);
  background(150);
}

int b = 5;
float theta = 0.0;
int i = 0;

void draw() {  
  theta = theta + .01;
  a = 15 + (i * 5);
  if ( a > 220){
    stop();
  }
  if (theta > 6.243){
    theta = 0.0;
    i = i + 1;
  }
  float x = (a-b)*cos(theta) + (b*cos(((a-b)/b)*theta));
  float y = (a-b)*sin(theta) - (b*sin(((a-b)/b)*theta));
  translate(250, 250);
  int red = 0;
  if ( x > 0){
    red = x;
  } else {
    red = x * -1;
  }
  int blue = 0;
  if ( y > 0){
    blue = y;
  } else {
    blue = y * -1;
  }
  stroke(red, 0, blue);
  point(x, y);
}
