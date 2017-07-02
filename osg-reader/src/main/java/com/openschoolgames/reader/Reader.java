package com.openschoolgames.reader;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Reader
 * <ul>
 * <li> readCSV </li>
 * </ul>
 * @author charlie
 *
 */
public class Reader {

	/**
	 * Read CSV
	 * <ol>
	 * <li>First row becomes column names
	 * <li>Every additional row becomes a value map keyed by column name
	 * <li>Each row map is keyed by the concatenation of primary column values
	 * </ol>
	 * @param primaryKeys -zero based
	 * @param inputStream
	 * @return tableMap -keyed by concatenation of primary keys
	 */
	public Map<String, Map<String, String>> readCSV(final int[] primaryKeys, final InputStream inputStream) {
		final Map<String, Map<String, String>> table = new HashMap<String, Map<String, String>>();
		final List<String> lines = getLines(inputStream);
		boolean header = true;
		String[] columns = null;
		for (final String line : lines) {
			final String[] tokens = line.split(",");
			if (header) {
				columns = tokens;
				header = false;
				continue;
			}
			
			final StringBuilder key = new StringBuilder();
			for (int i = 0; i < primaryKeys.length; i++) {
				key.append(tokens[primaryKeys[i]]);
			}
			
			final Map<String, String> row = new HashMap<String, String>();
			table.put(key.toString(), row);
			for (int i = 0; i < tokens.length; i++) {
				row.put(columns[i], tokens[i]);
			}
		}

		return table;
	}

	private static List<String> getLines(final InputStream in) {
		final List<String> lines = new ArrayList<String>();
		try {
			final BufferedReader reader = new BufferedReader(new InputStreamReader(in));
			String line = null;
			while ((line = reader.readLine()) != null) {
				lines.add(line);
			}
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
		return lines;
	}
}
