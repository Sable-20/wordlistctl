#include <stdlib.h>
#include <ncurses.h>
#include <form.h>

#include "tui.h"
#include "download.h"
#include "config.h"

static void trim_whitespace(char *str)
{

    int len = strlen(str);

    while (len > 0 &&
           (str[len - 1] == ' ' ||
            str[len - 1] == '\n' ||
            str[len - 1] == '\t'))
    {

        str[len - 1] = '\0';
        len--;
    }
}

static void open_config_menu(config_t *cfg)
{
    FIELD *fields[3];
    FORM *form;
    WINDOW *win;

    int ch;

    fields[0] =
        new_field(
            1,
            40,
            2,
            18,
            0,
            0);

    fields[1] =
        new_field(
            1,
            40,
            4,
            18,
            0,
            0);

    fields[2] = NULL;

    /*
        field options
    */

    field_opts_off(
        fields[0],
        O_AUTOSKIP);

    field_opts_off(
        fields[1],
        O_AUTOSKIP);

    /*
        default values
    */

    set_field_buffer(
        fields[0],
        0,
        cfg->useragent);

    set_field_buffer(
        fields[1],
        0,
        cfg->download_path);

    /*
        form
    */

    form = new_form(fields);

    /*
        popup window
    */

    win = newwin(
        10,
        70,
        4,
        10);

    keypad(win, TRUE);

    set_form_win(form, win);

    set_form_sub(
        form,
        derwin(
            win,
            6,
            60,
            2,
            2));

    box(win, 0, 0);

    mvwprintw(
        win,
        1,
        2,
        "Configuration");

    mvwprintw(
        win,
        2,
        2,
        "User Agent:");

    mvwprintw(
        win,
        4,
        2,
        "Download Path:");

    post_form(form);

    wrefresh(win);

    /*
        input loop
    */

    while ((ch = wgetch(win)))
    {

        switch (ch)
        {

        case KEY_DOWN:

            form_driver(
                form,
                REQ_NEXT_FIELD);

            form_driver(
                form,
                REQ_END_LINE);

            break;

        case KEY_UP:

            form_driver(
                form,
                REQ_PREV_FIELD);

            form_driver(
                form,
                REQ_END_LINE);

            break;

        case KEY_BACKSPACE:
        case 127:

            form_driver(
                form,
                REQ_DEL_PREV);

            break;

        case 10:

            /*
                save config
            */

            form_driver(
                form,
                REQ_VALIDATION);

            snprintf(
                cfg->useragent,
                sizeof(cfg->useragent),
                "%s",
                field_buffer(fields[0], 0));

            snprintf(
                cfg->download_path,
                sizeof(cfg->download_path),
                "%s",
                field_buffer(fields[1], 0));

            trim_whitespace(cfg->useragent);
            trim_whitespace(cfg->download_path);

            unpost_form(form);

            free_form(form);

            free_field(fields[0]);

            free_field(fields[1]);

            delwin(win);

            return;

        default:

            form_driver(form, ch);

            break;
        }

        wrefresh(win);
    }
}

void start_tui(wordlist_t *table)
{

    initscr();
    nodelay(stdscr, FALSE);
    immedok(stdscr, TRUE);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_CYAN);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
    }

    int total = HASH_COUNT(table);

    wordlist_t **items =
        malloc(sizeof(wordlist_t *) * total);

    int i = 0;
    wordlist_t *wl;

    for (wl = table;
         wl != NULL;
         wl = wl->hh.next)
    {

        items[i++] = wl;
    }

    int selected = 0;
    int scroll = 0;
    int running = 1;

    config_t cfg = {
        .useragent =
            "wordlistctl/2.0",

        .download_path =
            "/tmp"};

    while (running)
    {

        int height, width;

        getmaxyx(stdscr,
                 height,
                 width);

        erase();

        WINDOW *list_win =
            newwin(height - 3,
                   width / 2,
                   0,
                   0);

        WINDOW *detail_win =
            newwin(height - 3,
                   width - width / 2,
                   0,
                   width / 2);

        WINDOW *status_win =
            newwin(3,
                   width,
                   height - 3,
                   0);

        box(list_win, 0, 0);
        box(detail_win, 0, 0);
        box(status_win, 0, 0);

        mvwprintw(list_win,
                  0,
                  2,
                  " WORDLISTS ");

        mvwprintw(detail_win,
                  0,
                  2,
                  " DETAILS ");

        int visible_rows =
            height - 5;

        if (selected < scroll)
            scroll = selected;

        if (selected >= scroll + visible_rows)
            scroll =
                selected -
                visible_rows +
                1;

        /*
            left panel
        */

        for (i = 0;
             i < visible_rows &&
             i + scroll < total;
             i++)
        {

            int idx =
                i + scroll;

            if (idx == selected)
                wattron(list_win,
                        COLOR_PAIR(1));
            mvwprintw(
                list_win,
                i + 1,
                2,
                "%s ",
                items[idx]->name);
            mvwprintw(
                list_win,
                i + 1,
                70,
                "[%s]",
                items[idx]->group);

            if (idx == selected)
                wattroff(list_win,
                         COLOR_PAIR(1));
        }

        /*
            right panel
        */

        wordlist_t *cur =
            items[selected];

        wattron(detail_win,
                COLOR_PAIR(2));

        mvwprintw(detail_win,
                  2,
                  2,
                  "Name");

        mvwprintw(detail_win,
                  4,
                  2,
                  "Group");

        mvwprintw(detail_win,
                  6,
                  2,
                  "Size");

        mvwprintw(detail_win,
                  8,
                  2,
                  "URL");

        wattroff(detail_win,
                 COLOR_PAIR(2));

        mvwprintw(detail_win,
                  2,
                  12,
                  "%s",
                  cur->name);

        mvwprintw(detail_win,
                  4,
                  12,
                  "%s",
                  cur->group);

        mvwprintw(detail_win,
                  6,
                  12,
                  "%s",
                  cur->size);

        mvwprintw(detail_win,
                  8,
                  12,
                  "%s",
                  cur->url);

        /*
            status
        */

        mvwprintw(status_win,
                  1,
                  2,
                  "Arrows move | q quit | i to install | %d items",
                  total);

        wrefresh(list_win);
        wrefresh(detail_win);
        wrefresh(status_win);

        refresh();

        int ch =
            getch();

        switch (ch)
        {

        case KEY_UP:

            if (selected > 0)
                selected--;

            break;

        case KEY_DOWN:

            if (selected < total - 1)
                selected++;

            break;

        case 'q':

            running = 0;
            break;
        case 'i':
            char output_path[1024];
            sprintf(output_path, "%s/%s.txt", cfg.download_path, cur->name);
            mvwprintw(
                status_win,
                1,
                2,
                "Downloading: %s",
                output_path);
            download_file(cur->url, output_path, cfg.useragent);
            running = 0;
            break;
        case 'c':
            open_config_menu(&cfg);
            break;
        }

        delwin(list_win);
        delwin(detail_win);
        delwin(status_win);
    }

    free(items);
    endwin();
}