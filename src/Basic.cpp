#include <iostream>
#include <memory>
#include <string>

#include "../include/Lexer.hpp"
#include "../include/Parser.hpp"
#include "../include/Program.hpp"
#include "../include/Token.hpp"
#include "../include/utils/Error.hpp"

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {
      TokenStream tokens = lexer.tokenize(line);
      if (tokens.empty()) {
        throw BasicError("SYNTAX ERROR");
        continue;
      }
      const Token* firstToken = tokens.peek();
      switch (firstToken->type) {
        case TokenType::RUN:
          program.run();
          continue;
        case TokenType::LIST:
          program.list();
          continue;
        case TokenType::CLEAR:
          program.clear();
          continue;
        case TokenType::QUIT:
          return 0;
        case TokenType::HELP:
          std::cout << "支持的命令:\n"
                    << "  RUN - 开始执行程序\n"
                    << "  LIST - 列出当前所有的程序行\n"
                    << "  CLEAR - 清除当前所有的程序行\n"
                    << "  QUIT - 退出解释器\n"
                    << "  HELP - 打印帮助信息\n"
                    << "\n"
                    << "程序指令:\n"
                    << "  [行号] REM <注释> - 注释行\n"
                    << "  [行号] LET <变量> = <表达式> - 赋值语句\n"
                    << "  [行号] PRINT <表达式> - 打印表达式值\n"
                    << "  [行号] INPUT <变量> - 输入变量值\n"
                    << "  [行号] END - 结束程序\n"
                    << "  [行号] GOTO <行号> - 跳转到指定行\n"
                    << "  [行号] IF <表达式1> <操作符> <表达式2> THEN <行号> - 条件跳转\n"
                    << "\n"
                    << "立即执行指令 (不带行号):\n"
                    << "  LET <变量> = <表达式>\n"
                    << "  PRINT <表达式>\n"
                    << "  INPUT <变量>\n";
          continue;
        default:
          break;
      }
      ParsedLine parsed_ans = parser.parseLine(tokens, line);
      if (parsed_ans.getLine().has_value()){
        int line_number = parsed_ans.getLine().value();
        if (line_number == 0){ // 疑似非法
          throw BasicError("LINE NUMBER ERROR");
          continue;
        }
        if (parsed_ans.getStatement() == nullptr) { // 删除
          program.removeStmt(line_number);
        }
        else{
          program.addStmt(line_number, parsed_ans.fetchStatement());
        }
      }
      else{
        program.execute(parsed_ans.getStatement());
      }
      
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}