#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "irmruntime.h"

void IRMRuntime::execute(std::string filePath)
{
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file.is_open())
    {
        return;
    }
    // std::string data(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    std::vector<std::string> lines;
    std::string temp;
    while (getline(file, temp))
    {
        lines.push_back(temp);
    }
    // boost::split(data, lines, boost::is_any_of("\n"));
    for (unsigned long pc = 0; pc < lines.size(); pc++)
    {
        std::vector<std::string> args;
        boost::split(args, lines[pc], boost::is_any_of(" "));
        switch (opMap[args[0]])
        {
//-----------------------------------------------------------Data
        case PUSH:
            push(stod(args[1]));
            break;
        case POP:
            pop();
            break;
        case CREATE:
            create(std::stoul(args[1]));
            break;
        case LOAD:
            load(std::stoul(args[1]));
            break;
        case ERASE:
            erase(std::stoul(args[1]));
            break;
        case ASS:
            ass(std::stoul(args[1]));
            break;
//-----------------------------------------------------------Maths
        case ADD:
            add();
            break;
        case SUB:
            sub();
            break;
        case MUL:
            mul();
            break;
        case DIV:
            div();
            break;
//-----------------------------------------------------------Misc
        case PC:
            go_to(pc);
            break;
        case FLAG:
            flag(std::stoul(args[1]), pc);
            break;
//-----------------------------------------------------------Jumps
        case JL:
            jl(std::stol(args[1]), pc);
            break;
        case JLE:
            jle(std::stol(args[1]), pc);
            break;
        case JG:
            jg(std::stol(args[1]), pc);
            break;
        case JGE:
            jge(std::stol(args[1]), pc);
            break;
        case JE:
            je(std::stol(args[1]), pc);
            break;
        case JNE:
            jne(std::stol(args[1]), pc);
            break;
        case JLF:
            jlf(std::stol(args[1]), pc);
            break;
//-----------------------------------------------------------Flagjumps
        case JLEF:
            jlef(std::stoul(args[1]), pc);
            break;
        case JGF:
            jgf(std::stoul(args[1]), pc);
            break;
        case JGEF:
            jgef(std::stoul(args[1]), pc);
            break;
        case JEF:
            jef(std::stoul(args[1]), pc);
            break;
        case JNEF:
            jnef(std::stoul(args[1]), pc);
            break;
//-----------------------------------------------------------Output
        case POST:
            post();
            break;
        case POSTC:
            postc();
            break;
//-----------------------------------------------------------Error
        default:
            std::cout << "Byte code error. Unknown symbol was found in line " << pc + 1 << std::endl;
            return;
        }
    }
}

void IRMRuntime::push(double val)
{
    stack.push_back(val);
}
void IRMRuntime::pop()
{
    stack.pop_back();
}
void IRMRuntime::create(unsigned long adr)
{
    heap[adr] = 0;
}
void IRMRuntime::load(unsigned long adr)
{
    stack.push_back(heap[adr]);
}
void IRMRuntime::erase(unsigned long adr)
{
    heap.erase(adr);
}
void IRMRuntime::ass(unsigned long adr)
{
    heap[adr] = stack.back();
}

void IRMRuntime::retriveOperants(double &lh, double &rh)
{
    rh = stack.back();
    stack.pop_back();
    lh = stack.back();
    stack.pop_back();
}

void IRMRuntime::add()
{
    double lh, rh;
    retriveOperants(lh, rh);
    stack.push_back(lh + rh);
}
void IRMRuntime::sub()
{
    double lh, rh;
    retriveOperants(lh, rh);
    stack.push_back(lh - rh);
}
void IRMRuntime::mul()
{
    double lh, rh;
    retriveOperants(lh, rh);
    stack.push_back(lh * rh);
}
void IRMRuntime::div()
{
    double lh, rh;
    retriveOperants(lh, rh);
    stack.push_back(lh / rh);
}

void IRMRuntime::go_to(unsigned long &pc) {
    pc = stack.back();
}

void IRMRuntime::flag(unsigned long adr, unsigned long pc)
{
    flags[adr] = pc;
}

void IRMRuntime::jump(long amount, unsigned long &pc) {
    pc += amount;
}
void IRMRuntime::jl(long amount, unsigned long &pc)
{
    pc = stack.back() < stack.end()[-2] ? pc + amount : pc;
}
void IRMRuntime::jle(long amount, unsigned long &pc)
{
    pc = stack.back() <= stack.end()[-2] ? pc + amount : pc;
}
void IRMRuntime::jg(long amount, unsigned long &pc)
{
    pc = stack.back() > stack.end()[-2] ? pc + amount : pc;
}
void IRMRuntime::jge(long amount, unsigned long &pc)
{
    pc = stack.back() >= stack.end()[-2] ? pc + amount : pc;
}
void IRMRuntime::je(long amount, unsigned long &pc)
{
    pc = stack.end()[-2] == stack.back() ? pc + amount : pc;
}
void IRMRuntime::jne(long amount, unsigned long &pc)
{
    pc = stack.end()[-2] != stack.back() ? pc + amount : pc;
}

void IRMRuntime::jumpf(unsigned long flagAdr, unsigned long &pc){
    pc = flags[flagAdr];
}
void IRMRuntime::jlf(unsigned long flagAdr, unsigned long &pc)
{
    pc = stack.back() < stack.end()[-2] ? flags[flagAdr] : pc;
}
void IRMRuntime::jlef(unsigned long flagAdr, unsigned long &pc)
{
    pc = stack.back() <= stack.end()[-2] ? flags[flagAdr] : pc;
}
void IRMRuntime::jgf(unsigned long flagAdr, unsigned long &pc)
{
    pc = stack.back() > stack.end()[-2] ? flags[flagAdr] : pc;
}
void IRMRuntime::jgef(unsigned long flagAdr, unsigned long &pc)
{
    pc = stack.back() >= stack.end()[-2] ? flags[flagAdr] : pc;
}
void IRMRuntime::jef(unsigned long flagAdr, unsigned long &pc)
{
    pc = stack.end()[-2] == stack.back() ? flags[flagAdr] : pc;
}
void IRMRuntime::jnef(unsigned long flagAdr, unsigned long &pc)
{
    pc = stack.end()[-2] != stack.back() ? flags[flagAdr] : pc;
}

void IRMRuntime::post()
{
    std::cout << stack.back();
}
void IRMRuntime::postc()
{
    std::wcout << wchar_t(stack.back());
}