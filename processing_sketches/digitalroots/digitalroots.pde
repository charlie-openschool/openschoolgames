Inputs inputs;

void setup()
{
  size(700, 700);
  background(255);
  stroke(100,0,0);
  frameRate(1);
}

int rootsLength = 0;
int step = 0;

void draw() {
  if (this.inputs != null){
    List numberList = this.inputs.getNumberList();
    if (rootsLength != numberList.length) {
      step = 0;
      rootsLength = numberList.length;
    }
    if (step < rootsLength){    
      if (step == 0){
        background(0);
    }

      float midHorz = width/2;
      float midVert = height/2 + height/8;
      step++;
      int x = 0;
      int y = 0;
      translate(midHorz, midVert);
      for (int i = 0; i < step; i++){
        int root = 1+((numberList[i]-1) % 9);
        setRootColor(root);
        rect(x,y,root * 15, 10);
        translate(root * 15, 11);
        rotate(-1*PI/2);
      }
    }
  }
}

void setRootColor(int root){
  if (root % 9 == 0){
    fill(200,0,0);
  } else if (root % 8 == 0){
    fill(0,200,0);
  } else if (root % 7 == 0){
    fill(0,0,200);
  } else if (root % 6 == 0){
    fill(0,200,200);
  } else if (root % 5 == 0){
    fill(200,0,200);
  } else if (root % 4 == 0){
    fill(200,200,0);
  } else if (root % 3 == 0){
    fill(0,100,200);
  } else if (root % 2 == 0){
    fill(100,0,200);
  } else if (root % 1 == 0){
    fill(100,100,100);
  } else {
  fill(200,100,100);
  }
}


void bindInputsJS(Inputs inputs){
  this.inputs = inputs;
}