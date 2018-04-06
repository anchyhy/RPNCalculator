//
//  main.cpp
//  RPNCalculator
//
//  Created by 邵安琪 on 10/8/16.
//  Copyright © 2016 anchy. All rights reserved.
//

#include <iostream>
//Use the STL stack/queue classes in C++
#include <stack>
#include <queue>
#include <cMath>

using namespace std;
//judge the precedence of the operator
int precedence(char c) {
    if(c=='+'||c=='-')
        return 1;
    else if(c == '^')
        return 3;
    else
        return 2;
}
queue<char> conversionFromInfixtoPostfix(queue<char> infixQ) {
    queue<char> postQ;
    stack<char> opStack;
    char t;
    while (!infixQ.empty()) {
        t = infixQ.front();
        infixQ.pop();
        if (t>='0'&&t<='9') {
            postQ.push(t);
        } else if (opStack.empty()) {
            opStack.push(t);
            postQ.push(' ');
        } else if (t=='(') {
            opStack.push(t);
        } else if (t ==')') {
            while (opStack.top() != '('){
                postQ.push(opStack.top());
                opStack.pop();
            }
            opStack.pop(); // discard a left paren from stack
        } else {
            while (!opStack.empty()&&opStack.top()!='('&& precedence(t) <= precedence(opStack.top())) {
                postQ.push(opStack.top());
                opStack.pop();
            }
            opStack.push(t);
            postQ.push(' ');
        }
    }
    // Now there are no tokens left in infixQ, so transfer remaining operators.
    while (!opStack.empty()) { // (6)
        postQ.push(opStack.top());
        opStack.pop();
    }
    postQ.push('@');
    return postQ;
}
//
int evaluatingAPostfixExpression(queue<char> postQ) {
    stack<int> eval;
    eval.push(0);
    char t;
    int topNum, nextNum, answer = 0;
    while (!postQ.empty() && postQ.front() != '@') {
        t = postQ.front();
        postQ.pop();
        if(t == ' ') {
            eval.push(0);
        } else if (t>='0'&&t<='9') {
            eval.top() = eval.top() * 10 + (t-'0');
        } else {
            topNum = eval.top();
            eval.pop();
            nextNum = eval.top();
            eval.pop();
            switch (t) {
                case '+': answer = nextNum + topNum;
                    break;
                case '-': answer = nextNum - topNum;
                    break;
                case '*': answer = nextNum * topNum;
                    break;
                case '/': answer = nextNum / topNum;
                    break;
                case '%': answer = nextNum % topNum;
                    break;
                case '^': answer = pow(nextNum, topNum);
                    break;
            }
            eval.push(answer);
        }
    }
        return eval.top();
}
int main() {
    cout<<"please enter an infix math problem, press 'return' to stop:"<<endl;
    string a;
    cin>>a;
    while (a!="quit") {
        queue<char> infixQ;// infixQ contains the infix expression to be converted.
        for (char c : a)
            infixQ.push(c);
        cout<<"begin to converse......"<<endl<<"the result of conversion is:"<<endl;
        queue<char> postQ;
        postQ=conversionFromInfixtoPostfix(infixQ);// postQ contains the converted postfix expression.
        queue<char> tmp = postQ;
        while (tmp.front()!= '@') {
            cout<<tmp.front();
            tmp.pop();
        }
        cout<<endl;
        cout<<"begin to calculate......"<<endl;
        int answer=evaluatingAPostfixExpression(postQ);
        cout<<"The answer of calculation is: "<<answer<<endl;
        cout<<"You can type 'quit' now to stop the calculation. Or you can start another infix math problem."<<endl;
        cin>>a;
    }
    cout<<"Thx for your calculation!"<<endl;
    return 0;
}
