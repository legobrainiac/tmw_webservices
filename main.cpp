// Copyright, Tomás António Sanches Pinto 2019
// g++ main.cpp -o tmw_webservices -lboost_filesystem -lboost_system -pthread -O3 -std=c++14
// sudo apt-get install libboost-all-dev

#include "crow.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#define KEY ""
#define VERSION_MAJOR 0
#define VERSION_MINOR 2

int main()
{
	std::cout << "TMW Webservices v" << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
	crow::SimpleApp app;
	
	auto cmdAll = [](std::string key, std::string cmd) -> crow::json::wvalue
	{
		crow::json::wvalue result;
		
		if(key != KEY) 
		{
			result["apiKey"] = "invalid";
			return result;
		}
		
		std::string cmdStr = "sudo sh servercommands_all.sh ";
		cmdStr += cmd;
		
		int i = system(cmdStr.c_str());
		
		result["apiKey"] = "valid";
		result["script_return"] = std::to_string(i);
		return result;
	};
	
	auto cmdSpecific = [](std::string key, int id, std::string cmd) -> crow::json::wvalue
	{
		crow::json::wvalue result;
		
		if(key != KEY) 
		{
			result["apiKey"] = "invalid";
			return result;
		}
		
		// After building the string, it should look something like this: 
		//  sudo sh servercommands.sh <id> <command>
		std::string cmdStr = "sudo sh servercommands.sh ";
		cmdStr += std::to_string(id);
		cmdStr += " ";
		cmdStr += cmd;
		
		int i = system(cmdStr.c_str());
		
		result["apiKey"] = "valid";
		result["script_return"] = std::to_string(i);
		return result;
	};
	
	CROW_ROUTE(app, "/<string>/all/<string>")(cmdAll);
	CROW_ROUTE(app, "/<string>/<int>/<string>")(cmdSpecific);
	
	app.port(8080).multithreaded().run();
}