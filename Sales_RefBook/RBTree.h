#pragma once

#include "List.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;
using namespace list;

namespace tree
{

    // Базовый класс для ключей
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

    // Пример реализации ключа для строки (barcode)
    class BarcodeKey : public KeyType<long long>
    {
    public:
        long long barcode;

    public:
        BarcodeKey() : barcode(1000000000000) {}

        BarcodeKey(long long bc) : barcode(bc) {}

        bool operator<(const KeyType<long long>& other) const override
        {
            const BarcodeKey* otherKey = dynamic_cast<const BarcodeKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return barcode < otherKey->barcode;
        }

        bool operator>(const KeyType<long long>& other) const override
        {
            const BarcodeKey* otherKey = dynamic_cast<const BarcodeKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return barcode > otherKey->barcode;
        }

        bool operator==(const KeyType<long long>& other) const override
        {
            const BarcodeKey* otherKey = dynamic_cast<const BarcodeKey*>(&other);
            if (otherKey == nullptr)
                return false;
            return barcode == otherKey->barcode;
        }

        bool operator!=(const KeyType<long long>& other) const override
        {
            return !(*this == other);
        }

        string toString() const override
        {
            return to_string(barcode);
        }

        KeyType<long long>* clone() const override
        {
            return new BarcodeKey(barcode);
        }

        long long getBarcode() const { return barcode; }

        long long getKey() const { return barcode; }
    };

    enum class colors
    {
        RED,
        BLACK
    };

    template <typename T>
    class tNode
    {
    public:
        KeyType<T>* key; // ключ
        List* data = new List();
        tNode<T>* left = nullptr;
        tNode<T>* right = nullptr;
        tNode<T>* parent = nullptr;
        colors color = colors::RED;

        tNode(KeyType<T>* k)
        {
            key = k->clone();
        }

        ~tNode()
        {
            delete key;
            delete data;
            data = nullptr;
        }
    };

    template <typename T>
    tNode<T>* search(tNode<T>* root, KeyType<T>& searchingKey)
    {
        if (root == nullptr)
            return nullptr;

        tNode<T>* current = root;

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

    template <typename T>
    std::pair<int*, int> searchData(tNode<T>* root, KeyType<T>& searchingKey)
    {
        int* temp = nullptr;

        tNode<T>* foundNode = search(root, searchingKey);

        if (foundNode == nullptr)
        {
            temp = new int[1];
            temp[0] = -1;
            return { temp, -1 };
        }
        else
        {
            // Считаем количество элементов в списке
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


    template <typename T>
    void rotateLeft(tNode<T>*& curNode, tNode<T>*& root)
    {
        tNode<T>* child = curNode->right;
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

    template <typename T>
    void rotateRight(tNode<T>*& curNode, tNode<T>*& root)
    {
        tNode<T>* child = curNode->left;
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

    template <typename T>
    void fixAfterAdd(tNode<T>*& curNode, tNode<T>*& root)
    {
        while (curNode != root && curNode->parent != nullptr && curNode->parent->color == colors::RED)
        {
            tNode<T>* parent = curNode->parent;
            tNode<T>* grandparent = parent->parent;

            if (grandparent == nullptr)
                break;

            if (parent == grandparent->left)
            {
                tNode<T>* uncle = grandparent->right;

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
                tNode<T>* uncle = grandparent->left;

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

    template <typename T>
    void addElement(tNode<T>*& root, KeyType<T>& key, int index)
    {
        tNode<T>* parent = nullptr;
        tNode<T>* current = root;

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

        tNode<T>* newNode = new tNode<T>(key.clone());
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

    template <typename T>
    tNode<T>* minRightNode(tNode<T>* removingElement)
    {
        tNode<T>* current = removingElement->right;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    template <typename T>
    int getChildCount(tNode<T>* parent)
    {
        if (parent->left != nullptr && parent->right != nullptr)
            return 2;
        else if (parent->left != nullptr || parent->right != nullptr)
            return 1;
        return 0;
    }

    template <typename T>
    tNode<T>* getChild(tNode<T>* parent)
    {
        if (parent->left == nullptr)
            return parent->right;
        else
            return parent->left;
    }

    template <typename T>
    void transplantNodes(tNode<T>* toNode, tNode<T>* fromNode)
    {
        swap(toNode->key, fromNode->key);
        swap(toNode->data, fromNode->data);
    }

    template <typename T>
    void clearNode(tNode<T>*& node)
    {
        delete node;
        node = nullptr;
    }

    template <typename T>
    void fixAfterRemove(tNode<T>*& curNode, tNode<T>*& root)
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

            tNode<T>* brother = nullptr;
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

    template <typename T>
    void removeElement(tNode<T>*& root, KeyType<T>& key, int index)
    {
        tNode<T>* foundNode = search(root, key);
        if (foundNode == nullptr)
        {
            cout << "Элемент не найден в дереве\n";
            return;
        }

        // Удаляем индекс из списка
        foundNode->data->remove(index);

        // Если список не пустой, ничего больше не делаем
        if (!foundNode->data->isEmpty())
        {
            return;
        }

        // Если список пустой, удаляем весь узел
        tNode<T>* deleteNode = foundNode;
        int childCount = getChildCount(deleteNode);
        tNode<T>* nodeToDelete = deleteNode;
        colors originalColor = nodeToDelete->color;
        tNode<T>* fixNode = nullptr;

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
            tNode<T>* successor = minRightNode(deleteNode);
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

    template <typename T>
    void removeTree(tNode<T>* current)
    {
        if (current != nullptr)
        {
            removeTree(current->left);
            removeTree(current->right);
            delete current;
            current = nullptr;
        }
    }

    template <typename T>
    void preOrder(tNode<T>* current, ostream& output)
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

    template <typename T>
    int countBarcodes(tNode<T>* root)
    {
        if (root == nullptr) return 0;

        int count = 1;
        count += countBarcodes(root->left);
        count += countBarcodes(root->right);
        return count;
    }

    template <typename T>
    void fillBarcodes(tNode<T>* root, T* barcodes, int& index)
    {
        if (root == nullptr) return;

        bool exists = false;
        for (int i = 0; i < index; i++)
        {
            if (barcodes[i] == root->key->getKey())
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            barcodes[index++] = root->key->getKey();
        }

        fillBarcodes(root->left, barcodes, index);
        fillBarcodes(root->right, barcodes, index);
    }

    template <typename T>
    void printHelper(tNode<T>* node, string prefix = "", bool isLeft = true)
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

    template <typename T>
    void printTree(tNode<T>* root)
    {
        if (root == nullptr)
            cout << "Дерево пустое" << endl;
        else
        {
            printHelper(root, "", true);
        }
    }

    // Функции валидации для barcode (пример использования)
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

    // Пример использования дерева
    template <typename T>
    void menu(tNode<T>*& root)
    {
        int choice = 0;

        while (choice != 6)
        {
            cout << "\nМеню:\n";
            cout << "1. Добавить элемент\n";
            cout << "2. Удалить элемент\n";
            cout << "3. Найти элемент\n";
            cout << "4. Показать дерево\n";
            cout << "5. Показать все элементы (обход дерева)\n";
            cout << "6. Выход\n";
            cout << "Введите ваш выбор: ";
            cin >> choice;
            cout << endl;

            switch (choice)
            {
            case 1:
            {
                string barcode;
                int index;
                cout << "Введите штрих-код: ";
                cin >> barcode;
                cout << "Введите индекс: ";
                cin >> index;

                if (isValidBarcode(barcode))
                {
                    BarcodeKey key(barcode);
                    addElement(root, key, index);
                    cout << "Элемент добавлен успешно.\n";
                }
                else
                {
                    cout << "Некорректный штрих-код.\n";
                }
                break;
            }
            case 2:
            {
                string barcode;
                int index;
                cout << "Введите штрих-код для удаления: ";
                cin >> barcode;
                cout << "Введите индекс для удаления: ";
                cin >> index;

                if (isValidBarcode(barcode))
                {
                    BarcodeKey key(barcode);
                    removeElement(root, key, index);
                    cout << "Элемент удален успешно.\n";
                }
                else
                {
                    cout << "Некорректный штрих-код.\n";
                }
                break;
            }
            case 3:
            {
                string barcode;
                cout << "Введите штрих-код для поиска: ";
                cin >> barcode;

                if (isValidBarcode(barcode))
                {
                    BarcodeKey key(barcode);
                    tNode<T>* result = search(root, key);
                    if (result != nullptr)
                    {
                        cout << "Найдены элементы: " << result->data->to_str() << "\n";
                    }
                    else
                    {
                        cout << "Элементы не найдены.\n";
                    }
                }
                else
                {
                    cout << "Некорректный штрих-код.\n";
                }
                break;
            }
            case 4:
            {
                printTree(root);
                break;
            }
            case 5:
            {
                preOrder(root, cout);
                cout << "Обход дерева завершен.\n";
                break;
            }
            case 6:
            {
                cout << "Выход...\n";
                break;
            }
            default:
            {
                cout << "Некорректный выбор. Попробуйте снова.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            }
        }
    }
}