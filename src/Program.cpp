#include "../include/Program.hpp"
#include "../include/utils/Error.hpp"

Program::Program(){
    programCounter_ = -1;
    programEnd_ = false;
}

void Program::resetAfterRun() noexcept{
    programCounter_ = -1;
    programEnd_ = false;
}

void Program::addStmt(int line, Statement* stmt){
    recorder_.add(line, stmt);
}

void Program::removeStmt(int line){
    recorder_.remove(line);
}

void Program::run(){
    programEnd_ = false;
    programCounter_ = recorder_.nextLine(-1);
    try{
        int preCounter = programCounter_;
        while (!programEnd_ && recorder_.hasLine(programCounter_)){
            recorder_.get(programCounter_)->execute(vars_, *this);
            if (preCounter == programCounter_){
                programCounter_ = recorder_.nextLine(programCounter_);
            }
            preCounter = programCounter_;
        }
    } catch (const BasicError& e){
        resetAfterRun();
        throw;
    }
    resetAfterRun();
}

void Program::list() const{
    recorder_.printLines();
}

void Program::clear(){
    recorder_.clear();
    vars_.clear();
    resetAfterRun();
}

void Program::execute(Statement* stmt){
    stmt->execute(vars_, *this);
}

int Program::getPC() const noexcept{
    return programCounter_;
}

void Program::changePC(int line){
    programCounter_ = line;
}

void Program::programEnd(){
    programEnd_ = true;
}
