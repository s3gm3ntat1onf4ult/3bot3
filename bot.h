#ifndef BOT_H
#define BOT_H

#include <pthread.h>

static int id_counter = 1000;

/*
	This struct define the bot
	@attr bot_thread	thread
	@attr id	a number that identifies the bot
	@attr target_ip, target_port	server ip and port to connect
*/
typedef struct
{
	// attrs
	pthread_t bot_thread;
	int id;
	char *target_ip, *target_port;
	
	// attack attrs
	int times;
	
	// funcs
	void (*attack)(void*);
	void (*init_bot_thread)(void *func, void* thiz, void *args);

}bot;

void init_bot(bot*);
bot* create_bots(int);
void attack_(void*);
void init_bot_thread_(void*, void*, void*);

#endif