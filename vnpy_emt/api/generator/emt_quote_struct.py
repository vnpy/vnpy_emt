EMTSpecificTickerStruct = {
	"exchange_id": "enum",
	"ticker": "char",
}

EMTRspInfoStruct = {
	"error_id": "int32_t",
	"error_msg": "char",
}

EMTIndexDataStruct = {
	"exchange_id": "enum",
	"ticker": "char",
	"data_time": "int64_t",
	"pre_close_price": "double",
	"open_price": "double",
	"last_price": "double",
	"high_price": "double",
	"low_price": "double",
	"qty": "int64_t",
	"turnover": "double",
}

EMTMarketDataFundExData = {
	"iopv": "double",
	"etf_buy_count": "int32_t",
	"etf_sell_count": "int32_t",
	"etf_buy_qty": "double",
	"etf_buy_money": "double",
	"etf_sell_qty": "double",
	"etf_sell_money": "double",
	"pre_iopv": "double",
}

EMTMarketDataBondExData = {
	"ma_bond_bid_price": "double",
	"ma_bond_ask_price": "double",
	"yield_to_maturity": "double",
}

EMTMarketDataWarrantExData = {
	"total_warrant_exec_qty": "double",
	"warrant_lower_price": "double",
	"warrant_upper_price": "double",
}

EMTMarketDataOptionExData = {
	"auction_price": "double",
	"auction_qty": "int64_t",
	"last_enquiry_time": "int64_t",
	"pre_total_long_positon": "int64_t",
	"total_long_positon": "int64_t",
	"pre_settl_price": "double",
	"settl_price": "double",
}

EMTMarketDataStruct = {
	"exchange_id": "enum",
	"ticker": "char",
	"last_price": "double",
	"pre_close_price": "double",
	"open_price": "double",
	"high_price": "double",
	"low_price": "double",
	"close_price": "double",
	"upper_limit_price": "double",
	"lower_limit_price": "double",
	"data_time": "int64_t",
	"qty": "int64_t",
	"turnover": "double",
	"avg_price": "double",
	"bid": "double",
	"ask": "double",
	"bid_qty": "int64_t",
	"ask_qty": "int64_t",
	"trades_count": "int64_t",
	"ticker_status": "char",
	"total_bid_qty": "int64_t",
	"total_ask_qty": "int64_t",
	"ma_bid_price": "double",
	"ma_ask_price": "double",
	"cancel_buy_count": "int32_t",
	"cancel_sell_count": "int32_t",
	"cancel_buy_qty": "double",
	"cancel_sell_qty": "double",
	"cancel_buy_money": "double",
	"cancel_sell_money": "double",
	"total_buy_count": "int64_t",
	"total_sell_count": "int64_t",
	"duration_after_buy": "int32_t",
	"duration_after_sell": "int32_t",
	"num_bid_orders": "int32_t",
	"num_ask_orders": "int32_t",
	"bond": "EMTMarketDataBondExData",
	"fund": "EMTMarketDataFundExData",
	"warrant": "EMTMarketDataWarrantExData",
	"opt": "EMTMarketDataOptionExData",
	"data_type": "enum",
}

EMTTickByTickEntrust = {
	"channel_no": "int32_t",
	"side": "char",
	"ord_type": "char",
	"__filler": "char",
	"seq": "int64_t",
	"price": "double",
	"qty": "int64_t",
}

EMTTickByTickTrade = {
	"channel_no": "int32_t",
	"trade_flag": "char",
	"__filler": "char",
	"seq": "int64_t",
	"bid_no": "int64_t",
	"ask_no": "int64_t",
	"price": "double",
	"qty": "int64_t",
	"money": "double",
}

EMTTickByTickStruct = {
	"data_time": "int64_t",
	"seq": "int64_t",
	"exchange_id": "enum",
	"ticker": "char",
	"type": "enum",
	"entrust": "EMTTickByTickEntrust",
	"trade": "EMTTickByTickTrade",
}

EMTQuoteStaticInfo = {
	"exchange_id": "enum",
	"ticker": "char",
	"ticker_name": "char",
	"ticker_type": "enum",
	"pre_close_price": "double",
	"upper_limit_price": "double",
	"lower_limit_price": "double",
	"price_tick": "double",
	"buy_qty_unit": "int32_t",
	"sell_qty_unit": "int32_t",
}

EMTQuoteFullInfo = {
	"exchange_id": "enum",
	"ticker": "char",
	"ticker_name": "char",
	"security_type": "enum",
	"ticker_qualification_class": "enum",
	"is_registration": "bool",
	"is_VIE": "bool",
	"is_noprofit": "bool",
	"is_weighted_voting_rights": "bool",
	"is_have_price_limit": "bool",
	"upper_limit_price": "double",
	"lower_limit_price": "double",
	"pre_close_price": "double",
	"price_tick": "double",
	"bid_qty_upper_limit": "int32_t",
	"bid_qty_lower_limit": "int32_t",
	"bid_qty_unit": "int32_t",
	"ask_qty_upper_limit": "int32_t",
	"ask_qty_lower_limit": "int32_t",
	"ask_qty_unit": "int32_t",
	"market_bid_qty_upper_limit": "int32_t",
	"market_bid_qty_lower_limit": "int32_t",
	"market_bid_qty_unit": "int32_t",
	"market_ask_qty_upper_limit": "int32_t",
	"market_ask_qty_lower_limit": "int32_t",
	"market_ask_qty_unit": "int32_t",
	"unknown": "uint64_t",
}

EMTOrderBookStruct = {
	"exchange_id": "enum",
	"ticker": "char",
	"last_price": "double",
	"qty": "int64_t",
	"turnover": "double",
	"trades_count": "int64_t",
	"bid": "double",
	"ask": "double",
	"bid_qty": "int64_t",
	"ask_qty": "int64_t",
	"data_time": "int64_t",
}

EMTMinuteInfo = {
	"exchange_type": "enum",
	"ticker_type": "enum",
	"ticker": "char",
	"data_time": "int64_t",
	"last_price": "double",
	"volume_trade": "int64_t",
	"value_trade": "double",
	"avg_price": "double",
}

EMTTickerPriceInfo = {
	"exchange_type": "enum",
	"ticker": "char",
	"last_price": "double",
}

