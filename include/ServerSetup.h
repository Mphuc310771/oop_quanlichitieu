#pragma once
#include "../external/httplib.h"

using namespace httplib;

void ensureUsersFile();
void setupServer(Server &svr);
