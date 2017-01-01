package com.openschoolgames.reader;

import static org.junit.Assert.assertEquals;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.Map;

import org.junit.Test;

public class ReaderTest {

	@Test
	public void fourRowsFourColumnsTest() {
		Reader reader = new Reader();
		final String name = "four_by_four_test.csv";
		int[] primaryKeys = { 0 };
		final InputStream in = Reader.class.getResourceAsStream(name);
		Map<String, Map<String, String>> table = reader.readCSV(primaryKeys, in);
		assertEquals("Row 1 value 1", "r1v1", table.get("r1v1").get("h1"));
		assertEquals("Row 1 value 2", "r1v2", table.get("r1v1").get("h2"));
	}

	@Test
	public void compositeKeyTest() {
		int[] primaryKeys = { 0, 1 };
		Reader reader = new Reader();
		final String csvData = "h1,h2,h3\r\nr1v1,r1v2,r1v3\r\nr2v1,r2v2,r2v3";
		InputStream in = new ByteArrayInputStream(csvData.getBytes(StandardCharsets.UTF_8));
		Map<String, Map<String, String>> table = reader.readCSV(primaryKeys, in);
		assertEquals("row 1 value 1", "r1v1", table.get("r1v1r1v2").get("h1"));
		assertEquals("row 1 value 3", "r1v3", table.get("r1v1r1v2").get("h3"));
		assertEquals("row 2 value 2", "r2v2", table.get("r2v1r2v2").get("h2"));
	}

	@Test
	public void nonadjacentCompositeKeyTest() {
		int[] primaryKeys = { 1, 3 };
		Reader reader = new Reader();
		final String csvData = "h1,h2,h3,h4\r\nr1v1,r1v2,r1v3,r1v4\r\nr2v1,r2v2,r2v3,r2v4";
		InputStream in = new ByteArrayInputStream(csvData.getBytes(StandardCharsets.UTF_8));
		Map<String, Map<String, String>> table = reader.readCSV(primaryKeys, in);
		assertEquals("row 1 value 1", "r1v1", table.get("r1v2r1v4").get("h1"));
		assertEquals("row 1 value 3", "r1v3", table.get("r1v2r1v4").get("h3"));
		assertEquals("row 2 value 4", "r2v2", table.get("r2v2r2v4").get("h2"));
	}
}
