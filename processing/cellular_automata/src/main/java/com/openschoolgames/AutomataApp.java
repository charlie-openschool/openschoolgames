package com.openschoolgames;

import processing.core.PApplet;

public class AutomataApp extends PApplet {

    boolean[] bits = new boolean[8];
    boolean[] highLightBits = new boolean[8];
    boolean[] cells = new boolean[200];
    color[] ruleColor = new color[8];
    color[] cellColor = new color[200];
    boolean drawStandard = false;
    boolean fillInCircles = false;
    int drawMode = 0;

    public static void main(String[] args) {
        PApplet.main("com.openschoolgames.AutomataApp");
    }

    public void settings() {
        size(1000, 900);
    }

    public void setup() {
        background(250);
        strokeWeight(1);
        frameRate(24);
        initializeGlobals();
    }

    int generation = 0;
    int cellWidth = 5;
    int rule = 0;

    public void draw() {
        if (generation == 0) {
            for (int n = 0; n < cells.length; n++) {
                cells[n] = false;
            }
            cells[100] = true;
            background(250);
        }

        drawRuleSelectionButtons();
    
        if (generation > 150) {
            return;
        }
        pushMatrix();
        float delta = 2 * PI / 200;
        int segment = 0;
        translate(500, 450);
        boolean[] inprogressCells = new boolean[200];
        for (int k = 1; k < 199; k++) {
            fill(255);
            if (cells[k]) {
                if (drawStandard) {
                    stroke(cellColor[k].red, cellColor[k].green, cellColor[k].blue, 15);
                    fill(cellColor[k].red, cellColor[k].green, cellColor[k].blue, 15);
                    rect(5 * k - 500, generation * 5 - 400, cellWidth, cellWidth);
                }
                stroke(cellColor[k].red, cellColor[k].green, cellColor[k].blue, 150);
                fill(cellColor[k].red, cellColor[k].green, cellColor[k].blue, 3);// 150);
                float theta1 = segment * delta;
                float theta2 = theta1 + delta;
                arc(0, 0, 5 * generation, 5 * generation, theta1, theta2);
            } else {
                if (fillInCircles) {
                    float theta1 = segment * delta;
                    float theta2 = theta1 + delta;
                    fill(cellColor[k].red, cellColor[k].green, cellColor[k].blue, 0);
                    arc(0, 0, 5 * generation, 5 * generation, theta1, theta2);
                }
            }
            segment++;
           
            cellColor[k] = ruleColor[0];
            if (bits[0]) {
                if (!cells[k - 1] && !cells[k] && !cells[k + 1]) {
                    inprogressCells[k] = true;
                    cellColor[k] = ruleColor[0];
                }
            }
            if (bits[1]) {
                if (!cells[k - 1] && !cells[k] && cells[k + 1]) {
                    inprogressCells[k] = true;
                    cellColor[k] = ruleColor[1];
                }
            }
            if (bits[2]) {
                if (!cells[k - 1] && cells[k] && !cells[k + 1]) {
                    inprogressCells[k] = true;
                    cellColor[k] = ruleColor[2];
                }
            }
            if (bits[3]) {
                if (!cells[k - 1] && cells[k] && cells[k + 1]) {
                    inprogressCells[k] = true;
                    cellColor[k] = ruleColor[3];
                }
            }
            if (bits[4]) {
                if (cells[k - 1] && !cells[k] && !cells[k + 1]) {
                    inprogressCells[k] = true;
                    cellColor[k] = ruleColor[4];
                }
            }
            if (bits[5]) {
                if (cells[k - 1] && !cells[k] && cells[k + 1]) {
                    inprogressCells[k] = true;
                    cellColor[k] = ruleColor[5];
                }
            }
            if (bits[6]) {
                if (cells[k - 1] && cells[k] && !cells[k + 1]) {
                    inprogressCells[k] = true;
                    cellColor[k] = ruleColor[6];
                }
            }
            if (bits[7]) {
                if (cells[k - 1] && cells[k] && cells[k + 1]) {
                    inprogressCells[k] = true;
                    cellColor[k] = ruleColor[7];
                }
            }
        }
        for (int p = 0; p < 200; p++) {
            cells[p] = inprogressCells[p];
        }
        stroke(100, 0, 0);
        rule = 0;
        for (int b = 0; b < 8; b++) {
            if (bits[b]) {
                rule += Math.pow(2, b);
            }
        }
        popMatrix();
        fill(255);
        stroke(255);
        rect(480, 3, 90, 16);
        fill(0);
        text("Rule: " + rule, 490, 15);
        // saveFrame("automata_" + frameCount);
        generation++;
    }

    public void mouseClicked() {
        int j = 0;
        boolean ruleSelected = false;
        for (int i = 7; i >= 0; i--) {
            //if (mouseX > 40 * i + 5 && mouseX < 40 * i + 30 && mouseY > 15 && mouseY < 40) {
                if (mouseX > 40 * i && mouseX < 40 * i + 40 && mouseY > 5 && mouseY < 40) {
                bits[j] = !bits[j];
                ruleSelected = true;
            }
            j++;
        }
        generation = 0;
        
        if (!ruleSelected) {
            drawMode++;
            if (drawMode > 2) {
                drawMode = 0;
            }
            if (drawMode == 0) {
                drawStandard = false;
                fillInCircles = false;
            }
            if (drawMode == 1) {
                drawStandard = true;
                fillInCircles = false;
            }
            if (drawMode == 2) {
                drawStandard = false;
                fillInCircles = true;
            }
        }
    }

    public void mouseMoved() {
        int j = 0;
        for (int i = 7; i >= 0; i--) {
            highLightBits[j] = false;
            if (mouseX > 40 * i + 5 && mouseX < 40 * i + 30 && mouseY > 15 && mouseY < 40) {
                highLightBits[j] = true;
            }
            j++;
        }
    }

    private void initializeGlobals() {
        ruleColor[0] = new color(0, 0, 0);
        ruleColor[1] = new color(100, 0, 0);
        ruleColor[2] = new color(200, 0, 0);
        ruleColor[3] = new color(200, 200, 0);
        ruleColor[4] = new color(200, 100, 0);
        ruleColor[5] = new color(0, 0, 100);
        ruleColor[6] = new color(0, 0, 200);
        ruleColor[7] = new color(100, 0, 200);
        bits[1] = true;
        bits[4] = true;
        for (int i = 0; i < 200; i++) {
            cellColor[i] = new color(0, 0, 0);
        }
    }

    private void drawRuleSelectionButtons() {
        stroke(0);
        int i = 0;
        for (int j = 7; j >= 0; j--) {
            fill(255);
            if (i == 4 || i == 5 || i == 6 || i == 7) {
                fill(ruleColor[i].red, ruleColor[i].green, ruleColor[i].blue, 150);
            }
            rect(40 * j, 10, 10, 10);
            fill(255);
            if (i == 2 || i == 3 || i == 6 || i == 7) {
                fill(ruleColor[i].red, ruleColor[i].green, ruleColor[i].blue, 150);
            }
            rect(40 * j + 12, 10, 10, 10);
            fill(255);
            if (i % 2 == 1) {
                fill(ruleColor[i].red, ruleColor[i].green, ruleColor[i].blue, 150);
            }

            rect(40 * j + 24, 10, 10, 10);
            strokeWeight(5);
            if (highLightBits[i]) {
                stroke(0);
            } else {
                stroke(150);
            }
            rect(40 * j + 12, 24, 10, 10);
            stroke(0);
            strokeWeight(1);
            fill(255);
            if (bits[i]) {
                fill(ruleColor[i].red, ruleColor[i].green, ruleColor[i].blue, 150);
            }
            rect(40 * j + 12, 24, 10, 10);
            i++;
        }
    }

    private static class color {
        color(int red, int green, int blue) {
            this.red = red;
            this.green = green;
            this.blue = blue;
        }

        int red = 0;
        int green = 0;
        int blue = 0;
    }
}
