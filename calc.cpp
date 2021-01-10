#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>


int main ()
{
    std::cout << "Enter statement: " << std::endl;
    
    std::string input;
    std::getline(std::cin, input);
    
    
    std::string expression;
    std::cout << expression << std::endl;
    
    
    std::vector<char*> strStack_;
    
    input = "";
    
    std::vector<double> stack_;
    double whole = 0;
    double fraction = 0;
    double PI = 3.1415;
    int pow = 1;
    bool flag = true;
    bool flag_pow = false;
    
    
    int inputSize = input.size();
    
    for (int i = 0; i < inputSize; i++)
    {
        char c = input[i];
        if (isdigit(c))
        {
            if (!flag_pow)
            {
                whole *= 10;
                whole += (c - '0');
                flag = true;
            }
            else
            {
                fraction *= 10;
                fraction += (c - '0');
                flag = true;
                pow++;
            }
            
        }
        else if ((c == '.' && flag) || (c == ',' && flag))
        {
            flag_pow = true;
        }
        else if ((c == 'P') && (i < inputSize) && (input[i+1] == 'I') )
        {
            stack_.push_back(PI);
            flag = false;
            i++;
        }
        else
        {
            if (c != ' ')
            {
                double num2 = stack_.back();
                stack_.pop_back();
                double num1 = stack_.back();
                stack_.pop_back();
                
                double tmp = 0;
                switch (c){
                    
                    case '+' :
                        tmp = num1 + num2;
                        stack_.push_back(tmp);
                        break;
                    case '-' :
                        tmp = num1 - num2;
                        stack_.push_back(tmp);
                        break;
                    case '*' :
                        tmp = num1 * num2;
                        stack_.push_back(tmp);
                        break;
                    case '/' :
                        tmp = num1 / num2;
                        stack_.push_back(tmp);
                        break;
                    case '^' :
                        tmp = std::pow(num1, num2);
                        stack_.push_back(tmp);
                        break;
                    default:
                        break;
                    
                }
                
                flag = false;
                flag_pow = false;
            }
            else if (c == ' ' && flag)
            {
                double newPow = 1;
                for (int j = 1; j < pow; j++) {newPow *= 0.1;}
                stack_.push_back(whole + (fraction * newPow));
                whole = 0;
                fraction = 0;
                pow = 1;
                flag_pow = false;
            }
        }
    }
    
    
    double result = stack_.size() > 0 ? stack_.back() : 0;
    int iResult = result;
    if (result - iResult > 0)
    {
        std::cout << std::fixed << std::setw(10) << result << std::endl;
    }
    else
    {
        std::cout << std::fixed << std::setw(10) << std::setprecision(0) << result << std::endl;
    }
    
    
    return 0;
    
}
