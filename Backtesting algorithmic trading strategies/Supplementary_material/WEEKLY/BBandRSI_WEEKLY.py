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

def bbindicator(data):
  bbands = ta.bbands(close=data.Close.s, std=2, length=20)
  bbands.fillna(0)
  return bbands.to_numpy().T[:3]
    
def RSI(data):
    rsi = ta.rsi(close=data.Close.s, length=14)
    rsi.fillna(0)
    return rsi
 

#Creating the strategy

class BBands_RSI(Strategy):
    
    def init(self):
        self.bbands = self.I(bbindicator, self.data)
        self.rsi = self.I(RSI, self.data)

            
    def next(self):
        price = self.data.Close[-1]
        UpperBand = self.bbands[0]
        LowerBand = self.bbands[2]
        
        
        if (price > UpperBand[-1] and self.rsi[-1] > 70):
            self.buy(size=1, sl=price-30, tp = price+90)
        elif (price < LowerBand[-1] and self.rsi[-1] < 30):
            self.sell()
            

#Running and plotting the backtest
              
bt = Backtest(historical_data, BBands_RSI, cash=100000, commission=0.01,hedging=True, exclusive_orders=True)
btData = bt.run()
print(btData)
print(btData['_equity_curve'])
print(btData['_trades'])
bt.plot()



