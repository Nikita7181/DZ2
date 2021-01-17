#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <map>

template<typename T> std::string toString(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::string convertToRPN(std::string input)
{
    std::string result = "";
    int leftBr = 0, rightBr = 0;
    int size = input.size();
    bool left = false;
    bool error = false;
    
    for (int i = 0; i < size; i++)
    {
        char c = input[i];
        if (((c == '*') || (c == '/') || (c == '+')) && i > 0)
        {
            if ((i+1<size) && (input[i-1] == ' ')&& (input[i+1] == ' '))
            {}
            else
            {
                std::cout << "Wrong statement, check operator syntax or space absent";
                return "";
            }
            
        }
        if (c == '-' && i > 0 )
        {
            if ((i+1<size) && ((input[i-1] == ' ') || (input[i-1] == '(') ))
            {
            
            }
            else
            {
                std::cout << "Wrong statement, check operator syntax or space absent";
                return "";
            }
            
        }
        else if (c == '(')
        {
            leftBr++;
            left = true;
            //error = true;
        }
        else if (c == ')')
        {
            rightBr++;
            if (left)
            {
                error = false;
                left = false;
            }
            else
            {
                error = true;
                break;
            }
            
        }
        else if (i < size - 1 && ((c == '.') || (c == ',')) && ((input[i+1] = '.') || (input[i+1] == ',') ))
        {
            std::cout << "Error statement: wrong fractional separator detected";
            return "";
        }
    }
    if (error)
    {
        std::cout << "Error statement, maybe \"(\" or \")\" is missing";
        return "";
    }
    if (leftBr < rightBr)
    {
        std::cout << "Error statement, maybe \"(\" is missing";
        return "";
    }
    else if (leftBr > rightBr)
    {
        std::cout << "Error statement, maybe \")\" is missing";
        return "";
    }
    
    std::map<std::string, int> map;
    
    map.insert(std::make_pair(toString("*"), 3));
    map.insert(std::make_pair(toString("/"), 3));
    map.insert(std::make_pair(toString("+"), 2));
    map.insert(std::make_pair(toString("-"), 2));
    map.insert(std::make_pair(toString("("), 1));
    map.insert(std::make_pair(toString("SIN"), 3));
    map.insert(std::make_pair(toString("COS"), 3));
    map.insert(std::make_pair(toString("TAN"), 3));
    map.insert(std::make_pair(toString("CTG"), 3));
    map.insert(std::make_pair(toString("POW"), 2));
    map.insert(std::make_pair(toString("EXP"), 3));
    map.insert(std::make_pair(toString("SQRT"), 3));
    map.insert(std::make_pair(toString("--"), 3));
    
    std::vector<std::string> stack_;
    
    char c;
    bool flagKeyWord = false;
    int keyWordLenght = 0;
    
    
    for (int i = 0; i < size; i++)
    {
        c = input [i];
        if (isalpha(c) || c == '-')
        {
            if ((c == '-') && (i < size -1) && (input[i+1] == '-'))
            {
                flagKeyWord = true;
                keyWordLenght = 2;
            }
            if ((i < (size - 2)) && ((c=='S') || (c== 'C') || (c== 'T') || (c== 'P') || (c== 'E')))
            {
                if ((c == 'S') && input[i+1] == 'I' && input[i+2] =='N')
                {
                    flagKeyWord = true;
                    keyWordLenght = 3;
                } else
                if ((c == 'S') && input[i+1] == 'Q' && input[i+2] =='R' && input[i+3] =='T')
                {
                    flagKeyWord = true;
                    keyWordLenght = 4;
                }
                else if ((c == 'C') && input[i+1] == 'O' && input[i+2] =='S')
                {
                    flagKeyWord = true;
                    keyWordLenght = 3;
                }
                else if ((c == 'T') && input[i+1] == 'A' && input[i+2] =='N')
                {
                    flagKeyWord = true;
                    keyWordLenght = 3;
                }
                else if ((c == 'C') && input[i+1] == 'T' && input[i+2] =='G')
                {
                    flagKeyWord = true;
                    keyWordLenght = 3;
                }
                else if ((c == 'P') && input[i+1] == 'O' && input[i+2] =='W')
                {
                    flagKeyWord = true;
                    keyWordLenght = 3;
                }
                else if ((c == 'E') && input[i+1] == 'X' && input[i+2] =='P')
                {
                    flagKeyWord = true;
                    keyWordLenght = 3;
                }
                
                
            }
        }
        
        if (c == ' ')
        {
            continue;
        }
        else if (!isalnum(c) && ( c != '.' ) && (c != ',') && !((c == '-' &&  isalnum(input[i+1]))) && !flagKeyWord)
        {
            result += ' ';
            
            if ( c == ')')
            {
                while (stack_[stack_.size()-1] != toString("("))
                {
                    result += stack_[stack_.size()-1];
                    stack_.pop_back();
                    result += ' ';
                }
                stack_.pop_back();
            }
            else if ( c == '(')
            {
                stack_.push_back(toString(c));
                
            }
            else if ((stack_.size() == 0) || (map[stack_[stack_.size()-1]] < map[toString(c)]))
            {
                stack_.push_back(toString(c));
                
            }
            else
            {
                do
                {
                    result += toString(stack_[stack_.size()-1]);
                    result += ' ';
                    stack_.pop_back();
                } while (!(stack_.size()==0 || (map[stack_[stack_.size()-1]] < map[toString(c)])));
                stack_.push_back(toString(c));
                
            }
        }
        
        else if (flagKeyWord)
        {
            switch (keyWordLenght)
            {
                case 2:
                {
                    char tmp[2];
                    tmp[0] = c;
                    tmp[1] = input[i+1];
                    std::string str = toString(tmp);
                    //if (str.size() > 2) {str.erase(2,1);}
                    stack_.push_back(str.substr(0,2));
                    i=i+1;
                    result += ' ';
                    break;
                }
                
                case 3:
                {
                    char tmp[3];
                    tmp[0] = c;
                    tmp[1] = input[i+1];
                    tmp[2] = input[i+2];
                    std::string str = toString(tmp);
                    //if (str.size() > 3) {str.erase(4,1);}
                    stack_.push_back(str.substr(0,3));
                    i=i+2;
                    result += ' '; //
                    
                    break;
                }
                
                case 4:
                {
                    char tmp[4];
                    tmp[0] = c;
                    tmp[1] = input[i+1];
                    tmp[2] = input[i+2];
                    tmp[3] = input[i+3];
                    std::string str = toString(tmp);
                    //if (str.size() > 4) {str.erase(5,1);}
                    stack_.push_back(str.substr(0,4));
                    i=i+3;
                    result += ' ';
                    break;
                }
                
                
                default:
                    break;
            }
            
            flagKeyWord = false;
            keyWordLenght = 0;
        }
        else
        {
            result += toString(c);
        }
        
        
    }
    
    
    while (!stack_.size() == 0)
    {
        result += ' ';
        result += stack_[stack_.size()-1];
        
        stack_.pop_back();
    }
    
    
    if (result.size()>0)
    {
        if (result[0] == ' ')
        {
            result.erase(0,1);
        }
        
        for (int i = 0; i < result.size()-1; i++)
        {
            if ((result[i] == ' ') && (result[i+1] == ' '))
            {
                result.erase(i,1);
                i--;
            }
        }
    }
    
    
    return result;
}

void calculate (std::string input)
{
    std::vector<char*> strStack_;
    
    std::vector<double> stack_;
    double whole = 0;
    double fraction = 0;
    const double PI = 3.1415926535;
    const double E = 2.7182818284;
    int pow = 1;
    bool flag = true;
    bool flag_pow = false;
    bool negative = false;
    
    std::string varName = "";
    
    
    std::vector <std::string> vars;
    
    
    int inputSize = input.size();
    
    for (int i = 0; i < inputSize; i++)
    {
        char c = input[i];
        if (isdigit(c))
        {
            if (varName != "")
            {
                varName = varName + c;
                flag = true;
            }
            else
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
            
        }
        else if (isalpha (c))
        {
            if ((c == 'P') && (i < inputSize) && (input[i+1] == 'I') )
            {
                stack_.push_back(PI);
                flag = false;
                i++;
            }
            else if ((c == 'E') && (i < inputSize) && (input[i+1] == ' ') )
            {
                stack_.push_back(E);
                flag = false;
                i++;
            }
            else if ((c == 'S') && (i < inputSize - 1) && (input[i+1] == 'I') && (input[i+2] == 'N') )
            {
                double num = stack_.back();
                stack_.pop_back();
                double tmp = std::sin(num);
                stack_.push_back(tmp);
                
                flag = false;
                i = i + 2;
                //flag_pow = false;
            }
            else if ((c == 'C') && (i < inputSize - 1) && (input[i+1] == 'O') && (input[i+2] == 'S') )
            {
                double num = stack_.back();
                stack_.pop_back();
                double tmp = std::cos(num);
                stack_.push_back(tmp);
                
                flag = false;
                i = i + 2;
                //flag_pow = false;
            }
            else if ((c == 'T') && (i < inputSize - 1) && (input[i+1] == 'A') && (input[i+2] == 'N') )
            {
                double num = stack_.back();
                stack_.pop_back();
                double tmp = std::tan(num);
                stack_.push_back(tmp);
                
                flag = false;
                i = i + 2;
                //flag_pow = false;
            }
            else if ((c == 'C') && (i < inputSize - 1) && (input[i+1] == 'T') && (input[i+2] == 'G') )
            {
                double num = stack_.back();
                stack_.pop_back();
                if (std::tan(num) == 0)
                {
                    std::cout << "NAN" << std::endl;
                    return;
                }
                else
                {
                    double tmp = 1 / std::tan(num);
                    stack_.push_back(tmp);
                    
                    flag = false;
                    i = i + 2;
                }
                //flag_pow = false;
            }
            else if ((c == 'E') && (i < inputSize - 1) && (input[i+1] == 'X') && (input[i+2] == 'P') )
            {
                double num = stack_.back();
                stack_.pop_back();
                
                double tmp = std::exp(num);
                stack_.push_back(tmp);
                
                flag = false;
                i = i + 2;
                
            }
            else if ((c == 'S') && (i < inputSize - 2) && (input[i+1] == 'Q') && (input[i+2] == 'R') && (input[i+3] == 'T') )
            {
                double num = stack_.back();
                stack_.pop_back();
                
                double tmp = std::sqrt(num);
                stack_.push_back(tmp);
                
                flag = false;
                i = i + 3;
                
            }
            else if ((c == 'P') && (i < inputSize - 1) && (input[i+1] == 'O') && (input[i+2] == 'W') )
            {
                double num2 = stack_.back();
                stack_.pop_back();
                double num1 = stack_.back();
                stack_.pop_back();
                
                double tmp = std::pow(num1, num2);
                stack_.push_back(tmp);
                
                flag = false;
                i = i + 2;
            }
            else
            {
                varName = varName + c;
                flag = true;
            }
            
            
            
        }
        else if ((c == '.' && flag) || (c == ',' && flag))
        {
            flag_pow = true;
        }
        else
        {
            if (c != ' ')
            {
                
                
                double tmp = 0;
                switch (c)
                {
                    
                    case '+' :
                    {
                        double num2 = stack_.back();
                        stack_.pop_back();
                        double num1 = stack_.back();
                        stack_.pop_back();
                        tmp = num1 + num2;
                        stack_.push_back(tmp);
                        break;
                    }
                    case '-' :
                    {
                        if ((i < inputSize) && (input[i+1] == '-'))
                        {
                            double num1 = stack_.back();
                            stack_.pop_back();
                            tmp = num1 - 1;
                            i++;
                        }
                        else if ((i < inputSize) && (std::isdigit(input[i+1])))
                        {
                            negative = true;
                            break;
                        }
                        else
                        {
                            double num2 = stack_.back();
                            stack_.pop_back();
                            double num1 = stack_.back();
                            stack_.pop_back();
                            tmp = num1 - num2;
                        }
                        stack_.push_back(tmp);
                        break;
                    }
                    case '*' :
                    {
                        double num2 = stack_.back();
                        stack_.pop_back();
                        double num1 = stack_.back();
                        stack_.pop_back();
                        tmp = num1 * num2;
                        stack_.push_back(tmp);
                        break;
                    }
                    case '/' :
                    {
                        double num2 = stack_.back();
                        stack_.pop_back();
                        double num1 = stack_.back();
                        stack_.pop_back();
                        tmp = num1 / num2;
                        stack_.push_back(tmp);
                        break;
                    }
                    case '^' :
                    {
                        double num2 = stack_.back();
                        stack_.pop_back();
                        double num1 = stack_.back();
                        stack_.pop_back();
                        tmp = std::pow(num1, num2);
                        stack_.push_back(tmp);
                        break;
                    }
                    default:
                        break;
                }
                
                flag = false;
                flag_pow = false;
            }
            else if (c == ' ' && flag)
            {
                if (varName != "")
                {
                    bool newVar = true;
                    int varIndex = 0;
                    double varValue = 0;
                    for (int vNum = 0; vNum < vars.size(); vNum+=2)
                    {
                        if (vars[vNum] == varName) {newVar = false; varIndex = vNum+1;}
                    }
                    if (newVar)
                    {
                        std::cout << "variable detected: " << varName << ", enter value: ";
                        
                        std::cin >> varValue;
                        vars.push_back(varName);
                        vars.push_back(toString(varValue));
                    }
                    else
                    {
                        varValue = std::stod(vars[varIndex]);
                    }
                    stack_.push_back(varValue);
                    varName = "";
                    flag = false;
                    
                }
                else
                {
                    double newPow = 1;
                    for (int j = 1; j < pow; j++) {newPow *= 0.1;}
                    stack_.push_back((negative ? -1 : 1 ) * (whole + (fraction * newPow)));
                    whole = 0;
                    fraction = 0;
                    pow = 1;
                    flag_pow = false;
                    negative = false;
                    flag = false;
                }
            }
        }
    }
    
    
    double result = stack_.size() > 0 ? stack_.back() : 0;
    int iResult = result;
    if (result - iResult != 0)
    {
        std::cout << std::fixed << std::setw(10) <<"Result: " << result << std::endl;
    }
    else
    {
        std::cout << std::fixed << std::setw(10) << std::setprecision(0) <<"Result: " << result << std::endl;
    }
    
}
void printInstruction()
{
    std::cout << "Instruction: " << std::endl;
    std::cout << "1) Use function SIN(X), COS(X), TAN(X), CTG(X); X - Rad. value" << std::endl;
    std::cout << "2) Use X POW Y or X ^ Y to rise X in power Y" << std::endl;
    std::cout << "3) Use SQRT (X) to calculate square root of X: " << std::endl;
    std::cout << "4) You can use constant PI (PI = 3.1415926535) or E (E = 2.7182818284) in statemet" << std::endl;
    std::cout << "5) Use EXP (X) to calculate exponent X: " << std::endl;
    std::cout << "6) Use X-- to decrease X by 1: " << std::endl;
    std::cout << "7) You can use variable (eg. val1 or val2) in statement: " << std::endl;
    std::cout << "8) Any math (+,-,/,*) operator must be separated by spaces (eg. \"x + y\" is corect, but \"x+y\" is wrong syntax)" << std::endl;
}

int main ()
{
    
    printInstruction();
    
    std::cout << "Enter statement: " << std::endl;
    
    std::string input;// = toString("2 * (9 * -1)");
    //std::string input = toString("SIN(a-- + 2 * 5) + 4 * 6");
    //std::string input = toString("SIN (6--)");
    std::getline(std::cin, input);
    
    std::string tmp = convertToRPN(input);
    std::cout << "RPN: "<<  tmp << std::endl;
    calculate(tmp);
    return 0;
}
