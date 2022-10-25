int TdApi::queryOrderByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id)
{
	int i = this->api->QueryOrderByEMTID(order_emt_id, session_id, request_id);
	return i;
};

int TdApi::queryOrders(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOrderReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ticker", myreq.ticker);
	getInt64_t(req, "begin_time", &myreq.begin_time);
	getInt64_t(req, "end_time", &myreq.end_time);
	int i = this->api->QueryOrders(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryUnfinishedOrders(uint64_t session_id, int request_id)
{
	int i = this->api->QueryUnfinishedOrders(session_id, request_id);
	return i;
};

int TdApi::queryOrdersByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOrderByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryOrdersByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryTradesByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id)
{
	int i = this->api->QueryTradesByEMTID(order_emt_id, session_id, request_id);
	return i;
};

int TdApi::queryTrades(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryTraderReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ticker", myreq.ticker);
	getInt64_t(req, "begin_time", &myreq.begin_time);
	getInt64_t(req, "end_time", &myreq.end_time);
	int i = this->api->QueryTrades(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryTradesByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryTraderByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryTradesByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryPosition(char ticker, uint64_t session_id, int request_id, int market)
{
	int i = this->api->QueryPosition(ticker, session_id, request_id, market);
	return i;
};

int TdApi::queryPositionByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryPositionByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryPositionByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryAsset(uint64_t session_id, int request_id)
{
	int i = this->api->QueryAsset(session_id, request_id);
	return i;
};

int TdApi::queryFundTransfer(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryFundTransferLogReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getUint64_t(req, "serial_id", &myreq.serial_id);
	int i = this->api->QueryFundTransfer(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOtherServerFund(EMTFundQueryReq query_param, uint64_t session_id, int request_id)
{
	int i = this->api->QueryOtherServerFund(query_param, session_id, request_id);
	return i;
};

int TdApi::queryETF(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryETFBaseReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryETF(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryETFTickerBasket(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryETFComponentReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryETFTickerBasket(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryIPOInfoList(uint64_t session_id, int request_id)
{
	int i = this->api->QueryIPOInfoList(session_id, request_id);
	return i;
};

int TdApi::queryIPOQuotaInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryIPOQuotaInfo(session_id, request_id);
	return i;
};

int TdApi::queryOptionAuctionInfo(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOptionAuctionInfoReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryOptionAuctionInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditCashRepayInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryCreditCashRepayInfo(session_id, request_id);
	return i;
};

int TdApi::queryCreditFundInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryCreditFundInfo(session_id, request_id);
	return i;
};

int TdApi::queryCreditDebtInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryCreditDebtInfo(session_id, request_id);
	return i;
};

int TdApi::queryCreditDebtInfoByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryCreditDebtInfoByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getUint64_t(req, "u64", &myreq.u64);
	getUint8_t(req, "debttype", &myreq.debttype);
	getUint8_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryCreditDebtInfoByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditTickerDebtInfo(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdDebtStockReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditTickerDebtInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditAssetDebtInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryCreditAssetDebtInfo(session_id, request_id);
	return i;
};

int TdApi::queryCreditTickerAssignInfo(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdPositionStockReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditTickerAssignInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditTickerAssignInfoByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryTickerAssignInfoByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryCreditTickerAssignInfoByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditExcessStock(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdSurplusStkReqInfo myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditExcessStock(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryMulCreditExcessStock(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdSurplusStkReqInfo myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryMulCreditExcessStock(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditExtendDebtDateOrders(uint64_t emt_id, uint64_t session_id, int request_id)
{
	int i = this->api->QueryCreditExtendDebtDateOrders(emt_id, session_id, request_id);
	return i;
};

int TdApi::queryCreditFundExtraInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryCreditFundExtraInfo(session_id, request_id);
	return i;
};

int TdApi::queryCreditPositionExtraInfo(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdPositionStockReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditPositionExtraInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedUnfinishedOrders(uint64_t session_id, int request_id)
{
	int i = this->api->QueryOptionCombinedUnfinishedOrders(session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedOrderByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id)
{
	int i = this->api->QueryOptionCombinedOrderByEMTID(order_emt_id, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedOrders(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombOrderReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "comb_num", myreq.comb_num);
	getInt64_t(req, "begin_time", &myreq.begin_time);
	getInt64_t(req, "end_time", &myreq.end_time);
	int i = this->api->QueryOptionCombinedOrders(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedOrdersByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombOrderByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryOptionCombinedOrdersByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedTradesByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id)
{
	int i = this->api->QueryOptionCombinedTradesByEMTID(order_emt_id, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedTrades(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombTraderReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "comb_num", myreq.comb_num);
	getInt64_t(req, "begin_time", &myreq.begin_time);
	getInt64_t(req, "end_time", &myreq.end_time);
	int i = this->api->QueryOptionCombinedTrades(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedTradesByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombTraderByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryOptionCombinedTradesByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedPosition(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombPositionReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "comb_num", myreq.comb_num);
	getEnum(req, "market", &myreq.market);
	int i = this->api->QueryOptionCombinedPosition(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedStrategyInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryOptionCombinedStrategyInfo(session_id, request_id);
	return i;
};

int TdApi::queryCreditPledgeStkRate(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditPledgeStkRateReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditPledgeStkRate(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedExecPosition(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombExecPosReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "cntrt_code_1", myreq.cntrt_code_1);
	getString(req, "cntrt_code_2", myreq.cntrt_code_2);
	int i = this->api->QueryOptionCombinedExecPosition(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditMarginRate(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditMarginRateReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditMarginRate(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditPositionFullRate(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditPositionFullRateReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditPositionFullRate(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditPledgeStkPagination(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditPledgeStkPaginationReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt32_t(req, "page", &myreq.page);
	getInt32_t(req, "count", &myreq.count);
	int i = this->api->QueryCreditPledgeStkPagination(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditTargetStkPagination(const dict &req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditTargetStkPaginationReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt32_t(req, "page", &myreq.page);
	getInt32_t(req, "count", &myreq.count);
	int i = this->api->QueryCreditTargetStkPagination(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryIssueInfoList(uint64_t session_id, int request_id)
{
	int i = this->api->QueryIssueInfoList(session_id, request_id);
	return i;
};

int TdApi::querySecurityInfo(const dict &req, uint64_t session_id, int request_id)
{
	EMTQuerySecurityInfoReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ticker", myreq.ticker);
	getEnum(req, "market", &myreq.market);
	int i = this->api->QuerySecurityInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditQuotaTransfer(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryQuotaTransferLogReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getUint64_t(req, "serial_id", &myreq.serial_id);
	int i = this->api->QueryCreditQuotaTransfer(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryYesterdayAsset(uint64_t session_id, int request_id)
{
	int i = this->api->QueryYesterdayAsset(session_id, request_id);
	return i;
};

int TdApi::queryOtcPositionByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOtcPositionByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getString(req, "ticker", myreq.ticker);
	getEnum(req, "market", &myreq.market);
	int i = this->api->QueryOtcPositionByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOtcAsset(uint64_t session_id, int request_id)
{
	int i = this->api->QueryOtcAsset(session_id, request_id);
	return i;
};

int TdApi::queryOtcOrdersByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOtcOrdersByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getString(req, "ticker", myreq.ticker);
	getEnum(req, "market", &myreq.market);
	int i = this->api->QueryOtcOrdersByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOtcTradesByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryOtcTradesByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getString(req, "ticker", myreq.ticker);
	getEnum(req, "market", &myreq.market);
	int i = this->api->QueryOtcTradesByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryETFByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQueryETFByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryETFByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::querySecurityByPage(const dict &req, uint64_t session_id, int request_id)
{
	EMTQuerySecurityByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QuerySecurityByPage(&myreq, session_id, request_id);
	return i;
};

