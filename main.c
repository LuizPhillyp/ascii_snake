#include "input.h"
#include <unistd.h>
#include <string.h>

#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT 30

/* Assemble the display string into the display buffer 
and return its size*/
size_t assemble_display(char* display_buffer, char* screen){
   
    /*pointer to characters inside the string*/
    char* current_pointer = &display_buffer[0]; 
    
    /*first add the escape sequence to reset the terminal*/
    const char* reset_terminal = "\033[2J\033[H";
    size_t reset_length = strlen(reset_terminal);
    memcpy(current_pointer, reset_terminal, reset_length);
    current_pointer += reset_length;
 
    for(int row =0; row < SCREEN_HEIGHT; row++){

        /* assume screen is stored in row-major order*/
        char* current_screen_row = &screen[row*SCREEN_WIDTH];
        memcpy(current_pointer, current_screen_row, SCREEN_WIDTH); 
       
        /* skip the copied row, add the new line and increment one */
        current_pointer += SCREEN_WIDTH;
        *current_pointer++ = '\n';
    }
    
    /*size of the whole string*/
    return (size_t) (current_pointer - display_buffer);
}

/*Writes the display string buffer to the standard output
*/
void display_screen(char* screen){
    static char string_buffer[100 * 1024];
    size_t display_size = assemble_display(string_buffer, screen); 

    write(STDOUT_FILENO, string_buffer, display_size);
}

int main(void){
    /* init the screen with visible characters*/
    char screen[SCREEN_WIDTH * SCREEN_HEIGHT];
    memset(screen, 'O', sizeof(screen));

    display_screen(screen);

    return 0;
}
