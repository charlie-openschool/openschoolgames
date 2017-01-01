EnumModifier 
============
EnumModifier wraps the Java reflection calls that allows us to add values to an enum at runtime.
This ability can be very useful during testing. For example we might enumerate some valid character encoding with an enum like this:

    enum ENCODINGS {
      CP1252("CP1252"),
      UTF8("UTF-8");
    
      private final String encoding; 
      ENCODINGS(String encoding){
        this.encoding = encoding;
      }
      
      public String getEncoding() {
        return this.encoding;
      }
    }

	
With the ENCODINGS enum we can be sure that we only use valid encodings. The enum works better than static strings because we can enforce its use in method signitures.

    public static String encode(String str, ENCODINGS encoding){
      String encoded = null;
      try {	  
        encoded = URLEncoder.encode(str, encoding.getEncoding());
      } catch (UnsupportedEncodingException e){
	    throw new RuntimeException(e); 
	  }
      return encoded;
    }	  

Now we can write cleaner code when we need to use URLEncoder. We no longer need to catch a checked exception and we can be reasonably certain that we will never get a runtime exception, however, it would be nice to be able to force the code into the exception condition during testing.

    EnumModifier.addEnumValue(ENCODINGS.class, "invalidType", "invalidValue");
	ENCODINGS[] modifiedEnums = ENCODINGS.values();
    String encoded = encode("can we encode this?", modifiedEnums[2]); 

Notice how we used a list to access our new value? Does it make sense that we cannot just use ENCODINGS.invalidType ? 	
	
