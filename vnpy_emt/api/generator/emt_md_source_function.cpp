int MdApi::queryAllTickers(int exchange_id)
{
	int i = this->api->QueryAllTickers(exchange_id);
	return i;
};

int MdApi::queryAllTickersFullInfo(int exchange_id)
{
	int i = this->api->QueryAllTickersFullInfo(exchange_id);
	return i;
};

int MdApi::queryLatestInfo(char tickers, int count, int ticker_type, int exchange_id)
{
	int i = this->api->QueryLatestInfo(tickers, count, ticker_type, exchange_id);
	return i;
};

int MdApi::queryMinuteInfo(char tickers, int count, int ticker_type, int exchange_id)
{
	int i = this->api->QueryMinuteInfo(tickers, count, ticker_type, exchange_id);
	return i;
};

int MdApi::queryMinHistoryInfo(char tickers, int count, int datetime, int ticker_type, int exchange_id)
{
	int i = this->api->QueryMinHistoryInfo(tickers, count, datetime, ticker_type, exchange_id);
	return i;
};

int MdApi::queryTickersPriceInfo(char tickers, int count, int exchange_id)
{
	int i = this->api->QueryTickersPriceInfo(tickers, count, exchange_id);
	return i;
};

