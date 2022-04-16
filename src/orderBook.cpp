#include<iostream>
#include<stdexcept>
#include<string>
#include<tuple>

#include"orderBook.hpp"

/*****************************************************************
 * 
 * orderBook implementation
 * 
 *****************************************************************/

template <>
askBookType& orderBook::getBook() { return m_asks; }

template <>
bidBookType& orderBook::getBook() { return m_bids; }

template<>
orderId2BookIt& orderBook::getOrderId2BookIt<askBookType>(){ return m_orderId2AskBookIt; }

template<>
orderId2BookIt& orderBook::getOrderId2BookIt<bidBookType>(){ return m_orderId2BidBookIt; }

template<>
lib::orderSide orderBook::getCurBookSide<askBookType>(){ return lib::orderSide::ASK; };

template<>
lib::orderSide orderBook::getCurBookSide<bidBookType>(){ return lib::orderSide::BID; };

template<>
bool orderBook::priceCross(const Price4& p, const askBookType& askBook) const { return (*askBook.begin()).first <= p; };

template<>
bool orderBook::priceCross(const Price4& p, const bidBookType& bidBook) const { return (*bidBook.begin()).first >= p; };
