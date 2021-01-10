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

    
    //std::string expression;
    std::cout << input << std::endl; 


    std::vector<char*> strStack_;

    //input = "";

    std::vector<double> stack_;
    double whole = 0;
    double fraction = 0;
    double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172;
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
        else if (isalpha (c))
        {
            if ((c == 'P') && (i < inputSize) && (input[i+1] == 'I') )
            {
                stack_.push_back(PI);
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
                //flag_pow = false;
            }
            else if ((c == 'C') && (i < inputSize - 1) && (input[i+1] == 'O') && (input[i+2] == 'S') )
            {
                double num = stack_.back();
                stack_.pop_back();
                double tmp = std::cos(num);
                stack_.push_back(tmp);

                flag = false;
                //flag_pow = false;
            }
            else if ((c == 'T') && (i < inputSize - 1) && (input[i+1] == 'A') && (input[i+2] == 'N') )
            {
                double num = stack_.back();
                stack_.pop_back();
                double tmp = std::tan(num);
                stack_.push_back(tmp);

                flag = false;
                //flag_pow = false;
            }
            else if ((c == 'C') && (i < inputSize - 1) && (input[i+1] == 'T') && (input[i+2] == 'G') )
            {
                double num = stack_.back();
                stack_.pop_back();
                if (std::tan(num) == 0) 
                {
                    std::cout << "NAN" << std::endl;
                     return 0;
                }
                else
                {
                    double tmp = 1 / std::tan(num);
                    stack_.push_back(tmp);

                    flag = false;
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

            }
            else if ((c == 'S') && (i < inputSize - 2) && (input[i+1] == 'Q') && (input[i+2] == 'R') && (input[i+3] == 'T') )
            {
                double num = stack_.back();
                stack_.pop_back();

                double tmp = std::sqrt(num);
                stack_.push_back(tmp);

                flag = false;

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
    if (result - iResult != 0) 
    {
        std::cout << std::fixed << std::setw(10) << result << std::endl;
    }
    else
    {
        std::cout << std::fixed << std::setw(10) << std::setprecision(0) << result << std::endl;
    }
    

    return 0;
    
}
