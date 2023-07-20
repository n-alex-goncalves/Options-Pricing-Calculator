#include <iostream>
#include <cmath>
#include <vector>

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
    double calculateBinomial(int height = 100, double dividendYield = 0) {
       double deltaTime = timeToExpire / height;
       double up = exp(volatility * sqrt(deltaTime));
       double riskNeutralProbUp = (up * exp(-dividendYield * deltaTime) - exp(-riskFreeRate * deltaTime)) / (pow(up, 2) - 1);
       double riskNeutralProbDown = exp(-riskFreeRate * deltaTime) - riskNeutralProbUp;

       vector<double> p(height, 0.0);

       for (int i = 0; i < height; i++) {
            p[i] = strikePrice - stockPrice * pow(up, 2 * i - height);
            if (p[i] < 0) {
                p[i] = 0;
            }
       }

       double exercise {0};
       for (int j = height - 1; j > -1; j--) {
        for (int i = 0; i < j; i++) {
            p[i] = riskNeutralProbUp * p[i + 1] + riskNeutralProbDown * p[i];
            exercise = strikePrice - stockPrice * pow(up, 2 * i - j);
            if (p[i] < exercise) {
                p[i] = exercise;
            }
        }
       }

        return p[0];
    }

    void changeParameters(double spot, double strike, double rate, double vol, double time) {
        stockPrice = spot;
        strikePrice = strike;
        riskFreeRate = rate;
        volatility = vol;
        timeToExpire = time;
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

// Function to display the menu and get user choice
int getMenuChoice() {
    int choice;
    cout << "------- Option Pricing Menu -------" << endl;
    cout << "1. Calculate Option Price" << endl;
    cout << "2. Change Input Parameters" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

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

    bool exitMenu {false};

    while (!exitMenu) {
        int choice = getMenuChoice();
        
        switch (choice) {
            case 1: // Calculate Option Price
            {
                double optionPrice = myOption.calculatePrice();
                cout << "------------\nOption Price: " << optionPrice << "\n------------" << endl;
                break;
            }
            case 2: // Change Input Parameters
            {
                cout << "------------\nEnter the new price for the underlying asset: (£££ per share)" << endl;
                cin >> stockPrice;

                cout << "Enter the new strike price of the option: (£££ per share)" << endl;
                cin >> strikePrice;

                cout << "Enter the new risk-free interest rate: (% p.a.)" << endl;
                cin >> riskFreeRate;

                cout << "Enter the new volatility of the underlying asset: (% p.a.)" << endl;
                cin >> volatility;

                cout << "Enter the new time to expire (% of year)" << endl;
                cin >> timeToExpire;

                myOption.changeParameters(stockPrice, strikePrice, riskFreeRate, volatility, timeToExpire);
                cout << "Input parameters updated successfully.\n------------" << endl;
                break;
            }
            case 3: // Exit
            {
                exitMenu = true;
                cout << "Exiting the Option Pricing Menu. Goodbye!" << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}

