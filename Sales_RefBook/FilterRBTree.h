#pragma once

#include "List.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;
using namespace list;

namespace filterTree
{
    // Базовый класс для ключей - теперь просто интерфейс без шаблона
    template <typename T>
    class KeyType
    {
    public:
        virtual ~KeyType() = default;
        virtual bool operator<(const KeyType<T>& other) const = 0;
        virtual bool operator>(const KeyType<T>& other) const = 0;
        virtual bool operator==(const KeyType<T>& other) const = 0;
        virtual bool operator!=(const KeyType<T>& other) const = 0;
        virtual T getKey() const = 0;
        virtual string toString() const = 0;
        virtual KeyType<T>* clone() const = 0;
    };



    // Структура для даты
    struct Date {
        int day;
        int month;
        int year;

        bool operator==(const Date& other) const {
            return day == other.day && month == other.month && year == other.year;
        }

        bool operator<(const Date& other) const {
            if (year != other.year) return year < other.year;
            if (month != other.month) return month < other.month;
            return day < other.day;
        }

        bool operator>(const Date& other) const {
            return other < *this;
        }

        std::string toString() const {
            const std::string monthNames[] = { "янв", "фев", "мар", "апр", "май", "июн",
                                              "июл", "авг", "сен", "окт", "ноя", "дек" };
            return std::to_string(day) + " " + monthNames[month] + " " + std::to_string(year);
        }

        Date() : day(0), month(0), year(0) {}
        Date(int d, int m, int y) : day(d), month(m), year(y) {}
    };

    // Реализация ключа для даты
    class DateKey : public KeyType<Date>
    {
    public:
        Date date;

    public:
        DateKey() : date() {}
        DateKey(const Date& d) : date(d) {}
        DateKey(int day, int month, int year) : date(day, month, year) {}

        bool operator<(const KeyType<Date>& other) const override
        {
            const DateKey* otherKey = dynamic_cast<const DateKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return date < otherKey->date;
        }

        bool operator>(const KeyType<Date>& other) const override
        {
            const DateKey* otherKey = dynamic_cast<const DateKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return date > otherKey->date;
        }

        bool operator==(const KeyType<Date>& other) const override
        {
            const DateKey* otherKey = dynamic_cast<const DateKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return date == otherKey->date;
        }

        bool operator!=(const KeyType<Date>& other) const override
        {
            return !(*this == other);
        }

        string toString() const override
        {
            return date.toString();
        }

        KeyType<Date>* clone() const override
        {
            return new DateKey(date);
        }

        Date getKey() const override { return date; }
    };

    class NameKey : public KeyType<std::string>
    {
    private:
        std::string name;

    public:
        NameKey() : name("") {}
        NameKey(const std::string& n) : name(n) {}

        bool operator<(const KeyType<std::string>& other) const override
        {
            const NameKey* otherKey = dynamic_cast<const NameKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return name < otherKey->name;
        }

        bool operator>(const KeyType<std::string>& other) const override
        {
            const NameKey* otherKey = dynamic_cast<const NameKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return name > otherKey->name;
        }

        bool operator==(const KeyType<std::string>& other) const override
        {
            const NameKey* otherKey = dynamic_cast<const NameKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return name == otherKey->name;
        }

        bool operator!=(const KeyType<std::string>& other) const override
        {
            return !(*this == other);
        }

        std::string toString() const override
        {
            return name;
        }

        KeyType<std::string>* clone() const override
        {
            return new NameKey(name);
        }

        std::string getKey() const override { return name; }
    };

    class AmountKey : public KeyType<int>
    {
    private:
        int amount;

    public:
        AmountKey() : amount(0) {}
        AmountKey(int a) : amount(a) {}

        bool operator<(const KeyType<int>& other) const override
        {
            const AmountKey* otherKey = dynamic_cast<const AmountKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return amount < otherKey->amount;
        }

        bool operator>(const KeyType<int>& other) const override
        {
            const AmountKey* otherKey = dynamic_cast<const AmountKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return amount > otherKey->amount;
        }

        bool operator==(const KeyType<int>& other) const override
        {
            const AmountKey* otherKey = dynamic_cast<const AmountKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return amount == otherKey->amount;
        }

        bool operator!=(const KeyType<int>& other) const override
        {
            return !(*this == other);
        }

        std::string toString() const override
        {
            return std::to_string(amount);
        }

        KeyType<int>* clone() const override
        {
            return new AmountKey(amount);
        }

        int getKey() const override { return amount; }
    };


    enum class colors
    {
        RED,
        BLACK
    };

    // Обновленный класс узла с двумя шаблонными параметрами
    template <typename T, template<typename> class KType>
    class tNode
    {
    public:
        KType<T>* key; // ключ
        List* data = new List();
        tNode<T, KType>* left = nullptr;
        tNode<T, KType>* right = nullptr;
        tNode<T, KType>* parent = nullptr;
        colors color = colors::RED;

        tNode(KType<T>* k)
        {
            key = static_cast<KType<T>*>(k->clone());
        }

        void deleteElement(KType<T> key, int index)
        {
            removeElement(this, key, index);
        }

        ~tNode()
        {
            delete key;
            delete data;
        }
    };

    // Обновленные функции с двумя шаблонными параметрами
    template <typename T, template<typename> class KType>
    tNode<T, KType>* search(tNode<T, KType>* root, KType<T>& searchingKey)
    {
        if (root == nullptr)
            return nullptr;

        tNode<T, KType>* current = root;

        while (current != nullptr && !(*current->key == searchingKey))
        {
            if (*current->key > searchingKey)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return (current != nullptr && *current->key == searchingKey) ? current : nullptr;
    }

    template <typename T, template<typename> class KType>
    std::pair<int*, int> searchData(tNode<T, KType>* root, KType<T>& searchingKey)
    {
        int* temp = nullptr;

        tNode<T, KType>* foundNode = search(root, searchingKey);

        if (foundNode == nullptr)
        {
            temp = new int[1];
            temp[0] = -1;
            return { temp, -1 };
        }
        else
        {
            int count = 0;
            for (auto it = foundNode->data->begin(); it != foundNode->data->end(); ++it)
            {
                ++count;
            }

            temp = new int[count];
            int i = 0;
            for (auto it = foundNode->data->begin(); it != foundNode->data->end(); ++it)
            {
                temp[i++] = *it;
            }

            return { temp, count };
        }
    }

    template <typename T, template<typename> class KType>
    void rotateLeft(tNode<T, KType>*& curNode, tNode<T, KType>*& root)
    {
        tNode<T, KType>* child = curNode->right;
        curNode->right = child->left;

        if (curNode->right != nullptr)
            curNode->right->parent = curNode;

        child->parent = curNode->parent;

        if (curNode->parent == nullptr)
            root = child;
        else if (curNode == curNode->parent->left)
            curNode->parent->left = child;
        else
            curNode->parent->right = child;

        child->left = curNode;
        curNode->parent = child;
    }

    template <typename T, template<typename> class KType>
    void rotateRight(tNode<T, KType>*& curNode, tNode<T, KType>*& root)
    {
        tNode<T, KType>* child = curNode->left;
        curNode->left = child->right;

        if (curNode->left != nullptr)
            curNode->left->parent = curNode;

        child->parent = curNode->parent;

        if (curNode->parent == nullptr)
            root = child;
        else if (curNode == curNode->parent->left)
            curNode->parent->left = child;
        else
            curNode->parent->right = child;

        child->right = curNode;
        curNode->parent = child;
    }

    template <typename T, template<typename> class KType>
    void fixAfterAdd(tNode<T, KType>*& curNode, tNode<T, KType>*& root)
    {
        while (curNode != root && curNode->parent != nullptr && curNode->parent->color == colors::RED)
        {
            tNode<T, KType>* parent = curNode->parent;
            tNode<T, KType>* grandparent = parent->parent;

            if (grandparent == nullptr)
                break;

            if (parent == grandparent->left)
            {
                tNode<T, KType>* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == colors::RED)
                {
                    parent->color = colors::BLACK;
                    uncle->color = colors::BLACK;
                    grandparent->color = colors::RED;
                    curNode = grandparent;
                }
                else
                {
                    if (curNode == parent->right)
                    {
                        curNode = parent;
                        rotateLeft(curNode, root);
                        parent = curNode->parent;
                        if (parent != nullptr)
                            grandparent = parent->parent;
                    }

                    if (parent != nullptr && grandparent != nullptr)
                    {
                        parent->color = colors::BLACK;
                        grandparent->color = colors::RED;
                        rotateRight(grandparent, root);
                    }
                }
            }
            else
            {
                tNode<T, KType>* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == colors::RED)
                {
                    parent->color = colors::BLACK;
                    uncle->color = colors::BLACK;
                    grandparent->color = colors::RED;
                    curNode = grandparent;
                }
                else
                {
                    if (curNode == parent->left)
                    {
                        curNode = parent;
                        rotateRight(curNode, root);
                        parent = curNode->parent;
                        if (parent != nullptr)
                            grandparent = parent->parent;
                    }

                    if (parent != nullptr && grandparent != nullptr)
                    {
                        parent->color = colors::BLACK;
                        grandparent->color = colors::RED;
                        rotateLeft(grandparent, root);
                    }
                }
            }
        }

        if (root != nullptr)
            root->color = colors::BLACK;
    }

    template <typename T, template<typename> class KType>
    void addElement(tNode<T, KType>*& root, KType<T>& key, int index)
    {
        tNode<T, KType>* parent = nullptr;
        tNode<T, KType>* current = root;

        while (current != nullptr)
        {
            parent = current;
            if (*current->key == key)
            {
                current->data->add(index);
                return;
            }
            else if (*current->key > key)
                current = current->left;
            else
                current = current->right;
        }

        tNode<T, KType>* newNode = new tNode<T, KType>(static_cast<KType<T>*>(key.clone()));
        newNode->data->add(index);
        newNode->parent = parent;

        if (parent == nullptr)
        {
            root = newNode;
        }
        else
        {
            if (*parent->key > key)
                parent->left = newNode;
            else
                parent->right = newNode;
        }
        fixAfterAdd(newNode, root);
    }

    template <typename T, template<typename> class KType>
    tNode<T, KType>* minRightNode(tNode<T, KType>* removingElement)
    {
        tNode<T, KType>* current = removingElement->right;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    template <typename T, template<typename> class KType>
    int getChildCount(tNode<T, KType>* parent)
    {
        if (parent->left != nullptr && parent->right != nullptr)
            return 2;
        else if (parent->left != nullptr || parent->right != nullptr)
            return 1;
        return 0;
    }

    template <typename T, template<typename> class KType>
    tNode<T, KType>* getChild(tNode<T, KType>* parent)
    {
        if (parent->left == nullptr)
            return parent->right;
        else
            return parent->left;
    }

    template <typename T, template<typename> class KType>
    void transplantNodes(tNode<T, KType>* toNode, tNode<T, KType>* fromNode)
    {
        swap(toNode->key, fromNode->key);
        swap(toNode->data, fromNode->data);
    }

    template <typename T, template<typename> class KType>
    void clearNode(tNode<T, KType>*& node)
    {
        delete node;
        node = nullptr;
    }

    template <typename T, template<typename> class KType>
    void fixAfterRemove(tNode<T, KType>*& curNode, tNode<T, KType>*& root)
    {
        if (curNode == root)
        {
            clearNode(root);
            return;
        }

        while (curNode != root && (curNode == nullptr || curNode->color == colors::BLACK))
        {
            if (curNode == nullptr)
                break;

            tNode<T, KType>* brother = nullptr;
            if (curNode->parent != nullptr)
            {
                if (curNode == curNode->parent->left)
                {
                    brother = curNode->parent->right;
                    if (brother != nullptr && brother->color == colors::RED)
                    {
                        brother->color = colors::BLACK;
                        curNode->parent->color = colors::RED;
                        rotateLeft(curNode->parent, root);
                        brother = curNode->parent->right;
                    }

                    if (brother != nullptr &&
                        (brother->left == nullptr || brother->left->color == colors::BLACK) &&
                        (brother->right == nullptr || brother->right->color == colors::BLACK))
                    {
                        brother->color = colors::RED;
                        curNode = curNode->parent;
                    }
                    else if (brother != nullptr)
                    {
                        if (brother->right == nullptr || brother->right->color == colors::BLACK)
                        {
                            if (brother->left != nullptr)
                                brother->left->color = colors::BLACK;
                            brother->color = colors::RED;
                            rotateRight(brother, root);
                            brother = curNode->parent->right;
                        }
                        if (brother != nullptr)
                        {
                            brother->color = curNode->parent->color;
                            curNode->parent->color = colors::BLACK;
                            if (brother->right != nullptr)
                                brother->right->color = colors::BLACK;
                            rotateLeft(curNode->parent, root);
                        }
                        curNode = root;
                    }
                }
                else
                {
                    brother = curNode->parent->left;
                    if (brother != nullptr && brother->color == colors::RED)
                    {
                        brother->color = colors::BLACK;
                        curNode->parent->color = colors::RED;
                        rotateRight(curNode->parent, root);
                        brother = curNode->parent->left;
                    }

                    if (brother != nullptr &&
                        (brother->left == nullptr || brother->left->color == colors::BLACK) &&
                        (brother->right == nullptr || brother->right->color == colors::BLACK))
                    {
                        brother->color = colors::RED;
                        curNode = curNode->parent;
                    }
                    else if (brother != nullptr)
                    {
                        if (brother->left == nullptr || brother->left->color == colors::BLACK)
                        {
                            if (brother->right != nullptr)
                                brother->right->color = colors::BLACK;
                            brother->color = colors::RED;
                            rotateLeft(brother, root);
                            brother = curNode->parent->left;
                        }
                        if (brother != nullptr)
                        {
                            brother->color = curNode->parent->color;
                            curNode->parent->color = colors::BLACK;
                            if (brother->left != nullptr)
                                brother->left->color = colors::BLACK;
                            rotateRight(curNode->parent, root);
                        }
                        curNode = root;
                    }
                }
            }
            else
            {
                break;
            }
        }

        if (curNode != nullptr)
            curNode->color = colors::BLACK;
    }

    template <typename T, template<typename> class KType>
    void removeElement(tNode<T, KType>*& root, KType<T>& key, int index);

    void removeElementByName(tNode<string, filterTree::KeyType>* root, NameKey productNameKey, int index)
    {
        removeElement(root, productNameKey, index);
    }

    void removeElementByAmount(tNode<int, filterTree::KeyType>* root, AmountKey productNameKey, int index)
    {
        removeElement(root, productNameKey, index);
    }

    template <typename T, template<typename> class KType>
    void removeElement(tNode<T, KType>*& root, KType<T>& key, int index)
    {
        tNode<T, KType>* foundNode = search(root, key);
        if (foundNode == nullptr)
        {
            cout << "Элемент не найден в дереве\n";
            return;
        }

        foundNode->data->remove(index);

        if (!foundNode->data->isEmpty())
        {
            return;
        }

        tNode<T, KType>* deleteNode = foundNode;
        int childCount = getChildCount(deleteNode);
        tNode<T, KType>* nodeToDelete = deleteNode;
        colors originalColor = nodeToDelete->color;
        tNode<T, KType>* fixNode = nullptr;

        if (childCount == 0)
        {
            fixNode = nullptr;
            if (deleteNode->parent != nullptr)
            {
                if (deleteNode == deleteNode->parent->left)
                    deleteNode->parent->left = nullptr;
                else
                    deleteNode->parent->right = nullptr;
            }
            else
            {
                root = nullptr;
            }
        }
        else if (childCount == 1)
        {
            fixNode = getChild(deleteNode);
            if (fixNode != nullptr)
                fixNode->parent = deleteNode->parent;

            if (deleteNode->parent == nullptr)
                root = fixNode;
            else if (deleteNode == deleteNode->parent->left)
                deleteNode->parent->left = fixNode;
            else
                deleteNode->parent->right = fixNode;
        }
        else
        {
            tNode<T, KType>* successor = minRightNode(deleteNode);
            originalColor = successor->color;
            fixNode = successor->right;

            if (successor->parent == deleteNode)
            {
                if (fixNode != nullptr)
                    fixNode->parent = successor;
            }
            else
            {
                if (fixNode != nullptr)
                    fixNode->parent = successor->parent;
                successor->parent->left = fixNode;
                successor->right = deleteNode->right;
                deleteNode->right->parent = successor;
            }

            successor->parent = deleteNode->parent;
            if (deleteNode->parent == nullptr)
                root = successor;
            else if (deleteNode == deleteNode->parent->left)
                deleteNode->parent->left = successor;
            else
                deleteNode->parent->right = successor;

            successor->left = deleteNode->left;
            deleteNode->left->parent = successor;
            successor->color = deleteNode->color;
        }

        delete deleteNode;

        if (originalColor == colors::BLACK && fixNode != nullptr)
        {
            fixAfterRemove(fixNode, root);
        }
    }


    template <typename T, template<typename> class KType>
    void removeTree(tNode<T, KType>*& current)
    {
        if (current != nullptr)
        {
            removeTree(current->left);
            removeTree(current->right);
            delete current;
            current = nullptr;
        }
    }

    template <typename T, template<typename> class KType>
    void preOrder(tNode<T, KType>* current, ostream& output)
    {
        if (current == nullptr)
        {
            return;
        }
        output << "Ключ: " << current->key->toString() << " -> " << current->data->to_str();
        output << endl;
        preOrder(current->left, output);
        preOrder(current->right, output);
    }

    template <typename T, template<typename> class KType>
    int countNodes(tNode<T, KType>* root)
    {
        if (root == nullptr) return 0;

        int count = 1;
        count += countNodes(root->left);
        count += countNodes(root->right);
        return count;
    }

    template <typename T, template<typename> class KType>
    void fillKeys(tNode<T, KType>* root, T* keys, int& index)
    {
        if (root == nullptr) return;

        bool exists = false;
        for (int i = 0; i < index; i++)
        {
            if (keys[i] == root->key->getKey())
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            keys[index++] = root->key->getKey();
        }

        fillKeys(root->left, keys, index);
        fillKeys(root->right, keys, index);
    }

    template <typename T, template<typename> class KType>
    void printHelper(tNode<T, KType>* node, string prefix = "", bool isLeft = true)
    {
        if (node == nullptr)
        {
            return;
        }

        cout << prefix;
        cout << (isLeft ? "|__ " : "|-- ");

        cout << "[" << node->key->toString() << "] ("
            << (node->color == colors::RED ? "R" : "B")
            << ") " << node->data->to_str()
            << endl;

        string newPrefix = prefix + (isLeft ? "|   " : "    ");

        printHelper(node->left, newPrefix, true);
        printHelper(node->right, newPrefix, false);
    }

    template <typename T, template<typename> class KType>
    void printTree(tNode<T, KType>* root)
    {
        if (root == nullptr)
            cout << "Дерево пустое" << endl;
        else
        {
            printHelper(root, "", true);
        }
    }

    // Функции валидации
    bool isValidBarcode(const string& barcode)
    {
        if (barcode.length() != 13)
            return false;

        if (barcode[0] == '0')
            return false;

        for (char c : barcode)
        {
            if (!isdigit(c))
                return false;
        }

        return true;
    }

    bool isValidDate(int day, int month, int year)
    {
        if (year < 1900 || year > 2100) return false;
        if (month < 0 || month > 11) return false;
        if (day < 1 || day > 31) return false;

        // Простая проверка на количество дней в месяце
        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            daysInMonth[1] = 29; // високосный год

        return day <= daysInMonth[month];
    }

}