/**
 * @file tests-structures.cpp
 *
 * @date 17 juin 2014
 * @author bbfh
 *
 * @section description description
 * description du contenu du fichier
 */

#include <iostream>
#include <string>
#include <stdio.h>

#include "simple-queue.h"
#define __with_threads
#include "lockable.h"

using namespace std;

SimpleQueue<string> queue;

void add_string(void) {
    static int cpt = 0;
    char buffer[128];

    sprintf(buffer, "ligne %d", cpt++);
    queue.push(new string(buffer));
}

int main (int argc, char **argv) {
    queue =  SimpleQueue<string>();

    for (int i=0; i<256; i++) {
        add_string();
    }
    string *str = queue.pop();
    while (str != NULL) {
        cout << str->c_str() << endl;
        str = queue.pop();
    }
#if defined(__WATCOMC__)
    getchar();
#endif
}

