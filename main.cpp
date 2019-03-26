// Copyright, Tomás António Sanches Pinto 2019
// g++ main.cpp -lboost_filesystem -lboost_system -pthread -O3 -std=c++14

#include "crow.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#define KEY "tmw159"

int main()
{
	crow::SimpleApp app;
	
	auto cmdRt = [](std::string key, std::string cmd) 
	{
		if(key != KEY) return crow::response(400);
		
		std::string cmdStr = "sudo sh ";
		cmdStr += cmd;
		cmdStr += ".sh";
		
		int i = system(cmdStr.c_str());
		return crow::response("Shell script called!");
	};
	
	CROW_ROUTE(app, "/<string>/exec/<string>/")(cmdRt);
	
	app.port(8080).multithreaded().run();
}

