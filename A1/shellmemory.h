/*
 * shellmemory.h
 *
 *  Created on: Jan 18, 2020
 *      Author: sandr
 */

#ifndef SHELLMEMORY_H_
#define SHELLMEMORY_H_

typedef struct ShellMem {
	char* key;
	char* value;
} ShellMem;

extern ShellMem* shellMem[];
char* getValue (char*);
void setMem (char*, char*);


#endif /* SHELLMEMORY_H_ */
