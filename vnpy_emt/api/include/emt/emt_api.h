#ifndef __EMT_API_H__
#define __EMT_API_H__

#include "emt_api_struct.h"

#ifdef WIN32
#ifdef  ONEDLL_EXPORTS
#define EMTAPI_EXPORTS  __declspec(dllexport)
#else
#define EMTAPI_EXPORTS  __declspec(dllimport)
#endif
#else 
#define EMTAPI_EXPORTS
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************回调函数定义*******************************************************************/
    ///连接成功通知
    ///@remark 当客户端与交易后台成功建立连接时，该方法被调用；OnConnected接口仅用作连接成功通知，需要快速返回，用户无需在此函数中做特殊处理
    typedef void (*EMT_OnConnected)();
    
    ///断线通知
    ///@param reason 错误原因，请与错误代码表对应
    ///@remark 当客户端与交易后台的通信连接断开时，该方法被调用；api内部支持自动重连机制，OnDisconnected接口仅用做断线通知，需要快速返回，用户无需在此函数中做特殊处理
    typedef void (*EMT_OnDisconnected)(int reason);

    ///错误应答
    ///@param error_info 当服务器响应发生错误时的具体的错误代码和错误信息,当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@remark 此函数只有在服务器发生错误时才会调用，一般无需用户处理
    typedef void (*EMT_OnError)(EMTRI* error_info);

    ///报单通知
    ///@param order_info 订单响应具体信息，用户可以通过order_info.order_emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单，order_info.qty_left字段在订单为未成交、部成、全成、废单状态时，表示此订单还没有成交的数量，在部撤、全撤状态时，表示此订单被撤的数量。order_info.order_cancel_emt_id为其所对应的撤单ID，不为0时表示此单被撤成功
    ///@param error_info 订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 每次订单状态更新时，都会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，在订单未成交、全部成交、全部撤单、部分撤单、已拒绝这些状态时会有响应，对于部分成交的情况，请由订单的成交回报来自行确认。所有登录了此用户的客户端都将收到此用户的订单响应
    typedef void (*EMT_OnOrderEvent)(EMTOrderInfo* order_info, EMTRI* error_info, uint64_t session_id);

    ///成交通知
    ///@param trade_info 成交回报的具体信息，用户可以通过trade_info.order_emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。对于上交所，exec_id可以唯一标识一笔成交。当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交了。对于深交所，exec_id是唯一的，暂时无此判断机制。report_index+market字段可以组成唯一标识表示成交回报。
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 订单有成交发生的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的成交回报。相关订单为部成状态，需要用户通过成交回报的成交数量来确定，OnOrderEvent()不会推送部成状态。
    typedef void (*EMT_OnTradeEvent)(EMTTradeReport* trade_info, uint64_t session_id);

    ///撤单出错响应
    ///@param cancel_info 撤单具体信息，包括撤单的order_cancel_emt_id和待撤单的order_emt_id
    ///@param error_info 撤单被拒绝或者发生错误时错误代码和错误信息，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 此响应只会在撤单发生错误时被回调
    typedef void (*EMT_OnCancelOrderError)(EMTOrderCancelInfo* cancel_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询报单响应
    ///@param order_info 查询到的一个报单
    ///@param error_info 查询报单时发生错误时，返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryOrder)(EMTQueryOrderRsp* order_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询报单响应
    ///@param order_info 查询到的一个报单
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryOrderByPage)(EMTQueryOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询成交响应
    ///@param trade_info 查询到的一个成交回报
    ///@param error_info 查询成交回报发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryTrade)(EMTQueryTradeRsp* trade_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询成交响应
    ///@param trade_info 查询到的一个成交信息
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryTradeByPage)(EMTQueryTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询投资者持仓响应
    ///@param position 查询到的一只股票的持仓情况
    ///@param error_info 查询账户持仓发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于用户可能持有多个股票，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryPosition)(EMTQueryStkPositionRsp* position, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询资金账户响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param asset 查询到的资金账户情况
    ///@param error_info 查询资金账户发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryAsset)(EMTQueryAssetRsp* asset, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询持仓响应
    ///@param trade_info 查询到的一个持仓信息
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryPositionByPage)(EMTQueryStkPositionRsp *trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询资金划拨订单响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_transfer_info 查询到的资金账户情况
    ///@param error_info 查询资金账户发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryFundTransfer)(EMTFundTransferNotice* fund_transfer_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///资金划拨通知
    ///@param fund_transfer_info 资金划拨通知的具体信息，用户可以通过fund_transfer_info.serial_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 资金划拨订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。当资金划拨方向为一号两中心节点之间划拨，且error_info.error_id=11000384时，error_info.error_msg为结点中可用于划拨的资金（以整数为准），用户需进行stringToInt的转化，可据此填写合适的资金，再次发起划拨请求
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当资金划拨订单有状态变化的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的资金划拨通知。
    typedef void (*EMT_OnFundTransfer)(EMTFundTransferNotice* fund_transfer_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询ETF清单文件的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param etf_info 查询到的ETF清单文件情况
    ///@param error_info 查询ETF清单文件发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryETF)(EMTQueryETFBaseRsp* etf_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询ETF股票篮的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param etf_component_info 查询到的ETF合约的相关成分股信息
    ///@param error_info 查询ETF股票篮发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryETFBasket)(EMTQueryETFComponentRsp* etf_component_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询今日新股申购信息列表的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param ipo_info 查询到的今日新股申购的一只股票信息
    ///@param error_info 查询今日新股申购信息列表发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryIPOInfoList)(EMTQueryIPOTickerRsp* ipo_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询用户新股申购额度信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param quota_info 查询到的用户某个市场的今日新股申购额度信息
    ///@param error_info 查查询用户新股申购额度信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryIPOQuotaInfo)(EMTQueryIPOQuotaRsp* quota_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询期权合约的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param option_info 查询到的期权合约情况
    ///@param error_info 查询期权合约发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryOptionAuctionInfo)(EMTQueryOptionAuctionInfoRsp* option_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///融资融券业务中现金直接还款的响应
    ///@param cash_repay_info 现金直接还款通知的具体信息，用户可以通过cash_repay_info.emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 现金还款发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnCreditCashRepay)(EMTCrdCashRepayRsp* cash_repay_info, EMTRI* error_info, uint64_t session_id);

    ///融资融券业务中现金还息的响应
    ///@param cash_repay_info 现金还息通知的具体信息，用户可以通过cash_repay_info.emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 现金还息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnCreditCashRepayDebtInterestFee)(EMTCrdCashRepayDebtInterestFeeRsp* cash_repay_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询融资融券业务中的现金直接还款报单的响应
    ///@param cash_repay_info 查询到的某一笔现金直接还款通知的具体信息
    ///@param error_info 查询现金直接报单发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditCashRepayInfo)(EMTCrdCashRepayInfo* cash_repay_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询信用账户额外信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_info 查询到的信用账户额外信息情况
    ///@param error_info 查询信用账户额外信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditFundInfo)(EMTCrdFundInfo* fund_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///请求查询信用账户负债信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param debt_info 查询到的信用账户合约负债情况
    ///@param error_info 查询信用账户负债信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditDebtInfo)(EMTCrdDebtInfo* debt_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询负债信息响应
    ///@param debt_info 查询到的一个负债信息
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前负债信息信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有负债信息，可以进行下一次分页查询，如果不等，表示所有负债信息已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryCreditDebtInfoByPage)(EMTCrdDebtInfo *debt_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询信用账户指定证券负债未还信息响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param debt_info 查询到的信用账户指定证券负债未还信息情况
    ///@param error_info 查询信用账户指定证券负债未还信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditTickerDebtInfo)(EMTCrdDebtStockInfo* debt_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询信用账户待还资金的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param remain_amount 查询到的信用账户待还资金
    ///@param error_info 查询信用账户待还资金发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditAssetDebtInfo)(double remain_amount, EMTRI* error_info, int request_id, uint64_t session_id);

    ///请求查询信用账户可融券头寸信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param assign_info 查询到的信用账户可融券头寸信息
    ///@param error_info 查询信用账户可融券头寸信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditTickerAssignInfo)(EMTClientQueryCrdPositionStkInfo* assign_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询证券头寸信息响应
    ///@param debt_info 查询到的一个证券头寸信息
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前证券头寸信息信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有证券头寸信息，可以进行下一次分页查询，如果不等，表示所有证券头寸信息已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryCreditTickerAssignInfoByPage)(EMTClientQueryCrdPositionStkInfo* debt_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///融资融券业务中请求查询指定余券信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param stock_info 查询到的余券信息
    ///@param error_info 查询信用账户余券信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditExcessStock)(EMTClientQueryCrdSurplusStkRspInfo* stock_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///融资融券业务中请求查询余券信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param stock_info 查询到的余券信息
    ///@param error_info 查询信用账户余券信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryMulCreditExcessStock)(EMTClientQueryCrdSurplusStkRspInfo* stock_info, EMTRI* error_info, int request_id, uint64_t session_id, bool is_last);

    ///融资融券业务中负债合约展期的通知
    ///@param debt_extend_info 负债合约展期通知的具体信息，用户可以通过debt_extend_info.emtid来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 负债合约展期订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当负债合约展期订单有状态变化的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的负债合约展期通知。
    typedef void (*EMT_OnCreditExtendDebtDate)(EMTCreditDebtExtendNotice* debt_extend_info, EMTRI* error_info, uint64_t session_id);

    ///查询融资融券业务中负债合约展期订单响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param debt_extend_info 查询到的负债合约展期情况
    ///@param error_info 查询负债合约展期发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。当error_info.error_id=11000350时，表明没有记录，当为其他非0值时，表明合约发生拒单时的错误原因
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditExtendDebtDateOrders)(EMTCreditDebtExtendNotice* debt_extend_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询融资融券业务中信用账户附加信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_info 信用账户附加信息
    ///@param error_info 查询信用账户附加信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditFundExtraInfo)(EMTCrdFundExtraInfo* fund_info, EMTRI* error_info, int request_id, uint64_t session_id);

    ///查询融资融券业务中信用账户指定证券的附加信息的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_info 信用账户指定证券的附加信息
    ///@param error_info 查询信用账户附加信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditPositionExtraInfo)(EMTCrdPositionExtraInfo* fund_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///期权组合策略报单通知
    ///@param order_info 订单响应具体信息，用户可以通过order_info.order_emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单，order_info.qty_left字段在订单为未成交、部成、全成、废单状态时，表示此订单还没有成交的数量，在部撤、全撤状态时，表示此订单被撤的数量。order_info.order_cancel_emt_id为其所对应的撤单ID，不为0时表示此单被撤成功
    ///@param error_info 订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 每次订单状态更新时，都会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，在订单未成交、全部成交、全部撤单、部分撤单、已拒绝这些状态时会有响应，对于部分成交的情况，请由订单的成交回报来自行确认。所有登录了此用户的客户端都将收到此用户的订单响应
    typedef void (*EMT_OnOptionCombinedOrderEvent)(EMTOptCombOrderInfo* order_info, EMTRI* error_info, uint64_t session_id);

    ///期权组合策略成交通知
    ///@param trade_info 成交回报的具体信息，用户可以通过trade_info.order_emt_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。对于上交所，exec_id可以唯一标识一笔成交。当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交了。对于深交所，exec_id是唯一的，暂时无此判断机制。report_index+market字段可以组成唯一标识表示成交回报。
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 订单有成交发生的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的成交回报。相关订单为部成状态，需要用户通过成交回报的成交数量来确定，OnOrderEvent()不会推送部成状态。
    typedef void (*EMT_OnOptionCombinedTradeEvent)(EMTOptCombTradeReport* trade_info, uint64_t session_id);

    ///期权组合策略撤单出错响应
    ///@param cancel_info 撤单具体信息，包括撤单的order_cancel_emt_id和待撤单的order_emt_id
    ///@param error_info 撤单被拒绝或者发生错误时错误代码和错误信息，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 此响应只会在撤单发生错误时被回调
    typedef void (*EMT_OnCancelOptionCombinedOrderError)(EMTOptCombOrderCancelInfo* cancel_info, EMTRI* error_info, uint64_t session_id);

    ///请求查询期权组合策略报单响应
    ///@param order_info 查询到的一个报单
    ///@param error_info 查询报单时发生错误时，返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。此对应的请求函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    typedef void (*EMT_OnQueryOptionCombinedOrders)(EMTQueryOptCombOrderRsp* order_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询期权组合策略报单响应
    ///@param order_info 查询到的一个报单
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryOptionCombinedOrdersByPage)(EMTQueryOptCombOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询期权组合策略成交响应
    ///@param trade_info 查询到的一个成交回报
    ///@param error_info 查询成交回报发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于支持分时段查询，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。此对应的请求函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    typedef void (*EMT_OnQueryOptionCombinedTrades)(EMTQueryOptCombTradeRsp* trade_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询期权组合策略成交响应
    ///@param trade_info 查询到的一个成交信息
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryOptionCombinedTradesByPage)(EMTQueryOptCombTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///请求查询期权组合策略持仓响应
    ///@param position_info 查询到的一个持仓信息
    ///@param error_info 查询持仓发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryOptionCombinedPosition)(EMTQueryOptCombPositionRsp* position_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询期权组合策略信息响应
    ///@param strategy_info 查询到的一个组合策略信息
    ///@param error_info 查询成交回报发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryOptionCombinedStrategyInfo)(EMTQueryCombineStrategyInfoRsp* strategy_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询融资融券业务中担保品折算率的响应
    ///@param pledge_stk_rate_info 担保品折算率信息，查询发生错误时返回空
    ///@param error_info 查询担保品折算率发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    typedef void (*EMT_OnQueryCreditPledgeStkRate)(EMTClientQueryCreditPledgeStkRateRsp *pledge_stk_rate_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询融资融券业务中担保品折算率的响应
    ///@param pledge_stk_rate_info 担保品折算率信息，查询发生错误时返回空
    ///@param error_info 查询担保品折算率发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    typedef void (*EMT_OnQueryCreditMarginRate)(EMTClientQueryCreditMarginRateRsp *margin_rate_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

    ///查询期权行权合并头寸的响应
    ///@param position_info 查询到的一个行权合并头寸信息
    ///@param error_info 查询持仓发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    typedef void (*EMT_OnQueryOptionCombinedExecPosition)(EMTQueryOptCombExecPosRsp *position_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

     ///请求查询其他节点可用资金的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param fund_info 查询到的其他节点可用资金情况
    ///@param error_info 查询其他节点可用资金发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryOtherServerFund)(EMTFundQueryRsp *fund_info, EMTRI *error_info, int request_id, uint64_t session_id);

    ///查询融券头寸全额占用费率响应
    ///@param position_fullrate_info 融券头寸全额占用费率信息，查询发生错误时返回空
    ///@param error_info 查询融券头寸全额占用费率发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    typedef void (*EMT_OnQueryCreditPositionFullRate)(EMTClientQueryCreditPositionFullRateRsp *position_fullrate_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

    ///融资融券可担保证券分页查询响应
    ///@param pledge_stk_info 融资融券可担保证券信息，查询发生错误时返回空
    ///@param error_info 融资融券可担保证券分页查询发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    typedef void (*EMT_OnQueryCreditPledgeStkPagination)(EMTClientQueryCreditPledgeStkPaginationRsp *pledge_stk_info, EMTRI *error_info, int request_id, uint64_t session_id);

    ///融资融券标的证券分页查询响应
    ///@param target_stk_info 融资融券标的证券信息，查询发生错误时返回空
    ///@param error_info 融资融券标的证券分页查询发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param session_id 资金账户对应的session_id，登录时得到
    typedef void (*EMT_OnQueryCreditTargetStkPagination)(EMTClientQueryCreditTargetStkPaginationRsp *target_stk_info, EMTRI *error_info, int request_id, uint64_t session_id);

    ///请求查询配股业务信息列表的响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param issue_info 查询到的今日配股的一只股票信息
    ///@param error_info 查询今日配股信息列表发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryIssueInfoList)(EMTQueryIssueTickerRsp *issue_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询Security信息响应
    ///@param security 查询到的一只证券的详细信息
    ///@param error_info 查询证券信息发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 由于用户可能查询多个股票信息，一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQuerySecurityInfo)(EMTQuerySecurityInfoRsp *security, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

    ///融资融券两地分仓信用额度调拨通知
    ///@param quota_transfer_info 信用额度调拨通知的具体信息，用户可以通过quota_transfer_info.serial_id来管理订单，通过GetClientIDByEMTID() == client_id来过滤自己的订单。
    ///@param error_info 融券额度调拨订单被拒绝或者发生错误时错误代码和错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当融券额度调拨订单有状态变化的时候，会被调用，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。所有登录了此用户的客户端都将收到此用户的额度调拨通知。
    typedef void (*EMT_OnCreditQuotaTransfer)(EMTQuotaTransferNotice *quota_transfer_info, EMTRI *error_info, uint64_t session_id);

    ///请求查询融资融券两地分仓信用额度调拨订单响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param quota_transfer_info 信用额度调拨通知的具体信息
    ///@param error_info 查询信用额度发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryCreditQuotaTransfer)(EMTQuotaTransferNotice *quota_transfer_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

    ///请求查询昨日资产
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    typedef void (*EMT_OnQueryYesterdayAsset)(EMTQueryYesterdayAssetRsp *yesterday_asset, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

    ///场外Otc分页请求查询持仓响应
    ///@param trade_info 查询到的一个持仓信息
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryOtcPositionByPage)(EMTOtcPositionInfo *position_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///场外Otc请求查询资金账户响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    ///@param asset 查询到的资金账户情况
    ///@param error_info 查询资金账户发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    typedef void (*EMT_OnQueryOtcAsset)(EMTOtcAssetInfo *asset, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id);

    ///场外Otc分页请求查询委托响应
    ///@param order_info 查询到的一个报单
    ///@param req_count 请求到的最大数量
    ///@param order_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryOtcOrderByPage)(EMTQueryOrderRsp *order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///场外Otc分页请求查询成交响应
    ///@param trade_info 查询到的一个报单
    ///@param req_count 请求到的最大数量
    ///@param trade_sequence 分页请求的当前回报数量
    ///@param query_reference 当前报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当trade_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果trade_sequence等于req_count，那么表示还有回报，可以进行下一次分页查询，如果不等，表示所有回报已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryOtcTradeByPage)(EMTQueryTradeRsp *trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    ///分页请求查询ETF清单文件响应
    ///@param etf_info 查询到的一个ETF信息
    ///@param req_count 请求到的最大数量
    ///@param rsp_sequence 分页请求的当前回报数量
    ///@param query_reference 当前信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当rsp_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果rsp_sequence等于req_count，那么表示还有信息，可以进行下一次分页查询，如果不等，表示所有结果已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQueryETFByPage)(EMTQueryETFBaseRsp *etf_info, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);
			
    ///分页请求查询标的基础信息响应
    ///@param security_info 查询到的一个标的信息
    ///@param req_count 请求到的最大数量
    ///@param rsp_sequence 分页请求的当前回报数量
    ///@param query_reference 当前信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
    ///@param request_id 此消息响应函数对应的请求ID
    ///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@remark 当rsp_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果rsp_sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
    typedef void (*EMT_OnQuerySecurityByPage)(EMTQuerySecurityByPageRsp *security_info, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id);

    /*******************************************************************请求函数定义*******************************************************************/

    ///创建TraderApi
    ///@param client_id （必须输入）客户端id，用于区分同一用户的不同客户端，由用户自定义
    ///@param save_file_path （必须输入）存贮订阅信息文件的目录，请设定一个真实存在的有可写权限的路径
    ///@param log_level 日志输出级别
    ///@return 创建出的UserApi
    ///@remark 如果一个账户需要在多个客户端登录，请使用不同的client_id，系统允许一个账户同时登录多个客户端，但是对于同一账户，相同的client_id只能保持一个session连接，后面的登录在前一个session存续期间，无法连接。系统不支持过夜，请确保每天开盘前重新启动
    EMTAPI_EXPORTS int  CreateTraderApi(uint8_t client_id, const char* save_file_path, EMT_LOG_LEVEL log_level = EMT_LOG_LEVEL_DEBUG);

    ///注册回调接口
    ///@param EMT_* 回调接口函数，请在登录之前设定
    EMTAPI_EXPORTS int  RegistCallBack(
        EMT_OnConnected                        cb0, EMT_OnDisconnected                     cb1, EMT_OnError                            cb2, EMT_OnOrderEvent                         cb3, 
        EMT_OnTradeEvent                       cb4, EMT_OnCancelOrderError                 cb5, EMT_OnQueryOrder                       cb6, EMT_OnQueryOrderByPage                   cb7, 
        EMT_OnQueryTrade                       cb8, EMT_OnQueryTradeByPage                 cb9, EMT_OnQueryPosition                   cb10, EMT_OnQueryAsset                        cb11, 
        EMT_OnQueryPositionByPage             cb12, EMT_OnQueryFundTransfer               cb13, EMT_OnFundTransfer                    cb14, EMT_OnQueryETF                          cb15, 
        EMT_OnQueryETFBasket                  cb16, EMT_OnQueryIPOInfoList                cb17, EMT_OnQueryIPOQuotaInfo               cb18, EMT_OnQueryOptionAuctionInfo            cb19, 
        EMT_OnCreditCashRepay                 cb20, EMT_OnCreditCashRepayDebtInterestFee  cb21, EMT_OnQueryCreditCashRepayInfo        cb22, EMT_OnQueryCreditFundInfo               cb23, 
        EMT_OnQueryCreditDebtInfo             cb24, EMT_OnQueryCreditTickerDebtInfo       cb25, EMT_OnQueryCreditAssetDebtInfo        cb26, EMT_OnQueryCreditTickerAssignInfo       cb27, 
        EMT_OnQueryCreditExcessStock          cb28, EMT_OnQueryMulCreditExcessStock       cb29, EMT_OnCreditExtendDebtDate            cb30, EMT_OnQueryCreditExtendDebtDateOrders   cb31, 
        EMT_OnQueryCreditFundExtraInfo        cb32, EMT_OnQueryCreditPositionExtraInfo    cb33, EMT_OnOptionCombinedOrderEvent        cb34, EMT_OnOptionCombinedTradeEvent          cb35, 
        EMT_OnCancelOptionCombinedOrderError  cb36, EMT_OnQueryOptionCombinedOrders       cb37, EMT_OnQueryOptionCombinedOrdersByPage cb38, EMT_OnQueryOptionCombinedTrades         cb39, 
        EMT_OnQueryOptionCombinedTradesByPage cb40, EMT_OnQueryOptionCombinedPosition     cb41, EMT_OnQueryOptionCombinedStrategyInfo cb42, EMT_OnQueryOptionCombinedExecPosition   cb43, 
        EMT_OnQueryOtherServerFund            cb44, EMT_OnQueryCreditMarginRate           cb45, EMT_OnQueryCreditPositionFullRate     cb46, EMT_OnQueryCreditDebtInfoByPage         cb47, 
        EMT_OnQueryCreditTickerAssignInfoByPage cb48, EMT_OnQueryCreditPledgeStkPagination cb49, EMT_OnQueryCreditTargetStkPagination cb50, EMT_OnQueryCreditPledgeStkRate          cb51, 
        EMT_OnQueryIssueInfoList              cb52, EMT_OnQuerySecurityInfo               cb53, EMT_OnCreditQuotaTransfer             cb54, EMT_OnQueryCreditQuotaTransfer          cb55, 
        EMT_OnQueryYesterdayAsset             cb56, EMT_OnQueryOtcPositionByPage          cb57, EMT_OnQueryOtcAsset                   cb58, EMT_OnQueryOtcOrderByPage               cb59, 
        EMT_OnQueryOtcTradeByPage             cb60, EMT_OnQueryETFByPage                  cb61, EMT_OnQuerySecurityByPage             cb62);

    ///为emtsapi线程分配cpu-core,以提高api线程执行效率
    ///@param thread1_cpu_core_id 需要绑的CPU编号1,
    ///@param thread2_cpu_core_id 需要绑的CPU编号2(备用)
    ///@remark 1、非高配机器，不可调用此函数，以防止线程长期满负载独占cpu引起系统问题 2、请在登录之前设定
    EMTAPI_EXPORTS void         SetCpuAffinity(int32_t thread1_cpu_core_id, int32_t thread2_cpu_core_id);

    ///根据错误代码获取错误信息
    ///@param error_code 错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@return 错误信息
    EMTAPI_EXPORTS const char*  GetErrMsgByCode(int32_t error_code ,uint64_t session_id);

    ///删除接口对象本身
    ///@remark 不再使用本接口对象时,调用该函数删除接口对象
    EMTAPI_EXPORTS void         Release();

    ///获取当前交易日
    ///@return 获取到的交易日
    ///@remark 只有登录成功后,才能得到正确的交易日
    EMTAPI_EXPORTS const char*  GetTradingDay();

    ///获取API的系统错误
    ///@return 返回的错误信息，可以在Login、InsertOrder、CancelOrder返回值为0时调用，获取失败的原因
    ///@remark 可以在调用api接口失败时调用，例如login失败时
    EMTAPI_EXPORTS EMTRI*       GetApiLastError();

    ///获取API的发行版本号
    ///@return 返回api发行版本号
    EMTAPI_EXPORTS const char*  GetApiVersion();

    ///通过报单在emt系统中的ID获取下单的客户端id
    ///@return 返回客户端id，可以用此方法过滤自己下的订单
    ///@param order_emt_id 报单在emt系统中的ID
    ///@remark 由于系统允许同一用户在不同客户端上登录操作，每个客户端通过不同的client_id进行区分
    EMTAPI_EXPORTS uint8_t      GetClientIDByEMTID(uint64_t order_emt_id);

    ///通过报单在emt系统中的ID获取相关资金账户名
    ///@return 返回资金账户名
    ///@param order_emt_id 报单在emt系统中的ID
    ///@remark 只有资金账户登录成功后,才能得到正确的信息
    EMTAPI_EXPORTS const char*  GetAccountByEMTID(uint64_t order_emt_id);

    ///订阅公共流。
    ///@param resume_type 公共流（订单响应、成交回报）重传方式  
    ///        EMT_TERT_RESTART:从本交易日开始重传
    ///        EMT_TERT_RESUME:(保留字段，此方式暂未支持)从上次收到的续传
    ///        EMT_TERT_QUICK:只传送登录后公共流的内容
    ///@remark 该方法要在Login方法前调用。若不调用则不会收到公共流的数据。注意在用户断线后，如果不登出就login()，公共流订阅方式不会起作用。用户只会收到断线后的所有消息。如果先logout()再login()，那么公共流订阅方式会起作用，用户收到的数据会根据用户的选择方式而定。
    EMTAPI_EXPORTS void         SubscribePublicTopic(EMT_TE_RESUME_TYPE resume_type);

    ///设置软件开发版本号
    ///@param version 用户开发软件版本号，非api发行版本号，长度不超过15位，以'\0'结尾
    ///@remark 此函数必须在Login之前调用，标识的是客户端版本号，而不是API的版本号，由用户自定义
    EMTAPI_EXPORTS void         SetSoftwareVersion(const char* version);

    ///设置心跳检测时间间隔，单位为秒
    ///@param interval 心跳检测时间间隔，单位为秒
    ///@remark 此函数必须在Login之前调用
    EMTAPI_EXPORTS void         SetHeartBeatInterval(uint32_t interval);

    ///用户登录请求
    ///@return session_id表明此资金账号登录是否成功，“0”表示登录失败，可以调用GetApiLastError()来获取错误代码，非“0”表示登录成功，此时需要记录下这个返回值session_id，与登录的资金账户对应
    ///@param ip 服务器地址，类似“127.0.0.1”
    ///@param port 服务器端口号
    ///@param user 登录用户名
    ///@param password 登录密码
    ///@param sock_type “1”代表TCP，“2”代表UDP
    ///@param local_ip 本地网卡地址，类似“127.0.0.1”
    ///@param info 终端信息
    ///@remark 此函数为同步阻塞式，不需要异步等待登录成功，当函数返回即可进行后续操作，此api可支持多个账户连接，但是同一个账户同一个client_id只能有一个session连接，后面的登录在前一个session存续期间，无法连接
    EMTAPI_EXPORTS uint64_t     Login(const char* ip, int port, const char* user, const char* password, int sock_type, const char* local_ip = NULL, const EMTUserTerminalInfoReq* info = NULL, EMT_SYSTEM_LOGIN login_type = EMT_ORDER_SYSTEM);
    
    ///登出请求
    ///@return 登出是否成功，“0”表示登出成功，“-1”表示登出失败
    ///@param session_id 资金账户对应的session_id,登录时得到
    EMTAPI_EXPORTS int          Logout(uint64_t session_id);

    ///服务器是否重启过
    ///@return “true”表示重启过，“false”表示没有重启过
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@remark 此函数必须在Login之后调用
    EMTAPI_EXPORTS bool         IsServerRestart(uint64_t session_id);

    ///报单录入请求
    ///@return 报单在EMT系统中的ID,如果为‘0’表示报单发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示报单发送成功，用户需要记录下返回的order_emt_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param order 报单录入信息，其中order.order_client_id字段是用户自定义字段，用户输入什么值，订单响应OnOrderEvent()返回时就会带回什么值，类似于备注，方便用户自己定位订单。当然，如果你什么都不填，也是可以的。order.order_emt_id字段无需用户填写，order.ticker必须不带空格，以'\0'结尾
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@remark 交易所接收订单后，会在报单响应函数OnOrderEvent()中返回报单未成交的状态，之后所有的订单状态改变（除了部成状态）都会通过报单响应函数返回
    EMTAPI_EXPORTS uint64_t     InsertOrder(EMTOrderInsertInfo* order, uint64_t session_id);

    ///报单操作请求
    ///@return 撤单在EMT系统中的ID,如果为‘0’表示撤单发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示撤单发送成功，用户需要记录下返回的order_cancel_emt_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param order_emt_id 需要撤销的委托单在EMT系统中的ID
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@remark 如果撤单成功，会在报单响应函数OnOrderEvent()里返回原单部撤或者全撤的消息，如果不成功，会在OnCancelOrderError()响应函数中返回错误原因
    EMTAPI_EXPORTS uint64_t     CancelOrder(const uint64_t order_emt_id, uint64_t session_id);

    ///根据报单ID请求查询报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param order_emt_id 需要查询的报单在emt系统中的ID，即InsertOrder()成功时返回的order_emt_id
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryOrderByEMTID(const uint64_t order_emt_id, uint64_t session_id, int request_id);

    ///请求查询报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的订单相关筛选条件，其中合约代码可以为空，则默认所有存在的合约代码，如果不为空，请不带空格，并以'\0'结尾，其中起始时间格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点，结束时间格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分时段查询，如果股票代码为空，则默认查询时间段内的所有报单，否则查询时间段内所有跟股票代码相关的报单，此函数查询出的结果可能对应多个查询结果响应。此函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线。查询记录数不能超过1000，否则会报错，甚至崩溃。
    EMTAPI_EXPORTS int          QueryOrders(const EMTQueryOrderReq* query_param, uint64_t session_id, int request_id);

    ///请求查询未完结报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryUnfinishedOrders(uint64_t session_id, int request_id);

    ///分页请求查询报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询订单的条件，如果第一次查询，那么query_param.reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    EMTAPI_EXPORTS int          QueryOrdersByPage(const EMTQueryOrderByPageReq* query_param, uint64_t session_id, int request_id);

    ///根据委托编号请求查询相关成交
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param order_emt_id 需要查询的委托编号，即InsertOrder()成功时返回的order_emt_id
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 此函数查询出的结果可能对应多个查询结果响应
    EMTAPI_EXPORTS int          QueryTradesByEMTID(const uint64_t order_emt_id, uint64_t session_id, int request_id);

    ///请求查询已成交
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的成交回报筛选条件，其中合约代码可以为空，则默认所有存在的合约代码，如果不为空，请不带空格，并以'\0'结尾，其中起始时间格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点，结束时间格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分时段查询，如果股票代码为空，则默认查询时间段内的所有成交回报，否则查询时间段内所有跟股票代码相关的成交回报，此函数查询出的结果可能对应多个查询结果响应。此函数不建议轮询使用，当报单量过多时。查询记录数不能超过1000，否则会报错，甚至崩溃。
    EMTAPI_EXPORTS int          QueryTrades(EMTQueryTraderReq* query_param, uint64_t session_id, int request_id);

    ///分页请求查询成交回报
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询成交回报的条件，如果第一次查询，那么reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    EMTAPI_EXPORTS int          QueryTradesByPage(const EMTQueryTraderByPageReq* query_param, uint64_t session_id, int request_id);

    ///请求查询投资者持仓
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param ticker 需要查询持仓的合约代码，可以为NULL，表示查询全市场，如果不为NULL，请不带空格，并以'\0'结尾，注意需与market匹配，不匹配的话，可能由于证券代码沪深2个市场有重复，而导致查询不到所需的持仓
    ///@param market 需要查询持仓的合约所在市场，默认为0，仅在合约代码不为NULL的时候，才会使用。market不指定或者为非0的其他非有效值情况下，可能由于证券代码沪深2个市场有重复，而导致查询不到所需的持仓。如果想正确查询指定持仓，请指定market
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法如果用户提供了合约代码，则会查询此合约的持仓信息（注意请指定market，如果market为0，可能会查询到2个市场的持仓，如果market为其他非有效值，则查询结果会返回找不到持仓），如果合约代码为空，则默认查询所有持仓信息。
    EMTAPI_EXPORTS int          QueryPosition(const char* ticker, uint64_t session_id, int request_id, EMT_MARKET_TYPE market = EMT_MKT_INIT);

    ///请求查询投资者持仓分页
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询持仓的条件，如果第一次查询，那么query_param.reference填0
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法如果用户提供了合约代码，则会查询此合约的持仓信息（注意请指定market，如果market为0，可能会查询到2个市场的持仓，如果market为其他非有效值，则查询结果会返回找不到持仓），如果合约代码为空，则默认查询所有持仓信息。
    EMTAPI_EXPORTS int          QueryPositionByPage(const EMTQueryPositionByPageReq *query_param, uint64_t session_id, int request_id);

    ///请求查询资产
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryAsset(uint64_t session_id, int request_id);

    ///资金划拨请求
    ///@return 资金划拨订单在EMT系统中的ID,如果为‘0’表示消息发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示消息发送成功，用户需要记录下返回的serial_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param fund_transfer 资金划拨的请求信息
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@remark 此函数支持一号两中心节点之间的资金划拨，注意资金划拨的方向。
    EMTAPI_EXPORTS uint64_t     FundTransfer(EMTFundTransferReq* fund_transfer, uint64_t session_id);

    ///请求查询资金划拨
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的资金划拨订单筛选条件，其中serial_id可以为0，则默认所有资金划拨订单，如果不为0，则请求特定的资金划拨订单
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryFundTransfer(EMTQueryFundTransferLogReq* query_param, uint64_t session_id, int request_id);

    ///请求查询其他节点可用资金
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 询时需要提供的信息
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryOtherServerFund(EMTFundQueryReq *query_param, uint64_t session_id, int request_id);

    ///请求查询ETF清单文件
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的ETF清单文件的筛选条件，其中合约代码可以为空，则默认所有存在的ETF合约代码，market字段也可以为初始值，则默认所有市场的ETF合约
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryETF(EMTQueryETFBaseReq* query_param, uint64_t session_id, int request_id);

    ///请求查询ETF股票篮
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询股票篮的的ETF合约，其中合约代码不可以为空，market字段也必须指定
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryETFTickerBasket(EMTQueryETFComponentReq* query_param, uint64_t session_id, int request_id);

    ///请求查询今日新股申购信息列表
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryIPOInfoList(uint64_t session_id, int request_id);

    ///请求查询用户新股申购额度信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryIPOQuotaInfo(uint64_t session_id, int request_id);

    ///请求查询期权合约
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的期权合约的筛选条件，可以为NULL（为NULL表示查询所有的期权合约）
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryOptionAuctionInfo(EMTQueryOptionAuctionInfoReq* query_param, uint64_t session_id, int request_id);

    ///融资融券业务中现金直接还款请求
    ///@return 现金直接还款订单在EMT系统中的ID,如果为‘0’表示消息发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示消息发送成功，用户需要记录下返回的emt_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param amount 现金还款的金额
    ///@param session_id 资金账户对应的session_id,登录时得到
    EMTAPI_EXPORTS uint64_t     CreditCashRepay(double amount, uint64_t session_id);

    ///融资融券业务中现金还指定负债合约息费请求
    ///@return 现金还息订单在EMT系统中的ID,如果为‘0’表示消息发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示消息发送成功，用户需要记录下返回的emt_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param debt_id 指定的负债合约编号
    ///@param amount 现金还息的金额
    ///@param session_id 资金账户对应的session_id,登录时得到
    EMTAPI_EXPORTS uint64_t     CreditCashRepayDebtInterestFee(const char* debt_id, double amount, uint64_t session_id);

    ///融资融券业务中卖券还指定负债合约息费请求
    ///@return 卖券还息订单在EMT系统中的ID,如果为‘0’表示消息发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示消息发送成功，用户需要记录下返回的emt_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param order 卖券的报单录入信息，其中order.order_client_id字段是用户自定义字段，用户输入什么值，订单响应OnOrderEvent()返回时就会带回什么值，类似于备注，方便用户自己定位订单。当然，如果你什么都不填，也是可以的。order.order_emt_id字段无需用户填写，order.ticker必须不带空格，以'\0'结尾
    ///@param debt_id 指定的负债合约编号
    ///@param session_id 资金账户对应的session_id,登录时得到
    EMTAPI_EXPORTS uint64_t     CreditSellStockRepayDebtInterestFee(EMTOrderInsertInfo* order, const char* debt_id, uint64_t session_id);

    ///请求查询融资融券业务中的现金直接还款报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditCashRepayInfo(uint64_t session_id, int request_id);

    ///请求查询信用账户特有信息，除资金账户以外的信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditFundInfo(uint64_t session_id, int request_id);

    ///请求查询信用账户负债合约信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditDebtInfo(uint64_t session_id, int request_id);

    ///分页请求信用账户负债合约信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询成交回报的条件，如果第一次查询，那么reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    EMTAPI_EXPORTS int         QueryCreditDebtInfoByPage(const EMTQueryCreditDebtInfoByPageReq* query_param, uint64_t session_id, int request_id);

    ///请求查询指定证券负债未还信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的指定证券，筛选条件中ticker可以全填0，如果不为0，请不带空格，并以'\0'结尾
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditTickerDebtInfo(EMTClientQueryCrdDebtStockReq* query_param, uint64_t session_id, int request_id);

    ///请求查询信用账户待还资金信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditAssetDebtInfo(uint64_t session_id, int request_id);

    ///请求查询信用账户可融券头寸信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的证券，筛选条件中ticker可以全填0，如果不为0，请不带空格，并以'\0'结尾
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditTickerAssignInfo(EMTClientQueryCrdPositionStockReq* query_param, uint64_t session_id, int request_id);

    ///分页请求信用账户证券头寸信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询成交回报的条件，如果第一次查询，那么reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    EMTAPI_EXPORTS int          QueryCreditTickerAssignInfoByPage(const EMTQueryTickerAssignInfoByPageReq* query_param, uint64_t session_id, int request_id);

    ///融资融券业务中请求查询指定证券的余券
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的余券信息，不可以为空，需要明确指定
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法中用户必须提供了证券代码和所在市场
    EMTAPI_EXPORTS int          QueryCreditExcessStock(EMTClientQueryCrdSurplusStkReqInfo* query_param, uint64_t session_id, int request_id);

    ///融资融券业务中请求查询余券
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的余券信息。若填入市场和股票代码，返回单支股票信息；若市场代码为空，股票代码非空，是无效查询，会在SPI中返回错误；若市场和股票代码均为空，返回全市场信息；若市场代码非空，股票代码为空，返回单市场信息。
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryMulCreditExcessStock(EMTClientQueryCrdSurplusStkReqInfo* query_param, uint64_t session_id, int request_id);

    ///融资融券业务中请求负债合约展期
    ///@return 负债合约展期订单在EMT系统中的ID,如果为‘0’表示消息发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示消息发送成功，用户需要记录下返回的emt_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param debt_extend 负债合约展期的请求信息
    ///@param session_id 资金账户对应的session_id,登录时得到
    EMTAPI_EXPORTS uint64_t     CreditExtendDebtDate(EMTCreditDebtExtendReq* debt_extend, uint64_t session_id);

    ///融资融券业务中请求查询负债合约展期
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param emt_id 需要查询的负债合约展期订单筛选条件，emt_id可以为0，则默认所有负债合约展期订单，如果不为0，则请求特定的负债合约展期订单
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditExtendDebtDateOrders(uint64_t emt_id, uint64_t session_id, int request_id);

    ///请求查询融资融券业务中账戶的附加信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditFundExtraInfo(uint64_t session_id, int request_id);

    ///请求查询融资融券业务中账戶指定证券的附加信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要指定的证券，筛选条件中ticker可以全填0，如果不为0，请不带空格，并以'\0'结尾
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditPositionExtraInfo(EMTClientQueryCrdPositionStockReq* query_param, uint64_t session_id, int request_id);

    ///期权组合策略报单录入请求
    ///@return 报单在EMT系统中的ID,如果为‘0’表示报单发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示报单发送成功，用户需要记录下返回的order_emt_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param order 报单录入信息，其中order.order_client_id字段是用户自定义字段，用户输入什么值，订单响应OnOptionCombinedOrderEvent()返回时就会带回什么值，类似于备注，方便用户自己定位订单。当然，如果你什么都不填，也是可以的。order.order_emt_id字段无需用户填写，order.ticker必须不带空格，以'\0'结尾
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@remark 交易所接收订单后，会在报单响应函数OnOptionCombinedOrderEvent()中返回报单未成交的状态，之后所有的订单状态改变（除了部成状态）都会通过报单响应函数返回
    EMTAPI_EXPORTS uint64_t     InsertOptionCombinedOrder(EMTOptCombOrderInsertInfo* order, uint64_t session_id);

    ///期权组合策略报单撤单请求
    ///@return 撤单在EMT系统中的ID,如果为‘0’表示撤单发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示撤单发送成功，用户需要记录下返回的order_cancel_emt_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param order_emt_id 需要撤销的期权组合策略委托单在EMT系统中的ID
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@remark 如果撤单成功，会在报单响应函数OnOptionCombinedOrderEvent()里返回原单部撤或者全撤的消息，如果不成功，会在OnCancelOrderError()响应函数中返回错误原因
    EMTAPI_EXPORTS uint64_t     CancelOptionCombinedOrder(const uint64_t order_emt_id, uint64_t session_id);

    ///请求查询期权组合策略未完结报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryOptionCombinedUnfinishedOrders(uint64_t session_id, int request_id);

    ///根据报单ID请求查询期权组合策略报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param order_emt_id 需要查询的报单在emt系统中的ID，即InsertOrder()成功时返回的order_emt_id
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryOptionCombinedOrderByEMTID(const uint64_t order_emt_id, uint64_t session_id, int request_id);

    ///请求查询期权组合策略报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的订单相关筛选条件，其中合约代码可以为空，则默认所有存在的合约代码，如果不为空，请不带空格，并以'\0'结尾，其中起始时间格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点，结束时间格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分时段查询，如果股票代码为空，则默认查询时间段内的所有报单，否则查询时间段内所有跟股票代码相关的报单，此函数查询出的结果可能对应多个查询结果响应。此函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    EMTAPI_EXPORTS int          QueryOptionCombinedOrders(const EMTQueryOptCombOrderReq* query_param, uint64_t session_id, int request_id);

    ///分页请求查询期权组合策略报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询订单的条件，如果第一次查询，那么query_param.reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    EMTAPI_EXPORTS int          QueryOptionCombinedOrdersByPage(const EMTQueryOptCombOrderByPageReq* query_param, uint64_t session_id, int request_id);

    ///根据期权组合策略委托编号请求查询相关成交
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param order_emt_id 需要查询的委托编号，即InsertOrder()成功时返回的order_emt_id
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 此函数查询出的结果可能对应多个查询结果响应
    EMTAPI_EXPORTS int          QueryOptionCombinedTradesByEMTID(const uint64_t order_emt_id, uint64_t session_id, int request_id);

    ///请求查询期权组合策略的成交回报
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的成交回报筛选条件，其中合约代码可以为空，则默认所有存在的合约代码，如果不为空，请不带空格，并以'\0'结尾，其中起始时间格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点，结束时间格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分时段查询，如果股票代码为空，则默认查询时间段内的所有成交回报，否则查询时间段内所有跟股票代码相关的成交回报，此函数查询出的结果可能对应多个查询结果响应。此函数不建议轮询使用，当报单量过多时，容易造成用户线路拥堵，导致api断线
    EMTAPI_EXPORTS int          QueryOptionCombinedTrades(const EMTQueryOptCombTraderReq* query_param, uint64_t session_id, int request_id);

    ///分页请求查询期权组合策略成交回报
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询成交回报的条件，如果第一次查询，那么reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    EMTAPI_EXPORTS int          QueryOptionCombinedTradesByPage(const EMTQueryOptCombTraderByPageReq* query_param, uint64_t session_id, int request_id);

    ///请求查询投资者期权组合策略持仓
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询持仓的筛选条件，其中组合策略代码可以初始化为空，表示查询所有，如果不为空，请不带空格，并以'\0'结尾，注意需与market匹配，不匹配的话，可能导致查询不到所需的持仓
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法如果用户提供了合约代码，则会查询此合约的持仓信息（注意请指定market，如果market为0，可能会查询到2个市场的持仓，如果market为其他非有效值，则查询结果会返回找不到持仓），如果合约代码为空，则默认查询所有持仓信息。
    EMTAPI_EXPORTS int          QueryOptionCombinedPosition(const EMTQueryOptCombPositionReq* query_param, uint64_t session_id, int request_id);

    ///请求查询期权组合策略信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法仅支持精确查询，不支持模糊查询
    EMTAPI_EXPORTS int          QueryOptionCombinedStrategyInfo(uint64_t session_id, int request_id);

    ///融资融券业务中请求查询担保品折算率
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要指定的证券，证券市场和证券代码为必填字段，请不带空格，并以'\0'结尾
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditPledgeStkRate(EMTClientQueryCreditPledgeStkRateReq *query_param, uint64_t session_id, int request_id);

    ///请求查询期权行权合并头寸
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的行权合并的筛选条件，其中market为0会默认查询全市场，成分合约代码可以初始化为空，如果不为空，请不带空格，并以'\0'结尾，注意所有填写的条件都会进行匹配
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryOptionCombinedExecPosition(const EMTQueryOptCombExecPosReq *query_param, uint64_t session_id, int request_id);

    ///融资融券业务中请求查询保证金率
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要指定的证券，证券市场和证券代码为必填字段，请不带空格，并以'\0'结尾
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditMarginRate(EMTClientQueryCreditMarginRateReq *query_param, uint64_t session_id, int request_id);

    ///融资融券查询融券头寸全额占用费率
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要指定的证券，证券市场和证券代码为非必填字段，如填写请不带空格，并以'\0'结尾，如不填或填0则默认查询全部
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditPositionFullRate(EMTClientQueryCreditPositionFullRateReq *query_param, uint64_t session_id, int request_id);

    ///融资融券可担保证券分页查询
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 分页查询请求条件，页码从1开始，单页请求数量不可超过200条
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditPledgeStkPagination(EMTClientQueryCreditPledgeStkPaginationReq *query_param, uint64_t session_id, int request_id);

    ///融资融券标的证券分页查询
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 分页查询请求条件，页码从1开始，单页请求数量不可超过200条
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditTargetStkPagination(EMTClientQueryCreditTargetStkPaginationReq *query_param, uint64_t session_id, int request_id);

    ///请求查询配股业务信息列表
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryIssueInfoList(uint64_t session_id, int request_id);

    ///请求查询Security信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的Security信息的筛选条件，其中market默认为0，标示查询全市场； ticker不能为空，即不支持全量查询，不带空格，并以'\0'结尾。注意需与market匹配，不匹配的话，可能由于证券代码沪深2个市场有重复，而导致查询不到所需的代码信息
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QuerySecurityInfo(EMTQuerySecurityInfoReq *query_param, uint64_t session_id, int request_id);

    ///融资融券两地分仓融券额度调拨请求
    ///@return 融券额度调拨订单在EMT系统中的ID,如果为‘0’表示消息发送失败，此时用户可以调用GetApiLastError()来获取错误代码，非“0”表示消息发送成功，用户需要记录下返回的serial_id，它保证一个交易日内唯一，不同的交易日不保证唯一性
    ///@param quota_transfer 融券额度划拨的请求信息
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@remark 此函数支持一号两中心节点之间的资金划拨，注意资金划拨的方向。
    EMTAPI_EXPORTS uint64_t     CreditQuotaTransfer(EMTQuotaTransferReq *quota_transfer, uint64_t session_id);

    ///融资融券两地分仓信用额度调拨查询请求
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要查询的信用额度调拨订单筛选条件，其中serial_id可以为0，则默认所有资金划拨订单，如果不为0，则请求特定的资金划拨订单
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryCreditQuotaTransfer(EMTQueryQuotaTransferLogReq *query_param, uint64_t session_id, int request_id);

    ///请求查询昨日资产
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryYesterdayAsset(uint64_t session_id, int request_id);

    ///场外OTC请求查询投资者持仓分页
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询持仓的条件，如果第一次查询，那么query_param.reference填0
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法如果用户提供了合约代码，则会查询此合约的持仓信息（注意请指定market，如果market为0，可能会查询到2个市场的持仓，如果market为其他非有效值，则查询结果会返回找不到持仓），如果合约代码为空，则默认查询所有持仓信息。
    EMTAPI_EXPORTS int          QueryOtcPositionByPage(const EMTQueryOtcPositionByPageReq *query_param, uint64_t session_id, int request_id);

    ///场外OTC请求查询资产
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param session_id 资金账户对应的session_id,登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    EMTAPI_EXPORTS int          QueryOtcAsset(uint64_t session_id, int request_id);

    ///场外OTC分页请求查询报单
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询订单的条件，如果第一次查询，那么query_param.reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    EMTAPI_EXPORTS int          QueryOtcOrdersByPage(const EMTQueryOtcOrdersByPageReq *query_param, uint64_t session_id, int request_id);

    ///场外OTC分页请求查询成交回报
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询成交回报的条件，如果第一次查询，那么reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
    EMTAPI_EXPORTS int          QueryOtcTradesByPage(const EMTQueryOtcTradesByPageReq *query_param, uint64_t session_id, int request_id);

    ///分页请求查询ETF清单文件
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询ETF清单文件的条件，如果第一次查询，那么query_param.reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用。每此请求订单条数req_count不超过200，超过时按200处理。
    EMTAPI_EXPORTS int          QueryETFByPage(const EMTQueryETFByPageReq *query_param, uint64_t session_id, int request_id);
		
    ///分页请求查询标的基础信息
    ///@return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    ///@param query_param 需要分页查询标的基础信息的条件，如果第一次查询，那么query_param.reference填0
    ///@param session_id 资金账户对应的session_id，登录时得到
    ///@param request_id 用于用户定位查询响应的ID，由用户自定义
    ///@remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用。每此请求订单条数req_count不超过200，超过时按200处理。
    EMTAPI_EXPORTS int          QuerySecurityByPage(const EMTQuerySecurityByPageReq *query_param, uint64_t session_id, int request_id);
#ifdef __cplusplus
}
#endif

#endif