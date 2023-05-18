#include "Order.h"

long long Get_NanoTime()
{
    system_clock::time_point current=system_clock::now();            // 获取当前时间
    nanoseconds Nano_current=current.time_since_epoch();             // 距离1970-01-01 00:00:00的纳秒数
    long long Count_current=Nano_current.count();
    return Count_current;
}

Time_Print Get_Time(long long current) 
{
    int year,month,day,days,seconds;
    int monthday[]{0,31,59,90,120,151,181,212,243,273,304,334,365};
    seconds=current/1000000000+8*3600;
    days=seconds/86400;
    year=1970+(int)(days/1461)*4; 
    month=0;
    day=days%1461;
    day=day > 730 ? day-1 : day;
    year+=(int)(day/365);
    day=day%365;
    for (int i=0;i<13;i++)
    {
        if (day<monthday[i+1]) 
        {
            month=i+1;
            day=day-monthday[i]+1;
            break;
        }        
    } 
    struct Time_Print time_=
    {
        .year_=year,
        .month_=month,
        .day_=day,
        .hour_=(int)(seconds%86400/3600),
        .mintue_=(int)(seconds%86400%3600/60),
        .second_=seconds%86400%60,
        .millisecond_=current%1000000000/1000,
    };
    return time_;
}

Order::Order(long long User_Id,char Order_Action,char Order_Type,char Order_Direction,double Price,long long Volumn,long long Order_Id)
{
    this->Nano_Time=Get_NanoTime();
    this->Order_Time=Get_Time(Nano_Time);
    this->User_Id=User_Id;
    this->Order_Action=Order_Action;
    this->Order_Type=Order_Type;
    this->Order_Direction=Order_Direction;
    this->Price=Price;
    this->Volumn=Volumn;
    this->Order_Id=Order_Id;
}
