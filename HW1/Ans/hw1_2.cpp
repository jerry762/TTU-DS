#include <iostream>
#include <memory>
#include <cctype>

using namespace std;

class Node
{
private:
    int m_value{0};
    shared_ptr<Node> m_nextNode{nullptr};

public:
    Node(int value);
    Node(const Node &node) = delete;
    Node &operator=(const Node &node) = delete;
    int getValue() const;
    void setValue(int value);
    shared_ptr<Node> getNextNode() const;
    void setNextNode(shared_ptr<Node> nextNode);
};

Node::Node(int value) : m_value(value), m_nextNode(nullptr)
{
}

int Node::getValue() const
{
    return m_value;
}

void Node::setValue(int value)
{
    m_value = value;
}

shared_ptr<Node> Node::getNextNode() const
{
    return m_nextNode;
}

void Node::setNextNode(shared_ptr<Node> nextNode)
{
    m_nextNode = nextNode;
}

class List
{
private:
    shared_ptr<Node> m_headNode{nullptr};

public:
    List() = default;
    List(const List &list) = delete;
    List &operator=(const List &list) = delete;
    bool empty() const;
    void insert(int value);
    void remove(int value);
    friend ostream &operator<<(ostream &out, const List &list);
};

bool List::empty() const
{
    return m_headNode ? false : true;
}

void List::insert(int value)
{
    shared_ptr<Node> newNode = make_shared<Node>(value);

    if (empty())
        m_headNode = newNode;
    else
    {
        shared_ptr<Node> currNode{m_headNode};
        shared_ptr<Node> prevNode{nullptr};

        while (currNode)
        {
            if (currNode->getValue() >= value)
            {
                if (m_headNode == currNode)
                    m_headNode = newNode;
                else
                    prevNode->setNextNode(newNode);

                newNode->setNextNode(currNode);
                break;
            }
            prevNode = currNode;
            currNode = currNode->getNextNode();
        }
        if (!currNode)
            prevNode->setNextNode(newNode);
    }
}

void List::remove(int value)
{
    if (!empty())
    {
        shared_ptr<Node> currNode{m_headNode};
        shared_ptr<Node> prevNode{nullptr};

        while (currNode)
        {
            if (currNode->getValue() == value)
            {
                while (currNode && currNode->getValue() == value)
                    currNode = currNode->getNextNode();

                if (prevNode)
                    prevNode->setNextNode(currNode);
                else
                    m_headNode = currNode;

                break;
            }
            prevNode = currNode;
            currNode = currNode->getNextNode();
        }
    }
}

ostream &operator<<(ostream &out, const List &list)
{
    shared_ptr<Node> currNode = list.m_headNode;

    while (currNode)
    {
        out << currNode->getValue() << " ";
        currNode = currNode->getNextNode();
    }
    return out;
}

int main()
{
    List list;
    char cmd = 0;
    int num = 0;

    while (tolower(cmd) != 'e')
    {
        cout << "Input or delete: ";
        cin >> cmd;

        switch (tolower(cmd))
        {
        case 'i':
            cout << "Input number: ";
            cin >> num;
            list.insert(num);
            break;
        case 'd':
            cout << "Delete number: ";
            cin >> num;
            list.remove(num);
            break;
        default:
            cout << "invalid input !\n"
                 << endl;
            continue;
        }

        if (!list.empty())
            cout << list;
        else
            cout << "empty !";

        cout << "\n"
             << endl;
    }

    return 0;
}