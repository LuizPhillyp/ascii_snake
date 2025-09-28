#ifndef INPUT_H
#define INPUT_H

#include <unistd.h>
#include <termios.h>

struct termios original_attributes;

void setup_input(){

    /* Enable raw input mode 
    (do not wait for a new line 
    when reading from stdin) */

    struct termios attributes;
    tcgetattr(STDIN_FILENO, &attributes);
    original_attributes = attributes;

    /* Disable cannonical mode and echo*/
    attributes.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}


void restore_input(){
    /* Restore the original terminal attributes
    (so that the terminal doesnt break after the program ends)*/
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_attributes);
}

#endif
