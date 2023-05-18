#ifndef ENGINE_H
#define ENGINE_H

#include "Book.h"
#include "Order.h"
#include "Logger.h"

class Engine
{
	public:
		void Update(Order& New_Order,int Level);
	private:
		Book Sell_Book;     // 卖簿
		Book Buy_Book;      // 买簿
		std::map<long long,Order> Id_Order;   // Order_ID ——> Order 用于撤单，由id可以得到该Order的Price,这样就可以进入Book类中的Order_List了
		long long num;
};

#endif