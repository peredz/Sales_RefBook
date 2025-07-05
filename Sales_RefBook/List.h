#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace list
{
    class List
    {
    private:
        struct Node
        {
            int index;
            Node* next;

            Node(int idx, Node* next_node = nullptr)
                : index(idx), next(next_node) {
            }
        };

        Node* head = nullptr;

    public:
        class Iterator
        {
        private:
            Node* current;

        public:
            explicit Iterator(Node* node) : current(node) {}

            // Оператор разыменования
            int operator*() const
            {
                return current->index;
            }

            // Префиксный инкремент
            Iterator& operator++()
            {
                if (current != nullptr)
                    current = current->next;
                return *this;
            }

            // Сравнение на неравенство
            bool operator!=(const Iterator& other) const
            {
                return current != other.current;
            }
        };

        // Возврат итераторов
        Iterator begin() const { return Iterator(head); }
        Iterator end() const { return Iterator(nullptr); }

        // Добавление элемента в конец списка
        void add(int index)
        {
            if (head == nullptr)
            {
                head = new Node(index);
            }
            else
            {
                Node* current = head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = new Node(index);
            }
        }

        // Удаление узла с заданным index
        void remove(int index)
        {
            if (head == nullptr)
                return;

            // Если удаляется головной узел
            if (head->index == index)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
            }

            Node* current = head;
            while (current->next != nullptr)
            {
                if (current->next->index == index)
                {
                    Node* temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    return;
                }
                current = current->next;
            }
        }



        // Получение головы списка (с нарушением инкапсуляции — но ты явно хотел это оставить)
        Node* getHead() { return head; }

        // Проверка на пустоту списка
        bool isEmpty() const
        {
            return head == nullptr;
        }

        // Очистка списка
        void clear()
        {
            while (head != nullptr)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        // Преобразование списка в строку (для тестирования)
        string to_str() const
        {
            if (head == nullptr)
                return "empty list";

            string result;
            Node* current = head;
            while (current != nullptr)
            {
                result += to_string(current->index);
                if (current->next != nullptr)
                    result += " -> ";
                current = current->next;
            }
            return result;
        }

        // Конструктор
        List() = default;

        // Деструктор
        ~List()
        {
            clear();
        }
    };
}
