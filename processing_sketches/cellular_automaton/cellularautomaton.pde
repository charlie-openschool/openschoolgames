Inputs inputs;

void setup()
{
  size(1400, 700);
  background(255);
  stroke(100,0,0);
  strokeWeight(1);
  frameRate(24);
  fill(255);
}

boolean [] bits = new boolean[8];
boolean [] elements = new boolean[200];
int m = 0;
int r = 5;
int rule = 0;
void draw() {
  if (m == 0){
    for (int n = 0; n < elements.length; n++){
      elements[n] = false;
    }
    elements[100] = true;
    background(255);
  }
  stroke(0);
  int i = 0;
  for (int j = 7; j >= 0; j--){
    fill(255);
    if (i == 4 || i == 5 || i == 6 || i == 7){
      fill(0);
    }
    rect(40*j, 10, 10, 10);
    fill(255);
    if (i == 2 || i == 3 || i == 6 || i == 7){
      fill(0);
    }
    rect(40*j + 12, 10, 10, 10);
    fill(255);
    if (i % 2 == 1) {
      fill(0);
    }
    rect(40*j +24, 10, 10, 10);
    fill(255);
    if (bits[i]){
      fill(0);
    }
    rect(40*j +12, 24, 10, 10);
    i++;
  }
if (m > 99){
return;
}

    boolean [] inprogressElements = new boolean[200];
    for (int k = 0; k < 200; k++){
      fill(255);
      if (elements[k]){
        fill(0);
        ellipse(5*k +12, m*5+44, r, r);	
      }
      if (bits[0]){
        if (!elements[k - 1] && !elements[k] && !elements[k + 1]){
          inprogressElements[k] = true;
        }
      }
      if (bits[1]){
        if (!elements[k - 1] && !elements[k] && elements[k + 1]){
          inprogressElements[k] = true;
        }
      }
      if (bits[2]){
        if (!elements[k - 1] && elements[k] && !elements[k + 1]){
          inprogressElements[k] = true;
         }
      }
      if (bits[3]){
        if (!elements[k - 1] && elements[k] && elements[k + 1]){
          inprogressElements[k] = true;
        }
      }
      if (bits[4]){
        if (elements[k - 1] && !elements[k] && !elements[k + 1]){
          inprogressElements[k] = true;
        }
      }
      if (bits[5]){
        if (elements[k - 1] && !elements[k] && elements[k + 1]){
          inprogressElements[k] = true;
        }
      }
      if (bits[6]){
        if (elements[k - 1] && elements[k] && !elements[k + 1]){
          inprogressElements[k] = true;
        }
      }
      if (bits[7]){
        if (elements[k - 1] && elements[k] && elements[k + 1]){
          inprogressElements[k] = true;
        }
      }
    }
    for (int p = 0; p < 200; p++){
      elements[p] = inprogressElements[p];
    }
  stroke(0);
  rule = 0;
  for (int b = 0; b < 8; b++){
    if (bits[b]){
      rule += Math.pow(2, b);
    }
  }
  fill(255);
  stroke(255);
  rect(480,3,90,16);
  fill(0);
  text("Rule: " + rule, 490, 15);
  m++;
}


void mouseClicked() {
  int j = 0;
  for (int i = 7; i >= 0; i--){
    if (mouseX > 40 * i + 12 && mouseX < 40 * i + 22 && mouseY > 23 && mouseY < 34){ 
      bits[j] = !bits[j];
    }
    j++;
  }
  m = 0;
}

void bindInputsJS(Inputs inputs){
  this.inputs = inputs;
}
