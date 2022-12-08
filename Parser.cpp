#include "./Parser.h"
#include <iostream>
#include <memory>

void Parser::parse(std::shared_ptr<Node> n)
{
    block(n);
}

void Parser::block(std::shared_ptr<Node> n)
{
    std::shared_ptr<Block> res;
    res = n->push<Block>();
    while (tc + 1 < lex.size() && lex.at(tc + 1).tokenType != TokenType::RCURL)
    {
        if (lex.at(tc + 1).tokenType == TokenType::LCURL)
        {
            ++tc; // consume lrcurl
            block(res);
        }
        else
        {
            statement(res);
        }
    }
    ++tc; // consume rcurl
}

void Parser::statement(std::shared_ptr<Node> n)
{
    std::shared_ptr<Statement> res;
    res = n->push<Statement>();
    if (lex.at(tc + 1).tokenType == TokenType::INTTYPE ||
        lex.at(tc + 1).tokenType == TokenType::STRINGTYPE ||
        lex.at(tc + 1).tokenType == TokenType::DOUBLETYPE)
    {
        declaration(res);
    }
    else if (lex.at(tc + 1).tokenType == TokenType::VAR)
    {
        assignment(res);
    }
    else
    {
        expression(res);
    }
    ++tc; // consume semicolon
}

void Parser::declaration(std::shared_ptr<Node> n){
    std::shared_ptr<Declaration> res;
    res = n->push<Declaration>();
    ++tc;  // consume vartype
    res->varType = lex.at(tc).tokenType;
    res->varName = lex.at(tc + 1).value;
    if (lex.at(tc + 2).tokenType == TokenType::EQUAL) {
        assignment(res);
    }
    else {
        ++tc;  // consume var    
    }
}
void Parser::assignment(std::shared_ptr<Node> n){
    std::shared_ptr<Assignment> res;
    res = n->push<Assignment>();
    ++tc;  // consume var
    res->varName = lex.at(tc).value;
    ++tc;  // consume equal
    if (lex.at(tc + 1).tokenType == TokenType::STRING)
        string(res);
    else
        expression(res);
}

void Parser::expression(std::shared_ptr<Node> n)
{
    std::shared_ptr<Expression> res;
    res = n->push<Expression>();
    boolop1(res);
}

void Parser::boolop1(std::shared_ptr<Node> n)
{
    std::shared_ptr<BoolOp1> res;
    res = n->push<BoolOp1>();
    boolop2(res);
    while (tc + 1 < lex.size() && lex.at(tc + 1).tokenType == TokenType::OR)
    {
        ++tc;
        boolop2(res);
    }
}

void Parser::boolop2(std::shared_ptr<Node> n)
{
    std::shared_ptr<BoolOp2> res;
    res = n->push<BoolOp2>();
    eqop(res);
    while (tc + 1 < lex.size() && lex.at(tc + 1).tokenType == TokenType::AND)
    {
        ++tc;
        eqop(res);
    }
}

void Parser::eqop(std::shared_ptr<Node> n)
{
    std::shared_ptr<EqOp> res;
    res = n->push<EqOp>();
    binop1(res);
    while (tc + 1 < lex.size() && lex.at(tc + 1).tokenType >= TokenType::DEQUAL && lex.at(tc + 1).tokenType <= TokenType::GREATEREQUAL)
    {
        ++tc;
        res->eqType = lex.at(tc).tokenType;
        binop1(res);
    }
}

void Parser::binop1(std::shared_ptr<Node> n)
{
    std::shared_ptr<BinOp1> res;
    res = n->push<BinOp1>();
    binop2(res);
    while (tc + 1 < lex.size() &&
           (lex.at(tc + 1).tokenType == TokenType::PLUS ||
            lex.at(tc + 1).tokenType == TokenType::MINUS))
    {
        ++tc;
        res->addition = lex.at(tc).tokenType == TokenType::PLUS;
        binop2(res);
    }
}

void Parser::binop2(std::shared_ptr<Node> n)
{
    std::shared_ptr<BinOp2> res;
    res = n->push<BinOp2>();
    atom(res);
    while (tc + 1 < lex.size() &&
           (lex.at(tc + 1).tokenType == TokenType::MUL ||
            lex.at(tc + 1).tokenType == TokenType::DIV))
    {
        ++tc;
        res->multiplication = lex.at(tc).tokenType == TokenType::MUL;
        atom(res);
    }
}

void Parser::atom(std::shared_ptr<Node> n)
{
    std::shared_ptr<Atom> res;
    res = n->push<Atom>();
    if (lex.at(tc + 1).tokenType == TokenType::LBRACE)
    {
        ++tc;
        binop1(res);
        ++tc; // consume rbrace
    }
    else if (lex.at(tc + 1).tokenType == TokenType::VAR)
    {
        var(res);
    }
    else
    {
        number(res);
    }
}

void Parser::number(std::shared_ptr<Node> n)
{
    std::shared_ptr<Number> res;
    res = n->push<Number>();
    if (lex.at(tc + 1).tokenType != TokenType::DOUBLE &&
        lex.at(tc + 1).tokenType != TokenType::INTEGER)
    {
        res->error(tc, lex);
    }
    ++tc;
    res->value = stod(lex.at(tc).value);
}

void Parser::var(std::shared_ptr<Node> n)
{
    std::shared_ptr<Var> res;
    res = n->push<Var>();
    if (lex.at(tc + 1).tokenType != TokenType::VAR)
    {
        res->error(tc, lex);
    }
    ++tc;
    res->name = lex.at(tc).value;
}
