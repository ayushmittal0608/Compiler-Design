#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

struct Token { 
    string value; 
    char type; 
};

struct ASTNode { 
    string type,value; 
    ASTNode* left=nullptr; 
    ASTNode* right=nullptr; 
};

int precedence(const std::string& op){
    if(op=="*") return 2;
    if(op=="/") return 2;
    if(op=="+" || op=="-") return 1;
    return 0;
}

ASTNode* parseExpressionPrecedence(std::vector<Token>& tokens){
    stack<ASTNode*> operand;
    stack<string> operators;
    for(int i=0;i<tokens.size();i++){
        if(tokens[i].type=='i'){
            operand.push(new ASTNode{"variable",tokens[i].value});
        }
        else if(tokens[i].type=='o'){
            while(!operators.empty() && precedence(operators.top()) >= precedence(tokens[i].value)){
                ASTNode* r = operand.top(); 
                operand.pop();
                ASTNode* l = operand.top(); 
                operand.pop();
                string op = operators.top(); 
                operators.pop();
                operand.push(new ASTNode{"binary",op,l,r});
            }
            operators.push(tokens[i].value);
        }
    }
    while(!operators.empty()){
        ASTNode* r = operand.top(); 
        operand.pop();
        ASTNode* l = operand.top(); 
        operand.pop();
        string op = operators.top(); 
        operators.pop();
        operand.push(new ASTNode{"binary",op,l,r});
    }
    return operand.top();
}

void printAST(ASTNode* node,int level=0){
    if(!node) return;
    for(int i=0;i<level;i++) std::cout<<"  ";
    cout<<node->type<<"("<<node->value<<")"<<endl;
    printAST(node->left,level+1);
    printAST(node->right,level+1);
}

int main(){
    vector<Token> tokens={{"a",'i'},{"+",'o'},{"b",'i'},{"*",'o'},{"c",'i'}};
    ASTNode* root = parseExpressionPrecedence(tokens);
    printAST(root);
}