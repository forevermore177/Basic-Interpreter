#include "../include/Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include "../include/Program.hpp"
#include "../include/VarState.hpp"
#include "../include/utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }

// Let
StmtLet::StmtLet(std::string s, std::string name, Expression * exp):Statement(s){
    varName = name;
    expr = exp;
}
StmtLet::~StmtLet(){
    delete expr;
}
void StmtLet::execute(VarState& state, Program& program) const{
    state.setValue(varName, expr->evaluate(state));
}

// Print
StmtPrint::StmtPrint(std::string s, Expression* exp):Statement(s){
    expr = exp;
}
StmtPrint::~StmtPrint(){
    delete expr;
}
void StmtPrint::execute(VarState& state, Program& program) const{
    std::cout << expr->evaluate(state) << '\n';
}

// Input
StmtInput::StmtInput(std::string s, std::string name):Statement(s){
    varName = name;
}
void StmtInput::execute(VarState& state, Program& program) const{
    std::cout << " ? ";
    int input_value;
    std::string input_line;
    while(std::getline(std::cin, input_line)){
        std::istringstream is(input_line);
        char leak;
        if (is >> input_value && !(is.peek() == EOF)){
            state.setValue(varName, input_value);
            break;
        }
        else {
            std::cout << "INVALID NUMBER\n ? ";
        }
    }
}

// Goto
StmtGoto::StmtGoto(std::string s, int linepos):Statement(s){
    targetLine = linepos;
}
void StmtGoto::execute(VarState& state, Program& program) const {
    program.changePC(targetLine);
}

// If
StmtIf::StmtIf(std::string s, Expression* left, char option, Expression* right, int linepos):Statement(s){
    leftExpr = left;
    rightExpr = right;
    op = option;
    targetLine = linepos;
}
StmtIf::~StmtIf(){
    delete leftExpr;
    delete rightExpr;
}
void StmtIf::execute(VarState& state, Program& program) const {
    int lhs = leftExpr->evaluate(state);
    int rhs = rightExpr->evaluate(state);
    bool flag;
    if (op == '=') flag = (lhs == rhs);
    else if (op == '>') flag = (lhs > rhs);
    else flag = (lhs < rhs);
    if (flag){
        program.changePC(targetLine);
    }
}

// Rem
StmtRem::StmtRem(std::string s):Statement(s){}
void StmtRem::execute(VarState& state, Program& program) const {}

// End
StmtEnd::StmtEnd(std::string s):Statement(s){}
void StmtEnd::execute(VarState& state, Program& program) const{
    program.programEnd();
}