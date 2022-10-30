//系统
#ifdef WIN32
//#include "stdafx.h"
#endif

#include "vnemt.h"
#include "pybind11/pybind11.h"
#include "emt/emt_trader_api.h"


using namespace pybind11;
using namespace EMT::API;


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public TraderSpi
{
private:
	TraderApi* api = NULL;            //API对象
	bool active = false;       //工作状态

public:
	TdApi()
	{
	};

	~TdApi()
	{
		if (this->active)
		{
			this->exit();
		}
	};

	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

    ///连接成功通知
            ///@remark 当客户端与交易后台成功建立连接时，该方法被调用；OnConnected接口仅用作连接成功通知，需要快速返回，用户无需在此函数中做特殊处理
    virtual void OnConnected();

    ///断线通知
    ///@param reason 错误原因，请与错误代码表对应
    ///@remark 当客户端与交易后台的通信连接断开时，该方法被调用；api内部支持自动重连机制，OnDisconnected接口仅用做断线通知，需要快速返回，用户无需在此函数中做特殊处理
    virtual void OnDisconnected(int reason);

    ///错误应答
    ///@param error_info 当服务器响应发生错误时的具体的错误代码和错误信息,当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@remark 此函数只有在服务器发生错误时才会调用，一般无需用户处理
    virtual void OnError(EMTRI* error_info);

    ///报单通知
    ///@param order_info 订单响应具体信息，用户可以通过order_info.order_emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单，order_info.qty_left字段在订单为未成交、部成、全成、废单状态时，表示此订单还没有成交的数量，在部撤、全撤状态时，表示此订单被撤的数量。order_info.order_cancel_emt_id为其所对应的撤单ID，不为0时表示此单被撤成功
    ///@param error_info 订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 每次订单状态更新时，都会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，在订单未成交、全部成交、全部撤单、部分撤单、已拒绝这些状态时会有响应，对于部分成交的情况，请由订单的成交回报来自行确认。所有登录了此用户的客户端都将收到此用户的订单响应
    virtual void OnOrderEvent(EMTOrderInfo* order_info, EMTRI* error_info, uint64_t session_id);

    ///成交通知
    ///@param trade_info 成交回报的具体信息，用户可以通过trade_info.order_emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。对于上交所，exec_id可以唯一标识一笔成交。当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交了。对于深交所，exec_id是唯一的，暂时无此判断机制。report_index+market字段可以组成唯一标识表示成交回报。
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 订单有成交发生的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的成交回报。相关订单为部成状态，需要用户通过成交回报的成交数量来确定，OnOrderEvent()不会推送部成状态。
    virtual void OnTradeEvent(EMTTradeReport* trade_info, uint64_t session_id);

    ///撤单出错响应
    ///@param cancel_info 撤单具体信息，包括撤单的order_cancel_emt_id和待撤单的order_emt_id
    ///@param error_info 撤单被拒绝或者发生错误时错误代码和错误信息，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 此响应只会在撤单发生错误时被回调
    virtual void OnCancelOrderError(EMTOrderCancelInfo* cancel_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询报单响应
    ///@param order_info 查询到的一个报单
    ///@param error_info 查询报单时发生错误时，返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryOrder(EMTQueryOrderRsp* order_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询报单响应
    ///@param order_info 查询到的一个报单
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryOrderByPage(EMTQueryOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询成交响应
    ///@param trade_info 查询到的一个成交回报
    ///@param error_info 查询成交回报发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryTrade(EMTQueryTradeRsp* trade_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询成交响应
    ///@param trade_info 查询到的一个成交信息
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryTradeByPage(EMTQueryTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询投资者持仓响应
    ///@param position 查询到的一只股票的持仓情况
    ///@param error_info 查询账户持仓发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于用户可能持有多个股票，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryPosition(EMTQueryStkPositionRsp* position, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询持仓响应
    ///@param trade_info 查询到的一个持仓信息
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryPositionByPage(EMTQueryStkPositionRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询资金账户响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param asset 查询到的资金账户情况
    ///@param error_info 查询资金账户发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryAsset(EMTQueryAssetRsp* asset, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询资金划拨订单响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_transfer_info 查询到的资金账户情况
    ///@param error_info 查询资金账户发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryFundTransfer(EMTFundTransferNotice* fund_transfer_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///资金划拨通知
    ///@param fund_transfer_info 资金划拨通知的具体信息，用户可以通过fund_transfer_info.serial_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 资金划拨订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。当资金划拨方向为一号两中心节点之间划拨，且error_info.error_id=11000384时，error_info.error_msg为结点中可用于划拨的资金（以整数为准），用户需进行stringToInt的转化，可据此填写合适的资金，再次发起划拨请求
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当资金划拨订单有状态变化的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的资金划拨通知。
    virtual void OnFundTransfer(EMTFundTransferNotice* fund_transfer_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询其他节点可用资金的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_info 查询到的其他节点可用资金情况
    ///@param error_info 查询其他节点可用资金发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryOtherServerFund(EMTFundQueryRsp* fund_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///请求查询ETF清单文件的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param etf_info 查询到的ETF清单文件情况
    ///@param error_info 查询ETF清单文件发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryETF(EMTQueryETFBaseRsp* etf_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询ETF股票篮的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param etf_component_info 查询到的ETF合约的相关成分股信息
    ///@param error_info 查询ETF股票篮发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryETFBasket(EMTQueryETFComponentRsp* etf_component_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询今日新股申购信息列表的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param ipo_info 查询到的今日新股申购的一只股票信息
    ///@param error_info 查询今日新股申购信息列表发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryIPOInfoList(EMTQueryIPOTickerRsp* ipo_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询用户新股申购额度信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param quota_info 查询到的用户某个市场的今日新股申购额度信息
    ///@param error_info 查查询用户新股申购额度信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryIPOQuotaInfo(EMTQueryIPOQuotaRsp* quota_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询期权合约的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param option_info 查询到的期权合约情况
    ///@param error_info 查询期权合约发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryOptionAuctionInfo(EMTQueryOptionAuctionInfoRsp* option_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///融资融券业务中现金直接还款的响应
    ///@param cash_repay_info 现金直接还款通知的具体信息，用户可以通过cash_repay_info.emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 现金还款发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnCreditCashRepay(EMTCrdCashRepayRsp* cash_repay_info, EMTRI* error_info, uint64_t session_id);

    ///融资融券业务中现金还息的响应
    ///@param cash_repay_info 现金还息通知的具体信息，用户可以通过cash_repay_info.emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 现金还息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnCreditCashRepayDebtInterestFee(EMTCrdCashRepayDebtInterestFeeRsp* cash_repay_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询融资融券业务中的现金直接还款报单的响应
    ///@param cash_repay_info 查询到的某一笔现金直接还款通知的具体信息
    ///@param error_info 查询现金直接报单发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditCashRepayInfo(EMTCrdCashRepayInfo* cash_repay_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询信用账户额外信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_info 查询到的信用账户额外信息情况
    ///@param error_info 查询信用账户额外信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditFundInfo(EMTCrdFundInfo* fund_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///请求查询信用账户负债信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param debt_info 查询到的信用账户合约负债情况
    ///@param error_info 查询信用账户负债信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditDebtInfo(EMTCrdDebtInfo* debt_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询负债信息响应
    ///@param debt_info 查询到的一个负债信息
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前负债信息信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有负债信息，可以进行下一次分页查询，如果不等，表示所有负债信息已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryCreditDebtInfoByPage(EMTCrdDebtInfo* debt_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询信用账户指定证券负债未还信息响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param debt_info 查询到的信用账户指定证券负债未还信息情况
    ///@param error_info 查询信用账户指定证券负债未还信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditTickerDebtInfo(EMTCrdDebtStockInfo* debt_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询信用账户待还资金的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param remain_amount 查询到的信用账户待还资金
    ///@param error_info 查询信用账户待还资金发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditAssetDebtInfo(double remain_amount, EMTRI* error_info, int request_id, uint64_t session_id);

    ///请求查询信用账户可融券头寸信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param assign_info 查询到的信用账户可融券头寸信息
    ///@param error_info 查询信用账户可融券头寸信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditTickerAssignInfo(EMTClientQueryCrdPositionStkInfo* assign_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询证券头寸信息响应
    ///@param debt_info 查询到的一个证券头寸信息
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前证券头寸信息信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有证券头寸信息，可以进行下一次分页查询，如果不等，表示所有证券头寸信息已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryCreditTickerAssignInfoByPage(EMTClientQueryCrdPositionStkInfo* debt_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///融资融券业务中请求查询指定余券信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param stock_info 查询到的余券信息
    ///@param error_info 查询信用账户余券信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditExcessStock(EMTClientQueryCrdSurplusStkRspInfo* stock_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///融资融券业务中请求查询余券信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param stock_info 查询到的余券信息
    ///@param error_info 查询信用账户余券信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryMulCreditExcessStock(EMTClientQueryCrdSurplusStkRspInfo* stock_info, EMTRI* error_info, int request_id, uint64_t session_id, bool is_last);

    ///融资融券业务中负债合约展期的通知
    ///@param debt_extend_info 负债合约展期通知的具体信息，用户可以通过debt_extend_info.emtid来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 负债合约展期订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当负债合约展期订单有状态变化的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的负债合约展期通知。
    virtual void OnCreditExtendDebtDate(EMTCreditDebtExtendNotice* debt_extend_info, EMTRI* error_info, uint64_t session_id);

    ///查询融资融券业务中负债合约展期订单响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param debt_extend_info 查询到的负债合约展期情况
    ///@param error_info 查询负债合约展期发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。当error_info.error_id=11000350时，表明没有记录，当为其他非0值时，表明合约发生拒单时的错误原因
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditExtendDebtDateOrders(EMTCreditDebtExtendNotice* debt_extend_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询融资融券业务中信用账户附加信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_info 信用账户附加信息
    ///@param error_info 查询信用账户附加信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditFundExtraInfo(EMTCrdFundExtraInfo* fund_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///查询融资融券业务中信用账户指定证券的附加信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_info 信用账户指定证券的附加信息
    ///@param error_info 查询信用账户附加信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditPositionExtraInfo(EMTCrdPositionExtraInfo* fund_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///期权组合策略报单通知
    ///@param order_info 订单响应具体信息，用户可以通过order_info.order_emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单，order_info.qty_left字段在订单为未成交、部成、全成、废单状态时，表示此订单还没有成交的数量，在部撤、全撤状态时，表示此订单被撤的数量。order_info.order_cancel_emt_id为其所对应的撤单ID，不为0时表示此单被撤成功
    ///@param error_info 订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 每次订单状态更新时，都会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，在订单未成交、全部成交、全部撤单、部分撤单、已拒绝这些状态时会有响应，对于部分成交的情况，请由订单的成交回报来自行确认。所有登录了此用户的客户端都将收到此用户的订单响应
    virtual void OnOptionCombinedOrderEvent(EMTOptCombOrderInfo* order_info, EMTRI* error_info, uint64_t session_id);

    ///期权组合策略成交通知
    ///@param trade_info 成交回报的具体信息，用户可以通过trade_info.order_emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。对于上交所，exec_id可以唯一标识一笔成交。当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交了。对于深交所，exec_id是唯一的，暂时无此判断机制。report_index+market字段可以组成唯一标识表示成交回报。
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 订单有成交发生的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的成交回报。相关订单为部成状态，需要用户通过成交回报的成交数量来确定，OnOrderEvent()不会推送部成状态。
    virtual void OnOptionCombinedTradeEvent(EMTOptCombTradeReport* trade_info, uint64_t session_id);

    ///期权组合策略撤单出错响应
    ///@param cancel_info 撤单具体信息，包括撤单的order_cancel_emt_id和待撤单的order_emt_id
    ///@param error_info 撤单被拒绝或者发生错误时错误代码和错误信息，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 此响应只会在撤单发生错误时被回调
    virtual void OnCancelOptionCombinedOrderError(EMTOptCombOrderCancelInfo* cancel_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询期权组合策略报单响应
    ///@param order_info 查询到的一个报单
    ///@param error_info 查询报单时发生错误时，返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。此对应的请求函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    virtual void OnQueryOptionCombinedOrders(EMTQueryOptCombOrderRsp* order_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询期权组合策略报单响应
    ///@param order_info 查询到的一个报单
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryOptionCombinedOrdersByPage(EMTQueryOptCombOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询期权组合策略成交响应
    ///@param trade_info 查询到的一个成交回报
    ///@param error_info 查询成交回报发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。此对应的请求函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    virtual void OnQueryOptionCombinedTrades(EMTQueryOptCombTradeRsp* trade_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询期权组合策略成交响应
    ///@param trade_info 查询到的一个成交信息
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryOptionCombinedTradesByPage(EMTQueryOptCombTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询期权组合策略持仓响应
    ///@param position_info 查询到的一个持仓信息
    ///@param error_info 查询持仓发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryOptionCombinedPosition(EMTQueryOptCombPositionRsp* position_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询期权组合策略信息响应
    ///@param strategy_info 查询到的一个组合策略信息
    ///@param error_info 查询成交回报发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryOptionCombinedStrategyInfo(EMTQueryCombineStrategyInfoRsp* strategy_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询融资融券业务中担保品折算率的响应
    ///@param pledge_stk_rate_info 担保品折算率信息，查询发生错误时返回空
    ///@param error_info 查询担保品折算率发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    virtual void OnQueryCreditPledgeStkRate(EMTClientQueryCreditPledgeStkRateRsp* pledge_stk_rate_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询期权行权合并头寸的响应
    ///@param position_info 查询到的一个行权合并头寸信息
    ///@param error_info 查询持仓发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    virtual void OnQueryOptionCombinedExecPosition(EMTQueryOptCombExecPosRsp* position_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询融资融券保证金率响应
    ///@param margin_rate_info 融资融券保证金率信息，查询发生错误时返回空
    ///@param error_info 查询融资融券保证金率发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    virtual void OnQueryCreditMarginRate(EMTClientQueryCreditMarginRateRsp* margin_rate_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询融券头寸全额占用费率响应
    ///@param position_fullrate_info 融券头寸全额占用费率信息，查询发生错误时返回空
    ///@param error_info 查询融券头寸全额占用费率发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    virtual void OnQueryCreditPositionFullRate(EMTClientQueryCreditPositionFullRateRsp* position_fullrate_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///融资融券可担保证券分页查询响应
    ///@param pledge_stk_info 融资融券可担保证券信息，查询发生错误时返回空
    ///@param error_info 融资融券可担保证券分页查询发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    virtual void OnQueryCreditPledgeStkPagination(EMTClientQueryCreditPledgeStkPaginationRsp* pledge_stk_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///融资融券标的证券分页查询响应
    ///@param target_stk_info 融资融券标的证券信息，查询发生错误时返回空
    ///@param error_info 融资融券标的证券分页查询发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    virtual void OnQueryCreditTargetStkPagination(EMTClientQueryCreditTargetStkPaginationRsp* target_stk_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///请求查询配股业务信息列表的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param issue_info 查询到的今日配股的一只股票信息
    ///@param error_info 查询今日配股信息列表发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryIssueInfoList(EMTQueryIssueTickerRsp* issue_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询Security信息响应
    ///@param security 查询到的一只证券的详细信息
    ///@param error_info 查询证券信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于用户可能查询多个股票信息，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQuerySecurityInfo(EMTQuerySecurityInfoRsp* security, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///融资融券两地分仓信用额度调拨通知
    ///@param quota_transfer_info 信用额度调拨通知的具体信息，用户可以通过quota_transfer_info.serial_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 信用额度调拨订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当信用额度调拨订单有状态变化的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的额度调拨通知。
    virtual void OnCreditQuotaTransfer(EMTQuotaTransferNotice* quota_transfer_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询融资融券两地分仓信用额度调拨订单响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param quota_transfer_info 信用额度调拨通知的具体信息
    ///@param error_info 查询信用额度发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryCreditQuotaTransfer(EMTQuotaTransferNotice* quota_transfer_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询昨日资产响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param yesterday_asset 查询到的昨日资产情况            
    ///@param error_info 查询昨日资产发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    virtual void OnQueryYesterdayAsset(EMTQueryYesterdayAssetRsp* yesterday_asset, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///场外Otc分页请求查询持仓响应
    ///@param position_info 查询到的一个持仓信息
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    ///virtual void OnQueryOtcPositionByPage(EMTOtcPositionInfo* position_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///场外Otc请求查询资金账户响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param asset 查询到的资金账户情况
    ///@param error_info 查询资金账户发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///virtual void OnQueryOtcAsset(EMTOtcAssetInfo* asset, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///场外Otc分页请求查询委托响应
    ///@param order_info 查询到的一个报单
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryOtcOrderByPage(EMTQueryOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///场外Otc分页请求查询成交响应
    ///@param trade_info 查询到的一个报单
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryOtcTradeByPage(EMTQueryTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询ETF清单文件响应
    ///@param etf_info 查询到的一个ETF信息
    ///@param req_count 请求到的最大数量
    ///@param rsp_sequence 分页请求的当前回报数量
    ///@param query_reference 当前信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当rsp_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果rsp_sequence等于req_count，那么表示还有信息，可以进行下一次分页查询，如果不等，表示所有结果已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQueryETFByPage(EMTQueryETFBaseRsp* etf_info, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询标的基础信息响应
    ///@param security_info 查询到的一个标的信息
    ///@param req_count 请求到的最大数量
    ///@param rsp_sequence 分页请求的当前回报数量
    ///@param query_reference 当前信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当rsp_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果rsp_sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    virtual void OnQuerySecurityByPage(EMTQuerySecurityByPageRsp* security_info, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//-------------------------------------------------------------------------------------

    virtual void onConnected() {};

    virtual void onDisconnected(int reason) {};

    virtual void onError(const dict& error) {};

    virtual void onOrderEvent(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onTradeEvent(const dict& data, uint64_t session_id) {};

    virtual void onCancelOrderError(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onQueryOrder(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOrderByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryTrade(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryTradeByPage(const dict& data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryPosition(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryPositionByPage(const dict& data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryAsset(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryFundTransfer(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onFundTransfer(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onQueryOtherServerFund(const dict& data, const dict& error, int request_id, uint64_t session_id) {};

    virtual void onQueryETF(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryETFBasket(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryIPOInfoList(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryIPOQuotaInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOptionAuctionInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onCreditCashRepay(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onCreditCashRepayDebtInterestFee(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onQueryCreditCashRepayInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditFundInfo(const dict& data, const dict& error, int request_id, uint64_t session_id) {};

    virtual void onQueryCreditDebtInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditDebtInfoByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditTickerDebtInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditAssetDebtInfo(double remain_amount, const dict& error, int request_id, uint64_t session_id) {};

    virtual void onQueryCreditTickerAssignInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditTickerAssignInfoByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditExcessStock(const dict& data, const dict& error, int request_id, uint64_t session_id) {};

    virtual void onQueryMulCreditExcessStock(const dict& data, const dict& error, int request_id, uint64_t session_id, bool is_last) {};

    virtual void onCreditExtendDebtDate(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onQueryCreditExtendDebtDateOrders(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditFundExtraInfo(const dict& data, const dict& error, int request_id, uint64_t session_id) {};

    virtual void onQueryCreditPositionExtraInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onOptionCombinedOrderEvent(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onOptionCombinedTradeEvent(const dict& data, uint64_t session_id) {};

    virtual void onCancelOptionCombinedOrderError(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onQueryOptionCombinedOrders(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOptionCombinedOrdersByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOptionCombinedTrades(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOptionCombinedTradesByPage(const dict& data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOptionCombinedPosition(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOptionCombinedStrategyInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditPledgeStkRate(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOptionCombinedExecPosition(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditMarginRate(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditPositionFullRate(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryCreditPledgeStkPagination(const dict& data, const dict& error, int request_id, uint64_t session_id) {};

    virtual void onQueryCreditTargetStkPagination(const dict& data, const dict& error, int request_id, uint64_t session_id) {};

    virtual void onQueryIssueInfoList(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQuerySecurityInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onCreditQuotaTransfer(const dict& data, const dict& error, uint64_t session_id) {};

    virtual void onQueryCreditQuotaTransfer(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryYesterdayAsset(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOtcPositionByPage(EMTOtcPositionInfo position_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOtcAsset(EMTOtcAssetInfo asset, const dict& error, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOtcOrderByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryOtcTradeByPage(const dict& data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQueryETFByPage(const dict& data, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

    virtual void onQuerySecurityByPage(const dict& data, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};




	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createTraderApi(int client_id, string save_file_path, int log_level);

	void release();

	void init();

	int exit();

	string getTradingDay();

	string getApiVersion();

	dict getApiLastError();

	int getClientIDByXTPID(uint64_t order_xtp_id);

	string getAccountByXTPID(uint64_t order_xtp_id);

	void subscribePublicTopic(int resume_type);

	void setSoftwareVersion(string version);

	///void setSoftwareKey(string key);

	void setHeartBeatInterval(int interval);

	uint64_t login(string ip, int port, string user, string password, int sock_type);

	int logout(uint64_t session_id);

	bool isServerRestart(uint64_t session_id);

	///int modifyUserTerminalInfo(const dict &req, uint64_t session_id);

	uint64_t insertOrder(const dict &req, uint64_t session_id);

	uint64_t cancelOrder(uint64_t order_xtp_id, uint64_t session_id);

    int queryOrderByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id);

    int queryOrders(const dict& req, uint64_t session_id, int request_id);

    int queryUnfinishedOrders(uint64_t session_id, int request_id);

    int queryOrdersByPage(const dict& req, uint64_t session_id, int request_id);

    int queryTradesByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id);

    int queryTrades(const dict& req, uint64_t session_id, int request_id);

    int queryTradesByPage(const dict& req, uint64_t session_id, int request_id);

    int queryPosition(string ticker, uint64_t session_id, int request_id, int market);

    int queryPositionByPage(const dict& req, uint64_t session_id, int request_id);

    int queryAsset(uint64_t session_id, int request_id);

    int queryFundTransfer(const dict& req, uint64_t session_id, int request_id);

    int queryOtherServerFund(const dict& req, uint64_t session_id, int request_id);

    int queryETF(const dict& req, uint64_t session_id, int request_id);

    int queryETFTickerBasket(const dict& req, uint64_t session_id, int request_id);

    int queryIPOInfoList(uint64_t session_id, int request_id);

    int queryIPOQuotaInfo(uint64_t session_id, int request_id);

    int queryOptionAuctionInfo(const dict& req, uint64_t session_id, int request_id);

    int queryCreditCashRepayInfo(uint64_t session_id, int request_id);

    int queryCreditFundInfo(uint64_t session_id, int request_id);

    int queryCreditDebtInfo(uint64_t session_id, int request_id);

    ///int queryCreditDebtInfoByPage(const dict& req, uint64_t session_id, int request_id);

    int queryCreditTickerDebtInfo(const dict& req, uint64_t session_id, int request_id);

    int queryCreditAssetDebtInfo(uint64_t session_id, int request_id);

    int queryCreditTickerAssignInfo(const dict& req, uint64_t session_id, int request_id);

    int queryCreditTickerAssignInfoByPage(const dict& req, uint64_t session_id, int request_id);

    int queryCreditExcessStock(const dict& req, uint64_t session_id, int request_id);

    int queryMulCreditExcessStock(const dict& req, uint64_t session_id, int request_id);

    int queryCreditExtendDebtDateOrders(uint64_t emt_id, uint64_t session_id, int request_id);

    int queryCreditFundExtraInfo(uint64_t session_id, int request_id);

    int queryCreditPositionExtraInfo(const dict& req, uint64_t session_id, int request_id);

    int queryOptionCombinedUnfinishedOrders(uint64_t session_id, int request_id);

    int queryOptionCombinedOrderByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id);

    int queryOptionCombinedOrders(const dict& req, uint64_t session_id, int request_id);

    int queryOptionCombinedOrdersByPage(const dict& req, uint64_t session_id, int request_id);

    int queryOptionCombinedTradesByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id);

    int queryOptionCombinedTrades(const dict& req, uint64_t session_id, int request_id);

    int queryOptionCombinedTradesByPage(const dict& req, uint64_t session_id, int request_id);

    int queryOptionCombinedPosition(const dict& req, uint64_t session_id, int request_id);

    int queryOptionCombinedStrategyInfo(uint64_t session_id, int request_id);

    int queryCreditPledgeStkRate(const dict& req, uint64_t session_id, int request_id);

    int queryOptionCombinedExecPosition(const dict& req, uint64_t session_id, int request_id);

    int queryCreditMarginRate(const dict& req, uint64_t session_id, int request_id);

    int queryCreditPositionFullRate(const dict& req, uint64_t session_id, int request_id);

    int queryCreditPledgeStkPagination(const dict& req, uint64_t session_id, int request_id);

    int queryCreditTargetStkPagination(const dict& req, uint64_t session_id, int request_id);

    int queryIssueInfoList(uint64_t session_id, int request_id);

    int querySecurityInfo(const dict& req, uint64_t session_id, int request_id);

    int queryCreditQuotaTransfer(const dict& req, uint64_t session_id, int request_id);

    int queryYesterdayAsset(uint64_t session_id, int request_id);

    int queryOtcPositionByPage(const dict& req, uint64_t session_id, int request_id);

    int queryOtcAsset(uint64_t session_id, int request_id);

    int queryOtcOrdersByPage(const dict& req, uint64_t session_id, int request_id);

    int queryOtcTradesByPage(const dict& req, uint64_t session_id, int request_id);

    int queryETFByPage(const dict& req, uint64_t session_id, int request_id);

    int querySecurityByPage(const dict& req, uint64_t session_id, int request_id);

};
