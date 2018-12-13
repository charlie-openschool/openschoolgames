var trigonometricInputsJS = {};
(function(impl) { 
    var bound = false;
    var processingInstanceName = '';
 
    impl.bindInputs = function(name) {
      if (name !== undefined){
        processingInstanceName = name;
      }
      var pjs = Processing.getInstanceById(processingInstanceName);
      if(pjs!=null) {
        pjs.bindInputsJS(impl);
        bound = true;
      }
     if(!bound) setTimeout(impl.bindInputs, 250); 
}

  getValue = function(value){
    var tokens = value.split("=");
    var val = null;
    if (tokens && tokens.length > 1){
      val = parseFloat(tokens[1]);
    }
    return !isNaN(val) ? val : null;
  }

  impl.getXPeriod = function(){
    return getValue(document.getElementById("x_period_input").value);
  }

  impl.getYPeriod = function(){
    return getValue(document.getElementById("y_period_input").value);
  }

  impl.getXAmplitude = function(){
    return getValue(document.getElementById("x_amplitude_input").value);
  }

  impl.getYAmplitude = function(){
    return getValue(document.getElementById("y_amplitude_input").value);
  }
})(trigonometricInputsJS);  
