#pragma once
#include <string>
#include <iostream>

namespace dataTypeeeesnotUsed {


    // Перечисление для месяцев
    enum class Month {
        янв, фев, мар, апр, май, июн, июл, авг, сен, окт, ноя, дек
    };

    // Класс для даты
    struct Date {
        int day;
        int month;
        int year;

        bool operator==(const Date& other) const {
            return day == other.day && month == other.month && year == other.year;
        }

        std::string toString() const {
            const std::string monthNames[] = { "янв", "фев", "мар", "апр", "май", "июн",
                                              "июл", "авг", "сен", "окт", "ноя", "дек" };
            return std::to_string(day) + " " + monthNames[static_cast<int>(month)] + " " + std::to_string(year);
        }

        Date() : day(0), month(0), year(0) {}
        Date(int d, int m, int y) : day(d), month(m), year(y) {}
    };

    // Класс Продукт
    struct Product {
        long long barcode;
        std::string name;
        int price;

        long long getKey() const {
            return barcode;
        }

        bool operator==(const Product& other) const {
            return barcode == other.barcode && name == other.name && price == other.price;
        }

        std::string printStruct() const {
            return std::to_string(barcode) + " | " + name + " | " + std::to_string(price);
        }

        std::string toFile() const {
            return std::to_string(barcode) + ";" + name + ";" + std::to_string(price);
        }

        Product() : barcode(0), name(""), price(0) {}
        Product(long long bc, const std::string& n, int p) : barcode(bc), name(n), price(p) {}
    };

    // Класс Продажа
    struct Sale {
        long long barcode;
        int cashRegister;
        int quantity;
        Date saleDate;

        long long getKey() const {
            return barcode;
        }

        bool operator==(const Sale& other) const {
            return barcode == other.barcode && cashRegister == other.cashRegister &&
                quantity == other.quantity && saleDate == other.saleDate;
        }

        std::string printStruct() const {
            return std::to_string(barcode) + " | Касса: " + std::to_string(cashRegister) +
                " | Кол-во: " + std::to_string(quantity) + " | Дата: " + saleDate.toString();
        }

        std::string toFile() const {
            return std::to_string(barcode) + ";" + std::to_string(cashRegister) + ";" +
                std::to_string(quantity) + ";" + saleDate.toString();
        }

        Sale() : barcode(0), cashRegister(0), quantity(0), saleDate() {}
        Sale(long long bc, int cr, int q, const Date& sd) : barcode(bc), cashRegister(cr), quantity(q), saleDate(sd) {}
    };
}