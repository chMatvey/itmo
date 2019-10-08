package ru.chudakov;

import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

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
    void task3() throws IOException {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//        String lines = br.readLine();
//
//        String[] variables = lines.trim().split("\\s+");

        String[] variables = "один два два три два".trim().split("\\s+");

        List<String> list = new ArrayList<>(Arrays.asList(variables));

        System.out.println();
    }
}