package com.openschoolgames.evaluator;

import org.junit.Test;

import com.openschoolgames.reader.Reader;

import static org.junit.Assert.assertEquals;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

import net.objecthunter.exp4j.Expression;
import net.objecthunter.exp4j.ExpressionBuilder;

/**
 * Evaluator test
 * 
 * @see <a href="http://www.objecthunter.net/exp4j/">exp4j</a>
 * @author charlie
 *
 */
public class EvaluatorTest {

	@Test
	public void addTest() {
		Map<String, Double> valueMap = new HashMap<String, Double>();
		valueMap.put("x", 2.3);
		valueMap.put("y", 3.14);

		Evaluator e = new Evaluator();
		e.setValueMap(valueMap);
		Reader reader = new Reader();
		int[] primaryKeys = { 0 };
		final String csvData = "name,expression\nexpression1, x + y";
		InputStream inputStream = new ByteArrayInputStream(csvData.getBytes(StandardCharsets.UTF_8));
		final Map<String, Map<String, String>> expressionMap = reader.readCSV(primaryKeys, inputStream);
		final String expression = expressionMap.get("expression1").get("expression");

		assertEquals("2.3 + 3.14", 5.44, e.evaluate(expression), 0.0001);
		valueMap.put("x", 2.0);
		valueMap.put("y", 3.0);
		assertEquals("2 + 3", 5, e.evaluate(expression), 0.0001);
	}

	@Test
	public void sinSquaredPlusCosSquaredTest() {
		Map<String, Double> valueMap = new HashMap<String, Double>();
		valueMap.put("x", 2.3);

		Evaluator e = new Evaluator();
		e.setValueMap(valueMap);
		Reader reader = new Reader();
		int[] primaryKeys = { 0 };
		final String csvData = "name,expression\nexpression1, sin(x)^2 + cos(x)^2";
		InputStream inputStream = new ByteArrayInputStream(csvData.getBytes(StandardCharsets.UTF_8));
		final Map<String, Map<String, String>> expressionMap = reader.readCSV(primaryKeys, inputStream);
		final String expression = expressionMap.get("expression1").get("expression");		
		assertEquals("", 1.0, e.evaluate(expression), 0.0001);
		valueMap.put("x", 2.0);
		assertEquals("", 1.0, e.evaluate(expression), 0.0001);
	}

	@Test
	public void evaluatorTest() {
		Map<String, Double> valueMap = new HashMap<String, Double>();
		valueMap.put("A1", 1.0);
		valueMap.put("C1", 2.0);
		valueMap.put("A2", 3.0);
		valueMap.put("C2", 5.0);
		valueMap.put("intercept", 7.0);

		Evaluator e = new Evaluator();
		e.setValueMap(valueMap);
		Reader reader = new Reader();
		final String name = "test_expressions.csv";
		int[] primaryKeys = { 0 };
		final InputStream inputStream = Evaluator.class.getResourceAsStream(name);
		final Map<String, Map<String, String>> expressionMap = reader.readCSV(primaryKeys, inputStream);
		final String expression = expressionMap.get("expression1").get("expression");
		assertEquals("", 24.0, e.evaluate(expression), 0.00001);
	}

	@Test
	public void evaluatorMathTest() {
		final Map<String, Double> valueMap = new HashMap<String, Double>();
		valueMap.put("A", 1.0);
		valueMap.put("B", 2.0);
		valueMap.put("C", 3.0);
		valueMap.put("D", 24.0);
		valueMap.put("E", 8.0);

		final Evaluator evaluator = new Evaluator();
		evaluator.setValueMap(valueMap);
		final Reader reader = new Reader();
		int[] primaryKeys = { 0 };
		final String csvData = "name,expression\nexpression1, A + ((B - C) * (D / E))\nexpression2, A + B";
		InputStream inputStream = new ByteArrayInputStream(csvData.getBytes(StandardCharsets.UTF_8));
		final Map<String, Map<String, String>> expressionMap = reader.readCSV(primaryKeys, inputStream);
		final String expression1 = expressionMap.get("expression1").get("expression");
		assertEquals("expression 1", -2.0, evaluator.evaluate(expression1), 0.00001);
		final String expression2 = expressionMap.get("expression2").get("expression");
		assertEquals("expression 2", 3.0, evaluator.evaluate(expression2), 0.00001);
	}

	@Test
	public void evaluatorModifiedValueMapTest() {
		final Map<String, Double> valueMap = new HashMap<String, Double>();
		valueMap.put("A", 1.0);
		valueMap.put("B", 2.0);
		valueMap.put("C", 3.0);
		valueMap.put("D", 24.0);
		valueMap.put("E", 3.0);

		final Evaluator evaluator = new Evaluator();
		evaluator.setValueMap(valueMap);
		final Reader reader = new Reader();
		int[] primaryKeys = { 0 };
		final String csvData = "name,expression\nexpression1, A + ((B - C) * (D / E))\nexpression2, A + B";
		InputStream inputStream = new ByteArrayInputStream(csvData.getBytes(StandardCharsets.UTF_8));
		final Map<String, Map<String, String>> expressionMap = reader.readCSV(primaryKeys, inputStream);
		final String expression1 = expressionMap.get("expression1").get("expression");
		assertEquals("expression 1", -7.0, evaluator.evaluate(expression1), 0.00001);

		valueMap.put("A", 1.0);
		valueMap.put("B", 1.0);
		valueMap.put("C", 1.0);
		valueMap.put("D", 1.0);
		valueMap.put("E", 1.0);
		assertEquals("expression 1 with modified values", 1.0, evaluator.evaluate(expression1), 0.00001);
	}
}
