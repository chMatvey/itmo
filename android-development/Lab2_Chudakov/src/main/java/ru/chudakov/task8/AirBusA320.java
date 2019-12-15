package ru.chudakov.task8;

public class AirBusA320 {

    private int speed;

    private int runLength;

    public AirBusA320(int speed, int runLength) {
        this.speed = speed;
        this.runLength = runLength;
    }

    public void printSpeed() {
        System.out.println(speed);
    }

    public void printRunLength() {
        System.out.println(runLength);
    }
}
