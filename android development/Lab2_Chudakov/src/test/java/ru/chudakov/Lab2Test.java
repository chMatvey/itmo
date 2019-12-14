package ru.chudakov;

import org.junit.jupiter.api.Test;

import java.text.MessageFormat;
import java.util.HashMap;
import java.util.Map;

class Lab2Test {

    @Test
    void task1() {
        int seven = 7;
        int ten = 10;
        int result = seven + ten;

        System.out.println(result);
    }

    @Test
    void task2() {
        String s1 = "one";
        String s2 = "two";
        String s3 = "three";
        String s4 = "four";

        System.out.println(MessageFormat.format("{0} {1} {2} {3}", s1, s2, s3, s4));
        System.out.println(MessageFormat.format("{0}\n{1}\n{2}\n{3}", s1, s2, s3, s4));
    }

    @Test
    void task3() {
        String[] variables = "один два два три два".trim().split("\\s+");
        HashMap<String, Integer> hashMap = new HashMap<>(variables.length);
        boolean isAllDifferent = true;

        for (String variable : variables) {
            if (hashMap.containsKey(variable)) {
                isAllDifferent = false;
                hashMap.put(variable, hashMap.get(variable) + 1);
            } else {
                hashMap.put(variable, 1);
            }
        }

        for (Map.Entry<String, Integer> entry : hashMap.entrySet()) {
            if (entry.getValue() == 1 && isAllDifferent) {
                System.out.println(entry.getKey());
            } else {
                int count = entry.getValue();
                while (count > 0) {
                    System.out.println(entry.getKey());
                    count--;
                }
            }
        }
    }
}