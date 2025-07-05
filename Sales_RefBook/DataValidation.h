#pragma once

#include <string>
#include <cctype>
#include <regex>
#include <cmath>
#include <iomanip>
#include <locale>
#include <vector>
#include <codecvt>
#include <sstream>
#include <iostream>

namespace DataValidation
{


    bool validateBarcode(const std::string& barcode)
    {
        // Проверка длины (ровно 13 символов)
        if (barcode.length() != 13)
        {
            return false;
        }

        // Проверка, что все символы - цифры
        for (char c : barcode)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }

        // Первая цифра не должна быть '0'
        if (barcode[0] == '0')
        {
            return false;
        }

        return true;
    }

    bool isRussianLetter(char32_t c, bool uppercase)
    {
        static const std::vector<char32_t> upperLetters = {
            U'А', U'Б', U'В', U'Г', U'Д', U'Е', U'Ё', U'Ж', U'З', U'И',
            U'Й', U'К', U'Л', U'М', U'Н', U'О', U'П', U'Р', U'С', U'Т',
            U'У', U'Ф', U'Х', U'Ц', U'Ч', U'Ш', U'Щ', U'Ъ', U'Ы', U'Ь',
            U'Э', U'Ю', U'Я' };

        static const std::vector<char32_t> lowerLetters = {
            U'а', U'б', U'в', U'г', U'д', U'е', U'ё', U'ж', U'з', U'и',
            U'й', U'к', U'л', U'м', U'н', U'о', U'п', U'р', U'с', U'т',
            U'у', U'ф', U'х', U'ц', U'ч', U'ш', U'щ', U'ъ', U'ы', U'ь',
            U'э', U'ю', U'я' };

        const auto& letters = uppercase ? upperLetters : lowerLetters;
        return std::find(letters.begin(), letters.end(), c) != letters.end();
    }

    bool validateProductName(const std::string& name)
    {
        return true;
        if (name.empty())
            return false;

        // Преобразуем в UTF-32 для корректной обработки русских букв
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::u32string u32name = converter.from_bytes(name);

        // Проверка первого символа (должна быть заглавная русская буква)
        if (!isRussianLetter(u32name[0], true))
        {
            std::cout << "1\n";
            return false;
        }

        // // Проверка остальных символов
        // for (size_t i = 1; i < u32name.size(); i++)
        // {
        //     char32_t c = u32name[i];

        //     // Допустимые символы
        //     bool valid = isRussianLetter(c, false) ||
        //                  c == U' ' ||
        //                  c == U'-' ||
        //                  c == U'.' ||
        //                  c == U'"' || 
        //                  c == U'\''||
        //                  c == U'%' ||
        //                  (c >= U'0' && c <= U'9');

        //     if (!valid)
        //     {
        //         std::cout << "2 : " << c <<"\n";
        //         return false;
        //     }

        //     // Проверка на двойные пробелы
        //     if (c == U' ' && i > 0 && u32name[i - 1] == U' ')
        //     {
        //         return false;
        //     }
        // }

        return true;
    }

    bool validatePrice(double price)
    {
        // Проверка диапазона
        if (price < 0.01 || price > 99999.99)
        {
            return false;
        }

        return true;
    }

    // Альтернативная версия с проверкой строкового представления
    bool validatePriceString(const std::string& priceStr)
    {
        std::regex priceRegex(R"(^[1-9]\d{0,4}(\.\d{1,2})?$|^0\.\d{1,2}$)");
        if (!std::regex_match(priceStr, priceRegex))
        {
            return false;
        }

        double price = std::stod(priceStr);
        return validatePrice(price);
    }

    bool isRussianLetter(char c, bool uppercase)
    {
        if (uppercase)
        {
            return (c >= 'А' && c <= 'Я') || c == 'Ё';
        }
        else
        {
            return (c >= 'а' && c <= 'я') || c == 'ё';
        }
    }

    bool isStingNum(const std::string& didgSrt)
    {
        for (char c : didgSrt)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

    bool validateDate(const std::string& dateString) {
        const char* months[] = { "янв", "фев", "мар", "апр", "май", "июн",
                               "июл", "авг", "сен", "окт", "ноя", "дек" };
        try {
            istringstream iss(dateString);
            int day, year;
            string monthStr;
            char remaining;  // Для проверки лишних символов

            if (iss >> day >> monthStr >> year) {
                // Проверяем, что нет лишних символов
                if (iss.get(remaining)) {
                    return false;
                }

                // Проверяем месяц
                int month = -1;
                for (int i = 0; i < 12; ++i) {
                    if (monthStr == months[i]) {
                        month = i;
                        break;
                    }
                }
                if (month == -1) {
                    return false;
                }

                // Проверяем день (1-31) и год 
                if (day < 1 || day > 31 || year < 1989 || year > 2050) {
                    return false;
                }

                return true;
            }
            return false;
        }
        catch (...) {
            return false;
        }
    }
}