#include "lexer.hpp"
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define BLANK_SYMBOLS_AMOUNT 4
const char* BLANK_SYMBOLS = " \n\r\t";


bool is_blank(char symbol){
    for (char* ch=(char*)BLANK_SYMBOLS;
            ch<BLANK_SYMBOLS+BLANK_SYMBOLS_AMOUNT;ch++){
        
        if(*ch == symbol){
            return true;
        }
    }
    return false;
}

bool Parser::match_str(char* expected){
    int len = strlen(expected);
    for (int i=0;i<len;i++){
        if(curChar != expected[i]){
            return false;
        }
        read_next(); //idk if this is ok as it's consumed...
    }
    return true;
}

Token Parser::is_keyword(char* str, unsigned long long size){
    Token to_return;
    to_return.data = 0;
    switch(size){
        case 9:
            // procedure
            if (match_str("procedure")){
                to_return.token = PROCEDURE;
                break;
            }

        case 8:
            // function
            if (match_str("function")){
                to_return.token = FUNCTION;
                break;
            }

        case 7:
            // program, forward, integer, boolean
            if (match_str("program")){
                to_return.token = PROGRAM;
                break;
            }
            if (match_str("forward")){
                to_return.token = FORWARD;
                break;
            }
            if (match_str("integer")){
                to_return.token = TYPEDEF;
                to_return.data = (char*)TYPE_DEFINITIONS::INTEGER;
                break;
            }
            if (match_str("boolean")){
                to_return.token = TYPEDEF;
                to_return.data = (char*)TYPE_DEFINITIONS::BOOLEAN;
                break;
            }

        case 6:
            // record
            if (match_str("record")){
                to_return.token = RECORD;
                break;
            }

        case 5:
            // const, array, begin, write
            if (match_str("const")){
                to_return.token = CONST;
                break;
            }
            if (match_str("array")){
                to_return.token = ARRAY;
                break;
            }
            if (match_str("begin")){
                to_return.token = BEGIN;
                break;
            }
            if (match_str("write")){
                to_return.token = WRITE;
                break;
            }
            
        case 4:
            // type, then, else, read, with, char, real
            if (match_str("type")){
                to_return.token = TYPE;
                break;
            }
            if (match_str("then")){
                to_return.token = THEN;
                break;
            }
            if (match_str("else")){
                to_return.token = ELSE;
                break;
            }
            if (match_str("read")){
                to_return.token = READ;
                break;
            }
            if (match_str("with")){
                to_return.token = WITH;
                break;
            }
            if (match_str("char")){
                to_return.token = TYPEDEF;
                to_return.data = (char*)TYPE_DEFINITIONS::CHAR;
                break;
            }
            if (match_str("real")){
                to_return.token = TYPEDEF;
                to_return.data = (char*)TYPE_DEFINITIONS::REAL;
                break;
            }
        
        case 3:
            // end, var, set, not, and, mod, div, for
            if (match_str("end")){
                to_return.token = END;
                break;
            }
            if (match_str("var")){
                to_return.token = VAR;
                break;
            }
            if (match_str("set")){
                to_return.token = SET;
                break;
            }
            if (match_str("not")){
                to_return.token = NOT;
                break;
            }
            if (match_str("and")){
                to_return.token = AND;
                break;
            }
            if (match_str("mod")){
                to_return.token = MOD;
                break;
            }
            if (match_str("div")){
                to_return.token = DIV;
                break;
            }
            if (match_str("for")){
                to_return.token = FOR;
                break;
            }

        case 2:
            // of, if, in, or, to
            if (match_str("of")){
                to_return.token = OF;
                break;
            }
            if (match_str("if")){
                to_return.token = IF;
                break;
            }
            if (match_str("in")){
                to_return.token = IN;
                break;
            }
            if (match_str("or")){
                to_return.token = OR;
                break;
            }
            if (match_str("to")){
                to_return.token = TO;
                break;
            }

        default:
            to_return.token = IDENT;
            to_return.data = (char*)malloc(size+1);
            memcpy(to_return.data,str,size+1);
            break;
            
    }

    return to_return;
}

void error(char* text){
    std::cout << text << std::endl; 
    exit(EXIT_FAILURE);
}


char Parser::peek_next(){
    if(this->size - this->position == 1){
        return '\0';
    }
    return this->data[this->position+1];
}

void Parser::read_next(){
    this->position += 1;
    if(this->size == this->position){
        this->curChar = '\0';
        return;
    }

    this->curChar = this->data[this->position];
    return; 
}

void Parser::skip_blank(){
    while(is_blank(this->curChar)){
        this->read_next();
    }
}

void Parser::skip_comment(){

    while(this->curChar != COMMENT_END){
        this->read_next();
        if(curChar == 0){
            error("Comment was never closed");
        }
    }

    this->read_next();
}

char Parser::parse_char(){
    if(this->curChar == '\\'){
        this->read_next();
        switch(this->curChar){
            case '\\':
                return '\\';
            case 'n':
                return '\n';
            case 'r':
                return '\r';
            case 't':
                return '\t';
            case '\'':
                return '\'';
            case '\"':
                return '\"';
            case '\n':
                //this->read_next();
                return 0;
            default:
                error("Unexpected char after '\\'");
        }
    }
    return this->curChar;
}


std::vector<Token> Parser::parse(char*, unsigned long long){
    std::vector<Token> to_return;
    while(this->position < this->size){
        this->skip_blank();
        this->skip_comment();

        switch(this->curChar){
            case COMMENT_START:
                skip_comment();
            case '+':
                Token to_push;
                to_push.token = PLUS;
                to_return.push_back(to_push);
            case '-':
                Token to_push;
                to_push.token = MINUS;
                to_return.push_back(to_push);
            case '*':
                Token to_push;
                to_push.token = ASTERISK;
                to_return.push_back(to_push);
            case '/':
                Token to_push;
                to_push.token = SLASH;
                to_return.push_back(to_push);
            case '%':
                Token to_push;
                to_push.token = MODULO;
                to_return.push_back(to_push);
            case '>':
                Token to_push;
                if(this->peek_next() == '='){
                    to_push.token = GREATEREQUAL;
                    this->read_next();
                }else{
                    to_push.token = GREATER;
                }
                to_return.push_back(to_push);
            case '<':
                Token to_push;
                if(this->peek_next() == '='){
                    to_push.token = LESSEQUAL;
                    this->read_next();
                }else if(this->peek_next() == '>'){
                    to_push.token = NOTEQUAL;
                }else{
                    to_push.token = LESS;
                }
                to_return.push_back(to_push);         
            case ';':
                Token to_push;
                to_push.token = SEMICOLON;
                to_return.push_back(to_push);
            case ':':
                Token to_push;
                to_push.token = COLON;
                to_return.push_back(to_push);
            case '[':
                Token to_push;
                to_push.token = SQUAREBRACKET_LEFT;
                to_return.push_back(to_push);
            case ']':
                Token to_push;
                to_push.token = SQUAREBRACKET_RIGHT;
                to_return.push_back(to_push);
            case '(':
                Token to_push;
                to_push.token = BRACKET_LEFT;
                to_return.push_back(to_push);
            case ')':
                Token to_push;
                to_push.token = BRACKET_RIGHT;
                to_return.push_back(to_push);
            case ',':
                Token to_push;
                to_push.token = KOMMA;
                to_return.push_back(to_push);
            case '.':
                Token to_push;
                if(this->peek_next() == '.'){
                    to_push.token = DOUBLEDOT;
                }else{
                    to_push.token = DOT;
                }
                to_return.push_back(to_push);
            case '=':
                Token to_push;
                if(this->peek_next() == ':'){
                    to_push.token = WALRUS;
                }else{
                    to_push.token = EQUAL;
                }
                to_return.push_back(to_push);
            case '\0':
                Token to_push;
                to_push.token = TOKENS::ENDOFFILE;
                to_return.push_back(to_push);
            case '\'':
                this->read_next();
                Token to_push;
                char ch = this->parse_char();

                to_push.token = TOKENS::CHAR;
                to_push.data = (char*)ch;

                this->read_next();
                if(this->curChar != '\''){
                    error("char was never closed with '");
                }

                to_return.push_back(to_push);
            case '"':
                Token to_push;
                std::vector<char> string;

                this->read_next();
                while(this->curChar != '"'){
                    if(this->curChar == 0){
                        error("String was never closed with \"");
                    }
                    char ch = this->parse_char();
                    if(ch != 0){
                        string.push_back(ch);
                    }
                    this->read_next();
                }
                string.push_back(0);
            case

        }
    }
}
       
