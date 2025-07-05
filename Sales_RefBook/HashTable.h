#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include "data.h"

namespace hashTable
{

    class Record
    {
    public:
        long long barCode;
        int index;

        Record() : index(0), barCode(1000000000000) {}

        Record(long long barCode_, int index_)
            : barCode(barCode_), index(index_)
        {
        }

        long long calculateHashKey() const
        {
            return barCode;
        }

        bool isSameRecord(const Record& other) const
        {
            return (barCode == other.barCode && index == other.index);
        }

        void printKey() const
        {
            std::cout << barCode;
        }

        void printDetails() const
        {
            std::cout << " " << index;
        }

        void print() const
        {
            printKey();
            printDetails();
        }
    };

    int midSquareHash(const Record& record, int tableSize)
    {
        long long key = record.calculateHashKey();
        long long squared = key * key;
        std::string squaredStr = std::to_string(squared);
        long long length = squaredStr.size();
        long long middle = length / 2;
        int digitsNeeded = static_cast<int>(std::to_string(tableSize).size());
        int middlePos = static_cast<int>(middle) - digitsNeeded / 2;
        std::string middleDigits = squaredStr.substr((((0) > (middlePos)) ? (0) : (middlePos)), digitsNeeded);
        if (middleDigits.empty())
            return 0;

        return std::stoi(middleDigits) % tableSize;
    }

    struct PrimaryHashFunction
    {
        int operator()(const Record& record, int tableSize) const
        {
            return midSquareHash(record, tableSize);
        }
    };

    struct QuadraticProbingFunction
    {
    private:
        const long long linearCoefficient = 1;
        const long long quadraticCoefficient = 2;

    public:
        long long operator()(long long hash, int attempt) const
        {
            return hash + linearCoefficient * attempt + quadraticCoefficient * attempt * attempt;
        }
    };

    template <
        class PrimaryHash = PrimaryHashFunction,
        class CollisionResolver = QuadraticProbingFunction>
    class HashTable
    {
    public:
        struct TableEntry
        {
            Record data;
            char state; // 0 = empty, 1 = occupied, 2 = deleted

            TableEntry() : state(0) {}
            TableEntry(Record value) : data(std::move(value)), state(1) {}

            void markAsDeleted()
            {
                state = 2;
            }
        };

    private:
        int initialCapacity = 8;
        static constexpr double MAX_LOAD_FACTOR = 0.75;
        static constexpr double MIN_LOAD_FACTOR = 0.25;

        int currentCapacity;
        int totalEntries;
        int occupiedSlots;
        TableEntry* hashTable;

        bool insertRecord(Record record, bool isRehashing = false)
        {
            PrimaryHash primaryHash;
            CollisionResolver resolveCollision;

            long long initialIndex = primaryHash(record, currentCapacity);
            TableEntry newEntry(std::move(record));

            if (hashTable[initialIndex].state != 1)
            {
                if (hashTable[initialIndex].state == 0)
                {
                    totalEntries++;
                }
                if (!isRehashing)
                    occupiedSlots++;
                hashTable[initialIndex] = newEntry;
                if (!isRehashing)
                    checkLoadFactor();
                return true;
            }

            int attempt = 1;
            long long currentIndex = initialIndex;
            while (hashTable[currentIndex].state != 0)
            {
                // Проверяем как полное совпадение, так и совпадение только по ключу
                if (hashTable[currentIndex].data.calculateHashKey() == newEntry.data.calculateHashKey())
                {
                    return false; // Запись с таким ключом уже существует
                }
                currentIndex = resolveCollision(initialIndex, attempt) % currentCapacity;
                attempt++;

                // Защита от бесконечного цикла
                if (attempt > currentCapacity)
                    return false;
            }

            hashTable[currentIndex] = newEntry;

            if (hashTable[currentIndex].state == 0)
            {
                totalEntries++;
            }
            if (!isRehashing)
                occupiedSlots++;
            if (!isRehashing)
                checkLoadFactor();
            return true;
        }

        void checkLoadFactor()
        {
            double currentLoad = double(occupiedSlots) / double(currentCapacity);

            TableEntry* oldTable = hashTable;
            int oldCapacity = currentCapacity;

            if (currentLoad > MAX_LOAD_FACTOR)
            {
                resizeTable(true);
            }
            else if (currentLoad < MIN_LOAD_FACTOR && currentCapacity > initialCapacity)
            {
                resizeTable(false);
            }
            else
            {
                return;
            }

            hashTable = new TableEntry[currentCapacity];
            rehashTable(oldTable, oldCapacity);
            delete[] oldTable;
        }

        void resizeTable(bool shouldExpand)
        {
            if (shouldExpand)
            {
                currentCapacity *= 2;
            }
            else
            {
                currentCapacity = (std::max)(initialCapacity, currentCapacity / 2);
            }
        }

        void rehashTable(TableEntry* oldTable, int oldCapacity)
        {
            for (int i = 0; i < oldCapacity; i++)
            {
                if (oldTable[i].state == 1)
                {
                    insertRecord(oldTable[i].data, true);
                }
            }
            totalEntries = occupiedSlots;
        }

        TableEntry findEntry(const Record& record, bool shouldMarkDeleted = false)
        {
            PrimaryHash primaryHash;
            CollisionResolver resolveCollision;

            long long initialIndex = primaryHash(record, currentCapacity);

            if (hashTable[initialIndex].data.isSameRecord(record) &&
                hashTable[initialIndex].state == 1)
            {
                if (shouldMarkDeleted)
                    hashTable[initialIndex].markAsDeleted();
                else
                    std::cout << "It took 1 step to find the Record." << std::endl;
                return hashTable[initialIndex];
            }

            int attempt = 1;
            long long currentIndex = initialIndex;
            while (hashTable[currentIndex].state != 0)
            {
                if (hashTable[currentIndex].data.isSameRecord(record) &&
                    hashTable[currentIndex].state == 1)
                {
                    if (shouldMarkDeleted)
                        hashTable[currentIndex].markAsDeleted();
                    else
                        std::cout << "It took " << attempt + 1 << " steps to find the Record." << std::endl;
                    return hashTable[currentIndex];
                }
                currentIndex = resolveCollision(initialIndex, attempt) % currentCapacity;
                attempt++;
            }

            return TableEntry();
        }

        int findByKey(long long barCodeKey)
        {
            PrimaryHash primaryHash;
            CollisionResolver resolveCollision;

            Record dummyRecord(barCodeKey, 0);
            int initialIndex = primaryHash(dummyRecord, currentCapacity);

            if (hashTable[initialIndex].data.barCode == barCodeKey &&
                hashTable[initialIndex].state == 1)
            {
                return hashTable[initialIndex].data.index;
            }

            int attempt = 1;
            int currentIndex = initialIndex;
            while (hashTable[currentIndex].state != 0)
            {
                if (hashTable[currentIndex].data.barCode == barCodeKey &&
                    hashTable[currentIndex].state == 1)
                {
                    return hashTable[currentIndex].data.index;
                }
                currentIndex = resolveCollision(initialIndex, attempt) % currentCapacity;
                attempt++;
                if (attempt > currentCapacity)
                    break;
            }

            return -1;
        }

        int findByKeyWithSteps(long long barCodeKey, int &steps)
        {
            PrimaryHash primaryHash;
            CollisionResolver resolveCollision;

            Record dummyRecord(barCodeKey, 0);
            int initialIndex = primaryHash(dummyRecord, currentCapacity);
            steps = 1;

            if (hashTable[initialIndex].data.barCode == barCodeKey &&
                hashTable[initialIndex].state == 1)
            {
                return hashTable[initialIndex].data.index;
            }

            int attempt = 1;
            int currentIndex = initialIndex;
            while (hashTable[currentIndex].state != 0)
            {
                if (hashTable[currentIndex].data.barCode == barCodeKey &&
                    hashTable[currentIndex].state == 1)
                {
                    return hashTable[currentIndex].data.index;
                }
                currentIndex = resolveCollision(initialIndex, attempt) % currentCapacity;
                attempt++;
                if (attempt > currentCapacity)
                    break;
            }
            steps = attempt + 1;

            return -1;
        }

        bool removeRecord(const Record& record)
        {
            TableEntry foundEntry = findEntry(record, true);

            if (foundEntry.state == 0)
            {
                return false;
            }

            occupiedSlots--;
            checkLoadFactor();
            return true;
        }

        bool removeByKey(long long barCodeKey)
        {
            PrimaryHash primaryHash;
            CollisionResolver resolveCollision;

            Record dummyRecord(barCodeKey, 0);
            int initialIndex = primaryHash(dummyRecord, currentCapacity);

            if (hashTable[initialIndex].data.barCode == barCodeKey &&
                hashTable[initialIndex].state == 1)
            {
                hashTable[initialIndex].markAsDeleted();
                occupiedSlots--;
                checkLoadFactor();
                return true;
            }

            int attempt = 1;
            int currentIndex = initialIndex;
            while (hashTable[currentIndex].state != 0)
            {
                if (hashTable[currentIndex].data.barCode == barCodeKey &&
                    hashTable[currentIndex].state == 1)
                {
                    hashTable[currentIndex].markAsDeleted();
                    occupiedSlots--;
                    checkLoadFactor();
                    return true;
                }
                currentIndex = resolveCollision(initialIndex, attempt) % currentCapacity;
                attempt++;
                if (attempt > currentCapacity)
                    break;
            }

            return false;
        }

        void saveDataToFile(const std::string& fileName)
        {
            std::ofstream output(fileName, std::ios::out | std::ios::trunc);
            if (!output)
            {
                std::cerr << "[Error] Failed to open file: " << fileName << std::endl;
                return;
            };
            formatTablePrint(output);
            output.close();
        }

        void formatTablePrint(std::ostream& stream = std::cout) const
        {
            stream << std::left;
            stream << std::setw(6) << "Number"
                << std::setw(15) << "BarCode"
                << std::setw(10) << "Index"
                << std::setw(12) << "Status\n";

            stream << std::string(43, '-') << "\n";

            for (int i = 0; i < currentCapacity; ++i)
            {
                stream << std::setw(6) << i;

                if (hashTable[i].state == 0)
                {
                    stream << std::setw(15) << "-"
                        << std::setw(10) << "-"
                        << std::setw(12) << "empty";
                }
                else if (hashTable[i].state == 1)
                {
                    stream << std::setw(15) << hashTable[i].data.barCode
                        << std::setw(10) << hashTable[i].data.index
                        << std::setw(12) << "occupied";
                }
                else // state == 2
                {
                    stream << std::setw(15) << "-"
                        << std::setw(10) << "-"
                        << std::setw(12) << "deleted";
                }
                stream << "\n";
            }
            stream << "Capacity: " << currentCapacity
                << ", Occupied: " << occupiedSlots
                << ", Load factor: " << std::fixed << std::setprecision(2)
                << (static_cast<double>(occupiedSlots) / currentCapacity) << "\n\n";
        }

        void loadFromArray(const dataTypes::Product* array, int arraySize)
        {
            delete[] hashTable;
            currentCapacity = initialCapacity;
            occupiedSlots = 0;
            totalEntries = 0;
            hashTable = new TableEntry[currentCapacity];

            for (int i = 0; i < arraySize; ++i)
            {
                add(Record(array[i].getKey(), i));
            }
        }

    public:
        HashTable() : currentCapacity(initialCapacity),
            totalEntries(0),
            occupiedSlots(0)
        {
            hashTable = new TableEntry[initialCapacity];
        }

        HashTable(int initialCapacity_) : initialCapacity(initialCapacity_),
            currentCapacity(initialCapacity_),
            totalEntries(0),
            occupiedSlots(0)
        {
            hashTable = new TableEntry[initialCapacity];
        }

        ~HashTable()
        {
            delete[] hashTable;
        }

        void print() const
        {
            formatTablePrint();
        }

        void load_data(const dataTypes::Product* array, int arraySize)
        {
            loadFromArray(array, arraySize);
        }

        int getCapacity()
        {
            return currentCapacity;
        }

        bool add(const Record& record)
        {
            return insertRecord(record);
        }

        int find(long long barCode, int index)
        {
            Record recordToFind(barCode, index);
            TableEntry entry = findEntry(recordToFind);
            return (entry.state == 1) ? entry.data.index : -1;
        }

        int findByBarcode(long long barCodeKey)
        {
            return findByKey(barCodeKey);
        }

        int findByBarcodeWithSteps(long long barCodeKey, int &steps)
        {
            return findByKeyWithSteps(barCodeKey, steps);
        }

        bool removeByBarcode(long long barCodeKey)
        {
            return removeByKey(barCodeKey);
        }

        bool remove(long long barCode, int index)
        {
            Record recordToRemove(barCode, index);
            return removeRecord(recordToRemove);
        }

        void saveTable(const std::string& fileName)
        {
            saveDataToFile(fileName);
        }
    };
}