#ifndef TUI_H_
#define TUI_H_

#include "file.h"

/**
 * Starts the terminal user interface (TUI) for managing and downloading wordlists. This function initializes the ncurses library, sets up the TUI layout, and handles user input for navigating through the list of wordlists, viewing details, and initiating downloads. The TUI displays a list of available wordlists on the left panel and shows detailed information about the selected wordlist on the right panel. Users can navigate using arrow keys and trigger downloads by pressing 'i'. The function continues to run until the user decides to quit by pressing 'q'.
 * 
 * @param table A pointer to the hash table of wordlist entries to be displayed in the TUI
 */
void start_tui(wordlist_t *table);

#endif // TUI_H_