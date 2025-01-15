# Monte Carlo Option Pricing

This program calculates the price of European call and put options using the Monte Carlo simulation method. It models stock price behavior via Geometric Brownian Motion and estimates option prices by simulating multiple stock price paths at maturity.

## Features
- Simulates stock prices using Gaussian noise.
- Calculates option payoffs (call and put).
- Discounts expected payoffs to obtain option prices.

## Parameters
- `S0`: Initial stock price
- `K`: Strike price
- `r`: Risk-free interest rate
- `sigma`: Stock volatility
- `T`: Time to maturity
- `numSimulations`: Number of simulations

Run the program to get option prices!
