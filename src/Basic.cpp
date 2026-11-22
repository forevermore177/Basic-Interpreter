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
      const Token* firstToken = tokens.peek();
      switch (firstToken->type) {
        case TokenType::RUN:
          tokens.get();
          if (!tokens.empty()) {
            throw BasicError("SYNTAX ERROR");
          }
          program.run();
          continue;
        case TokenType::LIST:
          tokens.get();
          if (!tokens.empty()) {
            throw BasicError("SYNTAX ERROR");
          }
          program.list();
          continue;
        case TokenType::CLEAR:
          tokens.get();
          if (!tokens.empty()) {
            throw BasicError("SYNTAX ERROR");
          }
          program.clear();
          continue;
        case TokenType::QUIT:
          tokens.get();
          if (!tokens.empty()) {
            throw BasicError("SYNTAX ERROR");
          }
          return 0;
        case TokenType::HELP:
          tokens.get();
          if (!tokens.empty()) {
            throw BasicError("SYNTAX ERROR");
          }
          std::cout << "The helping message is left to be done.Stay tuned.\n";
          continue;
        default:
          break;
      }
      ParsedLine parsed_ans = parser.parseLine(tokens, line);
      if (parsed_ans.getLine().has_value()){
        int line_number = parsed_ans.getLine().value();
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