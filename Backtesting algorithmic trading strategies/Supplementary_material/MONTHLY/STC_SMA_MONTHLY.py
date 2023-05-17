from backtesting import Backtest, Strategy
from alpha_vantage.timeseries import TimeSeries
import pandas as pd
import pandas_ta as ta


#Extracting and storing the financial data from alpha vantage  
class StockData:
    def __init__(self, api_key):
        self.api_key = api_key
        self.ts = TimeSeries(key=self.api_key, output_format='pandas')
    
    def get_historical_data(self, symbol):
        hist, meta_data = self.ts.get_monthly_adjusted(symbol)
        hist = hist.rename(columns={                      
            '1. open': 'Open',
            '2. high': 'High',
            '3. low': 'Low',
            '4. close': 'Close',
            '6. volume': 'Volume'
        })
        return pd.DataFrame(hist)
    

api_key = "MF60E5YSPGXB41GF"
stock_data = StockData(api_key)
symbol = 'NKE'
historical_data = stock_data.get_historical_data(symbol)

#Creating the indicators

def STC(data):
  stc = ta.stc(close=data.Close.s, tclen = 10, fast= 12, slow= 26, factor= 0.5, offset= 0 )
  stc.fillna(0)
  print(stc)
  return stc.to_numpy()

       
def SMA(data):
    sma = ta.sma (close = data.Close.s, length=10)
    sma.fillna(0)
    print(sma)
    return sma.to_numpy()

#Creating the strategy  
   
class STC_SMA(Strategy):
    
    def init(self):
        self.stc = self.I(STC, self.data)
        self.sma = self.I(SMA, self.data)

    
    def next(self):
        price = self.data.Close[-1]
        MACD = self.stc[1]
        STOCH = self.stc[2]
    
        if (MACD > self.stc[-1] and STOCH[-1] > 0.20 and price > self.sma[-1]):
            self.buy(size=1, sl= price - 30, tp = price +10)
        elif (MACD < self.stc[-1] and STOCH[-1] < 0.20 and price < self.sma[-1]):
            self.sell()

#Running and plotting the backtest    
                     
bt = Backtest(historical_data,STC_SMA , cash=100000, commission=0.01,hedging=True, exclusive_orders=True)
btData = bt.run()
print(btData)
print(btData['_equity_curve'])
print(btData['_trades'])
bt.plot()