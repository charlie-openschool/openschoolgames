EnumModifier 
============
EnumModifier wraps the Java reflection calls that allows us to add values to an enum at runtime.
This ability can be very useful during testing. For example we might enumerate some valid character encoding with an enum like this:

    enum ENCODINGS {
      CP1252("CP1252),
      UTF8("UTF-8");
    
      private final String encoding; 
      ENCODINGS(String encoding){
        this.encoding = encoding;
      }
      
      public String getEncoding(){
        return this.encoding;
      }
    }

	
