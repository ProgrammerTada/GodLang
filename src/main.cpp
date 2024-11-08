#include <iostream>
#include <memory>
#include "runtime/irmruntime.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/node.h"

int main(int argc, char *argv[])
{  
    //IRMRuntime i;
    //i.execute(argv[1]);
    Lexer l(argv[1]);
    Parser p(l);
    std::shared_ptr<Block> b = std::make_shared<Block>();
    p.parse(b);
    b->debug();
}