var bound = false;
var clear = false;
var bindName = '';
function bindInputs(name) {
  if (name !== undefined){
    bindName = name;
  }
  var pjs = Processing.getInstanceById(bindName);
  if(pjs!=null) {
    pjs.bindInputsJS(this);
    bound = true;
  }
  if(!bound) setTimeout(bindInputs, 250); 
}

function getAValue(){
  return getValue(document.getElementById("a_input").value);
}

function getBValue(){
  return getValue(document.getElementById("b_input").value);
}

function getHValue(){
  return getValue(document.getElementById("h_input").value);
}


function getCanClear(){
  var currentClear = clear;
  clear = false;
  return currentClear;
}

function setClear(){
  clear = true;
} 

function getValue(value){
  return parseInt(value.replace(/\D/g,''));
} 
