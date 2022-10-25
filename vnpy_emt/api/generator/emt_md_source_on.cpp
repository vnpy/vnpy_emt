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

void onError(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onError, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onIndexData(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onIndexData, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDepthMarketData(const dict &data, int64_t bid1_qty, int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty, int32_t ask1_count, int32_t max_ask1_count) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onDepthMarketData, data, bid1_qty, bid1_count, max_bid1_count, ask1_qty, ask1_count, max_ask1_count);
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

void onMinuteInfo(const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onMinuteInfo, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllIndexData(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllIndexData, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllIndexData(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllIndexData, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubIndexData(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubIndexData, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubIndexData(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubIndexData, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllMarketData(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllMarketData, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllMarketData(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllMarketData, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubMarketData(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubMarketData, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubMarketData(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubMarketData, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllTickByTick(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllTickByTick, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllTickByTick(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllTickByTick, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubTickByTick(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubTickByTick, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubTickByTick(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubTickByTick, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllOrderBook(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOrderBook, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllOrderBook(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOrderBook, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubOrderBook(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubOrderBook, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubOrderBook(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubOrderBook, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubscribeAllMinuteInfo(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllMinuteInfo, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubscribeAllMinuteInfo(int exchange_id, const dict &data) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllMinuteInfo, exchange_id, data);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onSubMinuteInfo(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onSubMinuteInfo, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onUnSubMinuteInfo(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onUnSubMinuteInfo, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryAllTickers(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryAllTickers, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryAllTickersFullInfo(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryAllTickersFullInfo, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryLatestIndexData(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryLatestIndexData, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryLatestMarketData(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryLatestMarketData, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryMinuteInfo(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryMinuteInfo, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryMinHistoryInfo(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryMinHistoryInfo, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryTickersPriceInfo(const dict &data, const dict &data, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, MdApi, onQueryTickersPriceInfo, data, data, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

