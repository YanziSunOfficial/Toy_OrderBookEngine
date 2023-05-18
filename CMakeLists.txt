cmake_minimum_required (VERSION 2.8)
project(OrderBook_Engine)
add_executable(OrderBook_Engine main.cpp Logger.cpp Order.cpp Book.cpp Engine.cpp CreateOrder.cpp)

