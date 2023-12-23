#include <iostream>
#include <fstream>
#include <string>
#include <stack>

//8(3(1,6(4,7)),10(,14(13,)))       <- ������

struct Element
{
    int value;
    Element* left;
    Element* right;
    Element* parent;
};

Element* treeMaker(int data, Element* root) //������ ������� ��������� ������
{
    Element* q = new Element;
    q->value = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = root;
    return q;
}

void addElement(int data, Element*& root)   //��������� ������� � ������
{
    if (root == nullptr)
    {
        root = treeMaker(data, nullptr);
        return;
    }

    Element* r = root;
    while ((data < r->value && r->left != nullptr) || (data > r->value && r->right != nullptr))
    {
        if (data < r->value)    //���� ������ �������� - ���������� ����� �������
            r = r->left;
        else
            r = r->right;   //���� ������ �������� - ���������� ������ �������
    }
    if (data == r->value)
        return;

    Element* t = treeMaker(data, r);
    if (data < r->value)
        r->left = t;
    else if (data > r->value)
        r->right = t;
}

void addParenthesis(int data, Element*& root, bool isLeft)
{
    Element* r = root;
    Element* t = treeMaker(data, r);
    if (isLeft)
        r->left = t;
    else
        r->right = t;
}

void fillTree(std::string& bracketEntry, int& i, Element*& root)    //����������� ������ ��������� �������
{
    int value = 0;
    while (bracketEntry[i] != '\0') //���� �� ����� ������
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
                addParenthesis(value, root, true);
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
                addParenthesis(value, root, false);
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

int depth(int data, Element* v, int k)  //��� ������� ������� ��������� � ������
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

//����������� ������
void straightPass(Element* root)    //������
{
    if (root == nullptr)
        return;
    std::cout << root->value << " ";
    straightPass(root->left);
    straightPass(root->right);
}

void centralPass(Element* root)     //�����������
{
    if (root == nullptr)
        return;
    centralPass(root->left);
    std::cout << root->value << " ";
    centralPass(root->right);
}

void endPass(Element* root)     //��������
{
    if (root == nullptr)
        return;
    endPass(root->left);
    endPass(root->right);
    std::cout << root->value << " ";

}

//������������� �����
void nonRecursivePass(Element* root)
{
    if (root == nullptr)
        return;
    std::stack<Element*> stack;
    stack.push(root);   //��������� � ���� ������
    while (!stack.empty())
    {
        Element* node = stack.top();
        stack.pop();
        std::cout << node->value << " ";
        if (node->left != nullptr) //��������� ������������� ������ ���������
        {
            stack.push(node->left);
        }
        if (node->right != nullptr) //��������� ������������� ������� ���������
        {
            stack.push(node->right);
        }
    }
}
int main()
{
    Element* root = nullptr;    //������ �������� �����
    std::string bracketEntry;   //��������� ������
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

    std::cout << "\nDirect pass:\n";
    straightPass(root);
    std::cout << "\n\nCentral pass:\n";
    centralPass(root);
    std::cout << "\n\nTerminal pass:\n";
    endPass(root);
    std::cout << "\n\nNon recursive pass:\n\n";
    nonRecursivePass(root);
    clearMemory(root);
    return 0;
}