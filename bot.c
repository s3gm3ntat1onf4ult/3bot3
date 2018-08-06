#include "bot.h"
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void attack_onthread(void*);

/*
	Connect to target_ip and send messages
	@param *bot_	bot pointer to attack
	@param times	the number of times to send msg to target_ip
*/

void attack_(void *bot_)
{
	bot *_bot = (bot*) bot_;

	struct addrinfo hints, *res;
	memset(&hints, 0,sizeof hints);

	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(_bot->target_ip, _bot->target_port, &hints, &res);

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    int status = connect(sockfd,res->ai_addr,res->ai_addrlen);

    if (status <= -1)
    {
    	printf("bot %d failed to connect to %s on port %s\n", _bot->id, _bot->target_ip, _bot->target_port);
    	return;
    }

	int t;
	for (t = 0; t < _bot->times; t++)
	{
		printf("bot %d being #%d attack\n", _bot->id, t);
		char *msg = "botnet test\r\n\r\n";
		send(sockfd, msg, strlen(msg), 0);
		printf("bot %d attacked\n", _bot->id);
	}

	close(sockfd);
	printf("\n* bot %d end of attack *\n", _bot->id);
}

/*
	Initialize the bot functions and attributes
	@param *bot_	bot to initialize
*/

void init_bot(bot *bot_)
{
	bot_->attack = &attack_;
	bot_->id = id_counter++;
	bot_->times = 1;
	bot_->init_bot_thread = &init_bot_thread_;
}

/*
	Create an array of bots of num_bots and return a pointer to array of bot
	@param num_bots	the number of bots to create
*/

bot* create_bots(int num_bots)
{
	bot *bots = (bot*) malloc(sizeof(bot) * num_bots);
	memset(bots, 0, sizeof bots); // set 0 to all bits

	int i = 0;
	for (; i < num_bots; i++)
		init_bot(&bots[i]);

	return bots;
}

void init_bot_thread_(void *func, void *bot_, void *args)
{
	bot *_bot = (bot*) bot_;
	int status = pthread_create(&_bot->bot_thread, NULL, (func != NULL) ? func : &attack_onthread, args);
}

void attack_onthread(void *bot_)
{
	bot *_bot = (bot*) bot_;
	_bot->attack(_bot);
}