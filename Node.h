#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <iostream>
#include <memory>
#include <string>

#define stringify(name) #name

class Node
{
public:
    virtual void debug() = 0;

    template <class T>
    std::shared_ptr<T> push()
    {
        std::shared_ptr<T> node = std::make_shared<T>();
        subNodes.push_back(node);
        return node;
    }
    void error(int tc, const Lexer &lex)
    {
        std::cout << "Unexpected value at " << tc + 1 << lex.at(tc + 1).tokenType << std::endl;
    }
    size_t size() { return subNodes.size(); }
    virtual ~Node() = default;

protected:
    std::vector<std::shared_ptr<Node>> subNodes;
};

class Block : public Node
{
public:
    void debug() override
    {
        std::cout << "{\n";
        for (std::shared_ptr<Node> n : subNodes)
        {
            n->debug();
        }
        std::cout << "}\n";
    }
};
class Statement : public Node {
    void debug() override
    {
        for (std::shared_ptr<Node> n : subNodes)
        {
            n->debug();
            std::cout << std::endl;
        }
    }
};
class Expression : public Node
{
public:
    void debug() override
    {
        std::cout << "<";
        for (std::shared_ptr<Node> n : subNodes)
        {
            n->debug();
        }
        std::cout << ">";
    }
};
class BoolOp1 : public Node
{
public:
    void debug() override
    {
        std::cout << "[";
        subNodes.at(0)->debug();
        for (size_t i = 1; i < subNodes.size(); ++i)
        {
            std::cout << " || ";
            subNodes.at(i)->debug();
        }
        std::cout << "]";
    }
};
class BoolOp2 : public Node
{
public:
    void debug() override
    {
        std::cout << "[";
        subNodes.at(0)->debug();
        for (size_t i = 1; i < subNodes.size(); ++i)
        {
            std::cout << " && ";
            subNodes.at(i)->debug();
        }
        std::cout << "]";
    }
};
class EqOp : public Node
{
public:
    void debug() override
    {
        std::cout << "[";
        subNodes.at(0)->debug();
        for (size_t i = 1; i < subNodes.size(); ++i)
        {
            std::cout << " " << stringify(eqType) << " ";
            subNodes.at(i)->debug();
        }
        std::cout << "]";
    }
    TokenType eqType; // true = PLUS, false = MINUS
};
class BinOp1 : public Node
{
public:
    void debug() override
    {
        std::cout << "[";
        subNodes.at(0)->debug();
        for (size_t i = 1; i < subNodes.size(); ++i)
        {
            std::cout << " " << (addition ? "+" : "-") << " ";
            subNodes.at(i)->debug();
        }
        std::cout << "]";
    }
    bool addition; // true = PLUS, false = MINUS
};
class BinOp2 : public Node
{
public:
    void debug() override
    {
        std::cout << "[";
        subNodes.at(0)->debug();
        for (size_t i = 1; i < subNodes.size(); ++i)
        {
            std::cout << " " << (multiplication ? "*" : "/") << " ";
            subNodes.at(i)->debug();
        }
        std::cout << "]";
    }
    bool multiplication; // true = MUL, false = DIV
};
class Atom : public Node
{
public:
    void debug() override
    {
        subNodes.at(0)->debug();
    }
};

class Number : public Node
{
public:
    void debug() override
    {
        std::cout << value;
    }
    double value;
};

class Var : public Node
{
public:
    void debug() override
    {
        std::cout << name;
    }
    std::string name;
};

#endif