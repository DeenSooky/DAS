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
        hist, meta_data = self.ts.get_weekly_adjusted(symbol)
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

def MACD(data):
  MACD = ta.macd(close=data.Close.s, fast=12, slow=26, signal=9)
  MACD.fillna(0)
  print(MACD)
  return MACD.to_numpy().T[:3]
    
def RVI(data):
    rvi = ta.rvi (close = data.Close.s, length=14)
    rvi.fillna(0)
    print(rvi)
    return rvi.to_numpy()
   
#Creating the strategy   
   
class MACD_RVI(Strategy):
    
    def init(self):
        self.MACD = self.I(MACD, self.data)
        self.rvi = self.I(RVI, self.data)

    
    def next(self):
        price = self.data.Close[-1]
        MACD_Signal = self.MACD[2]
        MACD_MACD = self.MACD[0]
        
        if ( MACD_MACD[-1] > MACD_Signal[-1] and self.rvi[-1] > 50):
            self.buy(size=1, sl= price - 30, tp= price +90)
        elif ( MACD_MACD[-1] < MACD_Signal[-1] and self.rvi[-1] < 50):
            self.sell
       
  
#Running and plotting the backtest  
              
bt = Backtest(historical_data, MACD_RVI, cash=100000, commission=0.01,hedging=True, exclusive_orders=True)
btData = bt.run()
print(btData)
print(btData['_equity_curve'])
print(btData['_trades'])
bt.plot()