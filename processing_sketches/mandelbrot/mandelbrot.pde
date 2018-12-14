

void setup() {
  size(1000, 1000);
  background(255);
}

void draw() {
  translate(500, 500);
  float r = 0.0;
  float i = 0.0;
    for(int x = -600; x < 400; x++){
      r = 0.007 * x;
      for(int y = -600; y < 400; y++){
        i = 0.007 * y;
        stroke(150); // in the set
        float real = r;
        float complex = i;
        for (int t = 0; t < 500; t++){
          float tr = real * real - (complex * complex);
          float ti = 2 * real * complex;
          if (tr > 500 || tr < -500 || ti > 500 || ti < -500){
            stroke(abs(tr)%255, 50, abs(ti)%255);
            break;
          }
          real = tr;
          complex = ti;
          real = real + r;
          complex = complex + i
        }
        point(x, y);
      }
    }
  exit();
}


