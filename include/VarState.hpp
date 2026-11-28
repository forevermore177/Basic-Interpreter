#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct scope{
  std::unordered_map<std::string, int> values;
  std::shared_ptr<scope> parent;
};
class VarState {
 public:
  VarState();
  void enter();
  void leave();
  void setValue(const std::string& name, int value);
  int getValue(const std::string& name) const;
  void clear();

 private:
  //std::unordered_map<std::string, int> values_;
  std::shared_ptr<scope> cur_scope;
  std::shared_ptr<scope> global_scope;
};
