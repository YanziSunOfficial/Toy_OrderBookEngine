#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <iomanip>
#include <string.h>
#include <chrono>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std::chrono;

struct Time_Print { int year_,month_,day_,hour_,mintue_,second_;long long millisecond_; };


// User_Id: 其实对程序没有影响，后续想法是会构建一个用户类，就需要用上
// Order_Action:     A(Add:下单)    R(Reduce:撤单)
// Order_Type:       L(Limit:限价)  M(Market:市价)
// Order_Direction:  B(Bid:买入)    A(Ask:卖出)
// Nano_Time:   距离1970-01-01 00:00:00的纳秒数
// Order_Time:  Nano_Time的结构化时间
// Order_Id:    挂单返回的编号
class Order
{
    public:
        Order(){}
        Order(long long User_Id,char Order_Action,char Order_Type,char Order_Direction,double Price,long long Volumn,long long Order_Id);
        char Order_Action,Order_Type,Order_Direction; 
        double Price;
        long long Volumn,User_Id,Order_Id,Nano_Time;
        Time_Print Order_Time;    
};

#endif