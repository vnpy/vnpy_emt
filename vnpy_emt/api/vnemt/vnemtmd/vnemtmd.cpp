// vnxtpmd.cpp : 定义 DLL 应用程序的导出函数。
//
#include "pch.h"
#include "vnemtmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnDisconnected(int reason)
{
	gil_scoped_acquire acquire;
	this->onDisconnected(reason);
};

void MdApi::OnError(EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onError(data);
};

void MdApi::OnIndexData(EMTIndexDataStruct* index_data)
{
	gil_scoped_acquire acquire;
	dict data;
	if (index_data)
	{
		data["exchange_id"] = (int)index_data->exchange_id;
		data["ticker"] = index_data->ticker;
		data["data_time"] = index_data->data_time;
		data["pre_close_price"] = index_data->pre_close_price;
		data["open_price"] = index_data->open_price;
		data["last_price"] = index_data->last_price;
		data["high_price"] = index_data->high_price;
		data["low_price"] = index_data->low_price;
		data["qty"] = index_data->qty;
		data["turnover"] = index_data->turnover;
	}
	this->onIndexData(data);
};

void MdApi::OnDepthMarketData(EMTMarketDataStruct* market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count)
{
	gil_scoped_acquire acquire;
	dict data;
	if (market_data)
	{
		data["exchange_id"] = (int)market_data->exchange_id;
		data["ticker"] = market_data->ticker;
		data["last_price"] = market_data->last_price;
		data["pre_close_price"] = market_data->pre_close_price;
		data["open_price"] = market_data->open_price;
		data["high_price"] = market_data->high_price;
		data["low_price"] = market_data->low_price;
		data["close_price"] = market_data->close_price;
		data["upper_limit_price"] = market_data->upper_limit_price;
		data["lower_limit_price"] = market_data->lower_limit_price;
		data["data_time"] = market_data->data_time;
		data["qty"] = market_data->qty;
		data["turnover"] = market_data->turnover;
		data["avg_price"] = market_data->avg_price;
		data["bid"] = market_data->bid;
		data["ask"] = market_data->ask;
		data["bid_qty"] = market_data->bid_qty;
		data["ask_qty"] = market_data->ask_qty;
		data["trades_count"] = market_data->trades_count;
		data["ticker_status"] = market_data->ticker_status;
		data["total_bid_qty"] = market_data->total_bid_qty;
		data["total_ask_qty"] = market_data->total_ask_qty;
		data["ma_bid_price"] = market_data->ma_bid_price;
		data["ma_ask_price"] = market_data->ma_ask_price;
		data["cancel_buy_count"] = market_data->cancel_buy_count;
		data["cancel_sell_count"] = market_data->cancel_sell_count;
		data["cancel_buy_qty"] = market_data->cancel_buy_qty;
		data["cancel_sell_qty"] = market_data->cancel_sell_qty;
		data["cancel_buy_money"] = market_data->cancel_buy_money;
		data["cancel_sell_money"] = market_data->cancel_sell_money;
		data["total_buy_count"] = market_data->total_buy_count;
		data["total_sell_count"] = market_data->total_sell_count;
		data["duration_after_buy"] = market_data->duration_after_buy;
		data["duration_after_sell"] = market_data->duration_after_sell;
		data["num_bid_orders"] = market_data->num_bid_orders;
		data["num_ask_orders"] = market_data->num_ask_orders;
		/*data["bond"] = market_data->bond;
		data["fund"] = market_data->fund;
		data["warrant"] = market_data->warrant;
		data["opt"] = market_data->opt;*/
		data["data_type"] = (int)market_data->data_type;
		pybind11::list ask;
		pybind11::list bid;
		pybind11::list ask_qty;
		pybind11::list bid_qty;

		for (int i = 0; i < 10; i++)
		{
			ask.append(market_data->ask[i]);
			bid.append(market_data->bid[i]);
			ask_qty.append(market_data->ask_qty[i]);
			bid_qty.append(market_data->bid_qty[i]);
		}

		data["ask"] = ask;
		data["bid"] = bid;
		data["bid_qty"] = bid_qty;
		data["ask_qty"] = ask_qty;
	}
	this->onDepthMarketData(data);
};

void MdApi::OnTickByTick(EMTTickByTickStruct* tbt_data)
{
	gil_scoped_acquire acquire;
	dict data;
	if (tbt_data)
	{
		data["data_time"] = tbt_data->data_time;
		data["seq"] = tbt_data->seq;
		data["exchange_id"] = (int)tbt_data->exchange_id;
		data["ticker"] = tbt_data->ticker;
		data["type"] = (int)tbt_data->type;
		data["entrust"] = tbt_data->entrust;
		data["trade"] = tbt_data->trade;
	}
	this->onTickByTick(data);
};

void MdApi::OnOrderBook(EMTOrderBookStruct* order_book)
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_book)
	{
		data["exchange_id"] = (int)order_book->exchange_id;
		data["ticker"] = order_book->ticker;
		data["last_price"] = order_book->last_price;
		data["qty"] = order_book->qty;
		data["turnover"] = order_book->turnover;
		data["trades_count"] = order_book->trades_count;
		data["bid"] = order_book->bid;
		data["ask"] = order_book->ask;
		data["bid_qty"] = order_book->bid_qty;
		data["ask_qty"] = order_book->ask_qty;
		data["data_time"] = order_book->data_time;
	}
	this->onOrderBook(data);
};

void MdApi::OnMinuteInfo(EMTMinuteInfo* minute_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (minute_info)
	{
		data["exchange_type"] = (int)minute_info->exchange_type;
		data["ticker_type"] = (int)minute_info->ticker_type;
		data["ticker"] = minute_info->ticker;
		data["data_time"] = minute_info->data_time;
		data["last_price"] = minute_info->last_price;
		data["volume_trade"] = minute_info->volume_trade;
		data["value_trade"] = minute_info->value_trade;
		data["avg_price"] = minute_info->avg_price;
	}
	this->onMinuteInfo(data);
};

void MdApi::OnSubscribeAllIndexData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllIndexData(exchange_id, data);
};

void MdApi::OnUnSubscribeAllIndexData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllIndexData(exchange_id, data);
};

void MdApi::OnSubIndexData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubIndexData(data, error, is_last);
};

void MdApi::OnUnSubIndexData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubIndexData(data, error, is_last);
};

void MdApi::OnSubscribeAllMarketData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllMarketData(exchange_id, data);
};

void MdApi::OnUnSubscribeAllMarketData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllMarketData(exchange_id, data);
};

void MdApi::OnSubMarketData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubMarketData(data, error, is_last);
};

void MdApi::OnUnSubMarketData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubMarketData(data, error, is_last);
};

void MdApi::OnSubscribeAllTickByTick(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllTickByTick(exchange_id, data);
};

void MdApi::OnUnSubscribeAllTickByTick(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllTickByTick(exchange_id, data);
};

void MdApi::OnSubTickByTick(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubTickByTick(data, error, is_last);
};

void MdApi::OnUnSubTickByTick(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubTickByTick(data, error, is_last);
};

void MdApi::OnSubscribeAllOrderBook(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllOrderBook(exchange_id, data);
};

void MdApi::OnUnSubscribeAllOrderBook(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllOrderBook(exchange_id, data);
};

void MdApi::OnSubOrderBook(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubOrderBook(data, error, is_last);
};

void MdApi::OnUnSubOrderBook(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubOrderBook(data, error, is_last);
};

void MdApi::OnSubscribeAllMinuteInfo(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllMinuteInfo(exchange_id, data);
};

void MdApi::OnUnSubscribeAllMinuteInfo(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllMinuteInfo(exchange_id, data);
};

void MdApi::OnSubMinuteInfo(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubMinuteInfo(data, error, is_last);
};

void MdApi::OnUnSubMinuteInfo(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int)ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubMinuteInfo(data, error, is_last);
};

void MdApi::OnQueryAllTickers(EMTQuoteStaticInfo* qsi, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (qsi)
	{
		data["exchange_id"] = (int)qsi->exchange_id;
		data["ticker"] = qsi->ticker;
		data["ticker_name"] = toUtf(qsi->ticker_name);
		data["ticker_type"] = (int)qsi->ticker_type;
		data["pre_close_price"] = qsi->pre_close_price;
		data["upper_limit_price"] = qsi->upper_limit_price;
		data["lower_limit_price"] = qsi->lower_limit_price;
		data["price_tick"] = qsi->price_tick;
		data["buy_qty_unit"] = qsi->buy_qty_unit;
		data["sell_qty_unit"] = qsi->sell_qty_unit;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryAllTickers(data, error, is_last);
};

void MdApi::OnQueryAllTickersFullInfo(EMTQuoteFullInfo* qfi, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (qfi)
	{
		data["exchange_id"] = (int)qfi->exchange_id;
		data["ticker"] = qfi->ticker;
		data["ticker_name"] = qfi->ticker_name;
		data["security_type"] = (int)qfi->security_type;
		data["ticker_qualification_class"] = (int)qfi->ticker_qualification_class;
		data["is_registration"] = qfi->is_registration;
		data["is_VIE"] = qfi->is_VIE;
		data["is_noprofit"] = qfi->is_noprofit;
		data["is_weighted_voting_rights"] = qfi->is_weighted_voting_rights;
		data["is_have_price_limit"] = qfi->is_have_price_limit;
		data["upper_limit_price"] = qfi->upper_limit_price;
		data["lower_limit_price"] = qfi->lower_limit_price;
		data["pre_close_price"] = qfi->pre_close_price;
		data["price_tick"] = qfi->price_tick;
		data["bid_qty_upper_limit"] = qfi->bid_qty_upper_limit;
		data["bid_qty_lower_limit"] = qfi->bid_qty_lower_limit;
		data["bid_qty_unit"] = qfi->bid_qty_unit;
		data["ask_qty_upper_limit"] = qfi->ask_qty_upper_limit;
		data["ask_qty_lower_limit"] = qfi->ask_qty_lower_limit;
		data["ask_qty_unit"] = qfi->ask_qty_unit;
		data["market_bid_qty_upper_limit"] = qfi->market_bid_qty_upper_limit;
		data["market_bid_qty_lower_limit"] = qfi->market_bid_qty_lower_limit;
		data["market_bid_qty_unit"] = qfi->market_bid_qty_unit;
		data["market_ask_qty_upper_limit"] = qfi->market_ask_qty_upper_limit;
		data["market_ask_qty_lower_limit"] = qfi->market_ask_qty_lower_limit;
		data["market_ask_qty_unit"] = qfi->market_ask_qty_unit;
		data["unknown"] = qfi->unknown;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryAllTickersFullInfo(data, error, is_last);
};

void MdApi::OnQueryLatestIndexData(EMTIndexDataStruct* index_data, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (index_data)
	{
		data["exchange_id"] = (int)index_data->exchange_id;
		data["ticker"] = index_data->ticker;
		data["data_time"] = index_data->data_time;
		data["pre_close_price"] = index_data->pre_close_price;
		data["open_price"] = index_data->open_price;
		data["last_price"] = index_data->last_price;
		data["high_price"] = index_data->high_price;
		data["low_price"] = index_data->low_price;
		data["qty"] = index_data->qty;
		data["turnover"] = index_data->turnover;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryLatestIndexData(data, error, is_last);
};

void MdApi::OnQueryLatestMarketData(EMTMarketDataStruct* market_data, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (market_data)
	{
		data["exchange_id"] = (int)market_data->exchange_id;
		data["ticker"] = market_data->ticker;
		data["last_price"] = market_data->last_price;
		data["pre_close_price"] = market_data->pre_close_price;
		data["open_price"] = market_data->open_price;
		data["high_price"] = market_data->high_price;
		data["low_price"] = market_data->low_price;
		data["close_price"] = market_data->close_price;
		data["upper_limit_price"] = market_data->upper_limit_price;
		data["lower_limit_price"] = market_data->lower_limit_price;
		data["data_time"] = market_data->data_time;
		data["qty"] = market_data->qty;
		data["turnover"] = market_data->turnover;
		data["avg_price"] = market_data->avg_price;
		data["bid"] = market_data->bid;
		data["ask"] = market_data->ask;
		data["bid_qty"] = market_data->bid_qty;
		data["ask_qty"] = market_data->ask_qty;
		data["trades_count"] = market_data->trades_count;
		data["ticker_status"] = market_data->ticker_status;
		data["total_bid_qty"] = market_data->total_bid_qty;
		data["total_ask_qty"] = market_data->total_ask_qty;
		data["ma_bid_price"] = market_data->ma_bid_price;
		data["ma_ask_price"] = market_data->ma_ask_price;
		data["cancel_buy_count"] = market_data->cancel_buy_count;
		data["cancel_sell_count"] = market_data->cancel_sell_count;
		data["cancel_buy_qty"] = market_data->cancel_buy_qty;
		data["cancel_sell_qty"] = market_data->cancel_sell_qty;
		data["cancel_buy_money"] = market_data->cancel_buy_money;
		data["cancel_sell_money"] = market_data->cancel_sell_money;
		data["total_buy_count"] = market_data->total_buy_count;
		data["total_sell_count"] = market_data->total_sell_count;
		data["duration_after_buy"] = market_data->duration_after_buy;
		data["duration_after_sell"] = market_data->duration_after_sell;
		data["num_bid_orders"] = market_data->num_bid_orders;
		data["num_ask_orders"] = market_data->num_ask_orders;
		data["bond"] = market_data->bond;
		data["fund"] = market_data->fund;
		data["warrant"] = market_data->warrant;
		data["opt"] = market_data->opt;
		data["data_type"] = (int)market_data->data_type;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryLatestMarketData(data, error, is_last);
};

void MdApi::OnQueryMinuteInfo(EMTMinuteInfo* minute_info, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (minute_info)
	{
		data["exchange_type"] = (int)minute_info->exchange_type;
		data["ticker_type"] = (int)minute_info->ticker_type;
		data["ticker"] = minute_info->ticker;
		data["data_time"] = minute_info->data_time;
		data["last_price"] = minute_info->last_price;
		data["volume_trade"] = minute_info->volume_trade;
		data["value_trade"] = minute_info->value_trade;
		data["avg_price"] = minute_info->avg_price;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryMinuteInfo(data, error, is_last);
};

void MdApi::OnQueryMinHistoryInfo(EMTMinuteInfo* minute_info, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (minute_info)
	{
		data["exchange_type"] = (int)minute_info->exchange_type;
		data["ticker_type"] = (int)minute_info->ticker_type;
		data["ticker"] = minute_info->ticker;
		data["data_time"] = minute_info->data_time;
		data["last_price"] = minute_info->last_price;
		data["volume_trade"] = minute_info->volume_trade;
		data["value_trade"] = minute_info->value_trade;
		data["avg_price"] = minute_info->avg_price;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryMinHistoryInfo(data, error, is_last);
};

void MdApi::OnQueryTickersPriceInfo(EMTTickerPriceInfo* price_info, EMTRspInfoStruct* error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (price_info)
	{
		data["exchange_type"] = (int)price_info->exchange_type;
		data["ticker"] = price_info->ticker;
		data["last_price"] = price_info->last_price;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryTickersPriceInfo(data, error, is_last);
};




///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createQuoteApi(int client_id, string save_file_path, int data_type, int log_level)
{
	if (!this->api)
	{
		this->api = QuoteApi::CreateQuoteApi(client_id, save_file_path.c_str(), data_type, EMT_LOG_LEVEL(log_level));
		this->api->RegisterSpi(this);
	}
};

void MdApi::init()
{
	if (!this->active)
	{
		this->active = true;
	}
};

void MdApi::release()
{
	this->api->Release();
};

int MdApi::exit()
{
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;

	this->active = false;
	return 1;
};

//string MdApi::getTradingDay()
//{
//	string day = this->api->GetTradingDay();
//	return day;
//};
//getTradingDay函数在交易API，不在这

string MdApi::getApiVersion()
{
	string version = this->api->GetApiVersion();
	return version;
};

dict MdApi::getApiLastError()
{
	EMTRspInfoStruct*last_error = this->api->GetApiLastError();
	dict error;
	error["error_id"] = last_error->error_id;
	error["error_msg"] = last_error->error_msg;
	return error;
};

void MdApi::setUDPBufferSize(int buff_size)
{
	this->api->SetUDPBufferSize(buff_size);
};

void MdApi::setHeartBeatInterval(int interval)
{
	this->api->SetHeartBeatInterval(interval);
};

int MdApi::subscribeMarketData(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeMarketData(myreq, 1, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeMarketData(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeMarketData(myreq, 1, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeOrderBook(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeOrderBook(myreq, 1, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeOrderBook(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeOrderBook(myreq, 1, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeTickByTick(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeTickByTick(myreq, 1, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeTickByTick(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeTickByTick(myreq, 1, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeAllMarketData(int exchange_id)
{
	int i = this->api->SubscribeAllMarketData((EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeAllMarketData(int exchange_id)
{
	int i = this->api->UnSubscribeAllMarketData((EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeAllOrderBook(int exchange_id)
{
	int i = this->api->SubscribeAllOrderBook((EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeAllOrderBook(int exchange_id)
{
	int i = this->api->UnSubscribeAllOrderBook((EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeAllTickByTick(int exchange_id)
{
	int i = this->api->SubscribeAllTickByTick((EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeAllTickByTick(int exchange_id)
{
	int i = this->api->UnSubscribeAllTickByTick((EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::login(string ip, int port, string user, string password, int sock_type, string local_ip)
{
	int i;

	//默认不设置本地网卡地址
	if (local_ip == "") 
	{
		i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (EMT_PROTOCOL_TYPE)sock_type);
	}
	else
	{
		i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (EMT_PROTOCOL_TYPE)sock_type, local_ip.c_str());
	}
	
	return i;
};

int MdApi::logout()
{
	int i = this->api->Logout();
	return i;
};

int MdApi::queryAllTickers(int exchange_id)
{
	int i = this->api->QueryAllTickers((EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::queryAllTickersFullInfo(int exchange_id)
{
	int i = this->api->QueryAllTickersFullInfo((EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::queryLatestInfo(string ticker, int ticker_type, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->QueryLatestInfo(myreq, 1, (EMT_TICKER_TYPE)ticker_type, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::queryMinuteInfo(string tickers, int count, int ticker_type, int exchange_id)
{
	char* buffer = (char*)tickers.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->QueryMinuteInfo(myreq, 1, (EMT_TICKER_TYPE)ticker_type, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::queryMinHistoryInfo(string tickers, int count, int datetime, int ticker_type, int exchange_id)
{
	char* buffer = (char*)tickers.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->QueryMinHistoryInfo(myreq, 1, datetime, (EMT_TICKER_TYPE)ticker_type, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::queryTickersPriceInfo(string tickers, int count, int exchange_id)
{
	char* buffer = (char*)tickers.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->QueryTickersPriceInfo(myreq, 1, (EMT_EXCHANGE_TYPE)exchange_id);
	return i;
};





///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyMdApi : public MdApi
{
public:
	using MdApi::MdApi;

	void onDisconnected(int reason) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onDisconnected, reason);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onError(const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onError, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onIndexData(const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onIndexData, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onDepthMarketData(const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onDepthMarketData, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onTickByTick(const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onTickByTick, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onOrderBook(const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onOrderBook, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onMinuteInfo(const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onMinuteInfo, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllIndexData(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllIndexData, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllIndexData(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllIndexData, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubIndexData(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubIndexData, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubIndexData(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubIndexData, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllMarketData(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllMarketData, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllMarketData(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllMarketData, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubMarketData(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubMarketData, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubMarketData(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubMarketData, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllTickByTick(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllTickByTick, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllTickByTick(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllTickByTick, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubTickByTick(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubTickByTick, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubTickByTick(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubTickByTick, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOrderBook(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOrderBook, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOrderBook(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOrderBook, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubOrderBook(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubOrderBook, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubOrderBook(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubOrderBook, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllMinuteInfo(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllMinuteInfo, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllMinuteInfo(int exchange_id, const dict& data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllMinuteInfo, exchange_id, data);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubMinuteInfo(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubMinuteInfo, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubMinuteInfo(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubMinuteInfo, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryAllTickers(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryAllTickers, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryAllTickersFullInfo(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryAllTickersFullInfo, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryLatestIndexData(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryLatestIndexData, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryLatestMarketData(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryLatestMarketData, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryMinuteInfo(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryMinuteInfo, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryMinHistoryInfo(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryMinHistoryInfo, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryTickersPriceInfo(const dict& data, const dict& error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryTickersPriceInfo, data, error, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};
};


PYBIND11_MODULE(vnemtmd, m)
{
	class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
	mdapi
		.def(init<>())
		.def("createQuoteApi", &MdApi::createQuoteApi)
		.def("init", &MdApi::init)
		.def("release", &MdApi::release)
		.def("exit", &MdApi::exit)
		//.def("getTradingDay", &MdApi::getTradingDay)
		.def("getApiVersion", &MdApi::getApiVersion)
		.def("getApiLastError", &MdApi::getApiLastError)
		.def("setUDPBufferSize", &MdApi::setUDPBufferSize)
		.def("setHeartBeatInterval", &MdApi::setHeartBeatInterval)
		.def("subscribeMarketData", &MdApi::subscribeMarketData)
		.def("unSubscribeMarketData", &MdApi::unSubscribeMarketData)
		.def("subscribeOrderBook", &MdApi::subscribeOrderBook)
		.def("unSubscribeOrderBook", &MdApi::unSubscribeOrderBook)
		.def("subscribeTickByTick", &MdApi::subscribeTickByTick)
		.def("unSubscribeTickByTick", &MdApi::unSubscribeTickByTick)
		.def("subscribeAllMarketData", &MdApi::subscribeAllMarketData)
		.def("unSubscribeAllMarketData", &MdApi::unSubscribeAllMarketData)
		.def("subscribeAllOrderBook", &MdApi::subscribeAllOrderBook)
		.def("unSubscribeAllOrderBook", &MdApi::unSubscribeAllOrderBook)
		.def("subscribeAllTickByTick", &MdApi::subscribeAllTickByTick)
		.def("unSubscribeAllTickByTick", &MdApi::unSubscribeAllTickByTick)
		.def("login", &MdApi::login)
		.def("logout", &MdApi::logout)

		.def("queryAllTickers", &MdApi::queryAllTickers)
		.def("queryAllTickersFullInfo", &MdApi::queryAllTickersFullInfo)
		.def("queryLatestInfo", &MdApi::queryLatestInfo)
		.def("queryMinuteInfo", &MdApi::queryMinuteInfo)
		.def("queryMinHistoryInfo", &MdApi::queryMinHistoryInfo)
		.def("queryTickersPriceInfo", &MdApi::queryTickersPriceInfo)

		.def("onDisconnected", &MdApi::onDisconnected)
		.def("onError", &MdApi::onError)
		.def("onIndexData", &MdApi::onIndexData)
		.def("onDepthMarketData", &MdApi::onDepthMarketData)
		.def("onTickByTick", &MdApi::onTickByTick)
		.def("onOrderBook", &MdApi::onOrderBook)
		.def("onMinuteInfo", &MdApi::onMinuteInfo)
		.def("onSubscribeAllIndexData", &MdApi::onSubscribeAllIndexData)
		.def("onUnSubscribeAllIndexData", &MdApi::onUnSubscribeAllIndexData)
		.def("onSubIndexData", &MdApi::onSubIndexData)
		.def("onUnSubIndexData", &MdApi::onUnSubIndexData)
		.def("onSubscribeAllMarketData", &MdApi::onSubscribeAllMarketData)
		.def("onUnSubscribeAllMarketData", &MdApi::onUnSubscribeAllMarketData)
		.def("onSubMarketData", &MdApi::onSubMarketData)
		.def("onUnSubMarketData", &MdApi::onUnSubMarketData)
		.def("onSubscribeAllTickByTick", &MdApi::onSubscribeAllTickByTick)
		.def("onUnSubscribeAllTickByTick", &MdApi::onUnSubscribeAllTickByTick)
		.def("onSubTickByTick", &MdApi::onSubTickByTick)
		.def("onUnSubTickByTick", &MdApi::onUnSubTickByTick)
		.def("onSubscribeAllOrderBook", &MdApi::onSubscribeAllOrderBook)
		.def("onUnSubscribeAllOrderBook", &MdApi::onUnSubscribeAllOrderBook)
		.def("onSubOrderBook", &MdApi::onSubOrderBook)
		.def("onUnSubOrderBook", &MdApi::onUnSubOrderBook)
		.def("onSubscribeAllMinuteInfo", &MdApi::onSubscribeAllMinuteInfo)
		.def("onUnSubscribeAllMinuteInfo", &MdApi::onUnSubscribeAllMinuteInfo)
		.def("onSubMinuteInfo", &MdApi::onSubMinuteInfo)
		.def("onUnSubMinuteInfo", &MdApi::onUnSubMinuteInfo)
		.def("onQueryAllTickers", &MdApi::onQueryAllTickers)
		.def("onQueryAllTickersFullInfo", &MdApi::onQueryAllTickersFullInfo)
		.def("onQueryLatestIndexData", &MdApi::onQueryLatestIndexData)
		.def("onQueryLatestMarketData", &MdApi::onQueryLatestMarketData)
		.def("onQueryMinuteInfo", &MdApi::onQueryMinuteInfo)
		.def("onQueryMinHistoryInfo", &MdApi::onQueryMinHistoryInfo)
		.def("onQueryTickersPriceInfo", &MdApi::onQueryTickersPriceInfo)
		;
}



