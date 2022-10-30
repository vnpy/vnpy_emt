#include "pch.h"
#include "vnemttd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

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

void TdApi::OnError(EMTRI* error_info)
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

void TdApi::OnOrderEvent(EMTOrderInfo* order_info, EMTRI* error_info, uint64_t session_id)
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
		data["market"] = (int)order_info->market;
		data["price"] = order_info->price;
		data["quantity"] = order_info->quantity;
		data["price_type"] = (int)order_info->price_type;
		data["u32"] = order_info->u32;
		data["side"] = order_info->side;
		data["position_effect"] = order_info->position_effect;
		data["reserved1"] = order_info->reserved1;
		data["reserved2"] = order_info->reserved2;
		data["business_type"] = (int)order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int)order_info->order_status;
		data["order_submit_status"] = (int)order_info->order_submit_status;
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

void TdApi::OnTradeEvent(EMTTradeReport* trade_info, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["ticker"] = trade_info->ticker;
		data["market"] = (int)trade_info->market;
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
		data["business_type"] = (int)trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
	}
	this->onTradeEvent(data, session_id);
};

void TdApi::OnCancelOrderError(EMTOrderCancelInfo* cancel_info, EMTRI* error_info, uint64_t session_id)
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

void TdApi::OnQueryOrder(EMTQueryOrderRsp* order_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
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
		data["market"] = (int)order_info->market;
		data["price"] = order_info->price;
		data["quantity"] = order_info->quantity;
		data["price_type"] = (int)order_info->price_type;
		data["u32"] = order_info->u32;
		data["side"] = order_info->side;
		data["position_effect"] = order_info->position_effect;
		data["reserved1"] = order_info->reserved1;
		data["reserved2"] = order_info->reserved2;
		data["business_type"] = (int)order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int)order_info->order_status;
		data["order_submit_status"] = (int)order_info->order_submit_status;
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

void TdApi::OnQueryOrderByPage(EMTQueryOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
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
		data["market"] = (int)order_info->market;
		data["price"] = order_info->price;
		data["quantity"] = order_info->quantity;
		data["price_type"] = (int)order_info->price_type;
		data["u32"] = order_info->u32;
		data["side"] = order_info->side;
		data["position_effect"] = order_info->position_effect;
		data["reserved1"] = order_info->reserved1;
		data["reserved2"] = order_info->reserved2;
		data["business_type"] = (int)order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int)order_info->order_status;
		data["order_submit_status"] = (int)order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
	}
	this->onQueryOrderByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

void TdApi::OnQueryTrade(EMTQueryTradeRsp* trade_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["ticker"] = trade_info->ticker;
		data["market"] = (int)trade_info->market;
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
		data["business_type"] = (int)trade_info->business_type;
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

void TdApi::OnQueryTradeByPage(EMTQueryTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["ticker"] = trade_info->ticker;
		data["market"] = (int)trade_info->market;
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
		data["business_type"] = (int)trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
	}
	this->onQueryTradeByPage(data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
};

void TdApi::OnQueryPosition(EMTQueryStkPositionRsp* position, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (position)
	{
		data["ticker"] = position->ticker;
		data["ticker_name"] = position->ticker_name;
		data["market"] = (int)position->market;
		data["total_qty"] = position->total_qty;
		data["sellable_qty"] = position->sellable_qty;
		data["avg_price"] = position->avg_price;
		data["unrealized_pnl"] = position->unrealized_pnl;
		data["yesterday_position"] = position->yesterday_position;
		data["purchase_redeemable_qty"] = position->purchase_redeemable_qty;
		data["position_direction"] = (int)position->position_direction;
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

void TdApi::OnQueryPositionByPage(EMTQueryStkPositionRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["ticker"] = trade_info->ticker;
		data["ticker_name"] = trade_info->ticker_name;
		data["market"] = (int)trade_info->market;
		data["total_qty"] = trade_info->total_qty;
		data["sellable_qty"] = trade_info->sellable_qty;
		data["avg_price"] = trade_info->avg_price;
		data["unrealized_pnl"] = trade_info->unrealized_pnl;
		data["yesterday_position"] = trade_info->yesterday_position;
		data["purchase_redeemable_qty"] = trade_info->purchase_redeemable_qty;
		data["position_direction"] = (int)trade_info->position_direction;
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

void TdApi::OnQueryAsset(EMTQueryAssetRsp* asset, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
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
		data["account_type"] = (int)asset->account_type;
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

void TdApi::OnQueryFundTransfer(EMTFundTransferNotice* fund_transfer_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_transfer_info)
	{
		data["serial_id"] = fund_transfer_info->serial_id;
		data["transfer_type"] = (int)fund_transfer_info->transfer_type;
		data["amount"] = fund_transfer_info->amount;
		data["oper_status"] = (int)fund_transfer_info->oper_status;
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

void TdApi::OnFundTransfer(EMTFundTransferNotice* fund_transfer_info, EMTRI* error_info, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_transfer_info)
	{
		data["serial_id"] = fund_transfer_info->serial_id;
		data["transfer_type"] = (int)fund_transfer_info->transfer_type;
		data["amount"] = fund_transfer_info->amount;
		data["oper_status"] = (int)fund_transfer_info->oper_status;
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

void TdApi::OnQueryOtherServerFund(EMTFundQueryRsp* fund_info, EMTRI* error_info, int request_id, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_info)
	{
		data["amount"] = fund_info->amount;
		data["query_type"] = (int)fund_info->query_type;
		data["unknown"] = fund_info->unknown;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryOtherServerFund(data, error, request_id, session_id);
};

void TdApi::OnQueryETF(EMTQueryETFBaseRsp* etf_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (etf_info)
	{
		data["market"] = (int)etf_info->market;
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

void TdApi::OnQueryETFBasket(EMTQueryETFComponentRsp* etf_component_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (etf_component_info)
	{
		data["market"] = (int)etf_component_info->market;
		data["ticker"] = etf_component_info->ticker;
		data["component_ticker"] = etf_component_info->component_ticker;
		data["component_name"] = etf_component_info->component_name;
		data["quantity"] = etf_component_info->quantity;
		data["component_market"] = (int)etf_component_info->component_market;
		data["replace_type"] = (int)etf_component_info->replace_type;
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

void TdApi::OnQueryIPOInfoList(EMTQueryIPOTickerRsp* ipo_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (ipo_info)
	{
		data["market"] = (int)ipo_info->market;
		data["ticker"] = ipo_info->ticker;
		data["ticker_name"] = ipo_info->ticker_name;
		data["ticker_type"] = (int)ipo_info->ticker_type;
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

void TdApi::OnQueryIPOQuotaInfo(EMTQueryIPOQuotaRsp* quota_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (quota_info)
	{
		data["market"] = (int)quota_info->market;
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

void TdApi::OnQueryOptionAuctionInfo(EMTQueryOptionAuctionInfoRsp* option_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (option_info)
	{
		data["ticker"] = option_info->ticker;
		data["security_id_source"] = (int)option_info->security_id_source;
		data["symbol"] = option_info->symbol;
		data["contract_id"] = option_info->contract_id;
		data["underlying_security_id"] = option_info->underlying_security_id;
		data["underlying_security_id_source"] = (int)option_info->underlying_security_id_source;
		data["list_date"] = option_info->list_date;
		data["last_trade_date"] = option_info->last_trade_date;
		data["ticker_type"] = (int)option_info->ticker_type;
		data["day_trading"] = option_info->day_trading;
		data["call_or_put"] = (int)option_info->call_or_put;
		data["delivery_day"] = option_info->delivery_day;
		data["delivery_month"] = option_info->delivery_month;
		data["exercise_type"] = (int)option_info->exercise_type;
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

void TdApi::OnCreditCashRepay(EMTCrdCashRepayRsp* cash_repay_info, EMTRI* error_info, uint64_t session_id)
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

void TdApi::OnCreditCashRepayDebtInterestFee(EMTCrdCashRepayDebtInterestFeeRsp* cash_repay_info, EMTRI* error_info, uint64_t session_id)
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

void TdApi::OnQueryCreditCashRepayInfo(EMTCrdCashRepayInfo* cash_repay_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (cash_repay_info)
	{
		data["emt_id"] = cash_repay_info->emt_id;
		data["status"] = (int)cash_repay_info->status;
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

void TdApi::OnQueryCreditFundInfo(EMTCrdFundInfo* fund_info, EMTRI* error_info, int request_id, uint64_t session_id)
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

void TdApi::OnQueryCreditDebtInfo(EMTCrdDebtInfo* debt_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
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
		data["market"] = (int)debt_info->market;
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

void TdApi::OnQueryCreditDebtInfoByPage(EMTCrdDebtInfo* debt_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
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
		data["market"] = (int)debt_info->market;
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

void TdApi::OnQueryCreditTickerDebtInfo(EMTCrdDebtStockInfo* debt_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_info)
	{
		data["market"] = (int)debt_info->market;
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

void TdApi::OnQueryCreditAssetDebtInfo(double remain_amount, EMTRI* error_info, int request_id, uint64_t session_id)
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

void TdApi::OnQueryCreditTickerAssignInfo(EMTClientQueryCrdPositionStkInfo* assign_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (assign_info)
	{
		data["market"] = (int)assign_info->market;
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
		data["market"] = (int)debt_info->market;
		data["ticker"] = debt_info->ticker;
		data["limit_qty"] = debt_info->limit_qty;
		data["yesterday_qty"] = debt_info->yesterday_qty;
		data["left_qty"] = debt_info->left_qty;
		data["frozen_qty"] = debt_info->frozen_qty;
		data["end_date"] = debt_info->end_date;
	}
	this->onQueryCreditTickerAssignInfoByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

void TdApi::OnQueryCreditExcessStock(EMTClientQueryCrdSurplusStkRspInfo* stock_info, EMTRI* error_info, int request_id, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (stock_info)
	{
		data["market"] = (int)stock_info->market;
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

void TdApi::OnQueryMulCreditExcessStock(EMTClientQueryCrdSurplusStkRspInfo* stock_info, EMTRI* error_info, int request_id, uint64_t session_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	if (stock_info)
	{
		data["market"] = (int)stock_info->market;
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

void TdApi::OnCreditExtendDebtDate(EMTCreditDebtExtendNotice* debt_extend_info, EMTRI* error_info, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_extend_info)
	{
		data["emtid"] = debt_extend_info->emtid;
		data["debt_id"] = debt_extend_info->debt_id;
		data["oper_status"] = (int)debt_extend_info->oper_status;
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

void TdApi::OnQueryCreditExtendDebtDateOrders(EMTCreditDebtExtendNotice* debt_extend_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (debt_extend_info)
	{
		data["emtid"] = debt_extend_info->emtid;
		data["debt_id"] = debt_extend_info->debt_id;
		data["oper_status"] = (int)debt_extend_info->oper_status;
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

void TdApi::OnQueryCreditFundExtraInfo(EMTCrdFundExtraInfo* fund_info, EMTRI* error_info, int request_id, uint64_t session_id)
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

void TdApi::OnQueryCreditPositionExtraInfo(EMTCrdPositionExtraInfo* fund_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (fund_info)
	{
		data["market"] = (int)fund_info->market;
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

void TdApi::OnOptionCombinedOrderEvent(EMTOptCombOrderInfo* order_info, EMTRI* error_info, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["market"] = (int)order_info->market;
		data["quantity"] = order_info->quantity;
		data["side"] = order_info->side;
		data["business_type"] = (int)order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int)order_info->order_status;
		data["order_submit_status"] = (int)order_info->order_submit_status;
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

void TdApi::OnOptionCombinedTradeEvent(EMTOptCombTradeReport* trade_info, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["market"] = (int)trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["side"] = trade_info->side;
		data["business_type"] = (int)trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
		data["opt_comb_info"] = trade_info->opt_comb_info;
	}
	this->onOptionCombinedTradeEvent(data, session_id);
};

void TdApi::OnCancelOptionCombinedOrderError(EMTOptCombOrderCancelInfo* cancel_info, EMTRI* error_info, uint64_t session_id)
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

void TdApi::OnQueryOptionCombinedOrders(EMTQueryOptCombOrderRsp* order_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["market"] = (int)order_info->market;
		data["quantity"] = order_info->quantity;
		data["side"] = order_info->side;
		data["business_type"] = (int)order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int)order_info->order_status;
		data["order_submit_status"] = (int)order_info->order_submit_status;
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

void TdApi::OnQueryOptionCombinedOrdersByPage(EMTQueryOptCombOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (order_info)
	{
		data["order_emt_id"] = order_info->order_emt_id;
		data["order_client_id"] = order_info->order_client_id;
		data["order_cancel_client_id"] = order_info->order_cancel_client_id;
		data["order_cancel_emt_id"] = order_info->order_cancel_emt_id;
		data["market"] = (int)order_info->market;
		data["quantity"] = order_info->quantity;
		data["side"] = order_info->side;
		data["business_type"] = (int)order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int)order_info->order_status;
		data["order_submit_status"] = (int)order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
		data["opt_comb_info"] = order_info->opt_comb_info;
	}
	this->onQueryOptionCombinedOrdersByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

void TdApi::OnQueryOptionCombinedTrades(EMTQueryOptCombTradeRsp* trade_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["market"] = (int)trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["side"] = trade_info->side;
		data["business_type"] = (int)trade_info->business_type;
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

void TdApi::OnQueryOptionCombinedTradesByPage(EMTQueryOptCombTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["market"] = (int)trade_info->market;
		data["local_order_id"] = trade_info->local_order_id;
		data["exec_id"] = trade_info->exec_id;
		data["quantity"] = trade_info->quantity;
		data["trade_time"] = trade_info->trade_time;
		data["trade_amount"] = trade_info->trade_amount;
		data["report_index"] = trade_info->report_index;
		data["order_exch_id"] = trade_info->order_exch_id;
		data["trade_type"] = trade_info->trade_type;
		data["side"] = trade_info->side;
		data["business_type"] = (int)trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
		data["opt_comb_info"] = trade_info->opt_comb_info;
	}
	this->onQueryOptionCombinedTradesByPage(data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
};

void TdApi::OnQueryOptionCombinedPosition(EMTQueryOptCombPositionRsp* position_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (position_info)
	{
		data["strategy_id"] = position_info->strategy_id;
		data["strategy_name"] = position_info->strategy_name;
		data["market"] = (int)position_info->market;
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

void TdApi::OnQueryOptionCombinedStrategyInfo(EMTQueryCombineStrategyInfoRsp* strategy_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (strategy_info)
	{
		data["strategy_id"] = strategy_info->strategy_id;
		data["strategy_name"] = strategy_info->strategy_name;
		data["market"] = (int)strategy_info->market;
		data["leg_num"] = strategy_info->leg_num;
		data["leg_strategy"] = strategy_info->leg_strategy;
		data["expire_date_type"] = (int)strategy_info->expire_date_type;
		data["underlying_type"] = (int)strategy_info->underlying_type;
		data["auto_sep_type"] = (int)strategy_info->auto_sep_type;
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

void TdApi::OnQueryCreditPledgeStkRate(EMTClientQueryCreditPledgeStkRateRsp* pledge_stk_rate_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (pledge_stk_rate_info)
	{
		data["market"] = (int)pledge_stk_rate_info->market;
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

void TdApi::OnQueryOptionCombinedExecPosition(EMTQueryOptCombExecPosRsp* position_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (position_info)
	{
		data["market"] = (int)position_info->market;
		data["cntrt_code_1"] = position_info->cntrt_code_1;
		data["cntrt_name_1"] = position_info->cntrt_name_1;
		data["position_side_1"] = (int)position_info->position_side_1;
		data["call_or_put_1"] = (int)position_info->call_or_put_1;
		data["avl_qty_1"] = position_info->avl_qty_1;
		data["orig_own_qty_1"] = position_info->orig_own_qty_1;
		data["own_qty_1"] = position_info->own_qty_1;
		data["cntrt_code_2"] = position_info->cntrt_code_2;
		data["cntrt_name_2"] = position_info->cntrt_name_2;
		data["position_side_2"] = (int)position_info->position_side_2;
		data["call_or_put_2"] = (int)position_info->call_or_put_2;
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

void TdApi::OnQueryCreditMarginRate(EMTClientQueryCreditMarginRateRsp* margin_rate_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (margin_rate_info)
	{
		data["market"] = (int)margin_rate_info->market;
		data["ticker"] = margin_rate_info->ticker;
		data["credit_fund_ctrl"] = (int)margin_rate_info->credit_fund_ctrl;
		data["margin_rate_fund"] = margin_rate_info->margin_rate_fund;
		data["credit_stk_ctrl"] = (int)margin_rate_info->credit_stk_ctrl;
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

void TdApi::OnQueryCreditPositionFullRate(EMTClientQueryCreditPositionFullRateRsp* position_fullrate_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (position_fullrate_info)
	{
		data["market"] = (int)position_fullrate_info->market;
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

void TdApi::OnQueryCreditPledgeStkPagination(EMTClientQueryCreditPledgeStkPaginationRsp* pledge_stk_info, EMTRI* error_info, int request_id, uint64_t session_id)
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

void TdApi::OnQueryCreditTargetStkPagination(EMTClientQueryCreditTargetStkPaginationRsp* target_stk_info, EMTRI* error_info, int request_id, uint64_t session_id)
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

void TdApi::OnQueryIssueInfoList(EMTQueryIssueTickerRsp* issue_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (issue_info)
	{
		data["market"] = (int)issue_info->market;
		data["ticker"] = issue_info->ticker;
		data["ticker_name"] = issue_info->ticker_name;
		data["ticker_type"] = (int)issue_info->ticker_type;
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

void TdApi::OnQuerySecurityInfo(EMTQuerySecurityInfoRsp* security, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (security)
	{
		data["ticker"] = security->ticker;
		data["ticker_name"] = security->ticker_name;
		data["market"] = (int)security->market;
		data["ticker_type"] = (int)security->ticker_type;
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

void TdApi::OnCreditQuotaTransfer(EMTQuotaTransferNotice* quota_transfer_info, EMTRI* error_info, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (quota_transfer_info)
	{
		data["serial_id"] = quota_transfer_info->serial_id;
		data["transfer_type"] = (int)quota_transfer_info->transfer_type;
		data["amount"] = quota_transfer_info->amount;
		data["oper_status"] = (int)quota_transfer_info->oper_status;
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

void TdApi::OnQueryCreditQuotaTransfer(EMTQuotaTransferNotice* quota_transfer_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (quota_transfer_info)
	{
		data["serial_id"] = quota_transfer_info->serial_id;
		data["transfer_type"] = (int)quota_transfer_info->transfer_type;
		data["amount"] = quota_transfer_info->amount;
		data["oper_status"] = (int)quota_transfer_info->oper_status;
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

void TdApi::OnQueryYesterdayAsset(EMTQueryYesterdayAssetRsp* yesterday_asset, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (yesterday_asset)
	{
		data["total_asset"] = yesterday_asset->total_asset;
		data["pure_asset"] = yesterday_asset->pure_asset;
		data["fund_asset"] = yesterday_asset->fund_asset;
		data["security_asset"] = yesterday_asset->security_asset;
		data["account_type"] = (int)yesterday_asset->account_type;
	}
	dict error;
	if (error_info)
	{
		error["error_id"] = error_info->error_id;
		error["error_msg"] = error_info->error_msg;
	}
	this->onQueryYesterdayAsset(data, error, request_id, is_last, session_id);
};

//void TdApi::OnQueryOtcPositionByPage(EMTOtcPositionInfo* position_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
//{
//	gil_scoped_acquire acquire;
//	this->onQueryOtcPositionByPage(position_info, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
//};

//void TdApi::OnQueryOtcAsset(EMTOtcAssetInfo* asset, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id)
//{
//	gil_scoped_acquire acquire;
//	dict error;
//	if (error_info)
//	{
//		error["error_id"] = error_info->error_id;
//		error["error_msg"] = error_info->error_msg;
//	}
//	this->onQueryOtcAsset(asset, error, request_id, is_last, session_id);
//};

void TdApi::OnQueryOtcOrderByPage(EMTQueryOrderRsp* order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
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
		data["market"] = (int)order_info->market;
		data["price"] = order_info->price;
		data["quantity"] = order_info->quantity;
		data["price_type"] = (int)order_info->price_type;
		data["u32"] = order_info->u32;
		data["side"] = order_info->side;
		data["position_effect"] = order_info->position_effect;
		data["reserved1"] = order_info->reserved1;
		data["reserved2"] = order_info->reserved2;
		data["business_type"] = (int)order_info->business_type;
		data["qty_traded"] = order_info->qty_traded;
		data["qty_left"] = order_info->qty_left;
		data["insert_time"] = order_info->insert_time;
		data["update_time"] = order_info->update_time;
		data["cancel_time"] = order_info->cancel_time;
		data["trade_amount"] = order_info->trade_amount;
		data["order_local_id"] = order_info->order_local_id;
		data["order_status"] = (int)order_info->order_status;
		data["order_submit_status"] = (int)order_info->order_submit_status;
		data["order_type"] = order_info->order_type;
	}
	this->onQueryOtcOrderByPage(data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
};

void TdApi::OnQueryOtcTradeByPage(EMTQueryTradeRsp* trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (trade_info)
	{
		data["order_emt_id"] = trade_info->order_emt_id;
		data["order_client_id"] = trade_info->order_client_id;
		data["ticker"] = trade_info->ticker;
		data["market"] = (int)trade_info->market;
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
		data["business_type"] = (int)trade_info->business_type;
		data["branch_pbu"] = trade_info->branch_pbu;
	}
	this->onQueryOtcTradeByPage(data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
};

void TdApi::OnQueryETFByPage(EMTQueryETFBaseRsp* etf_info, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (etf_info)
	{
		data["market"] = (int)etf_info->market;
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

void TdApi::OnQuerySecurityByPage(EMTQuerySecurityByPageRsp* security_info, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id)
{
	gil_scoped_acquire acquire;
	dict data;
	if (security_info)
	{
		data["ticker"] = security_info->ticker;
		data["ticker_name"] = security_info->ticker_name;
		data["market"] = (int)security_info->market;
		data["ticker_type"] = (int)security_info->ticker_type;
		data["qty_unit"] = security_info->qty_unit;
		data["day_trading"] = security_info->day_trading;
		data["highest_price"] = security_info->highest_price;
		data["minimum_price"] = security_info->minimum_price;
		data["interest"] = security_info->interest;
	}
	this->onQuerySecurityByPage(data, req_count, rsp_sequence, query_reference, request_id, is_last, session_id);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createTraderApi(int client_id, string save_file_path, int log_level)
{
	if (!this->api)
	{
		this->api = TraderApi::CreateTraderApi(client_id, save_file_path.c_str(), EMT_LOG_LEVEL(log_level));
		this->api->RegisterSpi(this);
	}
};

void TdApi::init()
{
	if (!this->active)
	{
		this->active = true;
	}
};

void TdApi::release()
{
	this->api->Release();
};

int TdApi::exit()
{	
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	
	this->active = false;
	return 1;
};

string TdApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

string TdApi::getApiVersion()
{
	string version = this->api->GetApiVersion();
	return version;
};

dict TdApi::getApiLastError()
{
	EMTRI*last_error = this->api->GetApiLastError();
	dict error;
	error["error_id"] = last_error->error_id;
	error["error_msg"] = last_error->error_msg;
	return error;
};

int TdApi::getClientIDByXTPID(uint64_t order_xtp_id)
{
	int i = this->api->GetClientIDByEMTID(order_xtp_id);
	return i;
};

string TdApi::getAccountByXTPID(uint64_t order_xtp_id)
{
	string account = this->api->GetAccountByEMTID(order_xtp_id);
	return account;
};

void TdApi::subscribePublicTopic(int resume_type)
{
	this->api->SubscribePublicTopic((EMT_TE_RESUME_TYPE)resume_type);
}

void TdApi::setSoftwareVersion(string version)
{
	this->api->SetSoftwareVersion(version.c_str());
}

///void TdApi::setSoftwareKey(string key)
///{
///	this->api->SetSoftwareKey(key.c_str());
///}

void TdApi::setHeartBeatInterval(int interval)
{
	this->api->SetHeartBeatInterval(interval);
}

uint64_t TdApi::login(string ip, int port, string user, string password, int sock_type)
{
	uint64_t i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (EMT_PROTOCOL_TYPE)sock_type);
	return i;
};

int TdApi::logout(uint64_t session_id)
{
	int i = this->api->Logout(session_id);
	return i;
};

bool TdApi::isServerRestart(uint64_t session_id)
{
	return this->api->IsServerRestart(session_id);
};

//int TdApi::modifyUserTerminalInfo(const dict &req, uint64_t session_id)
//{
//	EMTUserTerminalInfoReq myreq;
//	memset(&myreq, 0, sizeof(myreq));
//
//	getString(req, "local_ip", myreq.local_ip);
//	getString(req, "mac_addr", myreq.mac_addr);
//	getString(req, "hd", myreq.hd);
//	getString(req, "internet_ip", myreq.internet_ip);
//	getInt32_t(req, "internet_port", &myreq.internet_port);
//	getString(req, "client_version", myreq.client_version);
//	getString(req, "macos_sno", myreq.macos_sno);
//	getString(req, "unused", myreq.unused);
//	myreq.term_type = (EMTTerminalType)getIntValue(req, "term_type");
//
//	return this->api->ModifyUserTerminalInfo(&myreq, session_id);
//};

uint64_t TdApi::insertOrder(const dict &req, uint64_t session_id)
{
	EMTOrderInsertInfo myreq;
	memset(&myreq, 0, sizeof(myreq));

	getUint64_t(req, "order_xtp_id", &myreq.order_emt_id);
	getUint32_t(req, "order_client_id", &myreq.order_client_id);
	getString(req, "ticker", myreq.ticker);
	getDouble(req, "price", &myreq.price);
	getDouble(req, "stop_price", &myreq.stop_price);
	getInt64_t(req, "quantity", &myreq.quantity);
	
	myreq.side = getIntValue(req, "side");
	myreq.position_effect = getIntValue(req, "position_effect");
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	myreq.price_type = (EMT_PRICE_TYPE)getIntValue(req, "price_type");
	myreq.business_type = (EMT_BUSINESS_TYPE)getIntValue(req, "business_type");

	uint64_t i = this->api->InsertOrder(&myreq, session_id);
	return i;
};

uint64_t TdApi::cancelOrder(uint64_t order_xtp_id, uint64_t session_id)
{
	uint64_t i = this->api->CancelOrder(order_xtp_id, session_id);
	return i;
}

int TdApi::queryOrderByEMTID(uint64_t order_emt_id, uint64_t session_id, int request_id)
{
	int i = this->api->QueryOrderByEMTID(order_emt_id, session_id, request_id);
	return i;
};

int TdApi::queryOrders(const dict& req, uint64_t session_id, int request_id)
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

int TdApi::queryOrdersByPage(const dict& req, uint64_t session_id, int request_id)
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

int TdApi::queryTrades(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryTraderReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ticker", myreq.ticker);
	getInt64_t(req, "begin_time", &myreq.begin_time);
	getInt64_t(req, "end_time", &myreq.end_time);
	int i = this->api->QueryTrades(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryTradesByPage(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryTraderByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryTradesByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryPosition(string ticker, uint64_t session_id, int request_id, int market)
{
	int i = this->api->QueryPosition(ticker.c_str(), session_id, request_id, (EMT_MARKET_TYPE)market);
	return i;
};

int TdApi::queryPositionByPage(const dict& req, uint64_t session_id, int request_id)
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

int TdApi::queryFundTransfer(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryFundTransferLogReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getUint64_t(req, "serial_id", &myreq.serial_id);
	int i = this->api->QueryFundTransfer(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOtherServerFund(const dict& req, uint64_t session_id, int request_id)
{
	EMTFundQueryReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "fund_account", myreq.fund_account);
	getString(req, "password", myreq.password);
	myreq.query_type = (EMT_FUND_QUERY_TYPE)getIntValue(req, "query_type");
	getUint64_t(req, "unknown", myreq.unknown);
	int i = this->api->QueryOtherServerFund(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryETF(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryETFBaseReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryETF(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryETFTickerBasket(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryETFComponentReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
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

int TdApi::queryOptionAuctionInfo(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOptionAuctionInfoReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
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

//int TdApi::queryCreditDebtInfoByPage(const dict& req, uint64_t session_id, int request_id)
//{
//	EMTQueryCreditDebtInfoByPageReq myreq;
//	memset(&myreq, 0, sizeof(myreq));
//	getInt64_t(req, "req_count", &myreq.req_count);
//	getInt64_t(req, "reference", &myreq.reference);
//	getInt64_t(req, "reserved", &myreq.reserved);
//	int i = this->api->QueryCreditDebtInfoByPage(&myreq, session_id, request_id);
//	return i;
//};

int TdApi::queryCreditTickerDebtInfo(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdDebtStockReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditTickerDebtInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditAssetDebtInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryCreditAssetDebtInfo(session_id, request_id);
	return i;
};

int TdApi::queryCreditTickerAssignInfo(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdPositionStockReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditTickerAssignInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditTickerAssignInfoByPage(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryTickerAssignInfoByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryCreditTickerAssignInfoByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditExcessStock(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdSurplusStkReqInfo myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditExcessStock(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryMulCreditExcessStock(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdSurplusStkReqInfo myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
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

int TdApi::queryCreditPositionExtraInfo(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCrdPositionStockReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
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

int TdApi::queryOptionCombinedOrders(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombOrderReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "comb_num", myreq.comb_num);
	getInt64_t(req, "begin_time", &myreq.begin_time);
	getInt64_t(req, "end_time", &myreq.end_time);
	int i = this->api->QueryOptionCombinedOrders(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedOrdersByPage(const dict& req, uint64_t session_id, int request_id)
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

int TdApi::queryOptionCombinedTrades(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombTraderReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "comb_num", myreq.comb_num);
	getInt64_t(req, "begin_time", &myreq.begin_time);
	getInt64_t(req, "end_time", &myreq.end_time);
	int i = this->api->QueryOptionCombinedTrades(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedTradesByPage(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombTraderByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryOptionCombinedTradesByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedPosition(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombPositionReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "comb_num", myreq.comb_num);
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	int i = this->api->QueryOptionCombinedPosition(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedStrategyInfo(uint64_t session_id, int request_id)
{
	int i = this->api->QueryOptionCombinedStrategyInfo(session_id, request_id);
	return i;
};

int TdApi::queryCreditPledgeStkRate(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditPledgeStkRateReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditPledgeStkRate(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOptionCombinedExecPosition(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOptCombExecPosReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	getString(req, "cntrt_code_1", myreq.cntrt_code_1);
	getString(req, "cntrt_code_2", myreq.cntrt_code_2);
	int i = this->api->QueryOptionCombinedExecPosition(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditMarginRate(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditMarginRateReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditMarginRate(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditPositionFullRate(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditPositionFullRateReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditPositionFullRate(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditPledgeStkPagination(const dict& req, uint64_t session_id, int request_id)
{
	EMTClientQueryCreditPledgeStkPaginationReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt32_t(req, "page", &myreq.page);
	getInt32_t(req, "count", &myreq.count);
	int i = this->api->QueryCreditPledgeStkPagination(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditTargetStkPagination(const dict& req, uint64_t session_id, int request_id)
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

int TdApi::querySecurityInfo(const dict& req, uint64_t session_id, int request_id)
{
	EMTQuerySecurityInfoReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ticker", myreq.ticker);
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	int i = this->api->QuerySecurityInfo(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryCreditQuotaTransfer(const dict& req, uint64_t session_id, int request_id)
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

int TdApi::queryOtcPositionByPage(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOtcPositionByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getString(req, "ticker", myreq.ticker);
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	int i = this->api->QueryOtcPositionByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOtcAsset(uint64_t session_id, int request_id)
{
	int i = this->api->QueryOtcAsset(session_id, request_id);
	return i;
};

int TdApi::queryOtcOrdersByPage(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOtcOrdersByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getString(req, "ticker", myreq.ticker);
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	int i = this->api->QueryOtcOrdersByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryOtcTradesByPage(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryOtcTradesByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getString(req, "ticker", myreq.ticker);
	myreq.market = (EMT_MARKET_TYPE)getIntValue(req, "market");
	int i = this->api->QueryOtcTradesByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::queryETFByPage(const dict& req, uint64_t session_id, int request_id)
{
	EMTQueryETFByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QueryETFByPage(&myreq, session_id, request_id);
	return i;
};

int TdApi::querySecurityByPage(const dict& req, uint64_t session_id, int request_id)
{
	EMTQuerySecurityByPageReq myreq;
	memset(&myreq, 0, sizeof(myreq));
	getInt64_t(req, "req_count", &myreq.req_count);
	getInt64_t(req, "reference", &myreq.reference);
	getInt64_t(req, "reserved", &myreq.reserved);
	int i = this->api->QuerySecurityByPage(&myreq, session_id, request_id);
	return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
	using TdApi::TdApi;

	void onConnected() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onConnected);
		}
		catch (const error_already_set& e)
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
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onError(const dict& error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onError, error);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onOrderEvent(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onOrderEvent, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onTradeEvent(const dict& data, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onTradeEvent, data, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onCancelOrderError(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCancelOrderError, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOrder(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOrder, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOrderByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOrderByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryTrade(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryTrade, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryTradeByPage(const dict& data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryTradeByPage, data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryPosition(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryPosition, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryPositionByPage(const dict& data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryPositionByPage, data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryAsset(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryAsset, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryFundTransfer(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryFundTransfer, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onFundTransfer(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onFundTransfer, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOtherServerFund(const dict& data, const dict& error, int request_id, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOtherServerFund, data, error, request_id, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryETF(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryETF, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryETFBasket(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryETFBasket, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIPOInfoList(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIPOInfoList, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIPOQuotaInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIPOQuotaInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionAuctionInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionAuctionInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditCashRepay(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditCashRepay, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditCashRepayDebtInterestFee(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditCashRepayDebtInterestFee, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditCashRepayInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditCashRepayInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditFundInfo(const dict& data, const dict& error, int request_id, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditFundInfo, data, error, request_id, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditDebtInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditDebtInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditDebtInfoByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditDebtInfoByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditTickerDebtInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTickerDebtInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditAssetDebtInfo(double remain_amount, const dict& error, int request_id, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditAssetDebtInfo, remain_amount, error, request_id, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditTickerAssignInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTickerAssignInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditTickerAssignInfoByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTickerAssignInfoByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditExcessStock(const dict& data, const dict& error, int request_id, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditExcessStock, data, error, request_id, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryMulCreditExcessStock(const dict& data, const dict& error, int request_id, uint64_t session_id, bool is_last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryMulCreditExcessStock, data, error, request_id, session_id, is_last);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditExtendDebtDate(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditExtendDebtDate, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditExtendDebtDateOrders(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditExtendDebtDateOrders, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditFundExtraInfo(const dict& data, const dict& error, int request_id, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditFundExtraInfo, data, error, request_id, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditPositionExtraInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditPositionExtraInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onOptionCombinedOrderEvent(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onOptionCombinedOrderEvent, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onOptionCombinedTradeEvent(const dict& data, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onOptionCombinedTradeEvent, data, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onCancelOptionCombinedOrderError(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCancelOptionCombinedOrderError, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionCombinedOrders(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedOrders, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionCombinedOrdersByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedOrdersByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionCombinedTrades(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedTrades, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionCombinedTradesByPage(const dict& data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedTradesByPage, data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionCombinedPosition(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedPosition, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionCombinedStrategyInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedStrategyInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditPledgeStkRate(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditPledgeStkRate, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionCombinedExecPosition(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionCombinedExecPosition, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditMarginRate(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditMarginRate, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditPositionFullRate(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditPositionFullRate, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditPledgeStkPagination(const dict& data, const dict& error, int request_id, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditPledgeStkPagination, data, error, request_id, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditTargetStkPagination(const dict& data, const dict& error, int request_id, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTargetStkPagination, data, error, request_id, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIssueInfoList(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIssueInfoList, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQuerySecurityInfo(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQuerySecurityInfo, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditQuotaTransfer(const dict& data, const dict& error, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditQuotaTransfer, data, error, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditQuotaTransfer(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditQuotaTransfer, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryYesterdayAsset(const dict& data, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryYesterdayAsset, data, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
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
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOtcAsset(EMTOtcAssetInfo asset, const dict& error, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOtcAsset, asset, error, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOtcOrderByPage(const dict& data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOtcOrderByPage, data, req_count, order_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOtcTradeByPage(const dict& data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOtcTradeByPage, data, req_count, trade_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryETFByPage(const dict& data, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryETFByPage, data, req_count, rsp_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

	void onQuerySecurityByPage(const dict& data, int64_t req_count, int64_t rsp_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQuerySecurityByPage, data, req_count, rsp_sequence, query_reference, request_id, is_last, session_id);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};
};


PYBIND11_MODULE(vnemttd, m)
{
	class_<TdApi, PyTdApi> TdApi(m, "TdApi", module_local());
	TdApi
		.def(init<>())
		.def("createTraderApi", &TdApi::createTraderApi)
		.def("init", &TdApi::init)
		.def("release", &TdApi::release)
		.def("exit", &TdApi::exit)
		.def("getTradingDay", &TdApi::getTradingDay)
		.def("getApiVersion", &TdApi::getApiVersion)
		.def("getApiLastError", &TdApi::getApiLastError)
		.def("getClientIDByXTPID", &TdApi::getClientIDByXTPID)
		.def("getAccountByXTPID", &TdApi::getAccountByXTPID)
		.def("subscribePublicTopic", &TdApi::subscribePublicTopic)
		.def("setSoftwareVersion", &TdApi::setSoftwareVersion)
		/*.def("setSoftwareKey", &TdApi::setSoftwareKey)*/
		.def("setHeartBeatInterval", &TdApi::setHeartBeatInterval)
		.def("login", &TdApi::login)
		.def("logout", &TdApi::logout)
		.def("isServerRestart", &TdApi::isServerRestart)
		///.def("modifyUserTerminalInfo", &TdApi::modifyUserTerminalInfo)
		.def("insertOrder", &TdApi::insertOrder)
		.def("cancelOrder", &TdApi::cancelOrder)

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
		/*.def("queryCreditDebtInfoByPage", &TdApi::queryCreditDebtInfoByPage)*/
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
}


