virtual void onDisconnected(int reason) {};

virtual void onError(const dict &data) {};

virtual void onIndexData(const dict &data) {};

virtual void onDepthMarketData(const dict &data, int64_t bid1_qty, int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty, int32_t ask1_count, int32_t max_ask1_count) {};

virtual void onTickByTick(const dict &data) {};

virtual void onOrderBook(const dict &data) {};

virtual void onMinuteInfo(const dict &data) {};

virtual void onSubscribeAllIndexData(int exchange_id, const dict &data) {};

virtual void onUnSubscribeAllIndexData(int exchange_id, const dict &data) {};

virtual void onSubIndexData(const dict &data, const dict &data, bool is_last) {};

virtual void onUnSubIndexData(const dict &data, const dict &data, bool is_last) {};

virtual void onSubscribeAllMarketData(int exchange_id, const dict &data) {};

virtual void onUnSubscribeAllMarketData(int exchange_id, const dict &data) {};

virtual void onSubMarketData(const dict &data, const dict &data, bool is_last) {};

virtual void onUnSubMarketData(const dict &data, const dict &data, bool is_last) {};

virtual void onSubscribeAllTickByTick(int exchange_id, const dict &data) {};

virtual void onUnSubscribeAllTickByTick(int exchange_id, const dict &data) {};

virtual void onSubTickByTick(const dict &data, const dict &data, bool is_last) {};

virtual void onUnSubTickByTick(const dict &data, const dict &data, bool is_last) {};

virtual void onSubscribeAllOrderBook(int exchange_id, const dict &data) {};

virtual void onUnSubscribeAllOrderBook(int exchange_id, const dict &data) {};

virtual void onSubOrderBook(const dict &data, const dict &data, bool is_last) {};

virtual void onUnSubOrderBook(const dict &data, const dict &data, bool is_last) {};

virtual void onSubscribeAllMinuteInfo(int exchange_id, const dict &data) {};

virtual void onUnSubscribeAllMinuteInfo(int exchange_id, const dict &data) {};

virtual void onSubMinuteInfo(const dict &data, const dict &data, bool is_last) {};

virtual void onUnSubMinuteInfo(const dict &data, const dict &data, bool is_last) {};

virtual void onQueryAllTickers(const dict &data, const dict &data, bool is_last) {};

virtual void onQueryAllTickersFullInfo(const dict &data, const dict &data, bool is_last) {};

virtual void onQueryLatestIndexData(const dict &data, const dict &data, bool is_last) {};

virtual void onQueryLatestMarketData(const dict &data, const dict &data, bool is_last) {};

virtual void onQueryMinuteInfo(const dict &data, const dict &data, bool is_last) {};

virtual void onQueryMinHistoryInfo(const dict &data, const dict &data, bool is_last) {};

virtual void onQueryTickersPriceInfo(const dict &data, const dict &data, bool is_last) {};

