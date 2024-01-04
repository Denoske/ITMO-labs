#ifndef XML_USECASE_H
#define XML_USECASE_H

#include "crud_interface.h"
#include "server.h"

void manage(char xml_request[], FILE* file, int fd);

#endif //XML_USECASE_H
