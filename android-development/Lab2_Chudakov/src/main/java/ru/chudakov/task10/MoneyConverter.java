package ru.chudakov.task10;

import javax.money.Monetary;
import javax.money.convert.MonetaryConversions;

public class MoneyConverter {

    public double convertToRuble(double value, Currency currency) {
        var amount = Monetary.getDefaultAmountFactory()
                .setCurrency(getCurrency(currency))
                .setNumber(value).create();

        var conversionRUB = MonetaryConversions.getConversion("RUB");
        var convertedAmount = amount.with(conversionRUB);

        return convertedAmount.getNumber().doubleValueExact();
    }

    private String getCurrency(Currency currency) {
        switch (currency) {
            case EURO:
                return "EUR";
            case DOLLAR:
                return "USD";
            case YUAN:
                return "CNY";
            case RUBLE:
                return "RUB";
            default:
                return null;
        }
    }
}
