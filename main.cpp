#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <time.h>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Logger.h"
#include "Order.h"
#include "CreateOrder.h"
#include "Book.h"
#include "Engine.h"

#define LEVEL 5 // 5档

using namespace std::chrono;

enum log_level{debug,info,warning,error}; 
enum log_target{file,terminal,file_and_terminal};

long long num=-1;

int main()
{
	Logger logger(Logger::log_target::file_and_terminal,Logger::log_level::debug,"result.log");     // 日志信息
	std::ifstream input_file;	
	std::ofstream output_file;
	input_file.open("Input.txt",std::ios::in);
	output_file.open("Output.txt",std::ios::out);
	char str[1024];
	if(!input_file.is_open()) { logger.ERROR(" 未能成功打开输入文件 "); }
	else { logger.INFO(" 成功打开文件 ");}
	Engine orderbook;
	while(input_file.getline(str,sizeof(str)))           
	{
		Order New_Order=CreateOrder(str,++num);		// 逐行处理，构建订单
		orderbook.Update(New_Order,LEVEL);			// 新订单进入撮合引擎
	}
	input_file.close();
	output_file.close();
    return 0;
}


