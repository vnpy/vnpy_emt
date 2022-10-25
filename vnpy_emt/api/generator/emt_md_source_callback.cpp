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
		data["exchange_id"] = (int) index_data->exchange_id;
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
		data["exchange_id"] = (int) market_data->exchange_id;
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
		data["data_type"] = (int) market_data->data_type;
	}
	this->onDepthMarketData(data, bid1_qty, bid1_count, max_bid1_count, ask1_qty, ask1_count, max_ask1_count);
};

void MdApi::OnTickByTick(EMTTickByTickStruct* tbt_data) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (tbt_data)
	{
		data["data_time"] = tbt_data->data_time;
		data["seq"] = tbt_data->seq;
		data["exchange_id"] = (int) tbt_data->exchange_id;
		data["ticker"] = tbt_data->ticker;
		data["type"] = (int) tbt_data->type;
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
		data["exchange_id"] = (int) order_book->exchange_id;
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
		data["exchange_type"] = (int) minute_info->exchange_type;
		data["ticker_type"] = (int) minute_info->ticker_type;
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
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubIndexData(data, data, is_last);
};

void MdApi::OnUnSubIndexData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubIndexData(data, data, is_last);
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
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubMarketData(data, data, is_last);
};

void MdApi::OnUnSubMarketData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubMarketData(data, data, is_last);
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
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubTickByTick(data, data, is_last);
};

void MdApi::OnUnSubTickByTick(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubTickByTick(data, data, is_last);
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
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubOrderBook(data, data, is_last);
};

void MdApi::OnUnSubOrderBook(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubOrderBook(data, data, is_last);
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
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onSubMinuteInfo(data, data, is_last);
};

void MdApi::OnUnSubMinuteInfo(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker)
	{
		data["exchange_id"] = (int) ticker->exchange_id;
		data["ticker"] = ticker->ticker;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onUnSubMinuteInfo(data, data, is_last);
};

void MdApi::OnQueryAllTickers(EMTQuoteStaticInfo* qsi, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (qsi)
	{
		data["exchange_id"] = (int) qsi->exchange_id;
		data["ticker"] = qsi->ticker;
		data["ticker_name"] = qsi->ticker_name;
		data["ticker_type"] = (int) qsi->ticker_type;
		data["pre_close_price"] = qsi->pre_close_price;
		data["upper_limit_price"] = qsi->upper_limit_price;
		data["lower_limit_price"] = qsi->lower_limit_price;
		data["price_tick"] = qsi->price_tick;
		data["buy_qty_unit"] = qsi->buy_qty_unit;
		data["sell_qty_unit"] = qsi->sell_qty_unit;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onQueryAllTickers(data, data, is_last);
};

void MdApi::OnQueryAllTickersFullInfo(EMTQuoteFullInfo* qfi, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (qfi)
	{
		data["exchange_id"] = (int) qfi->exchange_id;
		data["ticker"] = qfi->ticker;
		data["ticker_name"] = qfi->ticker_name;
		data["security_type"] = (int) qfi->security_type;
		data["ticker_qualification_class"] = (int) qfi->ticker_qualification_class;
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
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onQueryAllTickersFullInfo(data, data, is_last);
};

void MdApi::OnQueryLatestIndexData(EMTIndexDataStruct* index_data, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (index_data)
	{
		data["exchange_id"] = (int) index_data->exchange_id;
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
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onQueryLatestIndexData(data, data, is_last);
};

void MdApi::OnQueryLatestMarketData(EMTMarketDataStruct* market_data, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (market_data)
	{
		data["exchange_id"] = (int) market_data->exchange_id;
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
		data["data_type"] = (int) market_data->data_type;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onQueryLatestMarketData(data, data, is_last);
};

void MdApi::OnQueryMinuteInfo(EMTMinuteInfo* minute_info, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (minute_info)
	{
		data["exchange_type"] = (int) minute_info->exchange_type;
		data["ticker_type"] = (int) minute_info->ticker_type;
		data["ticker"] = minute_info->ticker;
		data["data_time"] = minute_info->data_time;
		data["last_price"] = minute_info->last_price;
		data["volume_trade"] = minute_info->volume_trade;
		data["value_trade"] = minute_info->value_trade;
		data["avg_price"] = minute_info->avg_price;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onQueryMinuteInfo(data, data, is_last);
};

void MdApi::OnQueryMinHistoryInfo(EMTMinuteInfo* minute_info, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (minute_info)
	{
		data["exchange_type"] = (int) minute_info->exchange_type;
		data["ticker_type"] = (int) minute_info->ticker_type;
		data["ticker"] = minute_info->ticker;
		data["data_time"] = minute_info->data_time;
		data["last_price"] = minute_info->last_price;
		data["volume_trade"] = minute_info->volume_trade;
		data["value_trade"] = minute_info->value_trade;
		data["avg_price"] = minute_info->avg_price;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onQueryMinHistoryInfo(data, data, is_last);
};

void MdApi::OnQueryTickersPriceInfo(EMTTickerPriceInfo* price_info, EMTRspInfoStruct* error_info, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (price_info)
	{
		data["exchange_type"] = (int) price_info->exchange_type;
		data["ticker"] = price_info->ticker;
		data["last_price"] = price_info->last_price;
	}
	dict data;
	if (error_info)
	{
		data["error_id"] = error_info->error_id;
		data["error_msg"] = error_info->error_msg;
	}
	this->onQueryTickersPriceInfo(data, data, is_last);
};

