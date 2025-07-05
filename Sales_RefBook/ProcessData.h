#pragma once

#include <iostream>
#include "RBtree.h"
#include "data.h"
#include "DataValidation.h"
#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cassert>
#include <vector>
#include <utility>
#include <algorithm>

namespace dataProcess
{

    using namespace std;
    using namespace tree;
    using namespace hashTable;
    using namespace dataTypes;
    using namespace DataValidation;

    std::pair<int*, int> intersectionOfThree(int* arr1, int size1, int* arr2, int size2, int* arr3, int size3)
    {
        std::vector<int> result;

        // ��������� ������� ��� �������� �����������
        std::vector<int> temp1;

        // ������� ����������� ������� � ������� ��������
        for (int i = 0; i < size1; ++i)
        {
            for (int j = 0; j < size2; ++j)
            {
                if (arr1[i] == arr2[j])
                {
                    temp1.push_back(arr1[i]);
                    break;
                }
            }
        }

        // ������ ����������� temp1 � �������� �������
        for (int i = 0; i < temp1.size(); ++i)
        {
            for (int j = 0; j < size3; ++j)
            {
                if (temp1[i] == arr3[j])
                {
                    result.push_back(temp1[i]);
                    break;
                }
            }
        }

        // �������� ���������� �� ����������
        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());

        // ��������� ������������ ������ ��� ���������
        int* intersection = new int[result.size()];
        for (int i = 0; i < result.size(); ++i)
        {
            intersection[i] = result[i];
        }

        return { intersection, static_cast<int>(result.size()) };
    }

    template <class T>
    void resizeArray(T*& arr, int& size, size_t index, T value)
    {
        if (index < 0)
        {
            return;
        }

        if (index >= size)
        {
            int newSize = index + 1;
            T* newArr = new T[newSize];

            if (arr != nullptr && size > 0)
            {
                for (int i = 0; i < size; ++i)
                {
                    newArr[i] = arr[i];
                }
                delete[] arr;
            }

            for (int i = size; i < newSize; ++i)
            {
                newArr[i] = T{};
            }

            arr = newArr;
            size = newSize;
        }
        arr[index] = value;
    }

    template <class T>
    void removeElement(T*& arr, int& size, size_t index)
    {
        if (index < 0 || index >= size || arr == nullptr)
        {
            return; // ������������ ������ ��� ������ ������
        }

        if (size == 1)
        { // ���� ������� ������������
            delete[] arr;
            arr = nullptr;
            size = 0;
            return;
        }

        // �������� ��������� ������� ���������
        arr[index] = arr[size - 1];

        // ��������� ������
        T* newArr = new T[size - 1];
        for (int i = 0; i < size - 1; ++i)
        {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        size--;
    }

    template <class T>
    int appendElement(T*& arr, int& size, T value)
    {
        T* newArr = new T[size + 1];

        // �������� ������ ��������
        if (arr != nullptr && size > 0)
        {
            for (int i = 0; i < size; ++i)
            {
                newArr[i] = arr[i];
            }
            delete[] arr;
        }

        // ��������� ����� �������
        newArr[size] = value;
        arr = newArr;
        size++;

        return size - 1; // ���������� ������ ������������ ��������
    }

    template <typename T>
    bool loadArrayToTree(tree::tNode<T>*& root, const tree::KeyType<T>& key, T*& arr, int& size)
    {
        if (!arr || size <= 0)
            return false;

        bool success = true;
        for (int i = 0; i < size; i++)
        {
            try
            {
                addElement(root, key, i); // ��������� ������ �������� ������� � ������
            }
            catch (...)
            {
                success = false; // ���� �������� ������ ��� ����������
            }
        }
        return success;
    }

    template <typename T>
    void findAndRemoveMatches(tNode<T>*& root, const KeyType<T>& key, T*& arr, int& size)
    {
        tNode<T>* node = search(root, key); // ���� ���� � ������ ������
        if (!node || !node->data)
            return;

        List& list = *(node->data); // �������� ������ ��������

        // �������� �� ������ ��������
        for (typename List::Iterator it = list.begin(); it != list.end(); ++it)
        {
            int index = *it;
            if (index >= 0 && index < size)
            { // ��������� ������������ �������
                if (arr[index] == key)
                { // ���� ������ ����������
                    // ������� ������� �� ������
                    removeElement(root, key, index);

                    // // ������� ������� �� ������� (�������� ��������� � ��������� ������)
                    // if (size > 1) {
                    //     arr[index] = arr[size - 1];
                    // }
                    // size--;

                    // // ������� ������ �� ������
                    // it = list.erase(it);
                }
            }
        }
    }

    void readSalesFromFile(Sale*& salesArray, int& currentSize, const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // ������ �������� ������� � ���������� �������
        const char* monthNames[] = {
            "���", "���", "���", "���", "���", "���",
            "���", "���", "���", "���", "���", "���" };

        std::string line;
        int index = 0;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            long long barcode;
            int cashRegister, quantity, day, year;
            std::string monthStr;

            if (iss >> barcode >> cashRegister >> quantity >> day >> monthStr >> year)
            {
                // ���� ����� ������
                int month = -1;
                for (int i = 0; i < 12; ++i)
                {
                    if (monthStr == monthNames[i])
                    {
                        month = i;
                        break;
                    }
                }

                if (month == -1)
                {
                    std::cerr << "Invalid month in line: " << line << std::endl;
                    continue;
                }

                Date saleDate(day, month, year);
                Sale newSale(barcode, cashRegister, quantity, saleDate);

                // ��������� ������ � ��������� �������
                resizeArray(salesArray, currentSize, index, newSale);
                index++;
            }
            else
            {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }

        file.close();
    }

    void testReadSalesFromFile()
    {
        // 1. ������� �������� ����
        const std::string test_filename = "test_input.txt";
        std::ofstream out_file(test_filename);
        out_file << "467289154321 5 2 15 ��� 2023\n"
            << "891234567890 2 1 3 ��� 2024\n"
            << "123456789012 7 4 22 ��� 2023\n"
            << "345678901234 1 3 8 ��� 2023\n"
            << "678901234567 4 5 14 ��� 2023\n";
        out_file.close();

        // 2. ������ ������ �� �����
        Sale* sales = nullptr;
        int salesCount = 0;
        readSalesFromFile(sales, salesCount, test_filename);

        // 3. ��������� ����������
        std::cout << "=== Test Results ===\n";
        std::cout << "Records read: " << salesCount << "\n\n";

        // �������� ���������� ��������� �������
        assert(salesCount == 5 && "Wrong number of records");

        // �������� ������ ������
        assert(sales[0].barcode == 467289154321LL);
        assert(sales[0].cashRegister == 5);
        assert(sales[0].quantity == 2);
        assert(sales[0].saleDate.day == 15);
        assert(sales[0].saleDate.month == 6); // ��� - 6 ����� (0-based)
        assert(sales[0].saleDate.year == 2023);

        // �������� ��������� ������
        assert(sales[4].barcode == 678901234567LL);
        assert(sales[4].cashRegister == 4);
        assert(sales[4].quantity == 5);
        assert(sales[4].saleDate.day == 14);
        assert(sales[4].saleDate.month == 7); // ��� - 7 ����� (0-based)
        assert(sales[4].saleDate.year == 2023);

        // ������� ��� ������ ��� ���������� ��������
        for (int i = 0; i < salesCount; ++i)
        {
            std::cout << sales[i].printStruct() << "\n";
        }

        // 4. ������� �������
        delete[] sales;

        // 5. ������� �������� ���� (�����������)
        remove(test_filename.c_str());

        std::cout << "\nAll tests passed successfully!\n";
    }

    void processData()
    {
        // 1. ������ ������ �� ����� � ������������ ������
        Sale* salesArray = nullptr;
        int arraySize = 0;
        const string filename = "input.txt";

        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        const char* months[] = { "���", "���", "���", "���", "���", "���",
                                "���", "���", "���", "���", "���", "���" };
        string line;
        int index = 0;

        while (getline(inputFile, line))
        {
            istringstream iss(line);
            long long barcode;
            int cashRegister, quantity, day, year;
            string monthStr;

            if (iss >> barcode >> cashRegister >> quantity >> day >> monthStr >> year)
            {
                int month = -1;
                for (int i = 0; i < 12; ++i)
                {
                    if (strcmp(monthStr.c_str(), months[i]) == 0)
                    {
                        month = i;
                        break;
                    }
                }
                if (month == -1)
                    continue;

                Sale newSale(barcode, cashRegister, quantity, Date(day, month, year));
                resizeArray(salesArray, arraySize, index, newSale);
                index++;
            }
        }
        inputFile.close();

        // 2. ������ ������ � ��-������
        tNode<long long>* root = nullptr;
        for (int i = 0; i < arraySize; ++i)
        {
            BarcodeKey key(salesArray[i].barcode); // ������� ������
            addElement(root, key, i);              // �������� �� ������
        }

        // 3. ����� ������
        cout << "=== ������-������ ������ ===" << endl;
        printHelper(root); // ���������� ��� ����� ������ ������

        // 4. ����� � �������� ��������
        long long searchBarcode;
        cout << "\n������� �����-��� ��� ������ � ��������: ";
        cin >> searchBarcode;

        BarcodeKey searchKey(searchBarcode);

        tNode<long long>* foundNode = search(root, searchKey);
        if (foundNode)
        {
            cout << "������ �������: " << foundNode->key->toString() << endl;
            cout << "������ �������: " << salesArray[foundNode->data->getHead()->index].printStruct() << endl;

            removeElement(root, searchKey, foundNode->data->getHead()->index);
            cout << "\n����� ��������:\n";
            printHelper(root);
        }
        else
        {
            cout << "�����-��� �� ������!" << endl;
        }

        // ������� ������
        delete[] salesArray;
        // clearTree(root); // �������� ���� ���������� ������� ������
    }

    template <typename ArrayType>
    bool downloadDataFromFileToArray(const string filename, ArrayType*& array, int& arraySize)
    {
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return false;
        }

        // ������� ������ ������
        delete[] array;
        array = nullptr;
        arraySize = 0;

        const char* months[] = { "���", "���", "���", "���", "���", "���",
                                "���", "���", "���", "���", "���", "���" };
        string line;
        int index = 0;

        try
        {
            while (getline(inputFile, line))
            {
                istringstream iss(line);
                long long barcode;
                int cashRegister, quantity, day, year;
                string monthStr;

                if (iss >> barcode >> cashRegister >> quantity >> day >> monthStr >> year)
                {
                    int month = -1;
                    for (int i = 0; i < 12; ++i)
                    {
                        if (monthStr == months[i])
                        { // ����� ������������ ��������� string
                            month = i;
                            break;
                        }
                    }
                    if (month == -1)
                        continue;

                    resizeArray(array, arraySize, index,
                        Sale(barcode, cashRegister, quantity, Date(day, month, year)));
                    index++;
                }
            }
            inputFile.close();
            return true;
        }
        catch (...)
        {
            delete[] array;
            array = nullptr;
            arraySize = 0;
            inputFile.close();
            return false;
        }
    }

    template <typename ArrayType, typename KeyDataType, typename KeyType>
    void downloadDataFromArrayToTree(ArrayType* array, int arraySize, tNode<KeyDataType>*& root)
    {
        removeTree(root);
        root = nullptr;
        for (int i = 0; i < arraySize; ++i)
        {
            KeyType key(array[i].getKey());
            addElement(root, key, i);
        }
    }

    void addElementToTheArray(Sale newSale, Sale*& array, int& arraySize)
    {
        int index = arraySize;
        resizeArray(array, arraySize, index, newSale);
    }

    template <typename ArrayType, typename KeyDataType, typename KeyType>
    void addElementToTheTreeAndArray(Sale newSale, Sale*& array, int& arraySize, tNode<KeyDataType>*& root)
    {
        addElementToTheArray(newSale, array, arraySize);
        downloadDataFromArrayToTree < dataTypes::Sale, long long, tree::BarcodeKey > (array, arraySize, root);
    }


    template <typename KeyDataType, typename KeyType>
    List* getListOfIndexesByKeyInTheTree(tNode<KeyDataType>* root, KeyDataType keyData)
    {
        KeyType searchKey(keyData);
        tNode<KeyDataType>* foundNode = search(root, searchKey);
        if (foundNode)
        {
            return foundNode->data;
        }
        return nullptr;
    }

    template <typename ArrayType, typename KeyDataType, typename KeyType>
    int removeElementFromTheTreeByKey(ArrayType* array, int arraySize, tNode<KeyDataType>*& root, ArrayType unitData)
    {
        KeyDataType keyData = unitData.getKey();

        List* listOfIndexes = getListOfIndexesByKeyInTheTree<KeyDataType, KeyType>(root, keyData);

        if (listOfIndexes == nullptr)
            return 0;

        int deletedCount = 0;
        for (typename List::Iterator it = listOfIndexes->begin(); it != listOfIndexes->end(); ++it)
        {
            int index = *it;
            if (index >= 0 && index < arraySize)
            {
                if (array[index] == unitData)
                {
                    KeyType tempKey(keyData);
                    removeElement(root, tempKey, index);
                    deletedCount++;
                }
            }
        }
        return deletedCount;
    }

    bool downloadDataFromFileToArrayOfProducts(const string filename, Product*& array, int& arraySize, int elementsToReed)
    {
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return false;
        }

        // ������� ������ ������
        delete[] array;
        array = nullptr;
        arraySize = 0;

        string line;
        int index = 0;

        try
        {
            while (getline(inputFile, line) && (index < elementsToReed))
            {
                // ��������� ������ �� ������ � �������
                size_t pos1 = line.find(';');
                size_t pos2 = line.find(';', pos1 + 1);
                if (pos1 == string::npos || pos2 == string::npos)
                {
                    continue; // ���������� ������ � ������������ ��������
                }

                string barcodeStr = line.substr(0, pos1);
                string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string priceStr = line.substr(pos2 + 1);

                // ��������� �����-����
                if (!validateBarcode(barcodeStr))
                {
                    continue;
                }

                long long barcode = stoll(barcodeStr);
                std::cout << "5\n";

                // ��������� ��������
                if (!validateProductName(name))
                {
                    continue;
                }
                std::cout << "6\n";

                // ��������� ����
                double price;
                try
                {
                    price = stod(priceStr);
                }

                catch (...)
                {
                    continue;
                }

                if (!validatePrice(price))
                {
                    continue;
                }

                // ��������� ������� � ������
                resizeArray(array, arraySize, index, Product(barcode, name, price));
                index++;
            }
            inputFile.close();
            return true;
        }
        catch (...)
        {
            delete[] array;
            array = nullptr;
            arraySize = 0;
            inputFile.close();
            return false;
        }
    }

    void addElementToTheProductArray(Product newProduct, Product*& array, int& arraySize)
    {
        int index = arraySize;
        resizeArray(array, arraySize, index, newProduct);
    }


    void addElementToArrayAndHashTable(Product*& array, int &arraySize, HashTable<hashTable::PrimaryHashFunction,
        hashTable::QuadraticProbingFunction> *& hashTable, Product newProduct)
    {
        addElementToTheProductArray(newProduct, array, arraySize);
        hashTable->add(Record(newProduct.barcode, arraySize - 1));
    }


}