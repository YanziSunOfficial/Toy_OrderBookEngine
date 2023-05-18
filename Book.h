#ifndef BOOK_H
#define BOOK_H

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
#include <vector>

#include "Order.h"

class Book
{
    public:
        std::map<double,std::map<long long,Order>> Order_List;   // 价格 ——> 同一价格不同时间 ——> 订单
        std::map<double,long long> Price_TotalVolumn;        // Price(价格) ——> 同一价格下的订单总数
        std::map<long long,Order> Id_Order;                  // Order_Id(订单编号) ——> Order(订单信息)
        
        void Order_Deal(Order& New_Order);             // 限价单的撮合
        void Order_Market_Deal(Order& New_Order);      // 市价单的撮合
        void Order_Add(Order& Left_Order);             // 若限价单有余量，则添加进订单簿
        void Order_Cancel(long long Order_Id);         // 撤单操作
        void Order_Print(char Book_Type,int Level);    // 订单簿打印
};


#endif