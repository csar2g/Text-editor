#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>


struct termios original_att;

/* *
 *
 * TERMINAL MODES
 *
 * */

void disableRawMode(){
	//set original attributes of terminal
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_att);	
}

void enableRawMode(){
	
	tcgetattr(STDIN_FILENO, &original_att);
	atexit(disableRawMode);

	struct termios raw = original_att;
	
	//Disable standard terminal functions 
	raw.c_iflag &= ~(IXON | ICRNL); //CTRL + S and CRTL + Q, CTLR + M
	raw.c_oflag &= ~(OPOST); //OUTPUT processing (\r, \n)
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); //Echoing function, CTRL + C , CTRL + Z, CTRL + V

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main(int argc, char *argv[])
{
	//Clear terminal / compatibility with winows and unix type systems
	#ifdef _WIN32
		system("cls");
	#else 	
		system("clear");
	#endif
	
	enableRawMode();
	char c;
	while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q' ); //Read characters in console / quit program when "q" is pressed
	{
		if(iscntrl(c)){
			printf("%d \r \n", c);
		}else{
			printf("");
		}

	}
	return 0;
}
