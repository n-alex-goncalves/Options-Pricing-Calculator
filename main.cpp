#include <iostream>
#include <cmath>

using namespace std;

class Option 
{
    double stockPrice;      // (£££ per share)
    double strikePrice;     // (£££ per share)
    double riskFreeRate;    // (% p.a.)
    double volatility;      // (% p.a.) (Standard deviation of log returns)
    double timeToExpire;    // (% of year)

public:
    Option(double spot, double strike, double rate, double vol, double time) : stockPrice(spot), strikePrice(strike), riskFreeRate(rate), volatility(vol), timeToExpire(time) {}

    // Black Scholes model
    double calculatePrice() {
        double d1 = calculateD1();
        double d2 = calculateD2();

        double callPrice = (stockPrice * normalCDF(d1)) - (strikePrice * exp(-riskFreeRate * timeToExpire) * normalCDF(d2));
        return callPrice;
    }

    // Binomial model
    double calculateBinomial() {
        return 0.0;
    }

private:
    double normalCDF(double value) {
        return 0.5 * erfc(-value * M_SQRT1_2);
    }

    double calculateD1() {
        return ((log(stockPrice / strikePrice)) + ((riskFreeRate + 0.5 * pow(volatility, 2)) * timeToExpire)) / (volatility * sqrt(timeToExpire));
    }

    double calculateD2() {
        return calculateD1() - (volatility * sqrt(timeToExpire));
    }

};

// Main function
int main() {
    double stockPrice, strikePrice, riskFreeRate, volatility, timeToExpire;

    cout << "Enter the price for the underlying asset: (£££ per share)" << endl;
    cin >> stockPrice;

    cout << "Enter the strike price of the option: : (£££ per share)" << endl;
    cin >> strikePrice;

    cout << "Enter the risk-free interest rate: (% p.a.)" << endl;
    cin >> riskFreeRate;

    cout << "Enter the volatility of the underlying asset: (% p.a.)" << endl;
    cin >> volatility;

    cout << "Enter the time to expire (% of year)" << endl;
    cin >> timeToExpire;

    Option myOption(stockPrice, strikePrice, riskFreeRate, volatility, timeToExpire);

    double optionPrice = myOption.calculatePrice();

    cout << "Option Price: " << optionPrice << endl;

    return 0;
}
