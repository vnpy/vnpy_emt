// vnxtpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnxtpmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnDisconnected(int reason)
{
	gil_scoped_acquire acquire;
	this->onDisconnected(reason);
};

void MdApi::OnError(XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onError(error);
};

void MdApi::OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
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

void MdApi::OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
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

void MdApi::OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count)
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
		data["pre_total_long_positon"] = market_data->pre_total_long_positon;
		data["total_long_positon"] = market_data->total_long_positon;
		data["pre_settl_price"] = market_data->pre_settl_price;
		data["settl_price"] = market_data->settl_price;
		data["upper_limit_price"] = market_data->upper_limit_price;
		data["lower_limit_price"] = market_data->lower_limit_price;
		data["pre_delta"] = market_data->pre_delta;
		data["curr_delta"] = market_data->curr_delta;
		data["data_time"] = market_data->data_time;
		data["qty"] = market_data->qty;
		data["turnover"] = market_data->turnover;
		data["avg_price"] = market_data->avg_price;
		data["trades_count"] = market_data->trades_count;
		data["data_type_v2"] = (int)market_data->data_type_v2;

		//data["stk"] = market_data->stk;
		//data["opt"] = market_data->opt;
		//data["bond"] = market_data->bond;
		//data["data_type"] = market_data->data_type

		//Solve UDP protocol error text
		//string status = market_data->ticker_status;
		//data["ticker_status"] = status.substr(0, 4);

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

void MdApi::OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
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

void MdApi::OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
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

void MdApi::OnOrderBook(XTPOB *order_book)
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

void MdApi::OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
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

void MdApi::OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
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

void MdApi::OnTickByTick(XTPTBT *tbt_data)
{
	gil_scoped_acquire acquire;
	dict data;
	if (tbt_data)
	{
		data["exchange_id"] = (int)tbt_data->exchange_id;
		data["ticker"] = tbt_data->ticker;
		data["seq"] = tbt_data->seq;
		data["data_time"] = tbt_data->data_time;
		data["type"] = (int)tbt_data->type;

		dict entrust;
		dict trade;
		dict state;

		if (tbt_data->type == XTP_TBT_ENTRUST)
		{
			entrust["channel_no"] = tbt_data->entrust.channel_no;
			entrust["seq"] = tbt_data->entrust.seq;
			entrust["price"] = tbt_data->entrust.price;
			entrust["qty"] = tbt_data->entrust.qty;
			entrust["side"] = tbt_data->entrust.side;
			entrust["ord_type"] = tbt_data->entrust.ord_type;
			entrust["order_no"] = tbt_data->entrust.order_no;
		}
		else if (tbt_data->type == XTP_TBT_TRADE)
		{
			trade["channel_no"] = tbt_data->trade.channel_no;
			trade["seq"] = tbt_data->trade.seq;
			trade["price"] = tbt_data->trade.price;
			trade["qty"] = tbt_data->trade.qty;
			trade["money"] = tbt_data->trade.money;
			trade["bid_no"] = tbt_data->trade.bid_no;
			trade["ask_no"] = tbt_data->trade.ask_no;
			trade["trade_flag"] = tbt_data->trade.trade_flag;
		}
		else
		{
			state["channel_no"] = tbt_data->state.channel_no;
			state["seq"] = tbt_data->state.seq;
			state["flag"] = tbt_data->state.flag;
		}

		data["entrust"] = entrust;
		data["trade"] = trade;
	}
	this->onTickByTick(data);
};

void MdApi::OnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllMarketData(exchange_id, error);
};

void MdApi::OnUnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllMarketData(exchange_id, error);
};

void MdApi::OnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllOrderBook(exchange_id, error);
};

void MdApi::OnUnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllOrderBook(exchange_id, error);
};

void MdApi::OnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllTickByTick(exchange_id, error);
};

void MdApi::OnUnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllTickByTick(exchange_id, error);
};

void MdApi::OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker_info)
	{
		data["exchange_id"] = (int)ticker_info->exchange_id;
		data["ticker"] = ticker_info->ticker;
		data["ticker_name"] = ticker_info->ticker_name;
		data["ticker_type"] = (int)ticker_info->ticker_type;
		data["pre_close_price"] = ticker_info->pre_close_price;
		data["upper_limit_price"] = ticker_info->upper_limit_price;
		data["lower_limit_price"] = ticker_info->lower_limit_price;
		data["price_tick"] = ticker_info->price_tick;
		data["buy_qty_unit"] = ticker_info->buy_qty_unit;
		data["sell_qty_unit"] = ticker_info->sell_qty_unit;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryAllTickers(data, error, is_last);
};

void MdApi::OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker_info)
	{
		data["exchange_id"] = (int)ticker_info->exchange_id;
		data["ticker"] = ticker_info->ticker;
		data["last_price"] = ticker_info->last_price;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryTickersPriceInfo(data, error, is_last);
};

void MdApi::OnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllOptionMarketData(exchange_id, error);
};

void MdApi::OnUnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllOptionMarketData(exchange_id, error);
};

void MdApi::OnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllOptionOrderBook(exchange_id, error);
};

void MdApi::OnUnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllOptionOrderBook(exchange_id, error);
};

void MdApi::OnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onSubscribeAllOptionTickByTick(exchange_id, error);
};

void MdApi::OnUnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onUnSubscribeAllOptionTickByTick(exchange_id, error);
};

void MdApi::OnQueryAllTickersFullInfo(XTPQFI* ticker_info, XTPRI *error_info, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ticker_info)
	{
		data["exchange_id"] = (int)ticker_info->exchange_id;
		data["ticker"] = ticker_info->ticker;
		data["ticker_name"] = ticker_info->ticker_name;
		data["security_type"] = (int)ticker_info->security_type;
		data["ticker_qualification_class"] = (int)ticker_info->ticker_qualification_class;
		data["is_registration"] = ticker_info->is_registration;
		data["is_VIE"] = ticker_info->is_VIE;
		data["is_noprofit"] = ticker_info->is_noprofit;
		data["is_weighted_voting_rights"] = ticker_info->is_weighted_voting_rights;
		data["is_have_price_limit"] = ticker_info->is_have_price_limit;
		data["upper_limit_price"] = ticker_info->upper_limit_price;
		data["lower_limit_price"] = ticker_info->lower_limit_price;
		data["pre_close_price"] = ticker_info->pre_close_price;
		data["price_tick"] = ticker_info->price_tick;
		data["bid_qty_upper_limit"] = ticker_info->bid_qty_upper_limit;
		data["bid_qty_lower_limit"] = ticker_info->bid_qty_lower_limit;
		data["bid_qty_unit"] = ticker_info->bid_qty_unit;
		data["ask_qty_upper_limit"] = ticker_info->ask_qty_upper_limit;
		data["ask_qty_lower_limit"] = ticker_info->ask_qty_lower_limit;
		data["ask_qty_unit"] = ticker_info->ask_qty_unit;
		data["market_bid_qty_upper_limit"] = ticker_info->market_bid_qty_upper_limit;
		data["market_bid_qty_lower_limit"] = ticker_info->market_bid_qty_lower_limit;
		data["market_bid_qty_unit"] = ticker_info->market_bid_qty_unit;
		data["market_ask_qty_upper_limit"] = ticker_info->market_ask_qty_upper_limit;
		data["market_ask_qty_lower_limit"] = ticker_info->market_ask_qty_lower_limit;
		data["market_ask_qty_unit"] = ticker_info->market_ask_qty_unit;
		data["security_status"] = (int)ticker_info->security_status;
		data["unknown1"] = ticker_info->unknown1;
		data["unknown"] = ticker_info->unknown;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryAllTickersFullInfo(data, error, is_last);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createQuoteApi(int client_id, string save_file_path, int log_level)
{
	if (!this->api)
	{
		this->api = QuoteApi::CreateQuoteApi(client_id, save_file_path.c_str(), XTP_LOG_LEVEL(log_level));
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

string MdApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

string MdApi::getApiVersion()
{
	string version = this->api->GetApiVersion();
	return version;
};

dict MdApi::getApiLastError()
{
	XTPRI*last_error = this->api->GetApiLastError();
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
	int i = this->api->SubscribeMarketData(myreq, 1, (XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeMarketData(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeMarketData(myreq, 1, (XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeOrderBook(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeOrderBook(myreq, 1, (XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeOrderBook(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeOrderBook(myreq, 1, (XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeTickByTick(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeTickByTick(myreq, 1, (XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeTickByTick(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeTickByTick(myreq, 1, (XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeAllMarketData(int exchange_id)
{
	int i = this->api->SubscribeAllMarketData((XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeAllMarketData(int exchange_id)
{
	int i = this->api->UnSubscribeAllMarketData((XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeAllOrderBook(int exchange_id)
{
	int i = this->api->SubscribeAllOrderBook((XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeAllOrderBook(int exchange_id)
{
	int i = this->api->UnSubscribeAllOrderBook((XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::subscribeAllTickByTick(int exchange_id)
{
	int i = this->api->SubscribeAllTickByTick((XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::unSubscribeAllTickByTick(int exchange_id)
{
	int i = this->api->UnSubscribeAllTickByTick((XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::login(string ip, int port, string user, string password, int sock_type, string local_ip)
{
	int i;

	//默认不设置本地网卡地址
	if (local_ip == "") 
	{
		i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE)sock_type);
	}
	else
	{
		i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE)sock_type, local_ip.c_str());
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
	int i = this->api->QueryAllTickers((XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::queryTickersPriceInfo(string ticker, int count, int exchange_id)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->UnSubscribeTickByTick(myreq, 1, (XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::queryAllTickersPriceInfo()
{
	int i = this->api->QueryAllTickersPriceInfo();
	return i;
};

int MdApi::queryAllTickersFullInfo(int exchange_id)
{
	int i = this->api->QueryAllTickersFullInfo((XTP_EXCHANGE_TYPE)exchange_id);
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
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onError(const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onError, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubMarketData(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubMarketData, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubMarketData(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubMarketData, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onDepthMarketData(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onDepthMarketData, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubOrderBook(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubOrderBook, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubOrderBook(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubOrderBook, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onOrderBook(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onOrderBook, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubTickByTick(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubTickByTick, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubTickByTick(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubTickByTick, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onTickByTick(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onTickByTick, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllMarketData(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllMarketData, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllMarketData(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllMarketData, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOrderBook(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOrderBook, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOrderBook(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOrderBook, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllTickByTick(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllTickByTick, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllTickByTick(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllTickByTick, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryAllTickers(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryAllTickers, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryTickersPriceInfo(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryTickersPriceInfo, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOptionMarketData(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionMarketData, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOptionMarketData(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionMarketData, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOptionOrderBook(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionOrderBook, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOptionOrderBook(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionOrderBook, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOptionTickByTick(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionTickByTick, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOptionTickByTick(int exchange_id, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionTickByTick, exchange_id, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryAllTickersFullInfo(const dict &data, const dict &error, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryAllTickersFullInfo, data, error, is_last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
};


PYBIND11_MODULE(vnxtpmd, m)
{
	class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
	mdapi
		.def(init<>())
		.def("createQuoteApi", &MdApi::createQuoteApi)
		.def("init", &MdApi::init)
		.def("release", &MdApi::release)
		.def("exit", &MdApi::exit)
		.def("getTradingDay", &MdApi::getTradingDay)
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
		.def("queryTickersPriceInfo", &MdApi::queryTickersPriceInfo)
		.def("queryAllTickersPriceInfo", &MdApi::queryAllTickersPriceInfo)
		.def("queryAllTickersFullInfo", &MdApi::queryAllTickersFullInfo)

		.def("onDisconnected", &MdApi::onDisconnected)
		.def("onError", &MdApi::onError)
		.def("onSubMarketData", &MdApi::onSubMarketData)
		.def("onUnSubMarketData", &MdApi::onUnSubMarketData)
		.def("onDepthMarketData", &MdApi::onDepthMarketData)
		.def("onSubOrderBook", &MdApi::onSubOrderBook)
		.def("onUnSubOrderBook", &MdApi::onUnSubOrderBook)
		.def("onOrderBook", &MdApi::onOrderBook)
		.def("onSubTickByTick", &MdApi::onSubTickByTick)
		.def("onUnSubTickByTick", &MdApi::onUnSubTickByTick)
		.def("onTickByTick", &MdApi::onTickByTick)
		.def("onSubscribeAllMarketData", &MdApi::onSubscribeAllMarketData)
		.def("onUnSubscribeAllMarketData", &MdApi::onUnSubscribeAllMarketData)
		.def("onSubscribeAllOrderBook", &MdApi::onSubscribeAllOrderBook)
		.def("onUnSubscribeAllOrderBook", &MdApi::onUnSubscribeAllOrderBook)
		.def("onSubscribeAllTickByTick", &MdApi::onSubscribeAllTickByTick)
		.def("onUnSubscribeAllTickByTick", &MdApi::onUnSubscribeAllTickByTick)
		.def("onQueryAllTickers", &MdApi::onQueryAllTickers)
		.def("onQueryTickersPriceInfo", &MdApi::onQueryTickersPriceInfo)
		.def("onSubscribeAllOptionMarketData", &MdApi::onSubscribeAllOptionMarketData)
		.def("onUnSubscribeAllOptionMarketData", &MdApi::onUnSubscribeAllOptionMarketData)
		.def("onSubscribeAllOptionOrderBook", &MdApi::onSubscribeAllOptionOrderBook)
		.def("onUnSubscribeAllOptionOrderBook", &MdApi::onUnSubscribeAllOptionOrderBook)
		.def("onSubscribeAllOptionTickByTick", &MdApi::onSubscribeAllOptionTickByTick)
		.def("onUnSubscribeAllOptionTickByTick", &MdApi::onUnSubscribeAllOptionTickByTick)
		.def("onQueryAllTickersFullInfo", &MdApi::onQueryAllTickersFullInfo)
		;
}



