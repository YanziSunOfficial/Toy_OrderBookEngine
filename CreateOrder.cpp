#include "CreateOrder.h"


Order CreateOrder(char* str,long long num)
{
	Logger logger(Logger::log_target::file_and_terminal,Logger::log_level::debug,"result.log");
	std::string str_User_Id,str_Order_Action;
	std::stringstream word(str);
	word>>str_User_Id;
	long long User_Id=atol(str_User_Id.c_str());
	word>>str_Order_Action;
	char Order_Action=str_Order_Action[0];
	switch (Order_Action)
	{
		case 'A':  // 下单
		{
			std::string str_Order_Type;
			word>>str_Order_Type;
			char Order_Type=str_Order_Type[0];
			switch (Order_Type)
			{
				case 'L':  // 限价
				{
					std::string str_Order_Direction,str_Price,str_Volumn;
					word>>str_Order_Direction;
					word>>str_Price;
					word>>str_Volumn;
					char Order_Direction=str_Order_Direction[0];
					double Price=stod(str_Price);
					long long Volumn=atol(str_Volumn.c_str());
					Order New_Order(User_Id,Order_Action,Order_Type,Order_Direction,Price,Volumn,num);
					return New_Order;
					break;
				}

				case 'M':  // 市价
				{
					std::string str_Order_Direction,str_Volumn;
					word>>str_Order_Direction;
					word>>str_Volumn;
					char Order_Direction=str_Order_Direction[0];
					long long Volumn=atol(str_Volumn.c_str());
					Order New_Order(User_Id,Order_Action,Order_Type,Order_Direction,-1,Volumn,num);
					return New_Order;
					break;					
				}

				default:
				{
					logger.ERROR( "Order_Type类型输入错误 ");
					break;
				}
			}
			break;
		}
		case 'R':  // 撤单
		{
			std::string str_Input_Id;
			word>>str_Input_Id;
			long long Input_Id=atol(str_Input_Id.c_str());
			Order New_Order(User_Id,Order_Action,'X','X',-1,-1,Input_Id);
			return New_Order;
			break;
		}
		default:
		{
			logger.ERROR( "Order_Action类型输入错误 ");
			break;
		}
	}
	Order Fail_Order(-1,'X','X','X',-1,-1,-1);
	return Fail_Order;
}






