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

var len = 0;

function getValueList(value){
  var values = value.split('=');
  if (values.length > 1){
    values = values[1].split(",");
  } else {
    values = values[0].split(",");
  }

  var numberList = [];
  for (var i = 0; i < values.length; i++){
    if (values[i].length > 0){
      numberList[numberList.length] = Number(values[i]);
    }
  }
  return numberList;
} 

function getNumberList(){
  return getValueList(document.getElementById("a_input").value);
}
