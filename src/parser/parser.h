#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <memory>
#include "lexer.h"
#include "node.h"

class Parser {
public:
    Parser(Lexer& lex) : lex(lex){}
    void parse(std::shared_ptr<Node> n);
private:
    // every node generating function is expecting that tc is
    // the value last consumed by the caller
    void block(std::shared_ptr<Node> n);
    void statement(std::shared_ptr<Node> n);
    void declaration(std::shared_ptr<Node> n);
    void assignment(std::shared_ptr<Node> n);
    void expression(std::shared_ptr<Node> n);
    void boolop1(std::shared_ptr<Node> n);
    void boolop2(std::shared_ptr<Node> n);
    void eqop(std::shared_ptr<Node> n);
    void binop1(std::shared_ptr<Node> n);
    void binop2(std::shared_ptr<Node> n);
    void atom(std::shared_ptr<Node> n);
    void number(std::shared_ptr<Node> n);
    void var(std::shared_ptr<Node> n);
    void string(std::shared_ptr<Node> n);
    Lexer& lex;
    int tc = -1;
};

#endif