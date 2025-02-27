# AlgoTradeSim-C++

This project is a stock trading strategy simulator written in C++. It provides a framework to simulate and evaluate various trading strategies using historical price data. The simulator is designed to help users understand the potential outcomes of different trading strategies and make informed decisions.

## Key Features

1. **Average Price Calculation**: The simulator calculates the average price of a stock over a given period using historical price data.

2. **Trading Signal Generation**: The simulator generates trading signals (Buy, Hold, Sell) based on the comparison of the current price with the calculated average price.

3. **Signal Strength Calculation**: The simulator calculates the strength of the trading signal, providing a measure of confidence in the signal.

4. **Trading Strategy Execution**: The simulator executes various trading strategies using the generated signals and evaluates their performance.

5. **Multi-buy Strategy**: The simulator also includes a multi-buy strategy that allows for the purchase of multiple stocks at once, based on the strength of the buy signal.

6. **Advanced Multi-buy Strategy**: An advanced version of the multi-buy strategy is also included, which adjusts the buy and sell orders based on the strength of the buy signal.

7. **Performance Reporting**: The simulator provides detailed performance reports, including the final net worth and strategy success rate.

## Usage

To use the simulator, simply clone the repository and compile the C++ file. The simulator uses historical price data for Amazon (AMZN) as an example, but you can replace this with any other stock's historical data.

```bash
g++ main.cpp -o simulator
./simulator
