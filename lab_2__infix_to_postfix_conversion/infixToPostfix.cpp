/*
 * Name: Mike Brandin
 * Date Submitted: 09/12/20
 * Lab Section: 4
 * Assignment Name: Lab 2
 */

#include <string>
#include <stack>
#include <iostream>
#include <iostream>


using namespace std;

//Converts an infix arithmetic expression into postfix
//The function takes 3 parameters
//First parameter: array of strings for infix expression
//    each string is either an integer number or operator symbol
//Second parameter: number of strings in infix expression
//Third parameter: array of strings for postfix expression
//    generated by function, same format as first parameter
//    assumes that postfix is at least the size of postfix
//Return value: int, number of strings in postfix expression
//    Returns 0 if an error is encountered when converting expression
//    An error occurs with a mismatched parenthesis, e.g. ( ( ) or ( ) ) etc.
//Operator symbols:
// ( : left parenthesis, all operations between this and ")" take place first
// ) : right parenthesis, all op.s back to previous "(" take place first
// * : multiplication, higher precedence - takes place before "+" and "-"
// / : division, higher precedence - takes place before "+" and "-"
// % : remainder, higher precedence - takes place before "+" and "-"
// + : addition, lower precedence - takes place after "*" , "/" , "%"
// - : subtraction, lower precedence - takes place after "*" , "/" , "%"
//The function is not specified to work with any other operator symbols
//Any string in infix may be assumed to be an integer operand if none
// of the above symbols

int compareOperator(string op){//return the precedence value of the operator -1 if invalid operator (used for parenthesese mostly)
    
    if (op == "+" || op == "-"){
        return 0;
    }
    
    else if (op == "/" || op == "*" || op == "%"){
        return 1;
    }
    else{
    return -1;
    }
}

bool isOperator(string input){//check if valid operator
    
    if (input == "+" || input == "-" || input == "*" || input == "/" || input == "%"){
        return true;

    }
    else{
        return false;
    }
    
}

int infixToPostfix(string infix[], int length, string postfix[]){
    stack<string> oStack;
    
    int pc = 0;
    //int good = 0;
    int lCount = 0;
    int rCount = 0;
    bool invalid = false;
    
    
    for (int i = 0; i < length; i++){//count parenthesese
        if (infix[i] == "("){
            lCount++;
        }
        else if (infix[i] == ")"){
            rCount++;
        }
        if (i>0 && isOperator(infix[i]) && isOperator(infix[i-1])){//check if two operators are side by side
            invalid = true;
        }
        
    }
    
    if ((rCount != lCount) || invalid){//check if parenthesese match or invalid equation
        return 0;
    }
    

    
    for (int i = 0; i < length; i++){//loop through length of infix 
        //good++;
        //cout << "we're good!" << good << endl;
        
        if (isOperator(infix[i])){//if index is a valid operator
            
            while (!oStack.empty() && oStack.top() != "(" && compareOperator(infix[i]) <= compareOperator(oStack.top())) {  
                //cout << "infix = " << infix[i] << "  |  ostack = " << oStack.top() <<  endl;
                    
                string temp = oStack.top();
                postfix[pc] = temp;
                pc++;                    
                    
                oStack.pop();


            }  
            oStack.push(infix[i]);  
            //cout << "ostack2 = " << oStack.top() << endl;



        }
        else if (infix[i] == "("){//if index is a (
            
            oStack.push(infix[i]);
        }
        else if (infix[i] == ")"){//if index is a )

            while (!oStack.empty() && oStack.top() != "("){

                string temp = oStack.top();
                oStack.pop();
                postfix[pc] = temp;
                pc++;

            }
                
            oStack.pop();
        }
        else {//if index is a number (or anything else)
            postfix[pc] = infix[i];
            pc++;
        }
        
    } 
        
    while (!oStack.empty()){//empty oStack after loop has finished
        if (oStack.top() == "("){
         return 0;
        }
        string temp = oStack.top();
        oStack.pop();
        postfix[pc] = temp;
        pc++;
    }
    

    return pc;//return length of postfix array
    
}

//Main function to test infixToPostfix()
//Should convert 2 + 3 * 4 + ( 5 - 6 + 7 ) * 8
//            to 2 3 4 * + 5 6 - 7 + 8 * +
int main() //REVERT TO ORIGINAL TEST MAIN
{
    string infixExp[] = {"2", "+", "3", "*", "4", "+", "(", "5", "-", "6", "+", "7", ")", "*", "8"};
    //string infixExp[] = {"2", "+", "3", "*", "4", "+", "(", "5", "*", "6", "+", "7", ")", "*", "8"};
    //postfix = {234*+567+8*+};                 
    string postfixExp[15];
    int postfixLength;


    cout << "Infix expression: ";
    for (int i=0; i<15; i++)
    {
        cout << infixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: 15" << endl << endl;

    postfixLength = infixToPostfix(infixExp, 15, postfixExp);

    cout << "Postfix expression: ";
    for (int i=0; i<postfixLength; i++)
    {
        cout << postfixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: " << postfixLength << endl;
    
    return 0;
    
}