int queryAllTickers(int exchange_id);

int queryAllTickersFullInfo(int exchange_id);

int queryLatestInfo(char tickers, int count, int ticker_type, int exchange_id);

int queryMinuteInfo(char tickers, int count, int ticker_type, int exchange_id);

int queryMinHistoryInfo(char tickers, int count, int datetime, int ticker_type, int exchange_id);

int queryTickersPriceInfo(char tickers, int count, int exchange_id);

