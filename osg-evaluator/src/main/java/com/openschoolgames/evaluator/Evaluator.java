package com.openschoolgames.evaluator;

import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import net.objecthunter.exp4j.Expression;
import net.objecthunter.exp4j.ExpressionBuilder;

public class Evaluator {
	static final Set<String> operators = new HashSet<String>();
	static final Set<String> functions = new HashSet<String>();
	static {
		operators.add("+");
		operators.add("-");
		operators.add("/");
		operators.add("*");
		operators.add("%");
		operators.add("^");
		operators.add("(");
		operators.add(")");
		functions.add("sin");
		functions.add("cos");
		functions.add("log");
		functions.add("sqrt");
		functions.add("tan");
		functions.add("exp");
	}
	
	
	private Map<String, Double> valueMap;
	
	public void setValueMap(final Map<String, Double> valueMap){
		this.valueMap = valueMap;
	}
	
	public double evaluate(final String expression) {
		final Set<String> variables = getVariables(expression);
		final ExpressionBuilder expressionBuilder = new ExpressionBuilder(expression);
		expressionBuilder.variables(variables);
		final Expression ex = expressionBuilder.build();
		for (final String variable : variables) {
			ex.setVariable(variable, valueMap.get(variable));
		}
		return ex.evaluate();
	}
	
	private Set<String> getVariables(final String expression){
		final Set<String> variables = new HashSet<String>();
		String trimmedExpression = expression;
		for (final String operator : operators){
			trimmedExpression = trimmedExpression.replaceAll("\\" + operator, " ");
		}
		
		final String [] candidateVariables = trimmedExpression.split(" ");
		for (final String candidate : candidateVariables){
		boolean matchesFunction = false;
		for (final String function : functions){
			if (candidate.matches("^" + function)){
				matchesFunction = true;
				break;
			}
		}
			if (candidate.length() > 0 && !matchesFunction && !candidate.matches("^\\d+")){
				variables.add(candidate);
			}
		}
		return variables;
	}
}
