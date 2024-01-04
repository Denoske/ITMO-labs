#ifndef XML_CLIENT_H
#define XML_CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>

#include "inet.h"

void sendRequest(int port, int str_len, char request[]);

#endif //XML_CLIENT_H
