package com.openschoolgames;

import processing.core.PApplet;

/**
 * Lissajous Processing Applet
 * @author charlie
 *
 */
public class Lissajous extends PApplet {
	
	/**
	 * Constructor
	 */
	public Lissajous() {
		
	}

	boolean sizeSet = false;

	public void settings() {
		sizeSet = true;
		size(300, 300);
	}

	TrigonometricInputs inputs;

	public void setup() {
		if (!sizeSet) {
			size(300, 300);
		}
		background(155);
		frameRate(15);
	}

	void drawCurve(float xAmplitude, float yAmplitude, float xPeriod, float yPeriod, float phaseShift) {
		for (float theta = 0; theta < TWO_PI; theta += 0.01) {
			float x = xAmplitude * sin(xPeriod * theta);
			float y = yAmplitude * sin(yPeriod * theta + phaseShift);
			ellipse(x, y, 5, 5);
		}
	}

	float phaseShift = 0;

	public void draw() {
		background(155);
		translate(150, 150);
		float xPeriod = 3;
		float yPeriod = 5;
		float xAmplitude = 100;
		float yAmplitude = 100;
		if (this.inputs != null) {
			xPeriod = this.inputs.getXPeriod();
			yPeriod = this.inputs.getYPeriod();
			xAmplitude = this.inputs.getXAmplitude();
			yAmplitude = this.inputs.getYAmplitude();
		}
		phaseShift += .01;
		adjustColors(phaseShift);
		drawCurve(xAmplitude, yAmplitude, xPeriod, yPeriod, phaseShift);
	}

	void adjustColors(float r) {
		stroke(sin(r) * 128 + 128, 50, sin(r * PI / 2) * 128 + 128, 200);
	}

	void bindInputsJS(TrigonometricInputs inputs) {
		this.inputs = inputs;
	}
}
