#include <iostream>
#include <fstream>
#include <string>
#include <stack>

//8(3(1,6(4,7)),10(,14(13,)))       <- пример

struct Element
{
    int value;
    int level;
    Element* left;
    Element* right;
    Element* parent;
};

Element* treeMaker(int data, Element* p)
{
    Element* q = new Element;
    q->value = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}

void addElement(int data, Element*& root)   //добавляем элемент в дерево
{
    if (root == nullptr)
    {
        root = treeMaker(data, nullptr);
        return;
    }

    Element* r = root;
    while ((data < r->value && r->left != nullptr) || (data > r->value && r->right != nullptr))
    {
        if (data < r->value)    //если меньше значения - становится левым ребёнком
            r = r->left;
        else
            r = r->right;   //если больше значения - становится правым ребёнком
    }
    if (data == r->value)
        return;

    Element* t = treeMaker(data, r);
    if (data < r->value)
        r->left = t;
    else if (data > r->value)
        r->right = t;
}

void pass(Element* v)
{
    if (v == nullptr)
        return;
    pass(v->left);
    std::cout << v->value << " ";
    pass(v->right);
}

Element* searchElement(int data, Element* v)
{
    if (v == nullptr)
        return v;
    if (v->value == data)
        return v;
    if (data < v->value)
        return searchElement(data, v->left);
    else  if (data > v->value)
        return searchElement(data, v->right);
}

void deleteElement(int data, Element*& root)
{
    Element* u = searchElement(data, root);
    if (u == nullptr)
        return;
    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        delete root;
        root = nullptr;
        return;
    }
    if (u->left == nullptr && u->right != nullptr && u == root)
    {
        Element* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->value = t->value;
        u = t;
    }
    if (u->left != nullptr && u->right == nullptr && u == root)
    {
        Element* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->value = t->value;
        u = t;
    }
    if (u->left != nullptr && u->right != nullptr)
    {
        Element* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->value = t->value;
        u = t;
    }
    Element* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;
    delete u;
}

void inParenthesis(int data, Element*& root, bool inLeft)
{
    Element* v = root;
    Element* u = treeMaker(data, v);
    if (inLeft)
        v->left = u;
    else
        v->right = u;
}

void fillTree(std::string& bracketEntry, int& i, Element*& root)    //заполненяем дерево скобочной записью
{
    int value = 0;
    while (bracketEntry[i] != '\0') //пока не конец строки
    {
        switch (bracketEntry[i])
        {
        case '(':
        {
            i++;
            value = 0;
            while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
            {
                value = value * 10 + bracketEntry[i] - '0';
                i++;
            }
            if (value != 0)
            {
                inParenthesis(value, root, true);
                if (bracketEntry[i] == '(')
                    fillTree(bracketEntry, i, root->left);
            }
            value = 0;
            break;
        }
        case ',':
        {
            i++;
            value = 0;
            while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
            {
                value = value * 10 + bracketEntry[i] - '0';
                i++;
            }
            if (value != 0)
            {
                inParenthesis(value, root, false);
                if (bracketEntry[i] == '(')
                    fillTree(bracketEntry, i, root->right);
            }
            value = 0;
            break;
        }
        case ')':
            i++;
            return;
        default:
            break;
        }
    }
}

int depth(int data, Element* v, int k)  //как глубоко элемент находится в дереве
{
    if (v == nullptr)
    {
        return -1;
    }
    if (v->value == data)
    {
        return k;
    }
    if (data < v->value)
        return depth(data, v->left, k + 1);
    if (data > v->value)
        return depth(data, v->right, k + 1);
}

void clearMemory(Element*& v)
{
    if (v == nullptr)
        return;
    clearMemory(v->left);
    clearMemory(v->right);
    delete v;
    v = nullptr;
}

void straightPass(Element* root)    //прямой обход
{
    if (root == nullptr)
        return;
    std::cout << root->value << " ";
    straightPass(root->left);
    straightPass(root->right);
}

void printTree(Element* root)
{
    if (root == nullptr)
    {
        std::cout << "\n";
        return;
    }
    printTree(root->right);
    for (int i = root->level; i > 0; i--)
    {
        std::cout << '\n';
    }
    std::cout << root->value << "\n";
    printTree(root->left);
}
void menu(Element* root)
{
    bool fl = false;
    int choice;
    std::cout << "Menu.\n";
    while (!fl)
    {
        std::cout << "Choose binary tree operations:\n";
        std::cout << "Enter 1 to add an element,\n";
        std::cout << "Enter 2 to delete an element,\n";
        std::cout << "Enter 3 to find an element,\n";
        std::cout << "Enter 4 to exit.\n";

        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int value;
            std::cout << "Enter the value to add: ";
            std::cin >> value;
            addElement(value, root);
            break;
        }
        case 2:
        {
            int value;
            std::cout << "Enter the value to delete: ";
            std::cin >> value;
            deleteElement(value, root);
            break;
        }
        case 3:
        {
            int value;
            std::cout << "Enter the value to find: ";
            std::cin >> value;

            Element* e = nullptr;
            e = searchElement(value, root);
            if (e == nullptr)
                std::cout << "No such element has been found!\n";
            else
                std::cout << "The element is in the tree.\n";
            break;
        }
        case 4:
            fl = true;
            break;
        default:
            std::cout << "Sorry, unknown operation.\n";
            break;
        }
    }
}

int main()
{
    Element* root = nullptr;    //пустое значение корня
    std::string bracketEntry;   //скобочная запись
    std::cout << "Enter bracket-type binary tree entry:\n";
    std::cin >> bracketEntry;

    int digit = 0;
    int i = 0;
    while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
    {
        digit += digit * 10 + bracketEntry[i] - '0';
        i++;
    }
    addElement(digit, root);
    fillTree(bracketEntry, i, root);
    menu(root);
    straightPass(root);
    clearMemory(root);
    std::cout << "Tree printed.\n";
    std::cout << "End of programme\n";
    return 0;
}