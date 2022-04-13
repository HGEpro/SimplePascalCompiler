#pragma once

#include <vector>

enum TOKENS{
    // Keywords
    PROGRAM = 1,
    CONST,
    TYPE,
    ARRAY,
    OF,
    RECORD,
    BEGIN,
    END,
    FUNCTION,
    FORWARD,
    PROCEDURE,
    IF,
    THEN,
    ELSE,
    VAR,
    SET,
    IN,
    NOT,
    AND,
    OR,
    MOD,
    DIV,
    READ,
    WRITE,
    WITH,
    TO,
    FOR,

    // Types(Keywords)
    INTEGER,
    CHAR,
    REAL,
    BOOLEAN,

    // Type(not a keyword)
    STRING,

    TYPEDEF,

    // 1 long symbols
    SEMICOLON,
    COLON,
    SQUAREBRACKET_LEFT,
    SQUAREBRACKET_RIGHT,
    BRACKET_LEFT,
    BRACKET_RIGHT,
    KOMMA,
    DOT,
    EQUAL,

    // 2 long symbols
    DOUBLEDOT,
    WALRUS,

    // math operators
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    MODULO,

    // logic operators
    GREATER,
    LESS,
    GREATEREQUAL,
    LESSEQUAL,
    NOTEQUAL,

    IDENT,
    
    ENDOFFILE
};

enum TYPE_DEFINITIONS{
    INTEGER = 1,
    CHAR,
    REAL,
    BOOLEAN,
};

#define COMMENT_START '{'
#define COMMENT_END '}'

// static char* KEYWORDS[31] = {"program", "const", "type", "array",
//                              "of", "record", "begin", "end",
//                              "function", "forward", "procedure", "if",
//                              "then", "else", "var", ""}



struct Token{
    enum TOKENS token;
    char* data;
};

class Parser{
    private:
        unsigned long long position;
        char* data;
        unsigned long long size;
        char curChar;
    public:
        Parser(char* data, unsigned long long size){
            this->position = 0;
            this->data = data;
            this->size = size;
            if(size>0){
                this->curChar = data[0];
            }else{
                this->curChar = 0;
            }
        }
        std::vector<Token> parse(char*, unsigned long long);  
        void read_next();
        char peek_next();
        void skip_blank();
        void skip_comment();
        char parse_char();
};

