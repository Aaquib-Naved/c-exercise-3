/*
 * eval.cpp
 *
 *  Created on: 5 Mar 2017
 *      Author: aaquibnaved
 */
#include <string>
using namespace std;
#include "evalobj.h"

int getValue(string *var, env *list) {
    env *current = list;

    if(current == NULL) {
        return 0;
    }

    if(current->var == *var) {
        return current->value;
    }

    getValue(var, current->next);
    return 0;
};

int prepend(struct env **list, int n, string *x) {
    struct env *current = *list;
    if (*list == NULL) {
        (*list) = new struct env;
        (*list)->value = n;
        (*list)->var = *x;
        (*list)->next = NULL;
        return 0;
    }

    struct env *head = new struct env;

    head->next = current;
    head->value = n;
    head->var = *x;

    *list = head;

    return 0;
}

int sum(ExpList *list, struct env *env) {
    if(list) {
       return list->head->eval(env) + sum(list->tail, env);
    }
    else {
        return 0;
    }
}

int mult(ExpList *list, struct env *env) {
    if(list) {
        return list->head->eval(env) * mult(list->tail, env);
    }
    else {
        return 1;
    }
}

int Constant::eval(env *e) {
	return n;
}

int Var::eval(env *e) {
	return getValue(&this->name, e);
}

int Let::eval(env *e) {
	prepend(&e, bexp->eval(e), &bvar);
	return body->eval(e);
}

int OpApp::eval(env *e) {
	switch(this->op) {
		case(plusop):
			return sum(this->args, e);
		case(timesop):
			return mult(this->args, e);
		default:
			return 0;
	}
}





