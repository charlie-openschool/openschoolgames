//    Barnsley Fern for Processing 3.4

void setup() {
  size(800, 800);
  background(0);
}

void drawPoint(float x, float y) {
  // map x and y to canvas width and height
  float px = map(x, -2.1820, 2.6558, 0, width);
  float py = map(y, 0, 9.9983, height, 0);
  point(px, py);
}

// the next value of x is based on the
// old x and y values
float nextX(float x, float y, float r) {
  float nextX = 0;
  if (r < 0.01) {
    return  0;
  } else if (r < 0.86) {
    return 0.85 * x + 0.04 * y;
  } else if (r < 0.93) {
    return  0.20 * x - 0.26 * y;
  } else {
    return -0.15 * x + 0.28 * y;
  }
}

// the next value of y is based on the 
// old x and y values
float nextY(float x, float y, float r) {
  if (r < 0.01) {
    return 0.16 * y;
  } else if (r < 0.86) {
    return -0.04 * x + 0.85 * y + 1.6;
  } else if (r < 0.93) {
    return 0.23 * x + 0.22 * y + 1.6;
  } else {
    return 0.26 * x + 0.24 * y + 0.44;
  }
}

// global variables that 
// hold our state across
// calls to draw
int cnt = 0;
int theta = 0;
float x = 0.0;
float y = 0.0;

void draw() {
  stroke(34, 239, 34);
  strokeWeight(1);
  cnt++;
  // after 400 calls to draw
  // rotate the canvas 
  if (cnt > 400){
    cnt = 0;
    theta++;
  }
  
  if (theta > 16){
    exit();
  }
  
  translate(350,350);

  rotate(3.14159/4 * theta);
  if (theta > 8){
    scale(.4);
  } else {
    scale(.2);
  }

  // draw in bursts of 100
  for (int i = 0; i < 100; i++) {
    float r = random(1);
    float x1 = nextX(x, y, r);
	float y1 = nextY(x, y, r);
	drawPoint(x, y);
	x = x1;
	y = y1;
  }
}