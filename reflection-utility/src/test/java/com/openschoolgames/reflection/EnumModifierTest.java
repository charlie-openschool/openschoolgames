package com.openschoolgames.reflection;
import org.junit.Test;

import com.openschoolgames.reflection.EnumModifier;

import static org.junit.Assert.assertEquals;

public class EnumModifierTest {
	@Test
	public void addEnumValueTest(){
		assertEquals("Original number of values", 3, sampleEnum.values().length);
		EnumModifier.addEnumValue(sampleEnum.class, "four");
		assertEquals("After modify number of values", 4, sampleEnum.values().length);
		assertEquals("added value", "four", sampleEnum.values()[3].name());
	}
	
	@Test
	public void addEnumValueEnumConstructorTest(){
		assertEquals("Original number of values", 3, sampleEnumWithConstructor.values().length);
		EnumModifier.addEnumValue(sampleEnumWithConstructor.class, "FOUR", "four");
		assertEquals("After modify number of values", 4, sampleEnumWithConstructor.values().length);
		assertEquals("added value", "FOUR", sampleEnumWithConstructor.values()[3].name());
		assertEquals("added value", "four", sampleEnumWithConstructor.values()[3].getDisplayName());
	}

	public enum sampleEnum{
		one,
		two,
		three
	}
	
	public enum sampleEnumWithConstructor {
		ONE("one"),
		TWO("two"),
		THREE("three");
		
		private final String displayName;
		sampleEnumWithConstructor(String displayName){
			this.displayName = displayName;
		}
		
		public String getDisplayName(){
			return this.displayName;
		}
	}
}
