package com.openschoolgames.unitconversion;

import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;

import com.openschoolgames.evaluator.Evaluator;
import com.openschoolgames.reader.Reader;

public class UnitConversion {
	
	public double convert(final String from, final String to, final double value){
		final Reader reader = new Reader();
		final String name = "temperature_conversions.csv";
		int[] primaryKeys = { 0 };
		final InputStream in = UnitConversion.class.getResourceAsStream(name);
		final Map<String, Map<String, String>> unitConversionMap = reader.readCSV(primaryKeys, in);
		final Map<String, Double> valueMap = new HashMap<String, Double>();
		valueMap.put(from, value);
		final Evaluator ev = new Evaluator();
		ev.setValueMap(valueMap);
		return ev.evaluate(unitConversionMap.get(from + " to " + to).get("expression"));
	}
}
