#include <iostream>  // 包含标准输入输出流库
#include <stack>     // 包含栈库
#include <string>    // 包含字符串库
#include <cctype>    // 包含字符处理库
using namespace std; // 使用标准命名空间

// 比较运算符优先级
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2; // 乘除优先级为2
    if (op == '+' || op == '-')
        return 1; // 加减优先级为1
    return 0;     // 默认优先级为0
}

// 执行运算
int applyOp(int a, int b, char op)
{
    switch (op)
    { // 根据运算符执行相应的运算
    case '+':
        return a + b; // 加法
    case '-':
        return a - b; // 减法
    case '*':
        return a * b; // 乘法
    case '/':
        return a / b; // 除法
    }
    return 0; // 默认返回0
}

// 中缀表达式求值函数
int evaluateInfixExpression(const string &expression)
{
    stack<int> values; // 存储操作数的栈
    stack<char> ops;   // 存储运算符的栈
    for (size_t i = 0; i < expression.length(); ++i)
    { // 遍历表达式
        if (isdigit(expression[i]))
        { // 如果是数字
            int val = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {                                           // 处理多位数字
                val = val * 10 + (expression[i] - '0'); // 将字符转换为整数
                ++i;
            }
            --i;              // 回退一个字符位置
            values.push(val); // 将操作数压入栈
        }
        else if (expression[i] == '(')
        {                            // 如果是左括号
            ops.push(expression[i]); // 将左括号压入栈
        }
        else if (expression[i] == ')')
        { // 如果是右括号
            while (!ops.empty() && ops.top() != '(')
            { // 处理括号内的表达式
                int val2 = values.top();
                values.pop(); // 取出两个操作数
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty())
            {
                ops.pop(); // 弹出左括号
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i]))
            { // 处理优先级较高的运算符
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]); // 将当前运算符压入栈
        }
    }
    while (!ops.empty())
    { // 处理剩余的运算符
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }
    return values.top(); // 返回最终结果
}

int main()
{
    string expression = "3+(4*2)-(1+3)/2";
    int result = evaluateInfixExpression(expression);
    cout << "表达式 " << expression << " 的值为: " << result << endl;
    return 0;
}