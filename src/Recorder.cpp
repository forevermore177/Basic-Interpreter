#include "../include/Recorder.hpp"
#include <iostream>

Recorder::Recorder(){
    commands = {};
}

Recorder::~Recorder(){
    for (auto it = commands.begin(); it != commands.end(); it++){
        delete it->second;
    }
}

void Recorder::add(int line, Statement* stmt){
    auto it = commands.find(line);
    if (it != commands.end()){
        delete it->second;
        it->second = stmt;
    }
    else{
        commands.insert({line, stmt});
    }
}

void Recorder::remove(int line){
    if (commands.count(line) > 0){
       delete commands[line];
       commands.erase(line);
    }
}

const Statement* Recorder:: get(int line) const noexcept{
    auto it = commands.find(line);
    if (it == commands.end()){
        return nullptr;
    }
    else{
        return it->second;
    }
}

bool Recorder::hasLine(int line) const noexcept{
    auto it = commands.find(line);
    if (it == commands.end()){
        return false;
    }
    return true;
}

void Recorder::clear() noexcept{
    for (auto it = commands.begin(); it != commands.end(); it++){
        delete it->second;
    }
    commands.clear();
}

void Recorder::printLines() const{
    for (auto it = commands.begin(); it != commands.end(); it++){
        std::cout << it->second->text() << '\n';
        // note that "originLine" has already contained the line number!
    }
}

int Recorder::nextLine(int line) const noexcept{
    auto it = commands.upper_bound(line);
    if (it == commands.end()){
        return -1;
    }
    else{
        return it->first;
    }
}