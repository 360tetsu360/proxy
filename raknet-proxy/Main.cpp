#include <iostream>
#include "RaknetHandler.h"
int main() {
	RakNetHandler* server = new RakNetHandler();
	server->Initialize(19132, 10, "fuck");
}