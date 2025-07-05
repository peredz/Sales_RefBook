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

            // �������� �������������
            int operator*() const
            {
                return current->index;
            }

            // ���������� ���������
            Iterator& operator++()
            {
                if (current != nullptr)
                    current = current->next;
                return *this;
            }

            // ��������� �� �����������
            bool operator!=(const Iterator& other) const
            {
                return current != other.current;
            }
        };

        // ������� ����������
        Iterator begin() const { return Iterator(head); }
        Iterator end() const { return Iterator(nullptr); }

        // ���������� �������� � ����� ������
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

        // �������� ���� � �������� index
        void remove(int index)
        {
            if (head == nullptr)
                return;

            // ���� ��������� �������� ����
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



        // ��������� ������ ������ (� ���������� ������������ � �� �� ���� ����� ��� ��������)
        Node* getHead() { return head; }

        // �������� �� ������� ������
        bool isEmpty() const
        {
            return head == nullptr;
        }

        // ������� ������
        void clear()
        {
            while (head != nullptr)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        // �������������� ������ � ������ (��� ������������)
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

        // �����������
        List() = default;

        // ����������
        ~List()
        {
            clear();
        }
    };
}
