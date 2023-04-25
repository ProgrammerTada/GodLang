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
    // if anything between this
    DEQUAL,
    NEQUAL,
    LESS,
    LESSEQUAL,
    GREATER,
    GREATEREQUAL,
    // and this is added the parser will break it doesnt matter where they are
    // but they have to be together
    PLUS,
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
    IF,
    ELSE,
    LBRACE,
    RBRACE,
    LCURL,
    RCURL,
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
    Token at(int pos) const;
    int size() const {return tokens.size();}
private:
    /// @brief Recursevly scan the given data for tokens and appending them to the list of tokens in order
    /// @param data the string thats to be lexed
    /// @param tokens the list of tokens which are contained in the data
    void recLexing(std::string data, std::vector<Token> &tokens);
    
    /// @brief This will do a "hard match" (^regex$) for all possible tokens and fill out the given token accordingly
    /// @param e the string which could contain a token
    /// @param t the return value of the assitioated token
    /// @return returns if there was a match e.g. the token will have content
    bool hardMatch(std::string e, Token &t);

    /// @brief This will replace all chars from the data wich are defined in the search by the replacement char
    ///         with the exception of areas in between two chars defined by the exceptions
    /// @param data the string that needs cleaning
    /// @param search collection of elements that should be replaced
    /// @param replacement the replacement for search
    /// @param exceptions collection of chars in between there should be no replacement
    /// @return returns the cleaned string
    std::string cleanData (std::string data, std::string search, char replacement, std::string exceptions);
    std::vector<Token> tokens;
    const std::string replacementChar = "\a";
    const std::vector<TokenMatch> tokenMatch{
        {";",SEMICOLON},
        {"^\\d+$",INTEGER},
        {"==",DEQUAL},
        {"!=",NEQUAL},
        {"<",LESS},
        {"<=",LESSEQUAL},
        {">",GREATER},
        {">=",GREATEREQUAL},
        {"\\+",PLUS},
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
        {"if", IF},
        {"else", ELSE},
        {"\\(",LBRACE},
        {"\\)",RBRACE},
        {"\\{",LCURL},
        {"\\}",RCURL},
        {"return",RETURN},
        {"\".*\"",STRING},
        {"[a-zA-z_][a-zA-Z0-9_]*",VAR},
        {"[+-]?([0-9]*)[.][0-9]+",DOUBLE}
    };
};
#endif