package com.openschoolgames.unitconversion;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class UnitConversionTest {

	@Test
	public void fToCTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("32 degrees F", 0.0, uc.convert("f", "c", 32.0), 0.00001);
		assertEquals("212 degrees F", 100.0, uc.convert("f", "c", 212.0), 0.00001);
	}

	@Test
	public void cToFTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees C", 32.0, uc.convert("c", "f", 0.0), 0.00001);
		assertEquals("100 degrees C", 212.0, uc.convert("c", "f", 100.0), 0.00001);
	}

	@Test
	public void cToKTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees C", 273.15, uc.convert("c", "k", 0.0), 0.00001);
		assertEquals("100 degrees C", 373.15, uc.convert("c", "k", 100.0), 0.00001);
	}
	
	@Test
	public void kToCTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees K", -273.15, uc.convert("k", "c", 0.0), 0.00001);
		assertEquals("273.15 degrees K", 0.0, uc.convert("k", "c", 273.15), 0.00001);
	}
	
	@Test
	public void kToFTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees K", -459.67, uc.convert("k", "f", 0.0), 0.00001);
		assertEquals("255.37222222 degrees K", 0.0, uc.convert("k", "f", 255.37222222), 0.00001);
	}
	
	@Test
	public void fToKTest() {
		UnitConversion uc = new UnitConversion();
		assertEquals("0 degrees F", 255.37222222, uc.convert("f", "k", 0.0), 0.00001);
		assertEquals("-459.67 degrees F", 0.0, uc.convert("f", "k", -459.67), 0.00001);
	}
}
