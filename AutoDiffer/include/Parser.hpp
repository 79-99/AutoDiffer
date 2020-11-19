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
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
#endif

enum class ReturnCode {
  success = 1,
  parse_error = 2,
  // other errors.
};

struct Status {
  ReturnCode code = ReturnCode::success;
  std::string message = "";
};

template <class T>
class Parser {
  private:
    std::string equation_;
    std::unordered_map<std::string, ADValue<T>> values_;
    int left_cursor_, right_cursor_;
    int v_idx_ = 0;

    bool SetCursor();
    ADValue<T> GetValue(const std::string& key);

    std::set<char> operations = { '+','^','-','/','*' }; 

  public:
    Parser(std::string equation) : equation_(equation) {}
    Status Init(std::vector<std::pair<std::string, ADValue<T>>> seed_values);
    Status Next();
    std::pair<Status,ADValue<T>> Run();
    void print_hello() const;
};


/* Implementation */
template <class T>
std::pair<Status,ADValue<T>> Parser<T>::Run() {
    Status status;
    while (equation_.find('(') != std::string::npos) {
        status = Next();
        if (status.code != ReturnCode::success) {
            break; 
        }
    }
    std::string out = 'x' + std::to_string(--v_idx_);
    return std::pair<Status,ADValue<T>>(status,values_[out]);
}


template <class T>
Status Parser<T>::Init(
    std::vector<std::pair<std::string, ADValue<T>>> seed_values) {
    // Setting seed values in hash table.
    for (auto& seed_val : seed_values) {
        values_[seed_val.first] = seed_val.second;
    }
    Status status;

    // Check for unbalanced parentheses 
    std::stack<char> paren_stack; 
    for (char const &c : equation_) {
        if (c == '(') {
            paren_stack.push('('); 
        } else if (c == ')') {
            if (paren_stack.empty()) {
                status.code = ReturnCode::parse_error; 
                status.message = "Unbalanced parentheses"; 
                return status; 
            } else {
                paren_stack.pop(); 
            }
        }
    }

    if (!paren_stack.empty()) {
        status.code = ReturnCode::parse_error; 
        status.message = "Unbalanced parentheses"; 
        return status; 
    }

    if (!SetCursor()) {
        status.code = ReturnCode::parse_error;
        status.message = "No left parentheses found.";
        return status;
    }
    return status;
}

template <class T>
Status Parser<T>::Next() {
    Status status;
    std::string sub_str = equation_.substr(
        left_cursor_+1, right_cursor_ - (left_cursor_+1));
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
            } else if (op_char == '-') {
		        op = Operation::subtraction;
	        } else if (op_char == '/') {
		        op = Operation::division;
	        } else if (op_char == '*') {
		        op = Operation::multiplication;
	        }
            op_index = i;
            break;
        }
    }

    ADValue<T> left_val; 
    ADValue<T> right_val; 

    if (op_index == -1) {
        // Check if trig function
        // deal with (x)
        if (values_.find(sub_str) != values_.end()) {
            left_val = values_.find(sub_str)->second; 
            right_val = GetValue("0");
            op = Operation::addition; 
        } else if (sub_str.length() > 3) {
            std::string trig_str = sub_str.substr(0,3); 
            if (trig_str.compare("sin") == 0) {
                op = Operation::sin; 
                auto stored_val = values_.find(sub_str.substr(3)); 
                if (stored_val == values_.end()) {
                    status.code = ReturnCode::parse_error; 
                    status.message = "Invalid argument to sin"; 
                    return status; 
                }
                left_val = stored_val->second; 
                right_val = GetValue("0"); 
            } else if (trig_str.compare("cos") == 0) {
                op = Operation::cos;
                auto stored_val = values_.find(sub_str.substr(3)); 
                if (stored_val == values_.end()) {
                    status.code = ReturnCode::parse_error; 
                    status.message = "Invalid argument to cos"; 
                    return status; 
                }
                left_val = stored_val->second; 
                right_val = GetValue("0"); 
            } else if (trig_str.compare("tan") == 0) {
                op = Operation::tan; 
                auto stored_val = values_.find(sub_str.substr(3)); 
                if (stored_val == values_.end()) {
                    status.code = ReturnCode::parse_error; 
                    status.message = "Invalid argument to tan"; 
                    return status; 
                }
                left_val = stored_val->second; 
                right_val = GetValue("0"); 
            } else if (trig_str.compare("exp") == 0) {
                op = Operation::exp; 
                auto stored_val = values_.find(sub_str.substr(3)); 
                if (stored_val == values_.end()) {
                    status.code = ReturnCode::parse_error; 
                    status.message = "Invalid argument to exp"; 
                    return status; 
                }
                left_val = stored_val->second; 
                right_val = GetValue("0");                 
            } else {
                status.code = ReturnCode::parse_error; 
                status.message = "Invalid argument"; 
                return status;                 
            }
        } else {
            // binary / unary ops + , - , * , /
            // if string does not contain above and is not long enough
            // to contain sin, cos, tan, or exp throw error
            status.code = ReturnCode::parse_error; 
            status.message = "Invalid argument"; 
            return status;                  
        }
    } else {
        // Operations including negation, + , - , ^, *
        std::string LHS = sub_str.substr(0,op_index);
        std::string RHS = sub_str.substr(op_index+1);
        
        right_val = GetValue(RHS);

        if (op == Operation::subtraction && LHS.empty()) {
            left_val = GetValue("0"); 
        // When op and two sides
        } else {
            // Check operation requires LHS and RHS
            // Ensure non-empty strings
            if (LHS.empty() || RHS.empty()) {
                status.code = ReturnCode::parse_error; 
                status.message = "Binary operation requires LHS and RHS"; 
                return status; 
            }
            left_val = GetValue(LHS); 
        }
    }
    
    ADNode<T> cur_node(left_val, right_val, op);
    ADValue<T> cur_value = cur_node.Evaluate();
    std::string new_val_name = 'x' + std::to_string(v_idx_++);
    values_[new_val_name] = cur_value;
    std::string new_str = equation_.replace(
        left_cursor_, right_cursor_ - left_cursor_ + 1, new_val_name);
    equation_ = new_str;
    if (!SetCursor()) {
        return status;
    }
    return status;
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
