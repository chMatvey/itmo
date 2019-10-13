package ru.chudakov.task8;

public class AirBusA380 extends AirBusA320 {

    private int passengerCapacity;

    public AirBusA380(int speed, int runLength, int passengerCapacity) {
        super(speed, runLength);

        this.passengerCapacity = passengerCapacity;
    }

    public void printPassengerCapacity() {
        System.out.println(passengerCapacity);
    }
}
