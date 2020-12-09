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
#include <algorithm>
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
};

// Error handling object. If code != ReturnCode::success, then message will be
// filled with an appropriate error.
struct Status {
  ReturnCode code = ReturnCode::success;
  std::string message = "";
};

template <class T>
class Parser {
  private:
    // The string used to represent the equation.
    std::string equation_;

    // A map of variable names to ADValues.
    std::unordered_map<std::string, ADValue<T>> values_;
    
    // Cursors to keep track of current substring.
    int left_cursor_, right_cursor_;

    // The index of the intermediate values. This will be incremented to 
    // construct unique variable names (e.g., x0, x1, x2,...).
    int v_idx_ = 0;

    // The size of the seed vector. This will be 1 for scalar functions.
    int seed_size_;

    // The special characters representing the elementary operations that we
    // parse for.
    std::set<char> operations = { '+','^','-','/','*' };

    /**
     * Sets the cursors based on the deepest value of parentheses. This function
     * traverses the current value of equation_ to find the most inner nested
     * operation to be executed. 
     *
     * @return: bool describing whether or not the cursor was successfully set.
     */
    bool SetCursor();

    /**
     * Gets the value of a current key. This can either be a variable (e.g., "x")
     * or a positive constant value that can be cast to type T (e.g., "5.32").
     * This function is used by to fetch the intermediate ADValues as they are
     * created (e.g., GetValue("x0") will fetch the first constructed 
     * intermediate value).
     *
     * @param key: the string containing the id to be retrieved.
     * @return: a pair with a status as the first object and an ADValue as the
     *          second. One should check that that Status.code == success
     *          before using the ADValue. 
     */
    std::pair<Status,ADValue<T>> GetValue(const std::string& key);

    /**
     * Gets the index of the operation if it belongs to the single character
     * operation set (+,^,-,/,*). The Operation& parameter is also set to the 
     * matching enum value.
     *
     * @param sub_str: the current view of the equation from within the left and
     * right cursor.
     * @param op: a refernce to an op that can be set if an operation is found.
     * @return: the index inside the sub_str of the op. 
     */
    int GetOpIndex(const std::string& sub_str, Operation& op);

    /**
     * Handles any ops that are a single character (e.g., +,^,-,/,*).
     * The left and right ADValue references that are passed along with the 
     * operation reference will be set by this function.
     *
     * @param left_val: a reference to the left value of the ADNode. This will
     * be updated.
     * @param right_val: a reference to the right value. In unary operations,
     * this will be set to 0.
     * @param sub_str: the current substring within the left and right cursor.
     * @param op: a reference to the outer operation that will be set by this
     * function.
     * @param op_index: the index of the op within the sub_str to avoid finding 
     * it a second time.
     * @returns: a status containing either an success or failure with a message
     */
    Status HandleCharOps(ADValue<T>& left_val, ADValue<T>& right_val, 
                         std::string sub_str, Operation& op, int op_index);

    /**
     * Handles any ops that are not single character (e.g., sin, arcsin, ...).
     * The function works by figuring out how many letters the operation has and
     * delegating the processing to HandleThreeLetterOps, HandleFourLetterOps,
     * HandleSixLetterOps, or HandleLogisticOp. The left and right ADValue 
     * references that are passed along with the operation reference will be set
     * by this function.  
     *
     * @param left_val: a reference to the left value of the ADNode. This will
     * be updated.
     * @param right_val: a reference to the right value. In unary operations,
     * this will be set to 0.
     * @param sub_str: the current substring within the left and right cursor.
     * @param op: a reference to the outer operation that will be set by this
     * function.
     * @returns: a status containing either an success or failure with a message
     */
    Status HandleStringOps(ADValue<T>& left_val, ADValue<T>& right_val, 
                           std::string sub_str, Operation& op);

    /**
     * Handles any 3 letter ops (sin, cos, tan, exp, log). Called by 
     * HandleStringOps.
     *
     * @param left_val: a reference to the left value of the ADNode. This will
     * be updated.
     * @param right_val: a reference to the right value. In unary operations,
     * this will be set to 0.
     * @param sub_str: the current substring within the left and right cursor.
     * @param op: a reference to the outer operation that will be set by this
     * function.
     * @returns: a status containing either an success or failure with a message
     */
    Status HandleThreeLetterOps(ADValue<T>& left_val, ADValue<T>& right_val, 
                                std::string sub_str, Operation& op);  
    
    /**
     * Handles any 4 letter ops (sinh, cosh, tanh, sqrt). Called by 
     * HandleStringOps.
     *
     * @param left_val: a reference to the left value of the ADNode. This will
     * be updated.
     * @param right_val: a reference to the right value. In unary operations,
     * this will be set to 0.
     * @param sub_str: the current substring within the left and right cursor.
     * @param op: a reference to the outer operation that will be set by this
     * function.
     * @returns: a status containing either an success or failure with a message
     */
    Status HandleFourLetterOps(ADValue<T>& left_val, ADValue<T>& right_val, 
                               std::string sub_str, Operation& op);
    
    /**
     * Handles any 6 letter ops (arcsin, arccos, arctan). Called by 
     * HandleStringOps.
     *
     * @param left_val: a reference to the left value of the ADNode. This will
     * be updated.
     * @param right_val: a reference to the right value. In unary operations,
     * this will be set to 0.
     * @param sub_str: the current substring within the left and right cursor.
     * @param op: a reference to the outer operation that will be set by this
     * function.
     * @returns: a status containing either an success or failure with a message
     */
    Status HandleSixLetterOps(ADValue<T>& left_val, ADValue<T>& right_val, 
                               std::string sub_str, Operation& op);
    
    /**
     * Handles the logistic operation. Called by HandleStringOps.
     *
     * @param left_val: a reference to the left value of the ADNode. This will
     * be updated.
     * @param right_val: a reference to the right value. In unary operations,
     * this will be set to 0.
     * @param sub_str: the current substring within the left and right cursor.
     * @param op: a reference to the outer operation that will be set by this
     * function.
     * @returns: a status containing either an success or failure with a message
     */
    Status HandleLogisticOp(ADValue<T>& left_val, ADValue<T>& right_val, 
                            std::string sub_str, Operation& op);

    /**
     * Checks if an argument to a string operations (e.g., sin) is valid.
     *
     * @param left_val: a reference to the left value of the ADNode. This will
     * be updated.
     * @param right_val: a reference to the right value. In unary operations,
     * this will be set to 0.
     * @param op_name: the name of the op to check for validity (e.g., "sin").
     * @param sub_str: the current substring within the left and right cursor.
     * function.
     * @returns: a status containing either an success or failure with a message
     */
    Status CheckValidArgument(ADValue<T>& left_val, 
                              ADValue<T>& right_val, 
                              const std::string& op_name, 
                              const std::string& sub_str);

    /**
     * Evaluate the current part of the equation that is within the left and 
     * right cursor. This function will call HandleStringOps or HandleCharOps
     * depending on the operation that it parses. The new ADValue created from
     * the result of the evaluation of the ADNode will be stored in the values
     * table under a unique name (e.g., "x4"). The cursor values will then be
     * reset and the status of the parser returned.
     *
     * @returns: a status to indicate success or failure with a message.
     */
    Status Next();

  public:
    /**
     * Parser constructor.
     *
     * @param equation: a string representation of the equation.
     */
    Parser(std::string equation) : equation_(equation) {}

    /**
     * Initialize the state of the parser. Using the provided seed values and 
     * seed names, fill the values_ hash map. Init also checks to ensure that
     * the provided equation has balanced parentheses, and sets the initial
     * values of the left and right cursor objects.
     *
     * @param seed_values: a vector of string -> ADValue pairs. These will be
     * used to initialize the hash map the represents the values of intermediate
     * objects.
     * @returns: a status to indicate success or failure with a message.
     */
    Status Init(std::vector<std::pair<std::string, ADValue<T>>> seed_values);

    

    /**
     * Run the entire parsing flow. Run() calls Next until there is no 
     * parentheses left in the equation (each call to next removes one set).
     * Once the final result is available, Run returns this ADValue object as 
     * well as a status. After calling Init(), Run should be the only function
     * that the user calls.
     *
     * @returns: a pair of status and ADValue. If the status is success, then
     * the ADValue object will contain the result of the AutoDifferentiation.
     * If the status is a failure, then the ADValue object will be initialzed to
     * zero. It is up to the user to check the status before using the object.
     */
    std::pair<Status,ADValue<T>> Run();
};


/* Implementation */

template <class T>
std::pair<Status,ADValue<T>> Parser<T>::Run() {
    // Initialize to OK status.
    Status status;
    // Continue while there still remain parentheses in the equation_.
    while (equation_.find('(') != std::string::npos) {
        status = Next();
        if (status.code != ReturnCode::success) {
            break; 
        }
    }
    // The output variable is xn where n is v_idx - 1. Construct the string here
    // to retrieve the final ADValue from the values_ map.
    std::string out = 'x' + std::to_string(--v_idx_);
    return std::pair<Status,ADValue<T>>(status,values_[out]);
}


template <class T>
Status Parser<T>::Init(
    std::vector<std::pair<std::string, ADValue<T>>> seed_values) {
    seed_size_ = seed_values.size();
    // Setting seed values in hash table.
    for (auto& seed_val : seed_values) {
        values_[seed_val.first] = seed_val.second;
    }
    Status status;

    // Check for unbalanced parentheses where there are more left parens '(' 
    // than right ')'.
    std::stack<char> paren_stack; 
    for (char const &c : equation_) {
        if (c == '(') {
            paren_stack.push('('); 
        } else if (c == ')') {
            if (paren_stack.empty()) {
                status.code = ReturnCode::parse_error; 
                status.message = "Unbalanced parentheses -- too many \')\'"; 
                return status; 
            } else {
                paren_stack.pop(); 
            }
        }
    }
    // Case where there are more left than right parens.
    if (!paren_stack.empty()) {
        status.code = ReturnCode::parse_error; 
        status.message = "Unbalanced parentheses -- too many \'(\'"; 
        return status; 
    }

    // Try to set cursor. If no parentheses are found return an error status.
    if (!SetCursor()) {
        status.code = ReturnCode::parse_error;
        status.message = "No parentheses found.";
        return status;
    }
    return status;
}

template <class T> 
int Parser<T>::GetOpIndex(const std::string& sub_str, Operation& op) {
    int op_index = -1;
    // Iterate sub_str until an op character is found. If none retrun -1.
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
    return op_index;
}

template <class T>
Status Parser<T>::HandleCharOps(ADValue<T>& left_val, ADValue<T>& right_val, 
                                std::string sub_str, Operation& op, 
                                int op_index) {
    Status status;
    // Operations including negation, + , - , ^, *
    std::string LHS = sub_str.substr(0,op_index);
    std::string RHS = sub_str.substr(op_index+1);
    
    // Get value of variable or constant for RHS.
    auto res_right = GetValue(RHS);
    if (res_right.first.code != ReturnCode::success) {
        return res_right.first;
    }
    right_val = res_right.second;

    // Handle negation operation as a subcase of subtraction.
    if (op == Operation::subtraction && LHS.empty()) {
        left_val = GetValue("0").second; 
    // When op has two sides.
    } else {
        // Check operation requires LHS and RHS
        // Ensure non-empty strings
        if (LHS.empty() || RHS.empty()) {
            status.code = ReturnCode::parse_error; 
            status.message = "Binary operation requires LHS and RHS"; 
            return status; 
        }
        auto res_left = GetValue(LHS);
        if (res_left.first.code != ReturnCode::success) {
            return res_left.first;
        }
        left_val = res_left.second; 
    }
    return status;
}

template <class T>
Status Parser<T>::HandleStringOps(ADValue<T>& left_val, ADValue<T>& right_val, 
                                  std::string sub_str, Operation& op) {
    Status status;
    // Check if trig function
    // deal with (x)
    if (sub_str.length() <= 3) {
        // All of the alpha functions are three letters or more.
        auto value_cast_pair = GetValue(sub_str); 
        if (value_cast_pair.first.code != ReturnCode::success) {
            return value_cast_pair.first; 
        }
        left_val = value_cast_pair.second; 
        right_val = GetValue("0").second;
        op = Operation::addition; 
    } else {
        // Get each of the potential sub strings.
        std::string three_letter = sub_str.substr(0,3);
        std::string four_letter = sub_str.substr(0,4);
        std::string six_letter = sub_str.substr(0,6);
        std::string eight_letter = sub_str.substr(0,8); 

        // These are the operations that we support.
        std::vector<std::string> four_letter_ops = {
            "sinh", "cosh", "tanh", "sqrt"};
        std::vector<std::string> three_letter_ops = {
            "sin", "cos", "tan", "exp", "log"};
        std::vector<std::string> six_letter_ops = {
            "arcsin", "arccos", "arctan"};
        
        // Logistic is the only 8 letter op.
        if (eight_letter.compare("logistic") == 0) {
            return HandleLogisticOp(left_val, right_val, sub_str, op);
        }
        // Check if the four letter op is supported. This must come before the
        // three letter checks to avoid confusion between sin and sinh.
        if (std::find(four_letter_ops.begin(), 
                      four_letter_ops.end(), 
                      four_letter) != four_letter_ops.end()) {
            return HandleFourLetterOps(left_val, right_val, sub_str, op);
        }
        // Check if the six letter op is supported.
        if (std::find(six_letter_ops.begin(), 
                      six_letter_ops.end(), 
                      six_letter) != six_letter_ops.end()) {
            return HandleSixLetterOps(left_val, right_val, sub_str, op);
        }
        // Check if the three letter op is supported.
        if (std::find(three_letter_ops.begin(), 
                      three_letter_ops.end(), 
                      three_letter) != three_letter_ops.end()) {
            return HandleThreeLetterOps(left_val, right_val, sub_str, op);
        }
    
        // sub_str > 3, no alpha operation. Try to cast as into type T.
        auto value_cast_pair = GetValue(sub_str); 
        if (value_cast_pair.first.code != ReturnCode::success) {
            return value_cast_pair.first; 
        }
        left_val = value_cast_pair.second; 
        right_val = GetValue("0").second;
        op = Operation::addition;                            
    } 
    return status;
}

template <class T>
Status Parser<T>::CheckValidArgument(ADValue<T>& left_val, 
                                     ADValue<T>& right_val, 
                                     const std::string& op_name,
                                     const std::string& sub_str) {
    Status status;
    // Check if the argument is found in the table.
    auto stored_val = values_.find(sub_str.substr(op_name.length())); 
    if (stored_val == values_.end()) {
        status.code = ReturnCode::parse_error; 
        status.message = "Invalid argument to " + op_name; 
        return status; 
    }
    // Initialize right val to zero because it will not be used by unary ops.
    left_val = stored_val->second; 
    right_val = GetValue("0").second;
    return status;
}

template <class T>
Status Parser<T>::HandleThreeLetterOps(ADValue<T>& left_val, 
                                       ADValue<T>& right_val, 
                                       std::string sub_str, 
                                       Operation& op) {
    Status status;
    std::string three_letter = sub_str.substr(0,3);
    if (three_letter.compare("sin") == 0) {
        op = Operation::sin;
        return CheckValidArgument(left_val, right_val, "sin", sub_str);
    } else if (three_letter.compare("cos") == 0) {
        op = Operation::cos;
        return CheckValidArgument(left_val, right_val, "cos", sub_str);
    } else if (three_letter.compare("tan") == 0) {
        op = Operation::tan; 
        return CheckValidArgument(left_val, right_val, "tan", sub_str);
    } else if (three_letter.compare("exp") == 0) {
        op = Operation::exp; 
        return CheckValidArgument(left_val, right_val, "exp", sub_str);
    } else /* Must be log. */{
        // Log is more complicated because we need to parse the base.
        op = Operation::log;
        int right_marker = sub_str.substr(4).find('_');
        // Get base.
        right_val = GetValue(
            sub_str.substr(4, right_marker)).second;
        auto stored_val = values_.find(
            sub_str.substr(4+right_marker+1)); 
        if (stored_val == values_.end()) {
            status.code = ReturnCode::parse_error; 
            status.message = "Invalid argument to log"; 
            return status; 
        }
        left_val = stored_val->second;
    }
    return status; 
}

template <class T>
Status Parser<T>::HandleFourLetterOps(ADValue<T>& left_val, 
                                      ADValue<T>& right_val, 
                                      std::string sub_str, 
                                      Operation& op) {
    std::string four_letter = sub_str.substr(0,4);
    if (four_letter.compare("sinh") == 0) {
        op = Operation::sinh; 
        return CheckValidArgument(left_val, right_val, "sinh", sub_str);
    } else if (four_letter.compare("cosh") == 0) {
        op = Operation::cosh; 
        return CheckValidArgument(left_val, right_val, "cosh", sub_str);               
    } else if (four_letter.compare("tanh") == 0) {
        op = Operation::tanh; 
        return CheckValidArgument(left_val, right_val, "tanh", sub_str);               
    } else /* Must be sqrt. */ {
        op = Operation::sqrt; 
        return CheckValidArgument(left_val, right_val, "sqrt", sub_str);                
    }
}

template <class T>
Status Parser<T>::HandleSixLetterOps(ADValue<T>& left_val, 
            ADValue<T>& right_val, std::string sub_str, Operation& op) {
    std::string inv_trig_str = sub_str.substr(0,6);
    if (inv_trig_str.compare("arcsin") == 0) {
        op = Operation::arcsin; 
        return CheckValidArgument(left_val, right_val, "arcsin", sub_str);
    } else if (inv_trig_str.compare("arccos") == 0) {
        op = Operation::arccos; 
        return CheckValidArgument(left_val, right_val, "arccos", sub_str);
    } else /* Must be arctan. */ {
        op = Operation::arctan; 
        return CheckValidArgument(left_val, right_val, "arctan", sub_str);
    }
}

template <class T>
Status Parser<T>::HandleLogisticOp(ADValue<T>& left_val, ADValue<T>& right_val, 
                                   std::string sub_str, Operation& op) {
    op = Operation::logistic; 
    return CheckValidArgument(left_val, right_val, "logistic", sub_str);
}

template <class T>
Status Parser<T>::Next() {
    Status status;
    // We only focus on the part of the equation between the left and right 
    // cursor.
    std::string sub_str = equation_.substr(
        left_cursor_+1, right_cursor_ - (left_cursor_+1));
    Operation op;
    int op_index = GetOpIndex(sub_str, op);

    // The values to be used by the ADNode. In unary operation case the right
    // val will be set to 0.
    ADValue<T> left_val; 
    ADValue<T> right_val; 

    // Case where the operation is a string instead of a character.
    if (op_index == -1) {
        status = HandleStringOps(left_val, right_val, sub_str, op);
        if (status.code != ReturnCode::success) {
            return status;
        }
    } else {
        status = HandleCharOps(left_val, right_val, sub_str, op, op_index);
        if (status.code != ReturnCode::success) {
            return status;
        }
    }

    // Create node with our left and right values. In unary case, right is 0.
    ADNode<T> cur_node(left_val, right_val, op);

    // Combine value(s) and operation to get subsequent value.
    ADValue<T> cur_value = cur_node.Evaluate();
    
    // Get new intermediate name for the variable (e.g.,"x3").
    std::string new_val_name = 'x' + std::to_string(v_idx_++);
    values_[new_val_name] = cur_value;

    // Replace the old cursor contents with just this new value name.
    std::string new_str = equation_.replace(
        left_cursor_, right_cursor_ - left_cursor_ + 1, new_val_name);
    
    // Update equation.
    equation_ = new_str;
    if (!SetCursor()) {
        return status;
    }
    return status;
}

template <class T>
std::pair<Status,ADValue<T>> Parser<T>::GetValue(const std::string& key) {
    Status status;
    // Check for empty key.
    if (key.empty()) {
        return std::pair<Status, ADValue<T>>(status, ADValue<T>(0, 0));
    }
    auto it = values_.find(key);
    // Look in values table for key
    if (it != values_.end()) {
        return std::pair<Status, ADValue<T>>(status, values_[key]);
    }

    // Key is not in table, so try to cast the string to type T through use of
    // stringstream.
    std::istringstream ss(key);
    T num;
    ss >> num;
    // Casting failed.
    if (!ss.eof() || ss.fail()){
        status.code = ReturnCode::parse_error;
        status.message = "Key not found: " + key;
        return std::pair<Status, ADValue<T>>(status, ADValue<T>(0,0));
    }
    std::vector<T> zeros(seed_size_, 0);
    return std::pair<Status, ADValue<T>>(status, ADValue<T>(num, zeros));
}

template <class T>
bool Parser<T>::SetCursor() {
    int depth = 0;
    int max_depth = 0;
    // Look through equation and calculate the max depth (e.g., most nested
    // set of parens). Once this is found, update the values of the left and
    // right cursor. 
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
