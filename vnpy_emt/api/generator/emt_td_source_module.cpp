.def("queryOrderByEMTID", &TdApi::queryOrderByEMTID)
.def("queryOrders", &TdApi::queryOrders)
.def("queryUnfinishedOrders", &TdApi::queryUnfinishedOrders)
.def("queryOrdersByPage", &TdApi::queryOrdersByPage)
.def("queryTradesByEMTID", &TdApi::queryTradesByEMTID)
.def("queryTrades", &TdApi::queryTrades)
.def("queryTradesByPage", &TdApi::queryTradesByPage)
.def("queryPosition", &TdApi::queryPosition)
.def("queryPositionByPage", &TdApi::queryPositionByPage)
.def("queryAsset", &TdApi::queryAsset)
.def("queryFundTransfer", &TdApi::queryFundTransfer)
.def("queryOtherServerFund", &TdApi::queryOtherServerFund)
.def("queryETF", &TdApi::queryETF)
.def("queryETFTickerBasket", &TdApi::queryETFTickerBasket)
.def("queryIPOInfoList", &TdApi::queryIPOInfoList)
.def("queryIPOQuotaInfo", &TdApi::queryIPOQuotaInfo)
.def("queryOptionAuctionInfo", &TdApi::queryOptionAuctionInfo)
.def("queryCreditCashRepayInfo", &TdApi::queryCreditCashRepayInfo)
.def("queryCreditFundInfo", &TdApi::queryCreditFundInfo)
.def("queryCreditDebtInfo", &TdApi::queryCreditDebtInfo)
.def("queryCreditDebtInfoByPage", &TdApi::queryCreditDebtInfoByPage)
.def("queryCreditTickerDebtInfo", &TdApi::queryCreditTickerDebtInfo)
.def("queryCreditAssetDebtInfo", &TdApi::queryCreditAssetDebtInfo)
.def("queryCreditTickerAssignInfo", &TdApi::queryCreditTickerAssignInfo)
.def("queryCreditTickerAssignInfoByPage", &TdApi::queryCreditTickerAssignInfoByPage)
.def("queryCreditExcessStock", &TdApi::queryCreditExcessStock)
.def("queryMulCreditExcessStock", &TdApi::queryMulCreditExcessStock)
.def("queryCreditExtendDebtDateOrders", &TdApi::queryCreditExtendDebtDateOrders)
.def("queryCreditFundExtraInfo", &TdApi::queryCreditFundExtraInfo)
.def("queryCreditPositionExtraInfo", &TdApi::queryCreditPositionExtraInfo)
.def("queryOptionCombinedUnfinishedOrders", &TdApi::queryOptionCombinedUnfinishedOrders)
.def("queryOptionCombinedOrderByEMTID", &TdApi::queryOptionCombinedOrderByEMTID)
.def("queryOptionCombinedOrders", &TdApi::queryOptionCombinedOrders)
.def("queryOptionCombinedOrdersByPage", &TdApi::queryOptionCombinedOrdersByPage)
.def("queryOptionCombinedTradesByEMTID", &TdApi::queryOptionCombinedTradesByEMTID)
.def("queryOptionCombinedTrades", &TdApi::queryOptionCombinedTrades)
.def("queryOptionCombinedTradesByPage", &TdApi::queryOptionCombinedTradesByPage)
.def("queryOptionCombinedPosition", &TdApi::queryOptionCombinedPosition)
.def("queryOptionCombinedStrategyInfo", &TdApi::queryOptionCombinedStrategyInfo)
.def("queryCreditPledgeStkRate", &TdApi::queryCreditPledgeStkRate)
.def("queryOptionCombinedExecPosition", &TdApi::queryOptionCombinedExecPosition)
.def("queryCreditMarginRate", &TdApi::queryCreditMarginRate)
.def("queryCreditPositionFullRate", &TdApi::queryCreditPositionFullRate)
.def("queryCreditPledgeStkPagination", &TdApi::queryCreditPledgeStkPagination)
.def("queryCreditTargetStkPagination", &TdApi::queryCreditTargetStkPagination)
.def("queryIssueInfoList", &TdApi::queryIssueInfoList)
.def("querySecurityInfo", &TdApi::querySecurityInfo)
.def("queryCreditQuotaTransfer", &TdApi::queryCreditQuotaTransfer)
.def("queryYesterdayAsset", &TdApi::queryYesterdayAsset)
.def("queryOtcPositionByPage", &TdApi::queryOtcPositionByPage)
.def("queryOtcAsset", &TdApi::queryOtcAsset)
.def("queryOtcOrdersByPage", &TdApi::queryOtcOrdersByPage)
.def("queryOtcTradesByPage", &TdApi::queryOtcTradesByPage)
.def("queryETFByPage", &TdApi::queryETFByPage)
.def("querySecurityByPage", &TdApi::querySecurityByPage)

.def("onConnected", &TdApi::onConnected)
.def("onDisconnected", &TdApi::onDisconnected)
.def("onError", &TdApi::onError)
.def("onOrderEvent", &TdApi::onOrderEvent)
.def("onTradeEvent", &TdApi::onTradeEvent)
.def("onCancelOrderError", &TdApi::onCancelOrderError)
.def("onQueryOrder", &TdApi::onQueryOrder)
.def("onQueryOrderByPage", &TdApi::onQueryOrderByPage)
.def("onQueryTrade", &TdApi::onQueryTrade)
.def("onQueryTradeByPage", &TdApi::onQueryTradeByPage)
.def("onQueryPosition", &TdApi::onQueryPosition)
.def("onQueryPositionByPage", &TdApi::onQueryPositionByPage)
.def("onQueryAsset", &TdApi::onQueryAsset)
.def("onQueryFundTransfer", &TdApi::onQueryFundTransfer)
.def("onFundTransfer", &TdApi::onFundTransfer)
.def("onQueryOtherServerFund", &TdApi::onQueryOtherServerFund)
.def("onQueryETF", &TdApi::onQueryETF)
.def("onQueryETFBasket", &TdApi::onQueryETFBasket)
.def("onQueryIPOInfoList", &TdApi::onQueryIPOInfoList)
.def("onQueryIPOQuotaInfo", &TdApi::onQueryIPOQuotaInfo)
.def("onQueryOptionAuctionInfo", &TdApi::onQueryOptionAuctionInfo)
.def("onCreditCashRepay", &TdApi::onCreditCashRepay)
.def("onCreditCashRepayDebtInterestFee", &TdApi::onCreditCashRepayDebtInterestFee)
.def("onQueryCreditCashRepayInfo", &TdApi::onQueryCreditCashRepayInfo)
.def("onQueryCreditFundInfo", &TdApi::onQueryCreditFundInfo)
.def("onQueryCreditDebtInfo", &TdApi::onQueryCreditDebtInfo)
.def("onQueryCreditDebtInfoByPage", &TdApi::onQueryCreditDebtInfoByPage)
.def("onQueryCreditTickerDebtInfo", &TdApi::onQueryCreditTickerDebtInfo)
.def("onQueryCreditAssetDebtInfo", &TdApi::onQueryCreditAssetDebtInfo)
.def("onQueryCreditTickerAssignInfo", &TdApi::onQueryCreditTickerAssignInfo)
.def("onQueryCreditTickerAssignInfoByPage", &TdApi::onQueryCreditTickerAssignInfoByPage)
.def("onQueryCreditExcessStock", &TdApi::onQueryCreditExcessStock)
.def("onQueryMulCreditExcessStock", &TdApi::onQueryMulCreditExcessStock)
.def("onCreditExtendDebtDate", &TdApi::onCreditExtendDebtDate)
.def("onQueryCreditExtendDebtDateOrders", &TdApi::onQueryCreditExtendDebtDateOrders)
.def("onQueryCreditFundExtraInfo", &TdApi::onQueryCreditFundExtraInfo)
.def("onQueryCreditPositionExtraInfo", &TdApi::onQueryCreditPositionExtraInfo)
.def("onOptionCombinedOrderEvent", &TdApi::onOptionCombinedOrderEvent)
.def("onOptionCombinedTradeEvent", &TdApi::onOptionCombinedTradeEvent)
.def("onCancelOptionCombinedOrderError", &TdApi::onCancelOptionCombinedOrderError)
.def("onQueryOptionCombinedOrders", &TdApi::onQueryOptionCombinedOrders)
.def("onQueryOptionCombinedOrdersByPage", &TdApi::onQueryOptionCombinedOrdersByPage)
.def("onQueryOptionCombinedTrades", &TdApi::onQueryOptionCombinedTrades)
.def("onQueryOptionCombinedTradesByPage", &TdApi::onQueryOptionCombinedTradesByPage)
.def("onQueryOptionCombinedPosition", &TdApi::onQueryOptionCombinedPosition)
.def("onQueryOptionCombinedStrategyInfo", &TdApi::onQueryOptionCombinedStrategyInfo)
.def("onQueryCreditPledgeStkRate", &TdApi::onQueryCreditPledgeStkRate)
.def("onQueryOptionCombinedExecPosition", &TdApi::onQueryOptionCombinedExecPosition)
.def("onQueryCreditMarginRate", &TdApi::onQueryCreditMarginRate)
.def("onQueryCreditPositionFullRate", &TdApi::onQueryCreditPositionFullRate)
.def("onQueryCreditPledgeStkPagination", &TdApi::onQueryCreditPledgeStkPagination)
.def("onQueryCreditTargetStkPagination", &TdApi::onQueryCreditTargetStkPagination)
.def("onQueryIssueInfoList", &TdApi::onQueryIssueInfoList)
.def("onQuerySecurityInfo", &TdApi::onQuerySecurityInfo)
.def("onCreditQuotaTransfer", &TdApi::onCreditQuotaTransfer)
.def("onQueryCreditQuotaTransfer", &TdApi::onQueryCreditQuotaTransfer)
.def("onQueryYesterdayAsset", &TdApi::onQueryYesterdayAsset)
.def("onQueryOtcPositionByPage", &TdApi::onQueryOtcPositionByPage)
.def("onQueryOtcAsset", &TdApi::onQueryOtcAsset)
.def("onQueryOtcOrderByPage", &TdApi::onQueryOtcOrderByPage)
.def("onQueryOtcTradeByPage", &TdApi::onQueryOtcTradeByPage)
.def("onQueryETFByPage", &TdApi::onQueryETFByPage)
.def("onQuerySecurityByPage", &TdApi::onQuerySecurityByPage)
;
