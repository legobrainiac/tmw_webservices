// Copyright, Tomás António Sanches Pinto 2019
// g++ main.cpp -o tmw_webservices -lboost_filesystem -lboost_system -pthread -O3 -std=c++14
// sudo apt-get install libboost-all-dev

#include "crow.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#define KEY "" // Replace this with actual API key
#define VERSION_MAJOR 0
#define VERSION_MINOR 1

int main()
{
	std::cout << "TMW Webservices v" << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
	crow::SimpleApp app;
	
	auto cmdRt = [](std::string key, std::string cmd) -> crow::json::wvalue
	{
		crow::json::wvalue result;
		
		if(key != KEY) 
		{
			result["apiKey"] = "invalid";
			return result;
		}
		
		std::string cmdStr = "sudo sh ";
		cmdStr += cmd;
		cmdStr += ".sh";
		
		int i = system(cmdStr.c_str());
		
		result["apiKey"] = "valid";
		result["script_return"] = std::to_string(i);
		return result;
	};
	
	CROW_ROUTE(app, "/<string>/exec/<string>/")(cmdRt);
	
	app.port(8080).multithreaded().run();
}