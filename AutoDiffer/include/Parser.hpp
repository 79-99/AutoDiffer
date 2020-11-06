/**
 * @file Parser.h
 */

#ifndef PARSER_H
#define PARSER_H

/* header files */
#include "ADNode.hpp"
#include "ADValue.hpp"

/* system header files */
#ifndef DOXYGEN_IGNORE
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#endif

template <class T>
class Parser {
  private:
    std::string equation_;
    std::unordered_map<std::string, ADValue<T>> values_;
    int left_cursor_, right_cursor_;
    int v_idx_ = 0;

    bool SetCursor();
    ADValue<T> GetValue(const std::string& key);

    std::set<char> operations = { '+', '^' }; 

  public:
    Parser(std::string equation) : equation_(equation) {}
    void Init(std::vector<std::pair<std::string, ADValue<T>>> seed_values);
    void Next();
    ADValue<T> Run();
};


/* Implementation */
template <class T>
ADValue<T> Parser<T>::Run() {
    while (equation_.find('(') != std::string::npos) {
        Next();
    }
    std::string out = 'x' + std::to_string(--v_idx_);
    return values_[out];
}


template <class T>
void Parser<T>::Init(std::vector<std::pair<std::string, ADValue<T>>> seed_values) {
    // Setting seed values in hash table.
    for (auto& seed_val : seed_values) {
        values_[seed_val.first] = seed_val.second;
    }
    
    if (!SetCursor()) {
        return;
    }
}

template <class T>
void Parser<T>::Next() {
    std::string sub_str = equation_.substr(
        left_cursor_+1, right_cursor_ - (left_cursor_+1));
    std::cout << equation_ << ' ' << sub_str << std::endl;
    int op_index = -1;
    Operation op;
    for (int i = 0; i < sub_str.length(); ++i) {
        std::set<char>::iterator it = operations.find(sub_str[i]);
        if (it != operations.end()) {
            char op_char = *it;
            if (op_char == '+') {
                op = Operation::addition;
            } else if (op_char == '^') {
                op = Operation::power;
            }
            op_index = i;
            break;
        }
    }
    if (op_index == -1) {/* Throw error in here.*/}

    std::string LHS = sub_str.substr(0,op_index);
    std::string RHS = sub_str.substr(op_index+1);
    ADValue<T> left_val = GetValue(LHS);
    ADValue<T> right_val = GetValue(RHS);
    
    ADNode<T> cur_node(left_val, right_val, op);
    ADValue<T> cur_value = cur_node.Evaluate();
    std::string new_val_name = 'x' + std::to_string(v_idx_++);
    values_[new_val_name] = cur_value;
    std::string new_str = equation_.replace(
        left_cursor_, right_cursor_ - left_cursor_ + 1, new_val_name);
    equation_ = new_str;
    if (!SetCursor()) {
        return;
    }
}

template <class T>
ADValue<T> Parser<T>::GetValue(const std::string& key) {
    auto it = values_.find(key);
    if (it != values_.end()) {
        return values_[key];
    }
    std::istringstream ss(key);
    T num;
    ss >> num;
    return ADValue<T>(num, 0);
}



template <class T>
bool Parser<T>::SetCursor() {
    int depth = 0;
    int max_depth = 0;
    for (int i = 0; i < equation_.length(); ++i) {
        if (equation_[i] == '(') {
            depth += 1;
            if (depth > max_depth) {
                max_depth = depth;
                left_cursor_ = i;
                right_cursor_ = left_cursor_ + equation_.substr(
                    left_cursor_).find(')');
            }
        } else if (equation_[i] == ')') {
            depth -= 1;
        }
    }
    return max_depth != 0;
}


#endif /* PARSER_H */
