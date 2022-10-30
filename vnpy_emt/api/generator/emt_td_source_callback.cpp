            void TdApi::OnConnected() 
{
	gil_scoped_acquire acquire;
	this->onConnected();
};

            void TdApi::OnDisconnected(int reason) 
{
	gil_scoped_acquire acquire;
	this->onDisconnected(reason);
};

            void TdApi::OnError(EMTRI *error_info) 
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onError(error);
};

            void TdApi::OnOrderEvent(EMTOrderInfo *order_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["ticker"] = order_info->ticker;
		data["market"] = (int) order_info->market;
		data["price"] = order_info->price;
		data["quantity"] = order_info->quantity;
		data["price_type"] = (int) order_info->price_type;
		data["u32"] = order_info->u32;
		data["side"] = order_info->side;
		data["position_effect"] = order_info->position_effect;
		data["reserved1"] = order_info->reserved1;
		data["reserved2"] = order_info->reserved2;
		data["business_type"] = (int) order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int) order_info->order_status;
		data["order_submit_status"] = (int) order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onOrderEvent(data, error, session_id);
};

            void TdApi::OnTradeEvent(EMTTradeReport *trade_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["ticker"] = trade_info->ticker;
		data["market"] = (int) trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["price"] = trade_info->price;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["u32"] = trade_info->u32;
		data["side"] = trade_info->side;
		data["position_effect"] = trade_info->position_effect;
		data["reserved1"] = trade_info->reserved1;
		data["reserved2"] = trade_info->reserved2;
		data["business_type"] = (int) trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
	}
	this->onTradeEvent(data, session_id);
};

            void TdApi::OnCancelOrderError(EMTOrderCancelInfo *cancel_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (cancel_info)
	{
		data["order_cancel_emt_id"] = cancel_info->order_cancel_emt_id;
		data["order_emt_id"] = cancel_info->order_emt_id;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onCancelOrderError(data, error, session_id);
};

            void TdApi::OnQueryOrder(EMTQueryOrderRsp *order_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["ticker"] = order_info->ticker;
		data["market"] = (int) order_info->market;
		data["price"] = order_info->price;
		data["quantity"] = order_info->quantity;
		data["price_type"] = (int) order_info->price_type;
		data["u32"] = order_info->u32;
		data["side"] = order_info->side;
		data["position_effect"] = order_info->position_effect;
		data["reserved1"] = order_info->reserved1;
		data["reserved2"] = order_info->reserved2;
		data["business_type"] = (int) order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int) order_info->order_status;
		data["order_submit_status"] = (int) order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOrder(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryOrderByPage(EMTQueryOrderRsp *order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["ticker"] = order_info->ticker;
		data["market"] = (int) order_info->market;
		data["price"] = order_info->price;
		data["quantity"] = order_info->quantity;
		data["price_type"] = (int) order_info->price_type;
		data["u32"] = order_info->u32;
		data["side"] = order_info->side;
		data["position_effect"] = order_info->position_effect;
		data["reserved1"] = order_info->reserved1;
		data["reserved2"] = order_info->reserved2;
		data["business_type"] = (int) order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int) order_info->order_status;
		data["order_submit_status"] = (int) order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
	}
	this->onQueryOrderByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryTrade(EMTQueryTradeRsp *trade_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["ticker"] = trade_info->ticker;
		data["market"] = (int) trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["price"] = trade_info->price;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["u32"] = trade_info->u32;
		data["side"] = trade_info->side;
		data["position_effect"] = trade_info->position_effect;
		data["reserved1"] = trade_info->reserved1;
		data["reserved2"] = trade_info->reserved2;
		data["business_type"] = (int) trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryTrade(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryTradeByPage(EMTQueryTradeRsp *trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["ticker"] = trade_info->ticker;
		data["market"] = (int) trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["price"] = trade_info->price;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["u32"] = trade_info->u32;
		data["side"] = trade_info->side;
		data["position_effect"] = trade_info->position_effect;
		data["reserved1"] = trade_info->reserved1;
		data["reserved2"] = trade_info->reserved2;
		data["business_type"] = (int) trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
	}
	this->onQueryTradeByPage(data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryPosition(EMTQueryStkPositionRsp *position, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (position)
	{
		data["ticker"] = position->ticker;
		data["ticker_name"] = position->ticker_name;
		data["market"] = (int) position->market;
		data["total_qty"] = position->total_qty;
		data["sellable_qty"] = position->sellable_qty;
		data["avg_price"] = position->avg_price;
		data["unrealized_pnl"] = position->unrealized_pnl;
		data["yesterday_position"] = position->yesterday_position;
		data["purchase_redeemable_qty"] = position->purchase_redeemable_qty;
		data["position_direction"] = (int) position->position_direction;
		data["reserved1"] = position->reserved1;
		data["executable_option"] = position->executable_option;
		data["lockable_position"] = position->lockable_position;
		data["executable_underlying"] = position->executable_underlying;
		data["locked_position"] = position->locked_position;
		data["usable_locked_position"] = position->usable_locked_position;
		data["unknown"] = position->unknown;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryPosition(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryPositionByPage(EMTQueryStkPositionRsp *trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["ticker"] = trade_info->ticker;
		data["ticker_name"] = trade_info->ticker_name;
		data["market"] = (int) trade_info->market;
		data["total_qty"] = trade_info->total_qty;
		data["sellable_qty"] = trade_info->sellable_qty;
		data["avg_price"] = trade_info->avg_price;
		data["unrealized_pnl"] = trade_info->unrealized_pnl;
		data["yesterday_position"] = trade_info->yesterday_position;
		data["purchase_redeemable_qty"] = trade_info->purchase_redeemable_qty;
		data["position_direction"] = (int) trade_info->position_direction;
		data["reserved1"] = trade_info->reserved1;
		data["executable_option"] = trade_info->executable_option;
		data["lockable_position"] = trade_info->lockable_position;
		data["executable_underlying"] = trade_info->executable_underlying;
		data["locked_position"] = trade_info->locked_position;
		data["usable_locked_position"] = trade_info->usable_locked_position;
		data["unknown"] = trade_info->unknown;
	}
	this->onQueryPositionByPage(data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryAsset(EMTQueryAssetRsp *asset, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (asset)
	{
		data["total_asset"] = asset->total_asset;
		data["buying_power"] = asset->buying_power;
		data["security_asset"] = asset->security_asset;
		data["fund_buy_amount"] = asset->fund_buy_amount;
		data["fund_buy_fee"] = asset->fund_buy_fee;
		data["fund_sell_amount"] = asset->fund_sell_amount;
		data["fund_sell_fee"] = asset->fund_sell_fee;
		data["withholding_amount"] = asset->withholding_amount;
		data["account_type"] = (int) asset->account_type;
		data["frozen_margin"] = asset->frozen_margin;
		data["frozen_exec_cash"] = asset->frozen_exec_cash;
		data["frozen_exec_fee"] = asset->frozen_exec_fee;
		data["pay_later"] = asset->pay_later;
		data["preadva_pay"] = asset->preadva_pay;
		data["orig_banlance"] = asset->orig_banlance;
		data["banlance"] = asset->banlance;
		data["deposit_withdraw"] = asset->deposit_withdraw;
		data["trade_netting"] = asset->trade_netting;
		data["captial_asset"] = asset->captial_asset;
		data["force_freeze_amount"] = asset->force_freeze_amount;
		data["preferred_amount"] = asset->preferred_amount;
		data["repay_stock_aval_banlance"] = asset->repay_stock_aval_banlance;
		data["fund_order_data_charges"] = asset->fund_order_data_charges;
		data["fund_cancel_data_charges"] = asset->fund_cancel_data_charges;
		data["unknown"] = asset->unknown;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryAsset(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryFundTransfer(EMTFundTransferNotice *fund_transfer_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_transfer_info)
	{
		data["serial_id"] = fund_transfer_info->serial_id;
		data["transfer_type"] = (int) fund_transfer_info->transfer_type;
		data["amount"] = fund_transfer_info->amount;
		data["oper_status"] = (int) fund_transfer_info->oper_status;
		data["transfer_time"] = fund_transfer_info->transfer_time;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryFundTransfer(data, error, request_id, is_last, session_id);
};

            void TdApi::OnFundTransfer(EMTFundTransferNotice *fund_transfer_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_transfer_info)
	{
		data["serial_id"] = fund_transfer_info->serial_id;
		data["transfer_type"] = (int) fund_transfer_info->transfer_type;
		data["amount"] = fund_transfer_info->amount;
		data["oper_status"] = (int) fund_transfer_info->oper_status;
		data["transfer_time"] = fund_transfer_info->transfer_time;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onFundTransfer(data, error, session_id);
};

            void TdApi::OnQueryOtherServerFund(EMTFundQueryRsp *fund_info, EMTRI *error_info, int request_id, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOtherServerFund(fund_info, error, request_id, session_id);
};

            void TdApi::OnQueryETF(EMTQueryETFBaseRsp *etf_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (etf_info)
	{
		data["market"] = (int) etf_info->market;
		data["etf"] = etf_info->etf;
		data["subscribe_redemption_ticker"] = etf_info->subscribe_redemption_ticker;
		data["unit"] = etf_info->unit;
		data["subscribe_status"] = etf_info->subscribe_status;
		data["redemption_status"] = etf_info->redemption_status;
		data["max_cash_ratio"] = etf_info->max_cash_ratio;
		data["estimate_amount"] = etf_info->estimate_amount;
		data["cash_component"] = etf_info->cash_component;
		data["net_value"] = etf_info->net_value;
		data["total_amount"] = etf_info->total_amount;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryETF(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryETFBasket(EMTQueryETFComponentRsp *etf_component_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (etf_component_info)
	{
		data["market"] = (int) etf_component_info->market;
		data["ticker"] = etf_component_info->ticker;
		data["component_ticker"] = etf_component_info->component_ticker;
		data["component_name"] = etf_component_info->component_name;
		data["quantity"] = etf_component_info->quantity;
		data["component_market"] = (int) etf_component_info->component_market;
		data["replace_type"] = (int) etf_component_info->replace_type;
		data["premium_ratio"] = etf_component_info->premium_ratio;
		data["amount"] = etf_component_info->amount;
		data["creation_premium_ratio"] = etf_component_info->creation_premium_ratio;
		data["redemption_discount_ratio"] = etf_component_info->redemption_discount_ratio;
		data["creation_amount"] = etf_component_info->creation_amount;
		data["redemption_amount"] = etf_component_info->redemption_amount;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryETFBasket(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryIPOInfoList(EMTQueryIPOTickerRsp *ipo_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (ipo_info)
	{
		data["market"] = (int) ipo_info->market;
		data["ticker"] = ipo_info->ticker;
		data["ticker_name"] = ipo_info->ticker_name;
		data["ticker_type"] = (int) ipo_info->ticker_type;
		data["price"] = ipo_info->price;
		data["unit"] = ipo_info->unit;
		data["qty_upper_limit"] = ipo_info->qty_upper_limit;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryIPOInfoList(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryIPOQuotaInfo(EMTQueryIPOQuotaRsp *quota_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (quota_info)
	{
		data["market"] = (int) quota_info->market;
		data["quantity"] = quota_info->quantity;
		data["tech_quantity"] = quota_info->tech_quantity;
		data["unused"] = quota_info->unused;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryIPOQuotaInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryOptionAuctionInfo(EMTQueryOptionAuctionInfoRsp *option_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (option_info)
	{
		data["ticker"] = option_info->ticker;
		data["security_id_source"] = (int) option_info->security_id_source;
		data["symbol"] = option_info->symbol;
		data["contract_id"] = option_info->contract_id;
		data["underlying_security_id"] = option_info->underlying_security_id;
		data["underlying_security_id_source"] = (int) option_info->underlying_security_id_source;
		data["list_date"] = option_info->list_date;
		data["last_trade_date"] = option_info->last_trade_date;
		data["ticker_type"] = (int) option_info->ticker_type;
		data["day_trading"] = option_info->day_trading;
		data["call_or_put"] = (int) option_info->call_or_put;
		data["delivery_day"] = option_info->delivery_day;
		data["delivery_month"] = option_info->delivery_month;
		data["exercise_type"] = (int) option_info->exercise_type;
		data["exercise_begin_date"] = option_info->exercise_begin_date;
		data["exercise_end_date"] = option_info->exercise_end_date;
		data["exercise_price"] = option_info->exercise_price;
		data["qty_unit"] = option_info->qty_unit;
		data["contract_unit"] = option_info->contract_unit;
		data["contract_position"] = option_info->contract_position;
		data["prev_close_price"] = option_info->prev_close_price;
		data["prev_clearing_price"] = option_info->prev_clearing_price;
		data["lmt_buy_max_qty"] = option_info->lmt_buy_max_qty;
		data["lmt_buy_min_qty"] = option_info->lmt_buy_min_qty;
		data["lmt_sell_max_qty"] = option_info->lmt_sell_max_qty;
		data["lmt_sell_min_qty"] = option_info->lmt_sell_min_qty;
		data["mkt_buy_max_qty"] = option_info->mkt_buy_max_qty;
		data["mkt_buy_min_qty"] = option_info->mkt_buy_min_qty;
		data["mkt_sell_max_qty"] = option_info->mkt_sell_max_qty;
		data["mkt_sell_min_qty"] = option_info->mkt_sell_min_qty;
		data["price_tick"] = option_info->price_tick;
		data["upper_limit_price"] = option_info->upper_limit_price;
		data["lower_limit_price"] = option_info->lower_limit_price;
		data["sell_margin"] = option_info->sell_margin;
		data["margin_ratio_param1"] = option_info->margin_ratio_param1;
		data["margin_ratio_param2"] = option_info->margin_ratio_param2;
		data["unknown"] = option_info->unknown;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOptionAuctionInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnCreditCashRepay(EMTCrdCashRepayRsp *cash_repay_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (cash_repay_info)
	{
		data["emt_id"] = cash_repay_info->emt_id;
		data["request_amount"] = cash_repay_info->request_amount;
		data["cash_repay_amount"] = cash_repay_info->cash_repay_amount;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onCreditCashRepay(data, error, session_id);
};

            void TdApi::OnCreditCashRepayDebtInterestFee(EMTCrdCashRepayDebtInterestFeeRsp *cash_repay_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (cash_repay_info)
	{
		data["emt_id"] = cash_repay_info->emt_id;
		data["request_amount"] = cash_repay_info->request_amount;
		data["cash_repay_amount"] = cash_repay_info->cash_repay_amount;
		data["debt_compact_id"] = cash_repay_info->debt_compact_id;
		data["unknow"] = cash_repay_info->unknow;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onCreditCashRepayDebtInterestFee(data, error, session_id);
};

            void TdApi::OnQueryCreditCashRepayInfo(EMTCrdCashRepayInfo *cash_repay_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (cash_repay_info)
	{
		data["emt_id"] = cash_repay_info->emt_id;
		data["status"] = (int) cash_repay_info->status;
		data["request_amount"] = cash_repay_info->request_amount;
		data["cash_repay_amount"] = cash_repay_info->cash_repay_amount;
		data["position_effect"] = cash_repay_info->position_effect;
		data["error_info"] = cash_repay_info->error_info;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditCashRepayInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditFundInfo(EMTCrdFundInfo *fund_info, EMTRI *error_info, int request_id, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_info)
	{
		data["maintenance_ratio"] = fund_info->maintenance_ratio;
		data["all_asset"] = fund_info->all_asset;
		data["all_debt"] = fund_info->all_debt;
		data["line_of_credit"] = fund_info->line_of_credit;
		data["guaranty"] = fund_info->guaranty;
		data["position_amount"] = fund_info->position_amount;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditFundInfo(data, error, request_id, session_id);
};

            void TdApi::OnQueryCreditDebtInfo(EMTCrdDebtInfo *debt_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_info)
	{
		data["debt_type"] = debt_info->debt_type;
		data["debt_id"] = debt_info->debt_id;
		data["position_id"] = debt_info->position_id;
		data["order_emt_id"] = debt_info->order_emt_id;
		data["debt_status"] = debt_info->debt_status;
		data["market"] = (int) debt_info->market;
		data["ticker"] = debt_info->ticker;
		data["order_date"] = debt_info->order_date;
		data["end_date"] = debt_info->end_date;
		data["orig_end_date"] = debt_info->orig_end_date;
		data["is_extended"] = debt_info->is_extended;
		data["remain_amt"] = debt_info->remain_amt;
		data["remain_qty"] = debt_info->remain_qty;
		data["remain_principal"] = debt_info->remain_principal;
		data["due_right_qty"] = debt_info->due_right_qty;
		data["trans_righs_amt"] = debt_info->trans_righs_amt;
		data["trans_righs_qty"] = debt_info->trans_righs_qty;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditDebtInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditDebtInfoByPage(EMTCrdDebtInfo *debt_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_info)
	{
		data["debt_type"] = debt_info->debt_type;
		data["debt_id"] = debt_info->debt_id;
		data["position_id"] = debt_info->position_id;
		data["order_emt_id"] = debt_info->order_emt_id;
		data["debt_status"] = debt_info->debt_status;
		data["market"] = (int) debt_info->market;
		data["ticker"] = debt_info->ticker;
		data["order_date"] = debt_info->order_date;
		data["end_date"] = debt_info->end_date;
		data["orig_end_date"] = debt_info->orig_end_date;
		data["is_extended"] = debt_info->is_extended;
		data["remain_amt"] = debt_info->remain_amt;
		data["remain_qty"] = debt_info->remain_qty;
		data["remain_principal"] = debt_info->remain_principal;
		data["due_right_qty"] = debt_info->due_right_qty;
		data["trans_righs_amt"] = debt_info->trans_righs_amt;
		data["trans_righs_qty"] = debt_info->trans_righs_qty;
	}
	this->onQueryCreditDebtInfoByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditTickerDebtInfo(EMTCrdDebtStockInfo *debt_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_info)
	{
		data["market"] = (int) debt_info->market;
		data["ticker"] = debt_info->ticker;
		data["stock_repay_quantity"] = debt_info->stock_repay_quantity;
		data["stock_total_quantity"] = debt_info->stock_total_quantity;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditTickerDebtInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditAssetDebtInfo(double remain_amount, EMTRI *error_info, int request_id, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditAssetDebtInfo(remain_amount, error, request_id, session_id);
};

            void TdApi::OnQueryCreditTickerAssignInfo(EMTClientQueryCrdPositionStkInfo *assign_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (assign_info)
	{
		data["market"] = (int) assign_info->market;
		data["ticker"] = assign_info->ticker;
		data["limit_qty"] = assign_info->limit_qty;
		data["yesterday_qty"] = assign_info->yesterday_qty;
		data["left_qty"] = assign_info->left_qty;
		data["frozen_qty"] = assign_info->frozen_qty;
		data["end_date"] = assign_info->end_date;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditTickerAssignInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditTickerAssignInfoByPage(EMTClientQueryCrdPositionStkInfo* debt_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_info)
	{
		data["market"] = (int) debt_info->market;
		data["ticker"] = debt_info->ticker;
		data["limit_qty"] = debt_info->limit_qty;
		data["yesterday_qty"] = debt_info->yesterday_qty;
		data["left_qty"] = debt_info->left_qty;
		data["frozen_qty"] = debt_info->frozen_qty;
		data["end_date"] = debt_info->end_date;
	}
	this->onQueryCreditTickerAssignInfoByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditExcessStock(EMTClientQueryCrdSurplusStkRspInfo* stock_info, EMTRI *error_info, int request_id, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (stock_info)
	{
		data["market"] = (int) stock_info->market;
		data["ticker"] = stock_info->ticker;
		data["transferable_quantity"] = stock_info->transferable_quantity;
		data["transferred_quantity"] = stock_info->transferred_quantity;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditExcessStock(data, error, request_id, session_id);
};

            void TdApi::OnQueryMulCreditExcessStock(EMTClientQueryCrdSurplusStkRspInfo* stock_info, EMTRI *error_info, int request_id, uint64_t session_id, bool is_last) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (stock_info)
	{
		data["market"] = (int) stock_info->market;
		data["ticker"] = stock_info->ticker;
		data["transferable_quantity"] = stock_info->transferable_quantity;
		data["transferred_quantity"] = stock_info->transferred_quantity;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryMulCreditExcessStock(data, error, request_id, session_id, is_last);
};

            void TdApi::OnCreditExtendDebtDate(EMTCreditDebtExtendNotice *debt_extend_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_extend_info)
	{
		data["emtid"] = debt_extend_info->emtid;
		data["debt_id"] = debt_extend_info->debt_id;
		data["oper_status"] = (int) debt_extend_info->oper_status;
		data["oper_time"] = debt_extend_info->oper_time;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onCreditExtendDebtDate(data, error, session_id);
};

            void TdApi::OnQueryCreditExtendDebtDateOrders(EMTCreditDebtExtendNotice *debt_extend_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_extend_info)
	{
		data["emtid"] = debt_extend_info->emtid;
		data["debt_id"] = debt_extend_info->debt_id;
		data["oper_status"] = (int) debt_extend_info->oper_status;
		data["oper_time"] = debt_extend_info->oper_time;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditExtendDebtDateOrders(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditFundExtraInfo(EMTCrdFundExtraInfo *fund_info, EMTRI *error_info, int request_id, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_info)
	{
		data["mf_rs_avl_used"] = fund_info->mf_rs_avl_used;
		data["reserve"] = fund_info->reserve;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditFundExtraInfo(data, error, request_id, session_id);
};

            void TdApi::OnQueryCreditPositionExtraInfo(EMTCrdPositionExtraInfo *fund_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_info)
	{
		data["market"] = (int) fund_info->market;
		data["ticker"] = fund_info->ticker;
		data["mf_rs_avl_used"] = fund_info->mf_rs_avl_used;
		data["reserve"] = fund_info->reserve;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditPositionExtraInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnOptionCombinedOrderEvent(EMTOptCombOrderInfo *order_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["market"] = (int) order_info->market;
		data["quantity"] = order_info->quantity;
		data["side"] = order_info->side;
		data["business_type"] = (int) order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int) order_info->order_status;
		data["order_submit_status"] = (int) order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
		data["opt_comb_info"] = order_info->opt_comb_info;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onOptionCombinedOrderEvent(data, error, session_id);
};

            void TdApi::OnOptionCombinedTradeEvent(EMTOptCombTradeReport *trade_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["market"] = (int) trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["side"] = trade_info->side;
		data["business_type"] = (int) trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
		data["opt_comb_info"] = trade_info->opt_comb_info;
	}
	this->onOptionCombinedTradeEvent(data, session_id);
};

            void TdApi::OnCancelOptionCombinedOrderError(EMTOptCombOrderCancelInfo *cancel_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (cancel_info)
	{
		data["order_cancel_emt_id"] = cancel_info->order_cancel_emt_id;
		data["order_emt_id"] = cancel_info->order_emt_id;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onCancelOptionCombinedOrderError(data, error, session_id);
};

            void TdApi::OnQueryOptionCombinedOrders(EMTQueryOptCombOrderRsp *order_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["market"] = (int) order_info->market;
		data["quantity"] = order_info->quantity;
		data["side"] = order_info->side;
		data["business_type"] = (int) order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int) order_info->order_status;
		data["order_submit_status"] = (int) order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
		data["opt_comb_info"] = order_info->opt_comb_info;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOptionCombinedOrders(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryOptionCombinedOrdersByPage(EMTQueryOptCombOrderRsp *order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["market"] = (int) order_info->market;
		data["quantity"] = order_info->quantity;
		data["side"] = order_info->side;
		data["business_type"] = (int) order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int) order_info->order_status;
		data["order_submit_status"] = (int) order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
		data["opt_comb_info"] = order_info->opt_comb_info;
	}
	this->onQueryOptionCombinedOrdersByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryOptionCombinedTrades(EMTQueryOptCombTradeRsp *trade_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["market"] = (int) trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["side"] = trade_info->side;
		data["business_type"] = (int) trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
		data["opt_comb_info"] = trade_info->opt_comb_info;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOptionCombinedTrades(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryOptionCombinedTradesByPage(EMTQueryOptCombTradeRsp *trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["market"] = (int) trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["side"] = trade_info->side;
		data["business_type"] = (int) trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
		data["opt_comb_info"] = trade_info->opt_comb_info;
	}
	this->onQueryOptionCombinedTradesByPage(data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryOptionCombinedPosition(EMTQueryOptCombPositionRsp *position_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (position_info)
	{
		data["strategy_id"] = position_info->strategy_id;
		data["strategy_name"] = position_info->strategy_name;
		data["market"] = (int) position_info->market;
		data["total_qty"] = position_info->total_qty;
		data["available_qty"] = position_info->available_qty;
		data["yesterday_position"] = position_info->yesterday_position;
		data["opt_comb_info"] = position_info->opt_comb_info;
		data["reserved"] = position_info->reserved;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOptionCombinedPosition(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryOptionCombinedStrategyInfo(EMTQueryCombineStrategyInfoRsp *strategy_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (strategy_info)
	{
		data["strategy_id"] = strategy_info->strategy_id;
		data["strategy_name"] = strategy_info->strategy_name;
		data["market"] = (int) strategy_info->market;
		data["leg_num"] = strategy_info->leg_num;
		data["leg_strategy"] = strategy_info->leg_strategy;
		data["expire_date_type"] = (int) strategy_info->expire_date_type;
		data["underlying_type"] = (int) strategy_info->underlying_type;
		data["auto_sep_type"] = (int) strategy_info->auto_sep_type;
		data["reserved"] = strategy_info->reserved;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOptionCombinedStrategyInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditPledgeStkRate(EMTClientQueryCreditPledgeStkRateRsp *pledge_stk_rate_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (pledge_stk_rate_info)
	{
		data["market"] = (int) pledge_stk_rate_info->market;
		data["ticker"] = pledge_stk_rate_info->ticker;
		data["pledge_rate"] = pledge_stk_rate_info->pledge_rate;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditPledgeStkRate(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryOptionCombinedExecPosition(EMTQueryOptCombExecPosRsp *position_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (position_info)
	{
		data["market"] = (int) position_info->market;
		data["cntrt_code_1"] = position_info->cntrt_code_1;
		data["cntrt_name_1"] = position_info->cntrt_name_1;
		data["position_side_1"] = (int) position_info->position_side_1;
		data["call_or_put_1"] = (int) position_info->call_or_put_1;
		data["avl_qty_1"] = position_info->avl_qty_1;
		data["orig_own_qty_1"] = position_info->orig_own_qty_1;
		data["own_qty_1"] = position_info->own_qty_1;
		data["cntrt_code_2"] = position_info->cntrt_code_2;
		data["cntrt_name_2"] = position_info->cntrt_name_2;
		data["position_side_2"] = (int) position_info->position_side_2;
		data["call_or_put_2"] = (int) position_info->call_or_put_2;
		data["avl_qty_2"] = position_info->avl_qty_2;
		data["orig_own_qty_2"] = position_info->orig_own_qty_2;
		data["own_qty_2"] = position_info->own_qty_2;
		data["net_qty"] = position_info->net_qty;
		data["order_qty"] = position_info->order_qty;
		data["confirm_qty"] = position_info->confirm_qty;
		data["avl_qty"] = position_info->avl_qty;
		data["reserved"] = position_info->reserved;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOptionCombinedExecPosition(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditMarginRate(EMTClientQueryCreditMarginRateRsp *margin_rate_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (margin_rate_info)
	{
		data["market"] = (int) margin_rate_info->market;
		data["ticker"] = margin_rate_info->ticker;
		data["credit_fund_ctrl"] = (int) margin_rate_info->credit_fund_ctrl;
		data["margin_rate_fund"] = margin_rate_info->margin_rate_fund;
		data["credit_stk_ctrl"] = (int) margin_rate_info->credit_stk_ctrl;
		data["margin_rate_stk"] = margin_rate_info->margin_rate_stk;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditMarginRate(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditPositionFullRate(EMTClientQueryCreditPositionFullRateRsp *position_fullrate_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (position_fullrate_info)
	{
		data["market"] = (int) position_fullrate_info->market;
		data["ticker"] = position_fullrate_info->ticker;
		data["fullrate"] = position_fullrate_info->fullrate;
		data["reserve"] = position_fullrate_info->reserve;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditPositionFullRate(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryCreditPledgeStkPagination(EMTClientQueryCreditPledgeStkPaginationRsp *pledge_stk_info, EMTRI *error_info, int request_id, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (pledge_stk_info)
	{
		data["page_info"] = pledge_stk_info->page_info;
		data["pledge_stk_info"] = pledge_stk_info->pledge_stk_info;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditPledgeStkPagination(data, error, request_id, session_id);
};

            void TdApi::OnQueryCreditTargetStkPagination(EMTClientQueryCreditTargetStkPaginationRsp *target_stk_info, EMTRI *error_info, int request_id, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (target_stk_info)
	{
		data["page_info"] = target_stk_info->page_info;
		data["target_stk_info"] = target_stk_info->target_stk_info;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditTargetStkPagination(data, error, request_id, session_id);
};

            void TdApi::OnQueryIssueInfoList(EMTQueryIssueTickerRsp *issue_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (issue_info)
	{
		data["market"] = (int) issue_info->market;
		data["ticker"] = issue_info->ticker;
		data["ticker_name"] = issue_info->ticker_name;
		data["ticker_type"] = (int) issue_info->ticker_type;
		data["under_ticker"] = issue_info->under_ticker;
		data["price"] = issue_info->price;
		data["unit"] = issue_info->unit;
		data["qty_upper_limit"] = issue_info->qty_upper_limit;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryIssueInfoList(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQuerySecurityInfo(EMTQuerySecurityInfoRsp *security, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (security)
	{
		data["ticker"] = security->ticker;
		data["ticker_name"] = security->ticker_name;
		data["market"] = (int) security->market;
		data["ticker_type"] = (int) security->ticker_type;
		data["qty_unit"] = security->qty_unit;
		data["day_trading"] = security->day_trading;
		data["highest_price"] = security->highest_price;
		data["minimum_price"] = security->minimum_price;
		data["interest"] = security->interest;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQuerySecurityInfo(data, error, request_id, is_last, session_id);
};

            void TdApi::OnCreditQuotaTransfer(EMTQuotaTransferNotice *quota_transfer_info, EMTRI *error_info, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (quota_transfer_info)
	{
		data["serial_id"] = quota_transfer_info->serial_id;
		data["transfer_type"] = (int) quota_transfer_info->transfer_type;
		data["amount"] = quota_transfer_info->amount;
		data["oper_status"] = (int) quota_transfer_info->oper_status;
		data["transfer_time"] = quota_transfer_info->transfer_time;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onCreditQuotaTransfer(data, error, session_id);
};

            void TdApi::OnQueryCreditQuotaTransfer(EMTQuotaTransferNotice *quota_transfer_info, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (quota_transfer_info)
	{
		data["serial_id"] = quota_transfer_info->serial_id;
		data["transfer_type"] = (int) quota_transfer_info->transfer_type;
		data["amount"] = quota_transfer_info->amount;
		data["oper_status"] = (int) quota_transfer_info->oper_status;
		data["transfer_time"] = quota_transfer_info->transfer_time;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryCreditQuotaTransfer(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryYesterdayAsset(EMTQueryYesterdayAssetRsp *yesterday_asset, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (yesterday_asset)
	{
		data["total_asset"] = yesterday_asset->total_asset;
		data["pure_asset"] = yesterday_asset->pure_asset;
		data["fund_asset"] = yesterday_asset->fund_asset;
		data["security_asset"] = yesterday_asset->security_asset;
		data["account_type"] = (int) yesterday_asset->account_type;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryYesterdayAsset(data, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryOtcPositionByPage(EMTOtcPositionInfo *position_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	this->onQueryOtcPositionByPage(position_info, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryOtcAsset(EMTOtcAssetInfo *asset, EMTRI *error_info, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOtcAsset(asset, error, request_id, is_last, session_id);
};

            void TdApi::OnQueryOtcOrderByPage(EMTQueryOrderRsp *order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["ticker"] = order_info->ticker;
		data["market"] = (int) order_info->market;
		data["price"] = order_info->price;
		data["quantity"] = order_info->quantity;
		data["price_type"] = (int) order_info->price_type;
		data["u32"] = order_info->u32;
		data["side"] = order_info->side;
		data["position_effect"] = order_info->position_effect;
		data["reserved1"] = order_info->reserved1;
		data["reserved2"] = order_info->reserved2;
		data["business_type"] = (int) order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int) order_info->order_status;
		data["order_submit_status"] = (int) order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
	}
	this->onQueryOtcOrderByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryOtcTradeByPage(EMTQueryTradeRsp *trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) 
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["ticker"] = trade_info->ticker;
		data["market"] = (int) trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["price"] = trade_info->price;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["u32"] = trade_info->u32;
		data["side"] = trade_info->side;
		data["position_effect"] = trade_info->position_effect;
		data["reserved1"] = trade_info->reserved1;
		data["reserved2"] = trade_info->reserved2;
		data["business_type"] = (int) trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
	}
	this->onQueryOtcTradeByPage(data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQueryETFByPage(EMTQueryETFBaseRsp *etf_info, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (etf_info)
	{
		data["market"] = (int) etf_info->market;
		data["etf"] = etf_info->etf;
		data["subscribe_redemption_ticker"] = etf_info->subscribe_redemption_ticker;
		data["unit"] = etf_info->unit;
		data["subscribe_status"] = etf_info->subscribe_status;
		data["redemption_status"] = etf_info->redemption_status;
		data["max_cash_ratio"] = etf_info->max_cash_ratio;
		data["estimate_amount"] = etf_info->estimate_amount;
		data["cash_component"] = etf_info->cash_component;
		data["net_value"] = etf_info->net_value;
		data["total_amount"] = etf_info->total_amount;
	}
	this->onQueryETFByPage(data, req_count, rsp_sequence, query_reference, request_id, is_last, session_id);
};

            void TdApi::OnQuerySecurityByPage(EMTQuerySecurityByPageRsp *security_info, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (security_info)
	{
		data["ticker"] = security_info->ticker;
		data["ticker_name"] = security_info->ticker_name;
		data["market"] = (int) security_info->market;
		data["ticker_type"] = (int) security_info->ticker_type;
		data["qty_unit"] = security_info->qty_unit;
		data["day_trading"] = security_info->day_trading;
		data["highest_price"] = security_info->highest_price;
		data["minimum_price"] = security_info->minimum_price;
		data["interest"] = security_info->interest;
	}
	this->onQuerySecurityByPage(data, req_count, rsp_sequence, query_reference, request_id, is_last, session_id);
};

