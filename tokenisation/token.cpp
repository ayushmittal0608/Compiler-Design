#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

enum class tokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SEMICOLON,
    END_OF_FILE
};

struct Token {
    tokenType type;
    string value;
};

bool isKeyword(const string& s){
    return s=="int" || s=="float" || s=="double" || s=="return" || s=="char";
}

vector<Token>tokenise(const string& code){
    vector<Token>tokens;
    int i=0;
    while(i<code.size()){
        char c=code[i];
        if(isspace(c)){
            i++;
            continue;
        }
        if(isdigit(c)){
            string num;
            while(i<code.size() && isdigit(code[i])){
                num+=code[i];
            }
            tokens.push_back({tokenType::NUMBER, num});
            continue;
        }
        if (isalpha(c) || c == '_') {
            string id;
            while (i < code.size() && (isalnum(code[i]) || code[i] == '_')) id += code[i++];
            if (isKeyword(id))
                tokens.push_back({tokenType::KEYWORD, id});
            else
                tokens.push_back({tokenType::IDENTIFIER, id});
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>') {
            tokens.push_back({tokenType::OPERATOR, string(1, c)});
            i++;
            continue;
        }
        if (c == ';') {
            tokens.push_back({tokenType::SEMICOLON, ";"});
            i++;
            continue;
        }
        i++;
    }
    tokens.push_back({tokenType::END_OF_FILE, ""});
    return tokens;
}

int main(){
    ifstream file("program.cpp");
    if(!file.is_open()){
        cerr<<"Cannot open file."<<endl;
        return 1;
    }
    stringstream buffer;
    buffer<<file.rdbuf();
    string code=buffer.str();

    auto tokens=tokenise(code);
    cout<<"Tokens: [ ";
    for (auto& t : tokens) { 
        switch(t.type) {
            case tokenType::KEYWORD: cout<<"KEYWORD"; break;
            case tokenType::IDENTIFIER: cout<<"IDENTIFIER"; break;
            case tokenType::NUMBER: cout<<"NUMBER"; break;
            case tokenType::OPERATOR: cout<<"OPERATOR"; break;
            case tokenType::SEMICOLON: cout<<"SEMICOLON"; break;
            case tokenType::END_OF_FILE: cout<<"EOF"; break;
        }
        cout<<" ";
    }
    cout<<"]";
    cout<<endl;
    return 0;
}