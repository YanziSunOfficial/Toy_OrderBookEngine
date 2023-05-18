#include "Book.h"

void Deal_Print(double price,double vol)    // 交易信息打印
{
    std::cout<<std::endl<<"  ====  "<<price<<" * "<<vol<<"  ====  "<<std::endl;
}

void Book::Order_Deal(Order& New_Order)
{
    std::vector<long long> temp;
    bool flag=0;
    switch (New_Order.Order_Direction)
    {
        case 'B':     // 限价买单
        {
            for(auto iter=this->Order_List.begin();iter!=this->Order_List.end();iter++)   // 根据价格由低到高排序
            {
                if(flag==1) break;    // 若买单已经完全成交
                if(New_Order.Price<iter->first) break;   // 若买单小于卖簿的最优价，即无法成交，则退出
                for(auto iter1=this->Order_List[iter->first].begin();iter1!=this->Order_List[iter->first].end();iter1++)  // 同一价格根据时间从先到后排序
                {
                    if(New_Order.Volumn<iter1->second.Volumn)   // 若买单可以被完全成交
                    {
                        Deal_Print(iter->first,New_Order.Volumn);   
                        iter1->second.Volumn-=New_Order.Volumn;   // 更新卖簿订单信息
                        this->Price_TotalVolumn[iter->first]-=New_Order.Volumn;   //维护卖簿的Price_TotalVolumn
                        this->Id_Order[iter1->second.Order_Id].Volumn-=New_Order.Volumn;   //维护卖簿的Id_Order
                        New_Order.Volumn=0; 
                        flag=1;
                        break;
                    }
                    // 若卖簿最优价被完全成交，买单有余量
                    Deal_Print(iter->first,iter1->second.Volumn);
                    this->Price_TotalVolumn[iter->first]-=iter1->second.Volumn;   //维护卖簿的Price_TotalVolumn
                    this->Id_Order[iter1->second.Order_Id].Volumn-=iter1->second.Volumn;  //维护卖簿的Id_Order
                    New_Order.Volumn-=iter1->second.Volumn;  // 更新买单信息
                    temp.push_back(iter1->second.Order_Id);      //记录卖簿Order_Id
                }
            }
            for(auto iter=temp.begin();iter!=temp.end();iter++)
                this->Order_Cancel((*iter));     // 将被完全成交的卖簿订单撤下
            break;            
        }
        case 'A':    // 限价卖单
        {
            for(auto iter=this->Order_List.rbegin();iter!=this->Order_List.rend();iter++)
            {
                if(flag) break;
                if(New_Order.Price>iter->first) break;
                for(auto iter1=this->Order_List[iter->first].begin();iter1!=this->Order_List[iter->first].end();iter1++)
                {
                    if(New_Order.Volumn<iter1->second.Volumn) 
                    {
                        Deal_Print(iter->first,New_Order.Volumn);
                        iter1->second.Volumn-=New_Order.Volumn;
                        this->Price_TotalVolumn[iter->first]-=New_Order.Volumn;
                        this->Id_Order[iter1->second.Order_Id].Volumn-=New_Order.Volumn;
                        New_Order.Volumn=0;
                        flag=1;
                        break;
                    }
                    Deal_Print(iter->first,iter1->second.Volumn);
                    this->Price_TotalVolumn[iter->first]-=iter1->second.Volumn;
                    New_Order.Volumn-=iter1->second.Volumn;
                    this->Id_Order[iter1->second.Order_Id].Volumn-=iter1->second.Volumn;
                    temp.push_back(iter1->second.Order_Id);
                }
            }
            for(auto iter=temp.begin();iter!=temp.end();iter++)
                this->Order_Cancel((*iter));
            break;            
        }
        default:   
        {
            std::cout<<"error"<<std::endl;
            break;
        }
    }
}

void Book::Order_Market_Deal(Order& New_Order)
{
    int gear=1;   // 记录档数，市价单前5档即时成交，剩余撤销
    bool flag=0;
    std::vector<long long> temp;
    switch (New_Order.Order_Direction)
    {
        case 'B':
        {
            for(auto iter=this->Order_List.begin();(iter!=this->Order_List.end()&&gear<=5);iter++,gear++)
            {
                if(flag) break;
                for(auto iter1=this->Order_List[iter->first].begin();iter1!=this->Order_List[iter->first].end();iter1++)
                {
                    if(New_Order.Volumn<iter1->second.Volumn)
                    {
                        Deal_Print(iter->first,New_Order.Volumn);
                        iter1->second.Volumn-=New_Order.Volumn;
                        this->Price_TotalVolumn[iter->first]-=New_Order.Volumn;
                        this->Id_Order[iter1->second.Order_Id].Volumn-=New_Order.Volumn;
                        New_Order.Volumn=0;
                        flag=1;
                        break;
                    }
                    Deal_Print(iter->first,iter1->second.Volumn);
                    this->Price_TotalVolumn[iter->first]-=iter1->second.Volumn;
                    New_Order.Volumn-=iter1->second.Volumn;
                    this->Id_Order[iter1->second.Order_Id].Volumn-=iter1->second.Volumn;
                    temp.push_back(iter1->second.Order_Id);
                }

            }               
            for(auto iter=temp.begin();iter!=temp.end();iter++)
                this->Order_Cancel((*iter));
            New_Order.Volumn=0;
            break;            
        }

        case 'A':
        {
            for(auto iter=this->Order_List.rbegin();(iter!=this->Order_List.rend()&&gear<=5);iter++,gear++)
            {
                if(flag) break;
                for(auto iter1=this->Order_List[iter->first].begin();iter1!=this->Order_List[iter->first].end();iter1++)
                {
                    if(New_Order.Volumn<iter1->second.Volumn)
                    {
                        Deal_Print(iter->first,New_Order.Volumn);
                        iter1->second.Volumn-=New_Order.Volumn;
                        this->Price_TotalVolumn[iter->first]-=New_Order.Volumn;
                        this->Id_Order[iter1->second.Order_Id].Volumn-=New_Order.Volumn;
                        New_Order.Volumn=0;
                        flag=1;
                        break;
                    }
                    Deal_Print(iter->first,iter1->second.Volumn);
                    this->Price_TotalVolumn[iter->first]-=iter1->second.Volumn;
                    New_Order.Volumn-=iter1->second.Volumn;
                    this->Id_Order[iter1->second.Order_Id].Volumn-=iter1->second.Volumn;
                    temp.push_back(iter1->second.Order_Id);
                }
            }  
            for(auto iter=temp.begin();iter!=temp.end();iter++)
                this->Order_Cancel((*iter));
            New_Order.Volumn=0;
            break;            
        }
        default:
        {
            std::cout<<"error"<<std::endl;
            break;
        }
    }
}

void Book::Order_Add(Order& Left_Order)
{
    if(Left_Order.Volumn!=0) 
    {
        if(this->Price_TotalVolumn.count(Left_Order.Price)==0) this->Price_TotalVolumn[Left_Order.Price]=Left_Order.Volumn;
        else this->Price_TotalVolumn[Left_Order.Price]+=Left_Order.Volumn;
        this->Order_List[Left_Order.Price][Left_Order.Nano_Time]=Left_Order;
        this->Id_Order[Left_Order.Order_Id]=Left_Order;
        //进簿回执
        std::cout<<std::endl<<"---- 用户"<<Left_Order.User_Id<<" 您好!"<<std::endl;
        std::cout<<"---- 您的挂单回执是: ----"<<std::endl;
        std::cout<<"---- OrderId: "<<Left_Order.Order_Id<<std::endl;
    }
}
void Book::Order_Cancel(long long Order_Id)
{    
    this->Order_List[this->Id_Order[Order_Id].Price].erase(this->Id_Order[Order_Id].Nano_Time);  // 更新买/卖簿Order_List信息
    if(this->Price_TotalVolumn[this->Id_Order[Order_Id].Price]==0)  // 如果同一价格下的订单数已为0
    {
        this->Order_List.erase(this->Id_Order[Order_Id].Price);
    }
}

void Book::Order_Print(char Book_Type,int Level)
{
    int gear=1;
    switch (Book_Type)
    {
        case 'S':
        {
            std::cout<<std::endl<<"**** 卖簿 ****"<<std::endl;
            for(auto iter=this->Order_List.begin();(iter!=this->Order_List.end()&&gear<=Level);iter++,gear++)
            {
                std::cout<<"["<<std::setw(2)<<gear<<"]"<<"  |Price:  "<<std::setw(6)<<iter->first<<"  |Vol:  "<<std::setw(6)<<this->Price_TotalVolumn[iter->first]<<std::endl;
            }        
            break;            
        }
        case 'B':
        {
            std::cout<<std::endl<<"**** 买簿 ****"<<std::endl;
            for(auto iter=this->Order_List.rbegin();(iter!=this->Order_List.rend()&&gear<=Level);iter++,gear++)
            {
                std::cout<<"["<<std::setw(2)<<gear<<"]"<<"  |Price:  "<<std::setw(6)<<iter->first<<"  |Vol:  "<<std::setw(6)<<this->Price_TotalVolumn[iter->first]<<std::endl;
            }
            break;            
        }
        default:
        {
            std::cout<<"error"<<std::endl;           
            break;
        }
    }
}




