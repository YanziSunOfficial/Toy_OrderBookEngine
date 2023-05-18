#include "Logger.h"

std::string currTime()
{
    char tmp[64];
    time_t ptime;
    time(&ptime);
    strftime(tmp,sizeof(tmp),"%Y-%m-%d %H:%M:%S",localtime(&ptime));
    return tmp;
}

Logger::Logger()
{
	this->target=terminal;
	this->level=debug;
	std::cout<<"[WELCOME] "<<__FILE__<<" "<<currTime()<<" : "<<"=== Start logging ==="<<std::endl; 
}

Logger::Logger(log_target target,log_level level,std::string path)
{
	this->target=target;
	this->path=path;
	this->level=level;
	std::string tmp="";
	std::string welcome_dialog=tmp+"[WELCOME] "+__FILE__+" "+currTime()+" : "+"=== Start logging ==="+"\n";
	if(target!=terminal)
	{
		this->outfile.open(path,std::ios::out | std::ios::app);
		this->outfile<<welcome_dialog;
	}	 
	if(target!=file) { std::cout<<welcome_dialog; }
}

void Logger::output(std::string text,log_level act_level)
{
	std::string prefix;  
	if(act_level==debug)         prefix="[DEBUG]    ";
	else if(act_level==info)     prefix="[INFO]    ";
	else if(act_level==warning)  prefix="[WARNING]    ";
	else if(act_level==error)    prefix="[ERROR]    ";
	else prefix="";
	prefix+=__FILE__;
	prefix+=" ";
	std::string output_content=prefix+currTime( )+" : "+text+" "+'\n';
	if(this->level<=act_level&&this->target!=file)  { std::cout<<output_content; }
	if(this->target!=terminal)  
    {    
        outfile<<output_content;
        this->outfile.flush();
    }
}

void Logger::DEBUG(std::string text)   { this->output(text,debug);   }
 
void Logger::INFO(std::string text)    { this->output(text,info);    }

void Logger::WARNING(std::string text) { this->output(text,warning); }

void Logger::ERROR(std::string text)   { this->output(text,error);   }