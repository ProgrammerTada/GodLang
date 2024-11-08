#pragma once

#include <vector>
#include <map>
#include <string>
#include <functional>


class IRMRuntime {
public:
    void execute(std::string filePath);

private:
    void push(double val);
    void pop();
    void create(unsigned long adr);
    void load(unsigned long adr);
    void erase(unsigned long adr);
    void ass(unsigned long adr);

    void retriveOperants(double &lh, double &rh);

    void add();
    void sub();
    void mul();
    void div();

    void go_to(unsigned long &pc);
    void flag(unsigned long adr, unsigned long pc);

    void jump(long amount, unsigned long &pc);
    void jl(long amount, unsigned long &pc);
    void jle(long amount, unsigned long &pc);
    void jg(long amount, unsigned long &pc);
    void jge(long amount, unsigned long &pc);
    void je(long amount, unsigned long &pc);
    void jne(long amount, unsigned long &pc);

    void jumpf(unsigned long flagAdr, unsigned long &pc);
    void jlf(unsigned long flagAdr, unsigned long &pc);
    void jlef(unsigned long flagAdr, unsigned long &pc);
    void jgf(unsigned long flagAdr, unsigned long &pc);
    void jgef(unsigned long flagAdr, unsigned long &pc);
    void jef(unsigned long flagAdr, unsigned long &pc);
    void jnef(unsigned long flagAdr, unsigned long &pc);

    void post();
    void postc();

    std::map<unsigned long, double> heap;
    std::map<unsigned long, unsigned long> flags;
    std::vector<double> stack;

    enum OpCode {
        PUSH, POP, CREATE, LOAD, ERASE, ASS,
        ADD, SUB, MUL, DIV,
        PC, FLAG,
        JUMP, JL, JLE, JG, JGE, JE, JNE,
        JUMPF, JLF, JLEF, JGF, JGEF, JEF, JNEF,
        POST, POSTC
    };

    std::map<std::string, OpCode> opMap 
        {{"push",PUSH},{"pop",POP},{"create",CREATE},{"load",LOAD},{"erase",ERASE},{"ass",ASS},
        {"add",ADD},{"sub",SUB},{"mul",MUL},{"div",DIV},
        {"pc",PC},{"flag",FLAG},
        {"jump",JUMP},{"jl",JL},{"jle",JLE},{"jg",JG},{"jge",JGE},{"je",JE},{"jne",JNE},
        {"jumpf",JUMPF},{"jlf",JLF},{"jlef",JLEF},{"jgf",JGF},{"jgef",JGEF},{"jef",JEF},{"jnef",JNEF},
        {"post",POST},{"postc",POSTC}};
};

#endif