#pragma once

#include "List.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace list;

namespace dateTree
{
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

        bool operator!=(const Date& other) const {
            return !(*this == other);
        }

        std::string toString() const {
            const std::string monthNames[] = { "янв", "фев", "мар", "апр", "май", "июн",
                                              "июл", "авг", "сен", "окт", "ноя", "дек" };
            return std::to_string(day) + " " + monthNames[month] + " " + std::to_string(year);
        }

        Date() : day(0), month(0), year(0) {}
        Date(int d, int m, int y) : day(d), month(m), year(y) {}
    };

    enum class colors
    {
        RED,
        BLACK
    };

    // Узел дерева для дат
    class DateNode
    {
    public:
        Date key;
        List* data = new List();
        DateNode* left = nullptr;
        DateNode* right = nullptr;
        DateNode* parent = nullptr;
        colors color = colors::RED;

        DateNode(const Date& date) : key(date) {}

        ~DateNode()
        {
            delete data;
        }
    };

    // Поиск узла по дате
    DateNode* search(DateNode* root, const Date& searchingDate)
    {
        if (root == nullptr)
            return nullptr;

        DateNode* current = root;

        while (current != nullptr && !(current->key == searchingDate))
        {
            if (current->key > searchingDate)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return (current != nullptr && current->key == searchingDate) ? current : nullptr;
    }

    // Поиск данных по дате
    std::pair<int*, int> searchData(DateNode* root, const Date& searchingDate)
    {
        int* temp = nullptr;

        DateNode* foundNode = search(root, searchingDate);

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

    // Левый поворот
    void rotateLeft(DateNode*& curNode, DateNode*& root)
    {
        DateNode* child = curNode->right;
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

    // Правый поворот
    void rotateRight(DateNode*& curNode, DateNode*& root)
    {
        DateNode* child = curNode->left;
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

    // Балансировка после добавления
    void fixAfterAdd(DateNode*& curNode, DateNode*& root)
    {
        while (curNode != root && curNode->parent != nullptr && curNode->parent->color == colors::RED)
        {
            DateNode* parent = curNode->parent;
            DateNode* grandparent = parent->parent;

            if (grandparent == nullptr)
                break;

            if (parent == grandparent->left)
            {
                DateNode* uncle = grandparent->right;

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
                DateNode* uncle = grandparent->left;

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

    // Добавление элемента
    void addElement(DateNode*& root, const Date& date, int index)
    {
        DateNode* parent = nullptr;
        DateNode* current = root;

        while (current != nullptr)
        {
            parent = current;
            if (current->key == date)
            {
                current->data->add(index);
                return;
            }
            else if (current->key > date)
                current = current->left;
            else
                current = current->right;
        }

        DateNode* newNode = new DateNode(date);
        newNode->data->add(index);
        newNode->parent = parent;

        if (parent == nullptr)
        {
            root = newNode;
        }
        else
        {
            if (parent->key > date)
                parent->left = newNode;
            else
                parent->right = newNode;
        }
        fixAfterAdd(newNode, root);
    }

    // Поиск минимального узла в правом поддереве
    DateNode* minRightNode(DateNode* removingElement)
    {
        DateNode* current = removingElement->right;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Подсчет количества детей
    int getChildCount(DateNode* parent)
    {
        if (parent->left != nullptr && parent->right != nullptr)
            return 2;
        else if (parent->left != nullptr || parent->right != nullptr)
            return 1;
        return 0;
    }

    // Получение единственного ребенка
    DateNode* getChild(DateNode* parent)
    {
        if (parent->left == nullptr)
            return parent->right;
        else
            return parent->left;
    }

    // Очистка узла
    void clearNode(DateNode*& node)
    {
        delete node;
        node = nullptr;
    }

    // Балансировка после удаления
    void fixAfterRemove(DateNode*& curNode, DateNode*& root)
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

            DateNode* brother = nullptr;
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

    // Удаление элемента
    void removeElement(DateNode* root, const Date& date, int index)
    {
        DateNode* foundNode = search(root, date);
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

        DateNode* deleteNode = foundNode;
        int childCount = getChildCount(deleteNode);
        DateNode* nodeToDelete = deleteNode;
        colors originalColor = nodeToDelete->color;
        DateNode* fixNode = nullptr;

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
            DateNode* successor = minRightNode(deleteNode);
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

    // Удаление всего дерева
    void removeTree(DateNode*& current)
    {
        if (current != nullptr)
        {
            removeTree(current->left);
            removeTree(current->right);
            delete current;
            current = nullptr;
        }
    }

    // Обход дерева (прямой порядок)
    void preOrder(DateNode* current, ostream& output)
    {
        if (current == nullptr)
        {
            return;
        }
        output << "Дата: " << current->key.toString() << " -> " << current->data->to_str();
        output << endl;
        preOrder(current->left, output);
        preOrder(current->right, output);
    }

    // Подсчет узлов
    int countNodes(DateNode* root)
    {
        if (root == nullptr) return 0;

        int count = 1;
        count += countNodes(root->left);
        count += countNodes(root->right);
        return count;
    }

    // Заполнение массива ключей
    void fillKeys(DateNode* root, Date* keys, int& index)
    {
        if (root == nullptr) return;

        bool exists = false;
        for (int i = 0; i < index; i++)
        {
            if (keys[i] == root->key)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            keys[index++] = root->key;
        }

        fillKeys(root->left, keys, index);
        fillKeys(root->right, keys, index);
    }

    // Вспомогательная функция для печати дерева
    void printHelper(DateNode* node, string prefix = "", bool isLeft = true)
    {
        if (node == nullptr)
        {
            return;
        }

        cout << prefix;
        cout << (isLeft ? "|__ " : "|-- ");

        cout << "[" << node->key.toString() << "] ("
            << (node->color == colors::RED ? "R" : "B")
            << ") " << node->data->to_str()
            << endl;

        string newPrefix = prefix + (isLeft ? "|   " : "    ");

        printHelper(node->left, newPrefix, true);
        printHelper(node->right, newPrefix, false);
    }

    // Печать дерева
    void printTree(DateNode* root)
    {
        if (root == nullptr)
            cout << "Дерево пустое" << endl;
        else
        {
            printHelper(root, "", true);
        }
    }

    // Функция валидации даты
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