#ifndef CALL_STACK_H_
#define CALL_STACK_H_

#include "common.h"

typedef struct{
    w_word          all_size;
    w_stack_entry   current;
    w_stack_entry   last_error;   
}w_stack_state;

typedef struct _w_call_entry{
    w_word          string;
    w_word          filename[40];
    w_word          callname[40];
    _w_call_entry*  next;
    _w_call_entry*  prev;    
}w_call_entry;

typedef struct{
    w_word          count;
    w_call_entry*   call_head;
    w_call_entry*   call_end;    
}w_stack_entry;

#endif /*CALL_STACK_H_*/
