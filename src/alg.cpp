// Copyright 2023 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include <memory>
#include <utility>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {  //
  build(elements, {});  //
}

PMTree::PMTree(const std::vector<char>& elements,  //
               const std::vector<char>& path) {
  build(elements, path);  //
}

void PMTree::build(const std::vector<char>& elements,  //
                   const std::vector<char>& path) {
  if (elements.empty()) {  //
    return;  //
  }
  for (char ch : elements) {  //
    std::vector<char> new_path = path;  //
    new_path.push_back(ch);  //

    std::vector<char> rest;  //
    for (char c : elements) {  //
      if (c != ch) {  //
        rest.push_back(c);  //
      }  //
    }  //

    auto child = std::make_shared<PMTree>();  //
    child->value = ch;  //
    child->build(rest, new_path);  //
    children.push_back(child);  //
  }  //
}  //

void PMTree::collectPermutations(std::vector<std::vector<char>>& perms,  //
                                 std::vector<char>& current) {
  current.push_back(value);  //
  if (children.empty()) {  //
    perms.push_back(current);  //
  } else {  //
    for (auto& child : children) {  //
      child->collectPermutations(perms, current);  //
    }  //
  }  //
  current.pop_back();  //
}  //

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {  //
  std::vector<std::vector<char>> perms;  //
  for (auto& child : tree.children) {  //
    std::vector<char> path;  //
    child->collectPermutations(perms, path);  //
  }  //
  return perms;  //
}  //

std::vector<char> PMTree::getPerm1(int& counter, int target) {  //
  std::vector<char> result;  //
  if (children.empty()) {  //
    if (++counter == target) {  //
      return {value};  //
    }  //
    return {};  //
  }  //
  for (auto& child : children) {  //
    std::vector<char> sub = child->getPerm1(counter, target);  //
    if (!sub.empty()) {  //
      result.push_back(value);  //
      result.insert(result.end(), sub.begin(), sub.end());  //
      return result;  //
    }  //
  }  //
  return {};  //
}  //

std::vector<char> getPerm1(PMTree& tree, int num) {  //
  int counter = 0;  //
  for (auto& child : tree.children) {  //
    std::vector<char> result = child->getPerm1(counter, num);  //
    if (!result.empty()) {  //
      return result;  //
    }  //
  }  //
  return {};  //
}  //

int PMTree::factorial(int n) const {  //
  return (n <= 1) ? 1 : n * factorial(n - 1);  //
}  //

std::vector<char> PMTree::getPerm2(int num, int& factorialLevel) const {  //
  std::vector<char> result;  //
  int n = children.size();  //
  if (n == 0) {  //
    result.push_back(value);  //
    return result;  //
  }  //

  int index = (num - 1) / factorial(factorialLevel - 1);  //
  num = (num - 1) % factorial(factorialLevel - 1) + 1;  //

  auto child = children[index];  //
  result.push_back(child->value);  //
  std::vector<char> suffix = child->getPerm2(num, --factorialLevel);  //
  result.insert(result.end(), suffix.begin(), suffix.end());  //
  return result;  //
}  //

std::vector<char> getPerm2(PMTree& tree, int num) {  //
  int level = tree.children.size();  //
  if (num < 1 || num > tree.factorial(level)) {  //
    return {};  //
  }  //

  auto child = tree.children[(num - 1) / tree.factorial(level - 1)];  //
  std::vector<char> result;  //
  result.push_back(child->value);  //
  int sub_num = (num - 1) % tree.factorial(level - 1) + 1;  //
  int next_level = level - 1;  //
  std::vector<char> suffix = child->getPerm2(sub_num, next_level);  //
  result.insert(result.end(), suffix.begin(), suffix.end());  //
  return result;  //
}  //
