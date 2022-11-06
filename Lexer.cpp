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
    tokenize(vectorize(text));
    // Debug
    for (Token t : tokens) {
        std::cout << "Type " << t.tokenType << " Val " << t.value << "\n";
    }
}

std::vector<std::string> Lexer::vectorize(std::string data){
    std::cout << data << std::endl;
    for(TokenMatch tm : tokenMatch) {
        std::regex match(tm.regex);
        data = std::regex_replace(data, match, " $& ");
        std::cout << tm.regex << "---------------------------" << std::endl << data << std::endl;
    }
    // Debug
    std::cout << data << std::endl;
    std::vector<std::string> sep;
    boost::split(sep, data, boost::is_any_of(" "));
    // Debug
    /*for (std::string s : sep){
        std::cout << s << std::endl;
    }*/
    return sep;
}
void Lexer::tokenize(std::vector<std::string> data){
    for(std::string s : data) {
        for(TokenMatch tm : tokenMatch) {
            std::regex match(tm.regex);
            if(std::regex_match(s, match)) {
                tokens.push_back({tm.tokenType, s});
                break;
            }
        }
    }
}
