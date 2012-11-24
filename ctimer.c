#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <ncurses.h>

void init_curses()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, FALSE);
    curs_set(0);
}

void end_curses()
{
    flushinp();
    erase();
    refresh();
    endwin();
}

void gpause()
{
	while (1) {
		int c = getchar();
		if (c == 'p' || c == 'P')
			break;
	}
	erase();
	refresh();
}

int main()
{
	int key = 0;
	unsigned long int h = 0;	// hours
	unsigned long int m = 0;	// minutes
	unsigned long int s = 0;	// seconds
	unsigned long int ms = 0;	// milliseconds

	unsigned long int s1, s2;

	char str[80];

	init_curses();

	struct timeval tv;

	strcpy(str, "Press <Enter> to start timer\nHit <Esc> to quit");

	mvprintw(0, 0, str);
	while (1) {
		key = getch();

		if (key == 'q' || key == 27)
		{
			strcpy(str, "bye");
			goto end;
		}
		else if (key == 10)
			break;
	}

	gettimeofday(&tv, NULL);
	s1 = tv.tv_sec;

	while (1)
	{
		gettimeofday(&tv, NULL);
		s2 = tv.tv_sec;

		ms = tv.tv_usec / 1000;

		s = s2 - s1;

		sprintf(str,
			"\n%ld : %ld : %ld : %ld\n",
			 h,    m,    s,    ms);

		refresh();
		mvprintw(0, 0, str);


		if (s == 60)
		{
			gettimeofday(&tv, NULL);
			s1 = tv.tv_sec;

			m++;
			if (m == 60) {
				m = 0;
				h++;
			}
		}

		key = getch();

		if (key == 'q' || key == 27)
			break;
	}

end:
	end_curses();

	puts(str);

	return 0;
}
