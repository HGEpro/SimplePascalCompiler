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

Token is_keyword(char* str,unsigned long long size){
    Token to_return;
    to_return.data = 0;
    switch(size){
        case 9:
            // procedure
            if (str[0] == 'p' &&
                    str[1] == 'r' &&
                    str[2] == 'o' &&
                    str[3] == 'c' &&
                    str[4] == 'e' &&
                    str[5] == 'd' &&
                    str[6] == 'u' &&
                    str[7] == 'r' &&
                    str[8] == 'e'){
                to_return.token = PROCEDURE;
                break;
            }

        case 8:
            // function
            if (str[0] == 'f' &&
                    str[1] == 'u' &&
                    str[2] == 'n' &&
                    str[3] == 'c' &&
                    str[4] == 't' &&
                    str[5] == 'i' &&
                    str[6] == 'o' &&
                    str[7] == 'n'){
                to_return.token = FUNCTION;
                break;
            }

        case 7:
            // program, forward, integer, boolean
            if (str[0] == 'p' &&
                    str[1] == 'r' &&
                    str[2] == 'o' &&
                    str[3] == 'g' &&
                    str[4] == 'r' &&
                    str[5] == 'a' &&
                    str[6] == 'm'){
                to_return.token = PROGRAM;
                break;
            }
            if (str[0] == 'f' &&
                    str[1] == 'o' &&
                    str[2] == 'r' &&
                    str[3] == 'w' &&
                    str[4] == 'a' &&
                    str[5] == 'r' &&
                    str[6] == 'd'){
                to_return.token = FORWARD;
                break;
            }
            if (str[0] == 'i' &&
                    str[1] == 'n' &&
                    str[2] == 't' &&
                    str[3] == 'e' &&
                    str[4] == 'g' &&
                    str[5] == 'e' &&
                    str[6] == 'r'){
                to_return.token = TYPEDEF;
                to_return.data = (char*)TYPE_DEFINITIONS::INTEGER;
                break;
            }
            if (str[0] == 'b' &&
                    str[1] == 'o' &&
                    str[2] == 'o' &&
                    str[3] == 'l' &&
                    str[4] == 'e' &&
                    str[5] == 'a' &&
                    str[6] == 'n'){
                to_return.token = TYPEDEF;
                to_return.data = (char*)TYPE_DEFINITIONS::BOOLEAN;
                break;
            }

        case 6:
            // record
            if (str[0] == 'r' &&
                    str[1] == 'e' &&
                    str[2] == 'c' &&
                    str[3] == 'o' &&
                    str[4] == 'r' &&
                    str[5] == 'd'){
                to_return.token = RECORD;
                break;
            }

        case 5:
            // const, array, begin, write
            if (str[0] == 'c' &&
                    str[1] == 'o' &&
                    str[2] == 'n' &&
                    str[3] == 's' &&
                    str[4] == 't'){
                to_return.token = CONST;
                break;
            }
            if (str[0] == 'a' &&
                    str[1] == 'r' &&
                    str[2] == 'r' &&
                    str[3] == 'a' &&
                    str[4] == 'y'){
                to_return.token = ARRAY;
                break;
            }
            if (str[0] == 'b' &&
                    str[1] == 'e' &&
                    str[2] == 'g' &&
                    str[3] == 'i' &&
                    str[4] == 'n'){
                to_return.token = BEGIN;
                break;
            }
            if (str[0] == 'w' &&
                    str[1] == 'r' &&
                    str[2] == 'i' &&
                    str[3] == 't' &&
                    str[4] == 'e'){
                to_return.token = BEGIN;
                break;
            }
            
        case 4:
            // type, then, else, read, with, char, real
            if (str[0] == 't' &&
                    str[1] == 'y' &&
                    str[2] == 'p' &&
                    str[3] == 'e'){
                to_return.token = TYPE;
                break;
            }
            if (str[0] == 't' &&
                    str[1] == 'h' &&
                    str[2] == 'e' &&
                    str[3] == 'n'){
                to_return.token = THEN;
                break;
            }
            if (str[0] == 'e' &&
                    str[1] == 'l' &&
                    str[2] == 's' &&
                    str[3] == 'e'){
                to_return.token = ELSE;
                break;
            }
            if (str[0] == 'r' &&
                    str[1] == 'e' &&
                    str[2] == 'a' &&
                    str[3] == 'd'){
                to_return.token = READ;
                break;
            }
            if (str[0] == 'w' &&
                    str[1] == 'i' &&
                    str[2] == 't' &&
                    str[3] == 'h'){
                to_return.token = WITH;
                break;
            }
            if (str[0] == 'c' &&
                    str[1] == 'h' &&
                    str[2] == 'a' &&
                    str[3] == 'r'){
                to_return.token = TYPEDEF;
                to_return.data = (char*)TYPE_DEFINITIONS::CHAR;
                break;
            }
            if (str[0] == 'r' &&
                    str[1] == 'e' &&
                    str[2] == 'a' &&
                    str[3] == 'l'){
                to_return.token = TYPEDEF;
                to_return.data = (char*)TYPE_DEFINITIONS::REAL;
                break;
            }
        
        case 3:
            // end, var, set, not, and, mod, div, for
            if (str[0] == 'e' &&
                    str[1] == 'n' &&
                    str[2] == 'd'){
                to_return.token = END;
                break;
            }
            if (str[0] == 'v' &&
                    str[1] == 'a' &&
                    str[2] == 'r'){
                to_return.token = VAR;
                break;
            }
            if (str[0] == 's' &&
                    str[1] == 'e' &&
                    str[2] == 't'){
                to_return.token = SET;
                break;
            }
            if (str[0] == 'n' &&
                    str[1] == 'o' &&
                    str[2] == 't'){
                to_return.token = END;
                break;
            }
            if (str[0] == 'a' &&
                    str[1] == 'n' &&
                    str[2] == 'd'){
                to_return.token = AND;
                break;
            }
            if (str[0] == 'm' &&
                    str[1] == 'o' &&
                    str[2] == 'd'){
                to_return.token = MOD;
                break;
            }
            if (str[0] == 'd' &&
                    str[1] == 'i' &&
                    str[2] == 'v'){
                to_return.token = DIV;
                break;
            }
            if (str[0] == 'f' &&
                    str[1] == 'o' &&
                    str[2] == 'r'){
                to_return.token = FOR;
                break;
            }

        case 2:
            // of, if, in, or, to
            if (str[0] == 'o' &&
                    str[1] == 'f'){
                to_return.token = OF;
                break;
            }
            if (str[0] == 'i' &&
                    str[1] == 'f'){
                to_return.token = IF;
                break;
            }
            if (str[0] == 'i' &&
                    str[1] == 'n'){
                to_return.token = IN;
                break;
            }
            if (str[0] == 'o' &&
                    str[1] == 'r'){
                to_return.token = OR;
                break;
            }
            if (str[0] == 't' &&
                    str[1] == 'o'){
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