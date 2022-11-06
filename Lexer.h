#ifndef LEXER_H_
#define LEXER_H_

#include <string>
#include <vector>

enum TokenType {
    SEMICOLON,
    STRING,
    VAR,
    DOUBLE,
    INTEGER,
    DEQUAL,
    NEQUAL,
    LESS,
    LESSEQUAL,
    GREATER,
    GREATEREQUAL,
    PULS,
    MINUS,
    MUL,
    DIV,
    AND,
    OR,
    EQUAL,
    INTTYPE,
    DOUBLETYPE,
    STRINGTYPE,
    WHILE,
    FOR,
    LBRACE,
    RBRACE,
    LCURL,
    RCURL,
    FUNC,
    RETURN
};

struct TokenMatch {
    std::string regex;
    TokenType tokenType;
};

struct Token {
    TokenType tokenType;
    std::string value;
};

class Lexer {
public:
    Lexer (std::string filePath);
    Token next();
private:
    std::vector<std::string> vectorize(std::string data);
    void tokenize(std::vector<std::string> data);
    std::vector<Token> tokens;
    unsigned long tokenCounter = 0;
    const std::vector<TokenMatch> tokenMatch{
        {";",SEMICOLON},
        {"^\\d+$",INTEGER},
        {"==",DEQUAL},
        {"!=",NEQUAL},
        {"<",LESS},
        {"<=",LESSEQUAL},
        {">",GREATER},
        {">=",GREATEREQUAL},
        {"\\+",PULS},
        {"-",MINUS},
        {"\\*",MUL},
        {"/",DIV},
        {"&&",AND},
        {"\\|\\|",OR},
        {"=",EQUAL},
        {"int",INTTYPE},
        {"double",DOUBLETYPE},
        {"string",STRINGTYPE},
        {"while",WHILE},
        {"for",FOR},
        {"\\(",LBRACE},
        {"\\)",RBRACE},
        {"\\{",LCURL},
        {"\\}",RCURL},
        {"func",FUNC},
        {"return",RETURN},
        {"\".*\"",STRING},
        {"[a-zA-z_][a-zA-Z0-9_]*",VAR},
        {"[+-]?([0-9]*)[.][0-9]+",DOUBLE}
    };
};
#endif