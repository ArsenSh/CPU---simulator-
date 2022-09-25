#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <map>
#include <cmath>

std::vector <std::string> keywords {"r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "mov", "add", "sub", "mul", "div", "jmp", "jl", "jg", "je", "cmp"};

int line = 1;

class CPU
{
private:
    std::map <std::string, int> mmap;
    
public:
    CPU& do_assembly(std::ifstream&);
    int  checking_keyword(std::string&);
    void do_move(std::ifstream&);
    void do_add(std::ifstream&);
    void do_sub(std::ifstream&);
    void do_mul(std::ifstream&);
    void do_div(std::ifstream&);
    void do_jmp(std::ifstream&);
    int  do_cmp(std::ifstream&);
    void do_jl(std::ifstream&);
    void do_jg(std::ifstream&);
    void do_je(std::ifstream&);
    bool is_digit(const char& ch);
    bool is_label(std::string&);
    void printing();
};

#include "instruction.hpp"
#endif /* HEADER_H */
