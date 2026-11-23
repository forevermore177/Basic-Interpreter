#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default; // defaul:生成默认析构函数

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;// correspond to "originLine"
};

class StmtLet: public Statement{
private:
  std::string varName;
  Expression* expr;
public:
  explicit StmtLet(std::string s, std::string name, Expression * exp);
  ~StmtLet() override;
  void execute(VarState& state, Program& program) const override;
};

class StmtPrint: public Statement{
private:
  Expression* expr;
public:
  explicit StmtPrint(std::string s, Expression* exp);
  ~StmtPrint() override; 
  void execute(VarState& state, Program& program) const override;
};

class StmtInput: public Statement{
private:
  std::string varName;
public:
  explicit StmtInput(std::string s, std::string name);
  ~StmtInput() override = default;
  void execute(VarState& state, Program& program) const override;
};

class StmtGoto: public Statement{
private:
  int targetLine;
public:
  explicit StmtGoto(std::string s, int linepos);
  ~StmtGoto() override = default;
  void execute(VarState& state, Program& program) const override;
};

class StmtIf: public Statement{
private:
  Expression* leftExpr;
  Expression* rightExpr;
  char op;
  int targetLine;
public:
  explicit StmtIf(std::string s, Expression* left, char option, Expression* right, int linepos);
  ~StmtIf() override;
  void execute(VarState& state, Program& program) const override;
};

class StmtRem: public Statement{
public:
  explicit StmtRem(std::string s);
  ~StmtRem() override = default;
  void execute(VarState& state, Program& program) const override;
};

class StmtEnd: public Statement{
public:
  explicit StmtEnd(std::string s);
  ~StmtEnd() override = default;
  void execute(VarState& state, Program& program) const override;
};