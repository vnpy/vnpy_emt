from typing import Any, Dict, List
from datetime import datetime
from copy import copy

from vnpy.event import EventEngine
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.constant import (
    Exchange,
    Product,
    Direction,
    OrderType,
    Status,
    Offset,
    OptionType
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    CancelRequest,
    OrderRequest,
    SubscribeRequest,
    TickData,
    ContractData,
    OrderData,
    TradeData,
    PositionData,
    AccountData
)
from vnpy.trader.utility import get_folder_path, round_to, ZoneInfo

from ..api import MdApi, TdApi


# 交易所映射
MARKET_EMT2VT: Dict[int, Exchange] = {
    1: Exchange.SZSE,
    2: Exchange.SSE
}
MARKET_VT2EMT: Dict[Exchange, int] = {v: k for k, v in MARKET_EMT2VT.items()}

EXCHANGE_EMT2VT: Dict[int, Exchange] = {
    1: Exchange.SSE,
    2: Exchange.SZSE,
}
EXCHANGE_VT2EMT: Dict[Exchange, int] = {v: k for k, v in EXCHANGE_EMT2VT.items()}

# 多空和开平方向映射
DIRECTION_STOCK_EMT2VT: Dict[int, Any] = {
    1: (Direction.LONG, Offset.NONE),
    2: (Direction.SHORT, Offset.NONE),
    21: (Direction.LONG, Offset.OPEN),
    22: (Direction.SHORT, Offset.OPEN),
    24: (Direction.LONG, Offset.CLOSE),
    23: (Direction.SHORT, Offset.CLOSE)
}
DIRECTION_STOCK_VT2EMT: Dict[Any, int] = {v: k for k, v in DIRECTION_STOCK_EMT2VT.items()}

DIRECTION_OPTION_EMT2VT: Dict[int, Direction] = {
    1: Direction.LONG,
    2: Direction.SHORT
}
DIRECTION_OPTION_VT2EMT: Dict[Direction, int] = {v: k for k, v in DIRECTION_OPTION_EMT2VT.items()}

# 持仓方向映射
POSITION_DIRECTION_EMT2VT = {
    0: Direction.NET,
    1: Direction.LONG,
    2: Direction.SHORT,
    3: Direction.SHORT
}

# 期权委托类型映射
OPTION_ORDERTYPE_EMT2VT: Dict[int, OrderType] = {
    1: OrderType.LIMIT,
    2: OrderType.MARKET,
    8: OrderType.FOK
}
OPTION_ORDERTYPE_VT2EMT: Dict[OrderType, int] = {v: k for k, v in OPTION_ORDERTYPE_EMT2VT.items()}

# 股票委托类型映射
EQUITY_ORDERTYPE_EMT2VT: Dict[int, OrderType] = {
    1: OrderType.LIMIT,
    4: OrderType.MARKET
}
EQUITY_ORDERTYPE_VT2EMT: Dict[OrderType, int] = {v: k for k, v in EQUITY_ORDERTYPE_EMT2VT.items()}

# 科创板委托类型映射
STAR_ORDERTYPE_EMT2VT: Dict[int, OrderType] = {
    1: OrderType.LIMIT,
    7: OrderType.MARKET
}
STAR_ORDERTYPE_VT2EMT: Dict[OrderType, int] = {v: k for k, v in STAR_ORDERTYPE_EMT2VT.items()}

# 通讯协议映射
PROTOCOL_VT2EMT: Dict[str, int] = {
    "TCP": 1,
    "UDP": 2
}

# 委托状态映射
STATUS_EMT2VT: Dict[int, Status] = {
    0: Status.SUBMITTING,
    1: Status.ALLTRADED,
    2: Status.PARTTRADED,
    3: Status.CANCELLED,
    4: Status.NOTTRADED,
    5: Status.CANCELLED,
    6: Status.REJECTED,
    7: Status.SUBMITTING
}

# 产品类型映射
PRODUCT_EMT2VT: Dict[int, Product] = {
    0: Product.EQUITY,
    1: Product.INDEX,
    2: Product.FUND,
    3: Product.BOND,
    4: Product.OPTION,
    5: Product.EQUITY,
    6: Product.FUND
}

# 开平方向映射
OFFSET_VT2EMT: Dict[Offset, int] = {
    Offset.NONE: 0,
    Offset.OPEN: 1,
    Offset.CLOSE: 2,
    Offset.CLOSETODAY: 4,
    Offset.CLOSEYESTERDAY: 5
}
OFFSET_EMT2VT: Dict[int, Offset] = {v: k for k, v in OFFSET_VT2EMT.items()}

# 业务类型映射
BUSINESS_VT2EMT: Dict[Any, int] = {
    "CASH": 0,
    Offset.NONE: 0,
    "MARGIN": 4,
    Offset.OPEN: 4,
    Offset.CLOSE: 4,
    "OPTION": 10,
}

# 期权类型映射
OPTIONTYPE_EMT2VT = {
    1: OptionType.CALL,
    2: OptionType.PUT
}

# 日志级别映射
LOGLEVEL_VT2EMT = {
    "FATAL": 0,
    "ERROR": 1,
    "WARNING": 2,
    "INFO": 3,
    "DEBUG": 4,
    "TRACE": 5,
}

# 其他常量
CHINA_TZ = ZoneInfo("Asia/Shanghai")       # 中国时区

# 合约数据全局缓存字典
symbol_contract_map: Dict[str, ContractData] = {}


class EmtGateway(BaseGateway):
    """
    VeighNa用于对接东方财富证券EMT柜台的交易接口。
    """

    default_name: str = "EMT"

    default_setting: Dict[str, Any] = {
        "账号": "",
        "密码": "",
        "客户号": 1,
        "行情地址": "",
        "行情端口": 0,
        "交易地址": "",
        "交易端口": 0,
        "行情协议": ["TCP", "UDP"],
        "日志级别": ["FATAL", "ERROR", "WARNING", "INFO", "DEBUG", "TRACE"],
    }

    exchanges: List[Exchange] = list(EXCHANGE_VT2EMT.keys())

    def __init__(self, event_engine: EventEngine, gateway_name: str):
        """构造函数"""
        super().__init__(event_engine, gateway_name)

        self.md_api: "EmtMdApi" = EmtMdApi(self)
        self.td_api: "EmtTdApi" = EmtTdApi(self)

    def connect(self, setting: dict) -> None:
        """连接交易接口"""
        userid: str = setting["账号"]
        password: str = setting["密码"]
        client_id: int = int(setting["客户号"])
        quote_ip: str = setting["行情地址"]
        quote_port: int = int(setting["行情端口"])
        trader_ip: str = setting["交易地址"]
        trader_port: int = int(setting["交易端口"])
        quote_protocol: str = setting["行情协议"]
        log_level: int = LOGLEVEL_VT2EMT[setting["日志级别"]]

        self.md_api.connect(
            userid, password, client_id, quote_ip,
            quote_port, quote_protocol, log_level
        )

        self.td_api.connect(
            userid, password, client_id, trader_ip,
            trader_port, log_level
        )
        self.init_query()

    def close(self) -> None:
        """关闭接口"""
        pass

    def subscribe(self, req: SubscribeRequest) -> None:
        """订阅行情"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """委托下单"""
        return self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """委托撤单"""
        self.td_api.cancel_order(req)

    def query_account(self) -> None:
        """查询资金"""
        self.td_api.query_account()

    def query_position(self) -> None:
        """查询持仓"""
        self.td_api.query_position()

    def process_timer_event(self, event) -> None:
        """定时事件处理"""
        self.count += 1
        if self.count < 2:
            return
        self.count = 0

        func = self.query_functions.pop(0)
        func()
        self.query_functions.append(func)

    def init_query(self) -> None:
        """初始化查询任务"""
        self.count: int = 0
        self.query_functions: list = [self.query_account, self.query_position]
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def write_error(self, msg: str, error: dict) -> None:
        """输出错误信息"""
        error_id: int = error["error_id"]
        error_msg: str = error["error_msg"]
        msg: str = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)


class EmtMdApi(MdApi):

    def __init__(self, gateway: EmtGateway):
        """构造函数"""
        super().__init__()

        self.gateway: EmtGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.userid: str = ""
        self.password: str = ""
        self.client_id: int = 0
        self.server_ip: str = ""
        self.server_port: int = 0
        self.protocol: int = 0
        self.session_id: int = 0

        self.connect_status: bool = False
        self.login_status: bool = False

        self.sse_inited: bool = False
        self.szse_inited: bool = False

    def onDisconnected(self, reason: int) -> None:
        """服务器连接断开回报"""
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"行情服务器连接断开, 原因{reason}")

        self.login_server()

    def onError(self, error: dict) -> None:
        """请求报错回报"""
        self.gateway.write_error("行情接口报错", error)

    def onSubMarketData(self, data: dict, error: dict, last: bool) -> None:
        """订阅行情回报"""
        if not error or not error["error_id"]:
            return

        self.gateway.write_error("行情订阅失败", error)

    def onDepthMarketData(self, data: dict) -> None:
        """行情推送回报"""
        timestamp: str = str(data["data_time"])
        dt: datetime = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")
        dt: datetime = dt.replace(tzinfo=CHINA_TZ)

        tick: TickData = TickData(
            symbol=data["ticker"],
            exchange=EXCHANGE_EMT2VT[data["exchange_id"]],
            datetime=dt,
            volume=data["qty"],
            turnover=data["turnover"],
            last_price=data["last_price"],
            limit_up=data["upper_limit_price"],
            limit_down=data["lower_limit_price"],
            open_price=data["open_price"],
            high_price=data["high_price"],
            low_price=data["low_price"],
            pre_close=data["pre_close_price"],
            gateway_name=self.gateway_name
        )

        tick.bid_price_1, tick.bid_price_2, tick.bid_price_3, tick.bid_price_4, tick.bid_price_5 = data["bid"][0:5]
        tick.ask_price_1, tick.ask_price_2, tick.ask_price_3, tick.ask_price_4, tick.ask_price_5 = data["ask"][0:5]
        tick.bid_volume_1, tick.bid_volume_2, tick.bid_volume_3, tick.bid_volume_4, tick.bid_volume_5 = data["bid_qty"][0:5]
        tick.ask_volume_1, tick.ask_volume_2, tick.ask_volume_3, tick.ask_volume_4, tick.ask_volume_5 = data["ask_qty"][0:5]

        # 基于合约的最小价格跳动，对浮点数价格进行四舍五入
        contract: ContractData = symbol_contract_map.get(tick.vt_symbol, None)
        if contract:
            pricetick: float = contract.pricetick
            tick.last_price = round_to(data["last_price"], pricetick)
            tick.limit_up = round_to(data["upper_limit_price"], pricetick)
            tick.limit_down = round_to(data["lower_limit_price"], pricetick)
            tick.open_price = round_to(data["open_price"], pricetick)
            tick.high_price = round_to(data["high_price"], pricetick)
            tick.low_price = round_to(data["low_price"], pricetick)
            tick.pre_close = round_to(data["pre_close_price"], pricetick)

            tick.bid_price_1 = round_to(tick.bid_price_1, pricetick)
            tick.bid_price_2 = round_to(tick.bid_price_2, pricetick)
            tick.bid_price_3 = round_to(tick.bid_price_3, pricetick)
            tick.bid_price_4 = round_to(tick.bid_price_4, pricetick)
            tick.bid_price_5 = round_to(tick.bid_price_5, pricetick)
            tick.ask_price_1 = round_to(tick.ask_price_1, pricetick)
            tick.ask_price_2 = round_to(tick.ask_price_2, pricetick)
            tick.ask_price_3 = round_to(tick.ask_price_3, pricetick)
            tick.ask_price_4 = round_to(tick.ask_price_4, pricetick)
            tick.ask_price_5 = round_to(tick.ask_price_5, pricetick)

            tick.name = contract.name

        self.gateway.on_tick(tick)

    def onQueryAllTickers(self, data: dict, error: dict, last: bool) -> None:
        """查询合约回报"""
        contract: ContractData = ContractData(
            symbol=data["ticker"],
            exchange=EXCHANGE_EMT2VT[data["exchange_id"]],
            name=data["ticker_name"],
            product=PRODUCT_EMT2VT[data["ticker_type"]],
            size=1,
            pricetick=data["price_tick"],
            min_volume=data["buy_qty_unit"],
            gateway_name=self.gateway_name
        )

        if contract.product != Product.OPTION:
            self.gateway.on_contract(contract)

        symbol_contract_map[contract.vt_symbol] = contract

        if last:
            self.gateway.write_log(f"{contract.exchange.value}合约信息查询成功")

            if contract.exchange == Exchange.SSE:
                self.sse_inited = True
            else:
                self.szse_inited = True

    def connect(
        self,
        userid: str,
        password: str,
        client_id: int,
        server_ip: str,
        server_port: int,
        quote_protocol: int,
        log_level: int
    ) -> None:
        """连接服务器"""
        self.userid = userid
        self.password = password
        self.client_id = client_id
        self.server_ip = server_ip
        self.server_port = server_port
        self.protocol = PROTOCOL_VT2EMT[quote_protocol]

        if not self.connect_status:
            path: str = str(get_folder_path(self.gateway_name.lower())).encode("GBK")
            self.createQuoteApi(self.client_id, path, 1, log_level)
            self.login_server()
        else:
            self.gateway.write_log("行情接口已登录，请勿重复操作")

    def login_server(self) -> None:
        """用户登录"""
        n: int = self.login(
            self.server_ip,
            self.server_port,
            self.userid,
            self.password,
            self.protocol,
            ""
        )

        if not n:
            self.connect_status = True
            self.login_status = True

            self.query_contract()
            self.init()

            msg: str = "行情服务器登录成功"
        else:
            error: dict = self.getApiLastError()
            msg: str = f"行情服务器登录失败，原因：{error['error_msg']}"

        self.gateway.write_log(msg)

    def close(self) -> None:
        """关闭连接"""
        if self.connect_status:
            self.exit()

    def subscribe(self, req: SubscribeRequest) -> None:
        """订阅行情"""
        if self.login_status:
            emt_exchange: int = EXCHANGE_VT2EMT.get(req.exchange, "")
            self.subscribeMarketData(req.symbol, 1, emt_exchange)

    def query_contract(self) -> None:
        """查询合约信息"""
        for exchange_id in EXCHANGE_EMT2VT.keys():
            self.queryAllTickers(exchange_id)


class EmtTdApi(TdApi):

    def __init__(self, gateway: EmtGateway):
        """"""
        super().__init__()

        self.gateway: EmtGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.userid: str = ""
        self.password: str = ""
        self.client_id: str = ""
        self.server_ip: str = ""
        self.server_port: str = ""

        self.session_id: int = 0
        self.reqid: int = 0
        self.protocol: int = 0

        # 账户是否支持两融或者期权交易
        self.margin_trading = False
        self.option_trading = False

        self.connect_status: bool = False
        self.login_status: bool = False

        self.short_positions: Dict[str, PositionData] = {}
        self.orders: Dict[str, OrderData] = {}

    def onDisconnected(self, session: int, reason: int) -> None:
        """服务器连接断开回报"""
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开, 原因{reason}")

        self.login_server()

    def onError(self, error: dict) -> None:
        """请求报错回报"""
        self.gateway.write_error("交易接口报错", error)

    def onOrderEvent(self, data: dict, error: dict, session: int) -> None:
        """委托状态更新"""
        if error["error_id"]:
            self.gateway.write_error("交易委托失败", error)

        symbol: str = data["ticker"]
        if len(symbol) == 8:
            direction: Direction = DIRECTION_OPTION_EMT2VT[data["side"]]
            offset: Offset = OFFSET_EMT2VT[data["position_effect"]]
            order_type: OrderType = OPTION_ORDERTYPE_EMT2VT.get(data["price_type"], OrderType.MARKET)
        else:
            direction, offset = DIRECTION_STOCK_EMT2VT[data["side"]]

            if symbol.startswith("688"):
                type_map: dict = STAR_ORDERTYPE_EMT2VT
            else:
                type_map: dict = EQUITY_ORDERTYPE_EMT2VT
            order_type: OrderType = type_map.get(data["price_type"], OrderType.MARKET)

        orderid: str = str(data["order_emt_id"])
        if orderid not in self.orders:
            order: OrderData = OrderData(
                symbol=symbol,
                exchange=MARKET_EMT2VT[data["market"]],
                orderid=orderid,
                type=order_type,
                direction=direction,
                offset=offset,
                price=data["price"],
                volume=data["quantity"],
                traded=data["qty_traded"],
                status=STATUS_EMT2VT[data["order_status"]],
                gateway_name=self.gateway_name
            )
            self.orders[orderid] = order
        else:
            order: OrderData = self.orders[orderid]
            order.traded = data["qty_traded"]
            order.status = STATUS_EMT2VT[data["order_status"]]

        if not order.datetime:
            timestamp: str = str(data["insert_time"])
            dt: datetime = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")
            dt: datetime = dt.replace(tzinfo=CHINA_TZ)
            order.datetime = dt

        self.gateway.on_order(copy(order))

    def onTradeEvent(self, data: dict, session: int) -> None:
        """成交推送"""
        symbol: str = data["ticker"]
        if len(symbol) == 8:
            direction: Direction = DIRECTION_OPTION_EMT2VT[data["side"]]
            offset: Offset = OFFSET_EMT2VT[data["position_effect"]]
        else:
            direction, offset = DIRECTION_STOCK_EMT2VT[data["side"]]

        timestamp: str = str(data["trade_time"])
        dt: datetime = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")
        dt: datetime = dt.replace(tzinfo=CHINA_TZ)

        trade: TradeData = TradeData(
            symbol=symbol,
            exchange=MARKET_EMT2VT[data["market"]],
            orderid=str(data["order_emt_id"]),
            tradeid=str(data["exec_id"]),
            direction=direction,
            offset=offset,
            price=data["price"],
            volume=data["quantity"],
            datetime=dt,
            gateway_name=self.gateway_name
        )

        if trade.orderid in self.orders:
            order: OrderData = self.orders[trade.orderid]
            order.traded += trade.volume

            if order.traded < order.volume:
                order.status = Status.PARTTRADED
            else:
                order.status = Status.ALLTRADED
            self.gateway.on_order(copy(order))
        else:
            self.gateway.write_log(f"成交找不到对应委托{trade.orderid}")

        self.gateway.on_trade(trade)

    def onCancelOrderError(self, data: dict, error: dict, session: int) -> None:
        """撤单报错"""
        if not error or not error["error_id"]:
            return

        self.gateway.write_error("撤单失败", error)

    def onQueryPosition(
        self,
        data: dict,
        error: dict,
        request: int,
        last: bool,
        session: int
    ) -> None:
        """查询持仓回报"""
        if not data:
            return

        if data["market"] == 100:
            return

        position: PositionData = PositionData(
            symbol=data["ticker"],
            exchange=MARKET_EMT2VT[data["market"]],
            direction=POSITION_DIRECTION_EMT2VT[data["position_direction"]],
            volume=data["total_qty"],
            frozen=data["total_qty"] - data["sellable_qty"],
            price=data["avg_price"],
            pnl=data["unrealized_pnl"],
            yd_volume=data["sellable_qty"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(position)

    def onQueryAsset(
        self,
        data: dict,
        error: dict,
        request: int,
        last: bool,
        session: int
    ) -> None:
        """查询资金回报"""
        account: AccountData = AccountData(
            accountid=self.userid,
            balance=round(data["buying_power"], 2),
            frozen=round(data["withholding_amount"], 2),
            gateway_name=self.gateway_name
        )
        account.available = round(data["buying_power"], 2)

        # 两融账户
        if data["account_type"] == 1:
            self.margin_trading = True
        # 期权账户
        elif data["account_type"] == 2:
            account.frozen = account.balance - account.available - data["security_asset"]
            account.frozen = round(account.frozen, 2)
            self.option_trading = True

        self.gateway.on_account(account)

    def onQueryOptionAuctionInfo(self, data: dict, error: dict, reqid: int, last: bool, session: int) -> None:
        """查询期权合约细节回报"""
        if not data or not data["ticker"]:
            return

        contract: ContractData = ContractData(
            symbol=data["ticker"],
            exchange=MARKET_EMT2VT[data["security_id_source"]],
            name=data["symbol"],
            product=Product.OPTION,
            size=data["contract_unit"],
            min_volume=data["qty_unit"],
            pricetick=data["price_tick"],
            gateway_name=self.gateway_name
        )

        contract.option_portfolio = data["underlying_security_id"] + "_O"
        contract.option_underlying = (
            data["underlying_security_id"]
            + "-"
            + str(data["delivery_month"])
        )
        contract.option_type = OPTIONTYPE_EMT2VT.get(data["call_or_put"], None)

        contract.option_strike = data["exercise_price"]
        contract.option_expiry = datetime.strptime(
            str(data["last_trade_date"]), "%Y%m%d"
        )
        contract.option_index = get_option_index(
            contract.option_strike, data["contract_id"]
        )

        self.gateway.on_contract(contract)
        symbol_contract_map[contract.vt_symbol] = contract

        if last:
            self.gateway.write_log("期权信息查询成功")

    def onQueryCreditDebtInfo(
        self,
        data: dict,
        error: dict,
        request: int,
        last: bool,
        session: int
    ) -> None:
        """查询两融持仓回报"""
        if data["debt_type"] == 1:
            symbol: str = data["ticker"]
            exchange: Exchange = MARKET_EMT2VT[data["market"]]

            position: PositionData = self.short_positions.get(symbol, None)
            if not position:
                position = PositionData(
                    symbol=symbol,
                    exchange=exchange,
                    direction=Direction.SHORT,
                    gateway_name=self.gateway_name
                )
                self.short_positions[symbol] = position

            position.volume += data["remain_qty"]

        if last:
            for position in self.short_positions.values():
                self.gateway.on_position(position)

            self.short_positions.clear()

    def connect(
        self,
        userid: str,
        password: str,
        client_id: int,
        server_ip: str,
        server_port: int,
        log_level: int
    ) -> None:
        """连接服务器"""

        self.userid = userid
        self.password = password
        self.client_id = client_id
        self.server_ip = server_ip
        self.server_port = server_port
        self.protocol = PROTOCOL_VT2EMT["TCP"]

        if not self.connect_status:
            path: str = str(get_folder_path(self.gateway_name.lower())).encode("GBK")
            self.createTraderApi(self.client_id, path, log_level)

            self.subscribePublicTopic(0)
            self.login_server()
        else:
            self.gateway.write_log("交易接口已登录，请勿重复操作")

    def login_server(self) -> None:
        """登录"""
        n: int = self.login(
            self.server_ip,
            self.server_port,
            self.userid,
            self.password,
            self.protocol
        )

        if n:
            self.session_id = n
            self.connect_status = True
            self.login_status = True
            msg: str = f"交易服务器登录成功, 会话编号：{self.session_id}"
            self.init()
        else:
            error: dict = self.getApiLastError()
            msg: str = f"交易服务器登录失败，原因：{error['error_msg']}"

        self.gateway.write_log(msg)
        self.query_option_info()

    def close(self) -> None:
        """关闭连接"""
        if self.connect_status:
            self.exit()

    def query_option_info(self) -> None:
        """查询期权信息"""
        self.reqid += 1
        self.queryOptionAuctionInfo({}, self.session_id, self.reqid)

    def send_order(self, req: OrderRequest) -> str:
        """委托下单"""
        if req.exchange not in MARKET_VT2EMT:
            self.gateway.write_log(f"委托失败，不支持的交易所{req.exchange.value}")
            return ""

        if self.margin_trading and req.offset == Offset.NONE:
            self.gateway.write_log("委托失败，两融交易需要选择开平方向")
            return ""

        # 期权委托
        if len(req.symbol) == 8:
            if req.type not in OPTION_ORDERTYPE_VT2EMT:
                self.gateway.write_log(f"委托失败，不支持的期权委托类型{req.type.value}")
                return ""

            emt_req: dict = {
                "ticker": req.symbol,
                "market": MARKET_VT2EMT[req.exchange],
                "price": req.price,
                "quantity": int(req.volume),
                "side": DIRECTION_OPTION_VT2EMT.get(req.direction, ""),
                "position_effect": OFFSET_VT2EMT[req.offset],
                "price_type": OPTION_ORDERTYPE_VT2EMT[req.type],
                "business_type": 10
            }
        # 股票委托
        else:
            # 科创版
            if req.symbol.startswith("688"):
                type_map: dict = STAR_ORDERTYPE_VT2EMT
            # 其他
            else:
                type_map: dict = EQUITY_ORDERTYPE_VT2EMT

            if req.type not in type_map:
                self.gateway.write_log(f"委托失败，不支持的股票委托类型{req.type.value}")
                return ""

            emt_req: dict = {
                "ticker": req.symbol,
                "market": MARKET_VT2EMT[req.exchange],
                "price": req.price,
                "quantity": int(req.volume),
                "price_type": type_map[req.type],
            }

            if self.margin_trading:
                emt_req["side"] = DIRECTION_STOCK_VT2EMT.get((req.direction, req.offset), "")
                emt_req["business_type"] = 4
            else:
                emt_req["side"] = DIRECTION_STOCK_VT2EMT.get((req.direction, Offset.NONE), "")
                emt_req["business_type"] = 0

        orderid: int = self.insertOrder(emt_req, self.session_id)
        orderid: str = str(orderid)

        order: OrderData = req.create_order_data(orderid, self.gateway_name)
        self.orders[orderid] = order
        self.gateway.on_order(copy(order))

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """委托撤单"""
        self.cancelOrder(int(req.orderid), self.session_id)

    def query_account(self) -> None:
        """查询资金"""
        if not self.connect_status:
            return

        self.reqid += 1
        self.queryAsset(self.session_id, self.reqid)

    def query_position(self) -> None:
        """查询持仓"""
        if not self.connect_status:
            return

        self.reqid += 1
        self.queryPosition("", self.session_id, self.reqid, 0)

        if self.margin_trading:
            self.reqid += 1
            self.queryCreditDebtInfo(self.session_id, self.reqid)


def get_option_index(strike_price: float, exchange_instrument_id: str) -> str:
    """获取期权索引"""
    exchange_instrument_id: str = exchange_instrument_id.replace(" ", "")

    if "M" in exchange_instrument_id:
        n: int = exchange_instrument_id.index("M")
    elif "A" in exchange_instrument_id:
        n: int = exchange_instrument_id.index("A")
    elif "B" in exchange_instrument_id:
        n: int = exchange_instrument_id.index("B")
    else:
        return str(strike_price)

    index: str = exchange_instrument_id[n:]
    option_index: str = f"{strike_price:.3f}-{index}"

    return option_index
