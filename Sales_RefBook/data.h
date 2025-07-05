#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <stdexcept>

namespace dataTypes
{
    // Перечисление для месяцев
    enum class Month
    {
        янв,
        фев,
        мар,
        апр,
        май,
        июн,
        июл,
        авг,
        сен,
        окт,
        ноя,
        дек
    };

    // Класс для даты
    struct Date
    {
        int day;
        int month;
        int year;

        bool operator==(const Date& other) const
        {
            return day == other.day && month == other.month && year == other.year;
        }

        std::string toString() const
        {
            const std::string monthNames[] = { "янв", "фев", "мар", "апр", "май", "июн",
                                              "июл", "авг", "сен", "окт", "ноя", "дек" };
            return std::to_string(day) + " " + monthNames[static_cast<int>(month)] + " " + std::to_string(year);
        }

        Date() : day(0), month(0), year(0) {}
        Date(int d, int m, int y) : day(d), month(m), year(y) {}

        Date parseDate(const std::string& dateString) {
            const char* months[] = { "янв", "фев", "мар", "апр", "май", "июн",
                                   "июл", "авг", "сен", "окт", "ноя", "дек" };

            std::istringstream iss(dateString);
            int day, year;
            std::string monthStr;
            char remaining;

            if (!(iss >> day >> monthStr >> year)) {
                throw std::invalid_argument("Invalid date format");
            }

            // Проверка на лишние символы
            if (iss.get(remaining)) {
                throw std::invalid_argument("Extra characters in date string");
            }

            // Поиск месяца
            int month = -1;
            for (int i = 0; i < 12; ++i) {
                if (monthStr == months[i]) {
                    month = i;
                    break;
                }
            }
            if (month == -1) {
                throw std::invalid_argument("Invalid month name");
            }

            // Проверка допустимости даты
            if (day < 1 || day > 31) {
                throw std::invalid_argument("Day must be between 1 and 31");
            }
            if (year < 0) {
                throw std::invalid_argument("Year must be positive");
            }

            return Date(day, month, year);
        }
    };

    // Класс Продукт
    struct Product
    {
        long long barcode;
        std::string name;
        double price; // Изменено с int на double

        long long getKey() const
        {
            return barcode;
        }

        bool operator==(const Product& other) const
        {
            return barcode == other.barcode && name == other.name &&
                fabs(price - other.price) < 1e-9; // Сравнение double с учетом погрешности
        }

        std::string printStruct() const
        {
            std::ostringstream oss;
            oss << barcode << " | " << name << " | " << std::fixed << std::setprecision(2) << price;
            return oss.str();
        }

        std::string toFile() const
        {
            std::ostringstream oss;
            oss << barcode << ";" << name << ";" << std::fixed << std::setprecision(2) << price;
            return oss.str();
        }

        Product() : barcode(0), name(""), price(0.0) {}
        Product(long long bc, const std::string& n, double p) : barcode(bc), name(n), price(p) {}
    };

    // Класс Продажа
    struct Sale
    {
        long long barcode;
        int cashRegister;
        int quantity;
        Date saleDate;

        long long getKey() const
        {
            return barcode;
        }

        bool operator==(const Sale& other) const
        {
            return barcode == other.barcode && cashRegister == other.cashRegister &&
                quantity == other.quantity && saleDate == other.saleDate;
        }

        std::string printStruct() const
        {
            return std::to_string(barcode) + " | Касса: " + std::to_string(cashRegister) +
                " | Кол-во: " + std::to_string(quantity) + " | Дата: " + saleDate.toString();
        }

        std::string toFile() const
        {
            return std::to_string(barcode) + ";" + std::to_string(cashRegister) + ";" +
                std::to_string(quantity) + ";" + saleDate.toString();
        }

        Sale() : barcode(0), cashRegister(0), quantity(0), saleDate() {}
        Sale(long long bc, int cr, int q, const Date& sd) : barcode(bc), cashRegister(cr), quantity(q), saleDate(sd) {}
    };
}