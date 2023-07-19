# C++ Options Pricing Calculator

This is a simple C++ program that calculates the price of a European call option using the Black-Scholes option pricing model. The Black-Scholes model is a widely used mathematical model for pricing European-style options.

## Table of Contents
- [Installation](#installation)
- [Disclaimer](#technologies-used)
- [License](#acknowledgements)

## Installation

1. First, clone this repository to your local machine using the following command: `git clone <repository_url>`

2. Navigate to the cloned repository directory and compile the C++ program using a C++ compiler (e.g., g++): `g++ option_pricing.cpp -o option_pricing`

3. Execute the compiled binary to run the program: `./option_pricing`

4. Input Parameters: The program will prompt you to enter the following input parameters for the option pricing calculation:
    - Stock Price: Current price of the underlying asset in GBP (£) per share.
    - Strike Price: The price at which the option can be exercised in GBP (£) per share.
    - Risk-Free Interest Rate: The annual risk-free interest rate as a percentage (%).
    - Volatility: The annualized standard deviation of log returns of the underlying asset as a percentage (%).
    - Time to Expiry: The time to expiration as a percentage (%) of a year.

5. After entering the input parameters, the program will calculate the price of the European call option using the Black-Scholes model and display the result as "Option Price."

# Disclaimer

This program is for educational and illustrative purposes only. The Black-Scholes model is a simplified mathematical model and may not accurately reflect real-world option prices. Options trading involves risks, and you should exercise caution and seek professional advice before making any financial decisions.