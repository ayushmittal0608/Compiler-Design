#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

struct Token { 
    string value; 
    char type; 
};

struct ASTNode { 
    string type, value; 
    ASTNode* left=nullptr; 
    ASTNode* right=nullptr; 
};

ASTNode* parseAssignmentNonRecursive(vector<Token>& tokens) {
    int pos=1;
    ASTNode* lhs=new ASTNode{"variable", tokens[pos].value};
    pos++;
    if(tokens[pos].value=="="){
        pos++;
    }
    stack<ASTNode*> s;
    ASTNode* left = new ASTNode{"variable",tokens[pos].value}; 
    pos++;
    ASTNode* right = nullptr;
    if(pos<tokens.size() && (tokens[pos].value=="+"||tokens[pos].value=="-")) {
        string op = tokens[pos].value; 
        pos++;
        right = new ASTNode{"variable",tokens[pos].value}; 
        pos++;
        ASTNode* binary = new ASTNode{"binary",op,left,right};
        lhs->right = binary;
    }
    return new ASTNode{"assign", "=", lhs, lhs->right};
}

void printAST(ASTNode* node,int level=0){
    if(!node) return;
    for(int i=0;i<level;i++){
        cout<<"  ";
    }
    cout<<node->type<<"("<<node->value<<")"<<endl;
    printAST(node->left,level+1);
    printAST(node->right,level+1);
}

int main() {
    vector<Token> tokens={{"int",'i'},{"x",'i'},{"=",'o'},{"a",'i'},{"+",'o'},{"b",'i'},{";",'o'}};
    ASTNode* root = parseAssignmentNonRecursive(tokens);
    printAST(root);
}