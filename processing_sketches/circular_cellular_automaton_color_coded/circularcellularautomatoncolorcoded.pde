
void setup() {
  size(1000, 900);
  background(150);
  stroke(100,0,0);
  strokeWeight(1);
  frameRate(24);
  fill(255);
}

boolean [] bits = new boolean[8];
boolean [] highLightBits = new boolean[8];
boolean [] elements = new boolean[200];
color [] cellColor = new color[200];
color [] ruleColor = new color[8];
ruleColor[0] = color(0, 0, 0);
ruleColor[1] = color(100, 0, 0);
ruleColor[2] = color(200, 0, 0);
ruleColor[3] = color(200, 200, 0);
ruleColor[4] = color(200, 100, 0);
ruleColor[5] = color(0, 0, 100);
ruleColor[6] = color(0, 0, 200);
ruleColor[7] = color(100, 0, 200);
bits[1] = true;
bits[4] = true;
int generation = 0;
int cellWidth = 5;
int rule = 0;

void draw() {
  if (generation == 0){
    for (int n = 0; n < elements.length; n++){
      elements[n] = false;
    }
    elements[100] = true;
    background(250);
  }
  stroke(0);
  int i = 0;
  for (int j = 7; j >= 0; j--){
    fill(255);
    if (i == 4 || i == 5 || i == 6 || i == 7){
      fill(ruleColor[i], 150);
    }
    rect(40*j, 10, 10, 10);
    fill(255);
    if (i == 2 || i == 3 || i == 6 || i == 7){
      fill(ruleColor[i], 150);
    }
    rect(40*j + 12, 10, 10, 10);
    fill(255);
    if (i % 2 == 1) {
      fill(ruleColor[i], 150);
    }

    rect(40*j +24, 10, 10, 10);
    strokeWeight(5);
    if (highLightBits[i]){
      stroke(0);  
    } else {
      stroke(150);
    }
    rect(40*j +12, 24, 10, 10);
    stroke(0);
    strokeWeight(1);
    fill(255);
    if (bits[i]){
      fill(ruleColor[i], 150);
    }
    rect(40*j +12, 24, 10, 10);
    i++;
  }

    stroke(255);
    strokeWeight(1);

  if (generation > 150){
    return;
  }
  pushMatrix();
    boolean [] inprogressCells = new boolean[200];
    int first = 0;
    int last = 0;
    for (int k = 0; k < 200; k++){
      if (first == 0 && elements[k]){
        first = k;
      }
      if (elements[k]){
        last = k;
      }
    }
    float delta = 2*PI/200;
    int segment = 0;
    translate(500,450);

    for (int k = 0; k < 200; k++){
      fill(255);
      if (elements[k]){
         stroke(cellColor[k], 150);
          fill(cellColor[k], 3);
          float theta1 = segment * delta;
          float theta2 = theta1 + delta;
          arc(0,0, 5*generation, 5*generation,theta1, theta2);
      }
      segment++;
 
      cellColor[k] = ruleColor[0];
      if (bits[0]){
        if (!elements[k - 1] && !elements[k] && !elements[k + 1]){
          inprogressCells[k] = true;
          cellColor[k] = ruleColor[0]
        }
      }
      if (bits[1]){
        if (!elements[k - 1] && !elements[k] && elements[k + 1]){
          inprogressCells[k] = true;
          cellColor[k] = ruleColor[1];
        }
      }
      if (bits[2]){
        if (!elements[k - 1] && elements[k] && !elements[k + 1]){
          inprogressCells[k] = true;
          cellColor[k] = ruleColor[2];
         }
      }
      if (bits[3]){
        if (!elements[k - 1] && elements[k] && elements[k + 1]){
          inprogressCells[k] = true;
          cellColor[k] = ruleColor[3];
        }
      }
      if (bits[4]){
        if (elements[k - 1] && !elements[k] && !elements[k + 1]){
          inprogressCells[k] = true;
          cellColor[k] = ruleColor[4];
        }
      }
      if (bits[5]){
        if (elements[k - 1] && !elements[k] && elements[k + 1]){
          inprogressCells[k] = true;
          cellColor[k] = ruleColor[5];
        }
      }
      if (bits[6]){
        if (elements[k - 1] && elements[k] && !elements[k + 1]){
          inprogressCells[k] = true;
          cellColor[k] = ruleColor[6];
        }
      }
      if (bits[7]){
        if (elements[k - 1] && elements[k] && elements[k + 1]){
          inprogressCells[k] = true;
          cellColor[k] = ruleColor[7];
        }
      }
    }
    for (int p = 0; p < 200; p++){
      elements[p] = inprogressCells[p];
    }
  stroke(100,0,0);
  rule = 0;
  for (int b = 0; b < 8; b++){
    if (bits[b]){
      rule += Math.pow(2, b);
    }
  }
  popMatrix();
  fill(255);
  stroke(255);
  rect(480,3,90,16);
  fill(0);
  text("Rule: " + rule, 490, 15);
  generation++;
}


void mouseClicked() {
  int j = 0;
  for (int i = 7; i >= 0; i--){
    if (mouseX > 40 * i && mouseX < 40 * i + 40 && mouseY > 5 && mouseY < 50){ 
      bits[j] = !bits[j];
    }
    j++;
  }
  generation = 0;
}

void mouseMoved() {
  int j = 0;
  for (int i = 7; i >= 0; i--){
    highLightBits[j] = false;
    if (mouseX > 40 * i && mouseX < 40 * i + 40 && mouseY > 5 && mouseY < 50){ 
      highLightBits[j] = true;
    }
    j++;
  }
}

