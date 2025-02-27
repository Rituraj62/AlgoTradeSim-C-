#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;
double getAvg(vector<double> values){
    double total = 0;
    int size = values.size();
    for(int i = 0; i < size;i++){
        total+=values[i];
    }
    return total/size;
}
double getFairPrice(vector<double> priceHistory){
    // Current Fair Price Model will be a basic Avg
    double fairPrice = getAvg(priceHistory);
    return fairPrice;
}
string getSignal(vector<double> priceHistory, double currentPrice){
    double fairPrice = getFairPrice(priceHistory);
    if(currentPrice < fairPrice){
        return "BUY";
    }else if(currentPrice == fairPrice){
        return "HOLD";
    }else
    {
        return "SELL";
    }
}
double getSignalStrength(vector<double> priceHistory, double currentPrice){
    double fairPrice = getFairPrice(priceHistory);
    return (fairPrice - currentPrice)/ fairPrice;
}
double getBuySignal(vector<double> priceHistory, double currentPrice, double bandMin){
    double fairPrice = getFairPrice(priceHistory);
    if(fairPrice==bandMin){
        fairPrice++;
    }
    double buySignal = ((fairPrice - currentPrice))/(fairPrice - bandMin);
    //E.g. 1.) FP = 110, CP = 100 EBV -> Strong Buy
        // (110 - 100)/(110 - 90)  = (10) / (20)  -> Signal = 0.5  -> New Signal = 0.75
        // 2.) FP = 105, CP = 110 EBV -> Weak Sell
        // (105 - 110)/(105 - 90) (-5/15) = -0.33 -> New Signal = 0.33
    double signal = (1+buySignal)/2;
    return buySignal;
}
double getSellSignalStrength(vector<double> priceHistory, double currentPrice, double bandMax){
    double fairPrice = getFairPrice(priceHistory);
    double sellSignal = ((currentPrice - fairPrice))/(bandMax - fairPrice);
    return sellSignal;
}
void printSignal(double curPrice, vector<double> priceHistory,int stocksOwned, double seedFund, double netWorth, double stratSucccess){
    cout << "Current Price: " << curPrice << "\tFair Price: " << getFairPrice(priceHistory) << "\tSignal: " << getSignal(priceHistory,curPrice) 
    << "\tstocksOwned: "<<stocksOwned << "\tFunds: "<<seedFund <<  "\tNet Worth: "<< netWorth << "\tstrategySuccess: " << stratSucccess<<   endl;
}
void executeStrategies(vector<double> priceHistory, vector<double> priceStream, double seedFund){
    //Setting shortCap to 3;
    int shortCap = 3;
    int stocksOwned = 0;
    double netWorth = seedFund;
    double netWorthNew = 0;
    double strategySuccess = 0.00;
    double strategySuccessCur = 0.00;
    for(int i = 0; i < priceStream.size();i++){
        double curPrice = priceStream[i];
        //printSignal(curPrice,priceHistory);
        string signal = getSignal(priceHistory,curPrice);
        if(signal=="BUY"){
            if(curPrice < seedFund){
                seedFund-=curPrice;
                stocksOwned++;
            }
        }else if(signal=="SELL"){
            if(stocksOwned > 0 || (0-stocksOwned) < shortCap){
                seedFund+=curPrice;
                stocksOwned--;
            }
        }
        netWorthNew = stocksOwned*curPrice + seedFund;
        strategySuccessCur = (netWorthNew - netWorth)*10000/netWorth;
        strategySuccess += strategySuccessCur;
        netWorth = netWorthNew;
        printSignal(curPrice,priceHistory,stocksOwned,seedFund,netWorth, strategySuccessCur);
    }
    strategySuccess/=priceStream.size();
    //strategySuccess*=1000;
    cout << "\n\nFinal Net Worth: " << netWorth <<"\tstrategySuccess: " << strategySuccess << endl;
}
void executeMultibuyStrategy(vector<double> priceHistory, vector<double> priceStream, double seedFund, int volumeLimit){
        //Setting shortCap to 3;
    int shortCap = volumeLimit;
    int stocksOwned = 0;
    double netWorth = seedFund;
    double netWorthNew = 0;
    double strategySuccess = 0.00;
    double strategySuccessCur = 0.00;
    for(int i = 0; i < priceStream.size();i++){
        double curPrice = priceStream[i];
        //printSignal(curPrice,priceHistory);
        string signal = getSignal(priceHistory,curPrice);
        if(signal=="BUY"){
            for(int j = 0; j < volumeLimit; j++){
                if(curPrice < seedFund){
                seedFund-=curPrice;
                stocksOwned++;
                }
            }
        }else if(signal=="SELL"){
            for(int j = 0; j < volumeLimit; j++){
                if(stocksOwned > 0 || (0-stocksOwned) < shortCap){
                    seedFund+=curPrice;
                    stocksOwned--;
                }   
            }
        }
        netWorthNew = stocksOwned*curPrice + seedFund;
        strategySuccessCur = (netWorthNew - netWorth)*10000/netWorth;
        strategySuccess += strategySuccessCur;
        netWorth = netWorthNew;
        printSignal(curPrice,priceHistory,stocksOwned,seedFund,netWorth, strategySuccessCur);
    }
    strategySuccess/=priceStream.size();
    //strategySuccess*=1000;
    cout << "\n\nFinal Net Worth: " << netWorth <<"\tstrategySuccess: " << strategySuccess << endl;
}
void executeAdvancedMultibuyStrategy(vector<double> priceHistory, vector<double> priceStream, double seedFund, int volumeLimit){
        //Setting shortCap to 3;
    int shortCap = volumeLimit;
    int stocksOwned = 0;
    double netWorth = seedFund;
    double netWorthNew = 0;
    double strategySuccess = 0.00;
    double strategySuccessCur = 0.00;
    for(int i = 0; i < priceStream.size();i++){
        double curPrice = priceStream[i];
        //printSignal(curPrice,priceHistory);
        //string signal = getSignal(priceHistory,curPrice);
        double signal = getBuySignal(priceHistory,curPrice,90);
        int buyOrder = signal * volumeLimit;
        int sellOrder = volumeLimit - buyOrder;
        for(int j = 0; j < buyOrder; j++){
            if(curPrice < seedFund){
            seedFund-=curPrice;
            stocksOwned++;
            }
        }
        for(int j = 0; j < sellOrder; j++){
            if(stocksOwned > 0 || (0-stocksOwned) < shortCap){
                seedFund+=curPrice;
                stocksOwned--;
                }   
        }
        netWorthNew = stocksOwned*curPrice + seedFund;
        strategySuccessCur = (netWorthNew - netWorth)*10000/netWorth;
        strategySuccess += strategySuccessCur;
        netWorth = netWorthNew;
        printSignal(curPrice,priceHistory,stocksOwned,seedFund,netWorth, strategySuccessCur);
    }
    strategySuccess/=priceStream.size();
    //strategySuccess*=1000;
    cout << "\n\nFinal Net Worth: " << netWorth <<"\tstrategySuccess: " << strategySuccess << endl;
}
int main(void){
    vector<double> amznTicker = {106,105.5,104,105.7,108,101,103.3,101.1,105.2,104.5};
    vector<double> amznPriceStream = {101,103,108,112,190,99,104.5,105.5,107.7};
    int amznTickerMin = 9000;
    int amznTickerMax = 12000;
    srand(time(0)*969696);
    for(int i = 0; i < 10;i++){
        int randomDiff = rand()% (amznTickerMax-amznTickerMin);
        int genPriceInt = amznTickerMin + randomDiff;
        double genPrice = genPriceInt/100.0;
        amznTicker.push_back(genPrice);
    }
    srand(time(0)*4612974);
   for(int i = 0; i < 10;i++){
        int randomDiff = rand()% (amznTickerMax-amznTickerMin);
        int genPriceInt = amznTickerMin + randomDiff;
        double genPrice = genPriceInt/100.0;
        amznPriceStream.push_back(genPrice);
    }
    //executeStrategies(amznTicker,amznPriceStream,500);
    executeMultibuyStrategy(amznTicker,amznPriceStream,500,1);
    //executeAdvancedMultibuyStrategy(amznTicker,amznPriceStream,500,1000);
    return 0;
}