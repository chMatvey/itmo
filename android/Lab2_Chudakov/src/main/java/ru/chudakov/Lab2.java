package ru.chudakov;

import ru.chudakov.task10.Currency;
import ru.chudakov.task10.MoneyConverter;
import ru.chudakov.task8.AirBusA320;
import ru.chudakov.task8.AirBusA380;
import ru.chudakov.task9.Student;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.MessageFormat;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.stream.Collectors;

public class Lab2 {

    public void task1() {
        System.out.println("task 1");

        int seven = 7;
        int ten = 10;
        int result = seven + ten;

        System.out.println(result);
    }

    public void task2() {
        System.out.println("task 2");

        String s1 = "one";
        String s2 = "two";
        String s3 = "three";
        String s4 = "four";

        System.out.println(MessageFormat.format("{0} {1} {2} {3}", s1, s2, s3, s4));
        System.out.println(MessageFormat.format("{0}\n{1}\n{2}\n{3}", s1, s2, s3, s4));
    }

    public void task3() throws IOException {
        System.out.println("task 3");
        System.out.println("Input 5 variables");

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String lines = br.readLine();

        List<String> variables = Arrays.asList(lines.trim().split("\\s+"));

        HashSet<String> set = new HashSet<>();
        HashMap<String, Integer> map = new HashMap<>();

        variables.forEach(v -> {
            if (set.contains(v)) {
                map.put(v, map.getOrDefault(v, 1) + 1);
            } else {
                set.add(v);
            }
        });

        if (map.isEmpty()) {
            System.out.println("All different");
        } else {
            map.forEach((k, v) -> {
               int count = v;
                while (count > 0) {
                    System.out.print(k + " ");
                    count--;
                }
            });
        }
    }

    public void task4() throws IOException {
        System.out.println("Task 4");
        System.out.println("Input number of points");

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();

        try {
            int countPoint = Integer.parseInt(input);

            if (countPoint < 0 || countPoint > 100) {
                System.out.println("Maximum score 100, minimum - 0");
            } else {
                System.out.print("Mark is ");

                if (countPoint <= 60) {
                    System.out.println("2");
                } else if (countPoint <= 74) {
                    System.out.println("3");
                } else if (countPoint <= 90) {
                    System.out.println("4");
                } else {
                    System.out.println("5");
                }
            }
        } catch (NumberFormatException e) {
            System.out.println("Input is not correct");
        }
    }

    public void task5() throws IOException {
        System.out.println("Task 5");
        System.out.println("Input number of points");

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();

        try {
            int countPoint = Integer.parseInt(input);

            Mark mark = getMark(countPoint);

            if (mark == null) {
                System.out.println("Maximum score 100, minimum - 0");
            } else {
                System.out.print("Mark is ");

                switch (mark) {
                    case TWO: {
                        System.out.print("2");
                        break;
                    }
                    case THREE: {
                        System.out.print("3");
                        break;
                    }
                    case FOUR: {
                        System.out.print("4");
                    }
                    default: {
                        System.out.print("5");
                    }
                }
            }
        } catch (NumberFormatException e) {
            System.out.println("Input is not correct");
        }
    }

    private Mark getMark(int points) {
        if (points < 0 || points > 100) {
            return null;
        }

        if (points <= 60) {
            return Mark.TWO;
        } else if (points <= 74) {
            return Mark.THREE;
        } else if (points <= 90) {
            return Mark.FOUR;
        } else {
            return Mark.FIFE;
        }
    }

    public void task6() throws IOException {
        System.out.println("task 6");
        System.out.println("Input 15 numbers");

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String lines = br.readLine();

        String[] variables = lines.trim().split("\\s+");
        List<Integer> numbers = Arrays.stream(variables).map(Integer::parseInt).sorted().collect(Collectors.toList());

        numbers.forEach(System.out::println);
    }

    public void task7() {
        int[] array = new int[] {0, 1, 2, 3, 4, 5};

        try {
            System.out.println(array[7]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println(e.getClass());
            System.out.println(e.getMessage());
        }
    }

    public void task8() {
        AirBusA320 a320 = new AirBusA320(1, 2);
        AirBusA380 a380 = new AirBusA380(1,2,3);
    }

    public void task9() {
        Student student = new Student();
    }

    public void task10() {
        MoneyConverter converter = new MoneyConverter();

        System.out.println(converter.convertToRuble(500, Currency.DOLLAR));
    }
}
