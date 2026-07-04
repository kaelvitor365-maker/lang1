#include "lexer.h"

Vector* Lexer__Tokenize(Lexer* this){
    Vector* arr = newVector();
    arr->__init__(arr, sizeof(Token*));
    Token* token;

    do{
        token = Lexer__LexerNext(this);
        arr = appendVector(arr, &token);
    }while(token->type != TOKEN_EOF);

    this = freeLexer(this);
    return arr;
}


Vector* Lexer__TransformTokens(Vector* this){
    Vector* arr = newVector();
    arr->__init__(arr, this->__size_value);

    for(size_t _i = 0; _i < len(this); ++_i){
        Token* token = *CAST_TO(Token**, getVector(this, _i));

        if(token->type == TOKEN_EOF){ // EOF
            arr = appendVector(arr, &token);
            break;
        }

        Token* nextToken = *CAST_TO(Token**, getVector(this, _i+1));

        if(token->type == TOKEN_AND){ // &
            if(nextToken->type == TOKEN_AND){ // &&
                token->type = TOKEN_ANDAND;
                token->word[1] = '&';
                token->word[2] = '\0';
                ++_i;
                free(nextToken);
            }
            goto append_token;
        }

        if(token->type == TOKEN_OR){ // |
            if(nextToken->type == TOKEN_OR){ //
                token->type = TOKEN_OROR;
                token->word[1] = '|';
                token->word[2] = '\0';
                ++_i;
                free(nextToken);
            }
            goto append_token;
        }

        if(token->type == TOKEN_EQUAL){ // =
            if(nextToken->type == TOKEN_EQUAL){ // ==
                token->type = TOKEN_EQEQ;
                token->word[1] = '=';
                token->word[2] = '\0';
                ++_i;
                free(nextToken);
            }
            goto append_token;
        }

        if(token->type == TOKEN_GT){ // >
            if(nextToken->type == TOKEN_EQUAL){ // >=
                token->type = TOKEN_GTEQ;
                token->word[1] = '=';
                token->word[2] = '\0';
                ++_i;
                free(nextToken);
                goto append_token;
            }
            if(nextToken->type == TOKEN_GT){ // >>
                token->type = TOKEN_RSHIFT;
                token->word[1] = '>';
                token->word[2] = '\0';
            }
            if(nextToken->type == TOKEN_EOF){
                goto append_token;
            }

            Token* nextNextToken = *CAST_TO(Token**, getVector(this, _i+2));
            if(nextNextToken->type == TOKEN_EQUAL){ // >>=
                token->type = TOKEN_RSHIFTEQ;
                token->word[2] = '=';
                token->word[3] = '\0';
                _i += 2;
                free(nextToken);
                free(nextNextToken);
                goto append_token;
            }


            ++_i;
            free(nextToken);
            goto append_token;
        }

        if(token->type == TOKEN_LT){ // <
            if(nextToken->type == TOKEN_EQUAL){ // <=
                token->type = TOKEN_LTEQ;
                token->word[1] = '=';
                token->word[2] = '\0';
                ++_i;
                free(nextToken);
                goto append_token;
            }
            if(nextToken->type == TOKEN_LT){ // <<
                token->type = TOKEN_LSHIFT;
                token->word[1] = '<';
                token->word[2] = '\0';
            }
            if(nextToken->type == TOKEN_EOF){
                goto append_token;
            }

            Token* nextNextToken = *CAST_TO(Token**, getVector(this, _i+2));
            if(nextNextToken->type == TOKEN_EQUAL){ // <<=
                token->type = TOKEN_LSHIFTEQ;
                token->word[2] = '=';
                token->word[3] = '\0';
                _i += 2;
                free(nextToken);
                free(nextNextToken);
                goto append_token;
            }


            ++_i;
            free(nextToken);
            goto append_token;
        }

        if(token->type == TOKEN_NOT){ // !
            if(nextToken->type == TOKEN_EQUAL){ // !=
                token->type = TOKEN_NOTEQ;
                token->word[1] = '=';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;
            }
            goto append_token;
        }

        if(token->type == TOKEN_PLUS){ // +
            if(nextToken->type == TOKEN_PLUS){ // ++
                token->type = TOKEN_INC;
                token->word[1] = '+';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token;           
            }
            if(nextToken->type == TOKEN_EQUAL){ // +=
                token->type = TOKEN_PLUSEQ;
                token->word[1] = '=';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token; 
            }
        }

        if(token->type == TOKEN_MINUS){ // -
            if(nextToken->type == TOKEN_MINUS){ // --
                token->type = TOKEN_DEC;
                token->word[1] = '-';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token;           
            }
            if(nextToken->type == TOKEN_EQUAL){ // -=
                token->type = TOKEN_MINUSEQ;
                token->word[1] = '=';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token; 
            }
        }

        if(token->type == TOKEN_MUL){ // *
            if(nextToken->type == TOKEN_EQUAL){ // *=
                token->type = TOKEN_MULEQ;
                token->word[1] = '=';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token; 
            }
            if(nextToken->type == TOKEN_DIV){ // */
                token->type = TOKEN_ENDCOMMENTMULTLINE;
                token->word[1] = '/';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token; 
            }
        }

        if(token->type == TOKEN_DIV){ // *
            if(nextToken->type == TOKEN_EQUAL){ // /=
                token->type = TOKEN_DIVEQ;
                token->word[1] = '=';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token; 
            }
            if(nextToken->type == TOKEN_DIV){ // //
                token->type = TOKEN_COMMENTLINE;
                token->word[1] = '/';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token; 
            }
            if(nextToken->type == TOKEN_MUL){ // /*
                token->type = TOKEN_BEGINCOMMENTMULTLINE;
                token->word[1] = '*';
                token->word[2] = '\0';
                free(nextToken);
                ++_i;    
                goto append_token; 
            }
        }

        
append_token:
        arr = appendVector(arr, &token);
    }

    freeVector(this);
    this = NULL;
    return arr;
}

