#include "Stack.hpp"

class answerGenerator
{
private:
    Stack<char> parenStack;
    Stack<char> operatorStack;
    Stack<float> operandStack;

public:
    int getPrecedence(char op)
    {
        if (op == '+' || op == '-')
            return 1; // Lower precedence
        else if (op == '*' || op == '/')
            return 2; // Higher precedence
        else
            return 0; // for digits and parenthesis
    }
    void operation()
    {
        char op = operatorStack.pop();
        float operand2 = operandStack.pop();
        float operand1 = operandStack.pop();
        float result = 0.0;

        if (op == '+')
            result = operand1 + operand2;
        else if (op == '-')
            result = operand1 - operand2;
        else if (op == '*')
            result = operand1 * operand2;
        else if (op == '/')
            result = operand1 / operand2;

        operandStack.push(result);
    }
    float evaluation(const string &str)
    {
        int i = 0;
        bool isNegative;
        bool expectOperand = true;
        while (i < str.length())
        {
            isNegative = false;
            if (str[i] == '-' && expectOperand) // Check for unary negation
            {
                isNegative = true;
                i++;
            }
            if (isdigit(str[i]))
            {
                string temp;
                while (i < str.length() && isdigit(str[i]))
                {
                    temp += str[i];
                    i++;
                }
                float num = stof(temp);
                if(isNegative)
                    num = -num;
                operandStack.push(num);
                expectOperand = false;
            }
            else if (str[i] == '(')
            {
                operatorStack.push(str[i]);
                i++;
                expectOperand = true;
            }
            else if (str[i] == ')')
            {
                while (!operatorStack.isEmpty() && operatorStack.topValue() != '(')
                {
                    operation();
                }
                if (!operatorStack.isEmpty() && operatorStack.topValue() == '(')
                    operatorStack.pop();
                i++;
                expectOperand = false;
            }
            else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
            {
                /*if (str[i] == '-' && (i == 0 || str[i - 1] == '('))
                    operandStack.push(0); // pushed 0 for unary negation
                */
                while (!operatorStack.isEmpty() && operatorStack.topValue() != '(' && getPrecedence(operatorStack.topValue()) >= getPrecedence(str[i]))
                {
                    operation();
                }
                operatorStack.push(str[i]);
                i++;
                expectOperand = true;
            }
            else
            {
                i++;
                expectOperand = false;
            }
        }
        while (!operatorStack.isEmpty())
        {
            operation();
        }
        return operandStack.pop();
    }
};

int main()
{
    string equation;
    getline(cin, equation);
    answerGenerator A;
    if (A.Validity(equation) && !isinf(A.evaluation(equation)))
    {
        cout << "Valid Expression" << endl;
        cout << "Computed Value: " << A.evaluation(equation) << endl;
    }
    else
        cout << "Not Valid" << endl;
    return 0;
}