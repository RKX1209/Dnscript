#include <string>
#include <boost/format.hpp>
#include <vector>
#include <map>
#include "Token.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

const int Parser::FAILED = -1;

Token Parser::LT(int i) {
  sync(i);
  return lookahead[p + i - 1];
}

int Parser::LA(int i) {
  return LT(i).type;
}

void Parser::match(int x) {
  if(LA(1) == x) consume();
  else {
    std::string error = (boost::format("expecting %c; ") % input.get_token_name(x) ).str();
    throw error;
  }
}

void Parser::sync(int i) {
  if(p + i - 1 > (lookahead.size() - 1)) {
    int n = (p + i - 1) - (lookahead.size() - 1);
    fill(n);
  }
}

void Parser::fill(int n) {
  for(int i = 0; i < n; i++) { lookahead.push_back(input.nextToken()); }
}

void Parser::consume() {
  p++;
  if(p == lookahead.size() && !isSpeculating() ) {
    p = 0;
    lookahead.clear();
  }
  sync(1);
}

int Parser::mark() {
  markers.push_back(p);
  return p;
}

void Parser::release() {
  int marker = markers[markers.size() - 1];
  markers.pop_back();
  seek(marker);
}

bool Parser::alreadyParsedRule(std::map<int,int> memo) {
  if(memo.find(index()) == memo.end()) return false;
  int memoI = memo[index()];
  if(memoI == FAILED) throw "Previous parse has already failed";
  seek(memoI);
  return true;
}

void Parser::memorize(std::map<int,int> memo, int startTokenIndex, bool failed) {

}

int Parser::index() {
  return p;
}

void Parser::seek(int index) {
  p = index;
}

bool Parser::isSpeculating() {
  return markers.size() > 0;
}
