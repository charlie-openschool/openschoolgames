package com.openschoolgames.unitconversion;

import java.io.InputStream;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.openschoolgames.evaluator.Evaluator;
import com.openschoolgames.reader.Reader;

public class UnitConversion {

	public double convert(final double value, final String from, final String to) {
		final String unitConversionExpression = getUnitConversionExpression(from, to);
		final Map<String, Double> valueMap = new HashMap<String, Double>();
		valueMap.put(from, value);
		final Evaluator ev = new Evaluator();
		ev.setValueMap(valueMap);
		return ev.evaluate(unitConversionExpression);
	}

	private String getUnitConversionExpression(final String from, final String to) {
		final List<String> conversionFiles = Arrays.asList("temperature_conversions", "weight_conversions", "length_conversions");
		final Reader reader = new Reader();
		int[] primaryKeys = { 0 };
		for (final String conversionFile : conversionFiles) {
			final InputStream in = UnitConversion.class.getResourceAsStream(conversionFile + ".csv");
			if (in != null) {
				final Map<String, Map<String, String>> unitConversionMap = reader.readCSV(primaryKeys, in);
				if (unitConversionMap.get(from + " to " + to) != null) {
					return unitConversionMap.get(from + " to " + to).get("expression");
				}
			}
		}
		return null;
	}
}
