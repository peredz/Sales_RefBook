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

namespace DataValidation
{

    using namespace std;

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
        if (name.empty())
            return false;

        // ����������� � UTF-32 ��� ���������� ��������� ������� ����
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::u32string u32name = converter.from_bytes(name);

        // �������� ������� ������� (������ ���� ��������� ������� �����)
        if (!isRussianLetter(u32name[0], true))
        {
            return false;
        }

        // �������� ��������� ��������
        for (size_t i = 1; i < u32name.size(); i++)
        {
            char32_t c = u32name[i];

            // ���������� �������
            bool valid = isRussianLetter(c, false) ||
                c == U' ' ||
                c == U'-' ||
                c == U'.' ||
                c == U'"' || c == U'\'' ||
                c == U'%' ||
                (c >= U'0' && c <= U'9');

            if (!valid)
            {
                return false;
            }

            // �������� �� ������� �������
            if (c == U' ' && i > 0 && u32name[i - 1] == U' ')
            {
                return false;
            }
        }

        return true;
    }

    bool validatePrice(double price)
    {
        // �������� ���������
        if (price < 0.01 || price > 99999.99)
        {
            return false;
        }

        // �������� �������� �� �����
        double rounded = round(price * 100) / 100;
        if (fabs(price - rounded) > 1e-9)
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
}