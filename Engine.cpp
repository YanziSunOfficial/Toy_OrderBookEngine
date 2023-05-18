#include "Engine.h"

void Engine::Update(Order& New_Order,int Level)
{
	Logger logger(Logger::log_target::file_and_terminal,Logger::log_level::debug,"result.log");
	if( New_Order.Order_Action!='R') this->Id_Order[New_Order.Order_Id]=New_Order;
	switch (New_Order.Order_Action)
	{
		case 'A': 
		{
			switch (New_Order.Order_Type)
			{
				case 'L': 
				{
					switch (New_Order.Order_Direction)
					{
						case 'B': 
						{
							this->Sell_Book.Order_Deal(New_Order);
							this->Buy_Book.Order_Add(New_Order);
							break;
						}
						case 'A': 
						{
							this->Buy_Book.Order_Deal(New_Order);
							this->Sell_Book.Order_Add(New_Order);    
							break;                            
						}
						default:
						{
							logger.ERROR( "Order_Direction类型输入错误 ");
							break;                                
						}
					}
					break;
				}
				case 'M':   
				{
					switch (New_Order.Order_Direction)
					{
						case 'B':
						{
							this->Sell_Book.Order_Market_Deal(New_Order);
							break;
						}
						case 'A':
						{
							this->Buy_Book.Order_Market_Deal(New_Order);
							break;
						}
						default:
						{
							logger.ERROR( "Order_Direction类型输入错误 ");
							break;                                
						}
					}
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
		case 'R':
		{
			std::cout<<std::endl<<" ==== 撤单成功 ===="<<std::endl;
			switch (this->Id_Order[New_Order.Order_Id].Order_Direction)
			{
				case 'B':
				{                          
					this->Buy_Book.Price_TotalVolumn[Buy_Book.Id_Order[New_Order.Order_Id].Price]-=Buy_Book.Id_Order[New_Order.Order_Id].Volumn; 
					this->Buy_Book.Order_Cancel(New_Order.Order_Id);
					break;
				}
				case 'A':
				{
					this->Sell_Book.Price_TotalVolumn[Sell_Book.Id_Order[New_Order.Order_Id].Price]-=Sell_Book.Id_Order[New_Order.Order_Id].Volumn; 
					this->Sell_Book.Order_Cancel(New_Order.Order_Id);
					break;
				}
				default:
				{
					logger.ERROR( "Order_Direction类型输入错误 ");
					break;                        
				}
			}
			break;
		}
		default:
		{
			logger.ERROR( "Order_Action类型输入错误 ");
			break;                    
		}
	}     
	this->Buy_Book.Order_Print('B',Level);
	this->Sell_Book.Order_Print('S',Level);
	std::cout<<std::endl<<"----- end of the book -----"<<std::endl;
}

