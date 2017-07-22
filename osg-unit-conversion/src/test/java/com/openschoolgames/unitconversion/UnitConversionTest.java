package com.openschoolgames.unitconversion;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class UnitConversionTest {

	@Test
	public void fToCTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("32 degrees F", 0.0, uc.convert(32.0, "f", "c"), 0.00001);
		assertEquals("212 degrees F", 100.0, uc.convert(212.0, "f", "c"), 0.00001);
	}

	@Test
	public void cToFTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees C", 32.0, uc.convert(0.0, "c", "f"), 0.00001);
		assertEquals("100 degrees C", 212.0, uc.convert(100.0, "c", "f"), 0.00001);
	}

	@Test
	public void cToKTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees C", 273.15, uc.convert(0.0, "c", "k"), 0.00001);
		assertEquals("100 degrees C", 373.15, uc.convert(100.0, "c", "k"), 0.00001);
	}
	
	@Test
	public void kToCTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees K", -273.15, uc.convert(0.0, "k", "c"), 0.00001);
		assertEquals("273.15 degrees K", 0.0, uc.convert(273.15, "k", "c"), 0.00001);
	}
	
	@Test
	public void kToFTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees K", -459.67, uc.convert(0.0, "k", "f"), 0.00001);
		assertEquals("255.37222222 degrees K", 0.0, uc.convert(255.37222222, "k", "f"), 0.00001);
	}
	
	@Test
	public void fToKTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees F", 255.37222222, uc.convert(0.0, "f", "k"), 0.00001);
		assertEquals("-459.67 degrees F", 0.0, uc.convert(-459.67, "f", "k"), 0.00001);
	}
	
	@Test
	public void ozToLbTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("16 oz", 1.0, uc.convert(16.0, "oz", "lb"), 0.00001);
		assertEquals("0 oz", 0.0, uc.convert(0.0, "oz", "lb"), 0.00001);
	}
	
	@Test
	public void lbToOzTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("1 lb", 16.0, uc.convert(1.0, "lb", "oz"), 0.00001);
		assertEquals("0 lb", 0.0, uc.convert(0.0, "lb", "oz"), 0.00001);
	}
}
