#ifndef CREATEORDER_H
#define CREATEORDER_H

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
#include "Book.h"
#include "Logger.h"

Order CreateOrder(char* str,long long num); // 输入文件的字符分割

#endif