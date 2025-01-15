#include <iostream>
#include <cmath>
#include <random>
#include <vector>

// Function to generate Gaussian (normal) noise with a given mean and standard deviation
double generateGaussianNoise(double mean, double stddev) {
    static std::mt19937 generator(std::random_device{}()); // Random number generator
    std::normal_distribution<double> distribution(mean, stddev); // Normal distribution
    return distribution(generator); // Generate and return a random number from the distribution
}

// Function to calculate the payoff of a call option
// Payoff for a call option is max(S - K, 0), where S is the stock price and K is the strike price
double callOptionPayoff(double S, double K) {
    return std::max(S - K, 0.0);
}

// Function to calculate the payoff of a put option
// Payoff for a put option is max(K - S, 0)
double putOptionPayoff(double S, double K) {
    return std::max(K - S, 0.0);
}

// Function to calculate the price of an option (call or put) using the Monte Carlo method
double monteCarloOptionPricing(double S0, double K, double r, double sigma, double T, int numSimulations, bool isCallOption) {
    double payOffSum = 0.0; // Sum of all simulated payoffs

    // Simulate `numSimulations` paths of the stock price
    for (int i = 0; i < numSimulations; i++) {
        // Simulate the stock price at maturity using Geometric Brownian Motion formula
        double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * generateGaussianNoise(0.0, 1.0));

        // Calculate the payoff based on whether it's a call or put option
        double payOff = isCallOption ? callOptionPayoff(ST, K) : putOptionPayoff(ST, K);

        // Accumulate the payoff
        payOffSum += payOff;
    }

    // Calculate the average payoff
    double averagePayoff = payOffSum / static_cast<double>(numSimulations);

    // Discount the average payoff to present value using the risk-free rate
    return std::exp(-r * T) * averagePayoff;
}

int main() {
    // Parameters for the option
    double S0 = 100.0;     // Initial stock price
    double K = 100.0;      // Strike price
    double r = 0.05;       // Risk-free interest rate
    double sigma = 0.2;    // Volatility of the stock
    double T = 1;          // Time to maturity in years
    int numSimulations = 100000; // Number of Monte Carlo simulations

    // Calculate the price of a European call option
    double callPrice = monteCarloOptionPricing(S0, K, r, sigma, T, numSimulations, true);

    // Calculate the price of a European put option
    double putPrice = monteCarloOptionPricing(S0, K, r, sigma, T, numSimulations, false);

    // Output the calculated prices
    std::cout << "European Call Option Price: " << callPrice << std::endl;
    std::cout << "European Put Option Price: " << putPrice << std::endl;

    return 0;
}
