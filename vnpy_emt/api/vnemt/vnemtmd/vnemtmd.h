//系统
#ifdef WIN32
//#include "stdafx.h"
#endif

#include "vnemt.h"
#include "pybind11/pybind11.h"
#include "emt/emt_quote_api.h"


using namespace pybind11;
using namespace EMT::API;


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public QuoteSpi
{
private:
	QuoteApi* api = NULL;				//API对象
	bool active = false;		//工作状态

public:
	MdApi()
	{
	};

	~MdApi()
	{
		if (this->active)
		{
			this->exit();
		}
	};

	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

	///当客户端与行情后台通信连接断开时，该方法被调用。
	///@param reason 错误原因，请与错误代码表对应
	///@remark api不会自动重连，当断线发生时，请用户自行选择后续操作。可以在此函数中调用Login重新登录。注意用户重新登录后，需要重新订阅行情
	virtual void OnDisconnected(int reason);

	/**
	*   错误应答
	*   @attention					此函数只有在服务器发生错误时才会调用，一般无需用户处理
	*   @param error_info			当服务器响应发生错误时的具体错误内容
	*   @return						该函数返回为void
	*/
	virtual void OnError(EMTRspInfoStruct* error_info);

	/**
	*   指数行情通知
	*   @attention					需要快速返回，否则阻塞后续消息，导致延时，当阻塞严重时，会触发断线
	*   @param index_data			指数行情数据，只有指数行情数据相关字段
	*/
	virtual void OnIndexData(EMTIndexDataStruct* index_data);

	/**
	*   深度行情通知，包含买一卖一队列
	*   @attention					需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	*   @param market_data			行情数据
	*   @param bid1_qty				买一队列数据
	*   @param bid1_count			买一队列的有效委托笔数
	*   @param max_bid1_count		买一队列总委托笔数
	*   @param ask1_qty				卖一队列数据
	*   @param ask1_count			卖一队列的有效委托笔数
	*   @param max_ask1_count		卖一队列总委托笔数
	*/
	virtual void OnDepthMarketData(EMTMarketDataStruct* market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count);

	/**
	*   逐笔行情通知，包括股票，基金，权证，债券和质押式回购
	*   @attention					每条订阅的合约均对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
	*   @param tbt_data				逐笔行情数据，包括逐笔委托和逐笔成交，此为共用结构体，需要根据type来区分是逐笔委托还是逐笔成交
	*/
	virtual void OnTickByTick(EMTTickByTickStruct* tbt_data);

	/**
	*   行情订单簿通知
	*   @param order_book			行情订单簿数据，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	*/
	virtual void OnOrderBook(EMTOrderBookStruct* order_book);

	/**
	*   分时行情通知
	*   @param minute_info			分时行情数据，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	*/
	virtual void OnMinuteInfo(EMTMinuteInfo* minute_info);

	/**
	*   订阅全市场的指数行情应答
	*   @attention					需要快速返回
	*   @param exchange_id			交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*	@param error_info			订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnSubscribeAllIndexData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   退订全市场的指数行情应答
	*   @attention					需要快速返回
	*   @param exchange_id			交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*	@param error_info			取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnUnSubscribeAllIndexData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   订阅指数行情应答
	*   @attention					每条订阅的合约对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
	*   @param ticker				订阅的合约编号代码
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*	@param is_last				是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnSubIndexData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   退订指数行情应答
	*   @attention					每条订阅的合约对应一条退订应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
	*   @param ticker				订阅的合约编号代码
	*   @param error_info			取消订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*	@param is_last				是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnUnSubIndexData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   订阅全市场股票快照行情应答
	*   @attention					需要快速返回
	*   @param exchange_id			交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*	@param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnSubscribeAllMarketData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   退订全市场的股票快照行情应答
	*   @attention					需要快速返回
	*   @param exchange_id			交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*	@param error_info			取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnUnSubscribeAllMarketData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   订阅快照行情应答，包括股票，基金，债券，权证和质押式回购
	*   @attention					每条订阅的合约对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
	*   @param ticker				订阅的合约编号代码
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*	@param is_last				是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnSubMarketData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   退订快照行情应答，包括股票，基金，债券，权证和质押式回购
	*   @attention					每条订阅的合约对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
	*   @param ticker				订阅的合约编号代码
	*   @param error_info			取消订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*	@param is_last				是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnUnSubMarketData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   订阅全市场的逐笔行情应答
	*   @attention					需要快速返回
	*   @param exchange_id			交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*	@param error_info			订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnSubscribeAllTickByTick(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   退订全市场的逐笔行情应答
	*   @attention					需要快速返回
	*   @param exchange_id			交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*	@param error_info			取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnUnSubscribeAllTickByTick(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   订阅逐笔行情应答，包括股票，基金，债券和权证
	*   @attention					每条订阅的合约均对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
	*   @param ticker				订阅的合约代码编号
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*	@param is_last				是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnSubTickByTick(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   退订逐笔行情应答，包括股票，基金，债券和权证
	*   @attention					每条订阅的合约均对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
	*   @param ticker				订阅的合约代码编号
	*   @param error_info			取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*	@param is_last				是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnUnSubTickByTick(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   订阅行情订单簿应答
	*   @attention                  需要快速返回
	*   @param exchange_id          交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*   @param error_info           订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误*/
	virtual void OnSubscribeAllOrderBook(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   退订全市场的股票行情订单簿应答
	*   @attention                  需要快速返回
	*   @param exchange_id          交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*   @param error_info           取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnUnSubscribeAllOrderBook(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   订阅行情订单簿应答
	*   @attention                  需要快速返回
	*   @param ticker               订阅的合约代码编号
	*   @param error_info           订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last              是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnSubOrderBook(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   退订行情订单簿应答
	*   @attention                  需要快速返回
	*   @param ticker               订阅的合约编号代码
	*   @param error_info           取消订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last              是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnUnSubOrderBook(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   订阅全市场分时行情
	*   @attention                  需要快速返回
	*   @param exchange_id          交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*   @param error_info           订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnSubscribeAllMinuteInfo(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   退订全市场分时行情
	*   @attention                  需要快速返回
	*   @param exchange_id          交易所代码，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
	*   @param error_info           取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*/
	virtual void OnUnSubscribeAllMinuteInfo(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info);

	/**
	*   订阅分时行情
	*   @attention                  需要快速返回
	*   @param ticker               订阅的合约代码编号
	*   @param error_info           订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last              是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnSubMinuteInfo(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   退订分时行情
	*   @attention                  需要快速返回
	*   @param ticker               订阅的合约代码编号
	*   @param error_info           订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last              是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnUnSubMinuteInfo(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   查询全市场合约部分静态信息的应答
	*   @attention					需要使用合约部分静态信息结构体EMTQuoteStaticInfo
	*   @param qsi					合约部分静态信息结构体
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnQueryAllTickers(EMTQuoteStaticInfo* qsi, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   查询全市场合约完整静态信息的应答
	*   @attention					需要使用合约完整静态信息结构体EMTQutoFullInfo
	*   @param qfi					合约完整静态信息结构体
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnQueryAllTickersFullInfo(EMTQuoteFullInfo* qfi, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   查询合约最新指数的应答
	*   @attention					需要使用最新数据结构体EMTIndexDataStruct
	*   @param index_data			最新指数数据
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnQueryLatestIndexData(EMTIndexDataStruct* index_data, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   查询合约最新现货快照的应答
	*   @attention					需要使用最新数据结构体EMTIndexDataStruct
	*   @param market_data			最新现货快照数据
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnQueryLatestMarketData(EMTMarketDataStruct* market_data, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   查询分时数据的应答
	*   @attention					需要使用分时结构体EMTMinuteInfo
	*   @param minute_info			最新分时数据
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnQueryMinuteInfo(EMTMinuteInfo* minute_info, EMTRspInfoStruct* error_info, bool is_last);

	/**
	*   查询历史分时数据的应答
	*   @attention					需要使用分时结构体EMTMinuteInfo
	*   @param minute_info			历史分时数据
	*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnQueryMinHistoryInfo(EMTMinuteInfo* minute_info, EMTRspInfoStruct* error_info, bool is_last);

	/*
	* 查询最新价
	* @attention					需要使用最新价结构体EMTTickerPriceInfo
	* @param price_info				最新价格数据
	* @param error_info				订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	* @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	*/
	virtual void OnQueryTickersPriceInfo(EMTTickerPriceInfo* price_info, EMTRspInfoStruct* error_info, bool is_last);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//其他参数采用原名称
	//-------------------------------------------------------------------------------------

	virtual void onDisconnected(int reason) {};

	virtual void onError(const dict& data) {};

	virtual void onIndexData(const dict& data) {};

	virtual void onDepthMarketData(const dict& data) {};

	virtual void onTickByTick(const dict& data) {};

	virtual void onOrderBook(const dict& data) {};

	virtual void onMinuteInfo(const dict& data) {};

	virtual void onSubscribeAllIndexData(int exchange_id, const dict& data) {};

	virtual void onUnSubscribeAllIndexData(int exchange_id, const dict& data) {};

	virtual void onSubIndexData(const dict& data, const dict& error, bool is_last) {};

	virtual void onUnSubIndexData(const dict& data, const dict& error, bool is_last) {};

	virtual void onSubscribeAllMarketData(int exchange_id, const dict& data) {};

	virtual void onUnSubscribeAllMarketData(int exchange_id, const dict& data) {};

	virtual void onSubMarketData(const dict& data, const dict& error, bool is_last) {};

	virtual void onUnSubMarketData(const dict& data, const dict& error, bool is_last) {};

	virtual void onSubscribeAllTickByTick(int exchange_id, const dict& data) {};

	virtual void onUnSubscribeAllTickByTick(int exchange_id, const dict& data) {};

	virtual void onSubTickByTick(const dict& data, const dict& error, bool is_last) {};

	virtual void onUnSubTickByTick(const dict& data, const dict& error, bool is_last) {};

	virtual void onSubscribeAllOrderBook(int exchange_id, const dict& data) {};

	virtual void onUnSubscribeAllOrderBook(int exchange_id, const dict& data) {};

	virtual void onSubOrderBook(const dict& data, const dict& error, bool is_last) {};

	virtual void onUnSubOrderBook(const dict& data, const dict& error, bool is_last) {};

	virtual void onSubscribeAllMinuteInfo(int exchange_id, const dict& data) {};

	virtual void onUnSubscribeAllMinuteInfo(int exchange_id, const dict& data) {};

	virtual void onSubMinuteInfo(const dict& data, const dict& error, bool is_last) {};

	virtual void onUnSubMinuteInfo(const dict& data, const dict& error, bool is_last) {};

	virtual void onQueryAllTickers(const dict& data, const dict& error, bool is_last) {};

	virtual void onQueryAllTickersFullInfo(const dict& data, const dict& error, bool is_last) {};

	virtual void onQueryLatestIndexData(const dict& data, const dict& error, bool is_last) {};

	virtual void onQueryLatestMarketData(const dict& data, const dict& error, bool is_last) {};

	virtual void onQueryMinuteInfo(const dict& data, const dict& error, bool is_last) {};

	virtual void onQueryMinHistoryInfo(const dict& data, const dict& error, bool is_last) {};

	virtual void onQueryTickersPriceInfo(const dict& data, const dict& error, bool is_last) {};


	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createQuoteApi(int client_id, string save_file_path, int data_type, int log_level);

	void release();

	void init();

	int exit();

	//string getTradingDay();这个函数在交易API里面

	string getApiVersion();

	dict getApiLastError();

	void setUDPBufferSize(int buff_size);

	void setHeartBeatInterval(int interval);

	int subscribeMarketData(string ticker, int count, int exchange_id);

	int unSubscribeMarketData(string ticker, int count, int exchange_id);

	int subscribeOrderBook(string ticker, int count, int exchange_id);

	int unSubscribeOrderBook(string ticker, int count, int exchange_id);

	int subscribeTickByTick(string ticker, int count, int exchange_id);

	int unSubscribeTickByTick(string ticker, int count, int exchange_id);

	int subscribeAllMarketData(int exchange_id);

	int unSubscribeAllMarketData(int exchange_id);

	int subscribeAllOrderBook(int exchange_id);

	int unSubscribeAllOrderBook(int exchange_id);

	int subscribeAllTickByTick(int exchange_id);

	int unSubscribeAllTickByTick(int exchange_id);

	int login(string ip, int port, string user, string password, int sock_type, string local_ip);

	int logout();

	int queryAllTickers(int exchange_id);

	int queryAllTickersFullInfo(int exchange_id);

	int queryLatestInfo(string ticker, int ticker_type, int exchange_id);

	int queryMinuteInfo(string tickers, int count, int ticker_type, int exchange_id);

	int queryMinHistoryInfo(string tickers, int count, int datetime, int ticker_type, int exchange_id);

	int queryTickersPriceInfo(string tickers, int count, int exchange_id);


};
