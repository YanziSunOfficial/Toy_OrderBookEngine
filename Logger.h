#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <iomanip>
#include <string.h>
#include <chrono>
#include <map>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

class Logger
{
	public:
		enum log_level{debug,info,warning,error};		        // 日志等级
		enum log_target{file,terminal,file_and_terminal};       // 日志输出目标
	private:
		std::ofstream outfile; 	// 将日志输出到文件的流对象
		log_target target; 		// 日志文件输出目标
		std::string path;		// 日志文件路径
		log_level level;		// 日志等级
		void output(std::string text,log_level act_level);		// 输出行为
	public:
		Logger();	
		Logger(log_target target,log_level level,std::string path);
        ~Logger(){ this->outfile.flush();}
		void DEBUG(std::string text);
		void INFO(std::string text);
		void WARNING(std::string text);
		void ERROR(std::string text);
};

#endif