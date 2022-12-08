#include <iostream>
#include <fstream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "./Lexer.h"

Lexer::Lexer(std::string filePath)
{
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file.is_open())
    {
        return;
    }
    std::string text = "";
    std::string temp;
    while (getline(file, temp))
    {
        text += temp;
    }
    recLexing(cleanData(text, " \n", replacementChar[0], "\""), tokens);
}

Token Lexer::at(int pos) const {
    return tokens.at(pos);
}

void Lexer::recLexing(std::string data, std::vector<Token> &tokens) {
    // maximum amount of matches for current data and amount of already found matches
    unsigned long max = INT_MAX, matches = 0;
    // go through every possible token
    for(TokenMatch tm : tokenMatch) {        
        // replace and split data for current token
        std::regex match(tm.regex);
        data = std::regex_replace(data, match, replacementChar+"$&"+replacementChar);
        std::vector<std::string> sep;
        boost::trim_if(data, boost::is_any_of(replacementChar));  // prepare split so that no empty fileds are created
        boost::split(sep, data, boost::is_any_of(replacementChar), boost::token_compress_on);
        max = sep.size();
        if(max <= 1) continue;  // no split happened
        // go through all split elements and search for hard match
        // otherwise lex the not matchable part
        for(std::string &e : sep) {
            Token t;
            if (matches == max) return;
            if(hardMatch(e, t)) {
                tokens.push_back(t);
                ++matches;
                continue;
            } else {
                recLexing(e, tokens);
                ++matches;
            }
        }
    }
}

bool Lexer::hardMatch(std::string e, Token &t) {
    for(TokenMatch tm : tokenMatch) {
        std::regex match("^" + tm.regex + "$");
        if(std::regex_match(e, match)) {
            t.tokenType = tm.tokenType;
            t.value = e;
            return true;
        }
    }
    return false;
}

std::string Lexer::cleanData (std::string data, std::string search, char replacement, std::string exceptions)
{
    bool exFalg = false;
    std::size_t usedException = std::string::npos;
    for(char &c : data)
    {
        std::size_t temp = exceptions.find(c);
        if(temp != std::string::npos){
            if(exFalg && temp != usedException){
                continue;
            } else {
                exFalg = !exFalg;
                usedException = temp;
                continue;
            }
        }
        if(!exFalg && search.find(c) != std::string::npos) {
            c = replacement;
        }
    }
    return data;
}
