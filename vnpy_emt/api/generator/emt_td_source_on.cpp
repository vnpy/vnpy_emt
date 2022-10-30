void onConnected() override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onConnected);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onDisconnected(int reason) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onDisconnected, reason);
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
		PYBIND11_OVERLOAD(void, TdApi, onError, error);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOrderEvent(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOrderEvent, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onTradeEvent(const dict &data, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onTradeEvent, data, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCancelOrderError(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCancelOrderError, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOrder(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOrder, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOrderByPage(const dict &data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOrderByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryTrade(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryTrade, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryTradeByPage(const dict &data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryTradeByPage, data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryPosition(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryPosition, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryPositionByPage(const dict &data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryPositionByPage, data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryAsset(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryAsset, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryFundTransfer(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryFundTransfer, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onFundTransfer(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onFundTransfer, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOtherServerFund(EMTFundQueryRsp fund_info, const dict &error, int request_id, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOtherServerFund, fund_info, error, request_id, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryETF(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryETF, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryETFBasket(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryETFBasket, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryIPOInfoList(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryIPOInfoList, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryIPOQuotaInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryIPOQuotaInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptionAuctionInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptionAuctionInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCreditCashRepay(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCreditCashRepay, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCreditCashRepayDebtInterestFee(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCreditCashRepayDebtInterestFee, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditCashRepayInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditCashRepayInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditFundInfo(const dict &data, const dict &error, int request_id, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditFundInfo, data, error, request_id, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditDebtInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditDebtInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditDebtInfoByPage(const dict &data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditDebtInfoByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditTickerDebtInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTickerDebtInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditAssetDebtInfo(double remain_amount, const dict &error, int request_id, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditAssetDebtInfo, remain_amount, error, request_id, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditTickerAssignInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTickerAssignInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditTickerAssignInfoByPage(const dict &data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTickerAssignInfoByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditExcessStock(const dict &data, const dict &error, int request_id, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditExcessStock, data, error, request_id, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryMulCreditExcessStock(const dict &data, const dict &error, int request_id, uint64_t session_id, bool is_last) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryMulCreditExcessStock, data, error, request_id, session_id, is_last);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCreditExtendDebtDate(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCreditExtendDebtDate, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditExtendDebtDateOrders(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditExtendDebtDateOrders, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditFundExtraInfo(const dict &data, const dict &error, int request_id, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditFundExtraInfo, data, error, request_id, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditPositionExtraInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditPositionExtraInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOptionCombinedOrderEvent(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOptionCombinedOrderEvent, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onOptionCombinedTradeEvent(const dict &data, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onOptionCombinedTradeEvent, data, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCancelOptionCombinedOrderError(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCancelOptionCombinedOrderError, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptionCombinedOrders(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedOrders, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptionCombinedOrdersByPage(const dict &data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedOrdersByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptionCombinedTrades(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedTrades, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptionCombinedTradesByPage(const dict &data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedTradesByPage, data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptionCombinedPosition(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedPosition, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptionCombinedStrategyInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedStrategyInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditPledgeStkRate(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditPledgeStkRate, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOptionCombinedExecPosition(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedExecPosition, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditMarginRate(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditMarginRate, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditPositionFullRate(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditPositionFullRate, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditPledgeStkPagination(const dict &data, const dict &error, int request_id, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditPledgeStkPagination, data, error, request_id, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditTargetStkPagination(const dict &data, const dict &error, int request_id, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTargetStkPagination, data, error, request_id, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryIssueInfoList(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryIssueInfoList, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQuerySecurityInfo(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQuerySecurityInfo, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onCreditQuotaTransfer(const dict &data, const dict &error, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onCreditQuotaTransfer, data, error, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryCreditQuotaTransfer(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryCreditQuotaTransfer, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryYesterdayAsset(const dict &data, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryYesterdayAsset, data, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOtcPositionByPage(EMTOtcPositionInfo position_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOtcPositionByPage, position_info, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOtcAsset(EMTOtcAssetInfo asset, const dict &error, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOtcAsset, asset, error, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOtcOrderByPage(const dict &data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOtcOrderByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryOtcTradeByPage(const dict &data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryOtcTradeByPage, data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQueryETFByPage(const dict &data, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQueryETFByPage, data, req_count, rsp_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

void onQuerySecurityByPage(const dict &data, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
{
	try
	{
		PYBIND11_OVERLOAD(void, TdApi, onQuerySecurityByPage, data, req_count, rsp_sequence, query_reference, request_id, is_last, session_id);
	}
	catch (const error_already_set &e)
	{
		cout << e.what() << endl;
	}
};

