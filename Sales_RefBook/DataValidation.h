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
        // �������� ����� (����� 13 ��������)
        if (barcode.length() != 13)
        {
            return false;
        }

        // ��������, ��� ��� ������� - �����
        for (char c : barcode)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }

        // ������ ����� �� ������ ���� '0'
        if (barcode[0] == '0')
        {
            return false;
        }

        return true;
    }

    bool isRussianLetter(char32_t c, bool uppercase)
    {
        static const std::vector<char32_t> upperLetters = {
            U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�',
            U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�',
            U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�',
            U'�', U'�', U'�' };

        static const std::vector<char32_t> lowerLetters = {
            U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�',
            U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�',
            U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�', U'�',
            U'�', U'�', U'�' };

        const auto& letters = uppercase ? upperLetters : lowerLetters;
        return std::find(letters.begin(), letters.end(), c) != letters.end();
    }

    bool validateProductName(const std::string& name)
    {
        return true;
        if (name.empty())
            return false;

        // ����������� � UTF-32 ��� ���������� ��������� ������� ����
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::u32string u32name = converter.from_bytes(name);

        // �������� ������� ������� (������ ���� ��������� ������� �����)
        if (!isRussianLetter(u32name[0], true))
        {
            std::cout << "1\n";
            return false;
        }

        // // �������� ��������� ��������
        // for (size_t i = 1; i < u32name.size(); i++)
        // {
        //     char32_t c = u32name[i];

        //     // ���������� �������
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

        //     // �������� �� ������� �������
        //     if (c == U' ' && i > 0 && u32name[i - 1] == U' ')
        //     {
        //         return false;
        //     }
        // }

        return true;
    }

    bool validatePrice(double price)
    {
        // �������� ���������
        if (price < 0.01 || price > 99999.99)
        {
            return false;
        }

        return true;
    }

    // �������������� ������ � ��������� ���������� �������������
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
            return (c >= '�' && c <= '�') || c == '�';
        }
        else
        {
            return (c >= '�' && c <= '�') || c == '�';
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
        const char* months[] = { "���", "���", "���", "���", "���", "���",
                               "���", "���", "���", "���", "���", "���" };
        try {
            istringstream iss(dateString);
            int day, year;
            string monthStr;
            char remaining;  // ��� �������� ������ ��������

            if (iss >> day >> monthStr >> year) {
                // ���������, ��� ��� ������ ��������
                if (iss.get(remaining)) {
                    return false;
                }

                // ��������� �����
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

                // ��������� ���� (1-31) � ��� 
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