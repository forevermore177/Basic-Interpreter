#include "../include/VarState.hpp"

#include <algorithm>
#include <cstddef>
#include <memory>

#include "../include/utils/Error.hpp"

VarState::VarState(){
  global_scope = std::make_shared<scope>();
  global_scope->parent = nullptr;
  global_scope->values = {};
  cur_scope = global_scope;
}
void VarState::enter(){
  scope newscope;
  newscope.values = {};
  newscope.parent = cur_scope;
  cur_scope = std::make_shared<scope>(newscope);
}

void VarState::leave(){
  if (cur_scope == global_scope) 
    throw BasicError("SCOPE UNDERFLOW");
  cur_scope = cur_scope->parent;
}

void VarState::setValue(const std::string& name, int value) {
  // 只修改当前作用域的变量
  cur_scope->values[name] = value;
}

int VarState::getValue(const std::string& name) const {
  std::shared_ptr<scope> curptr = cur_scope;
  while (curptr != nullptr){
    auto it = curptr->values.find(name);
    if (it != curptr->values.end()){
      return it->second;
    }
    curptr = curptr->parent;
  }
  throw BasicError("VARIABLE NOT DEFINED");
}

void VarState::clear() { 
  cur_scope = global_scope;
  cur_scope->values.clear();
}
