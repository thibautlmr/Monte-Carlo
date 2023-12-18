import QuantLib as ql
import numpy as np
import matplotlib.pyplot as plt

# Define option parameters
spot_price = 100.0  # Current stock price
strike_price = 100.0  # Strike price (ATM)
interest_rate = 0.05  # Risk-free interest rate
expiry = 1.0  # Time to expiration (in years)
dividend_yield = 0.0  # Dividend yield
option_type = ql.Option.Call
option_style = ql.Option.European

# Create QuantLib objects for the option and the Black-Scholes process
u = ql.SimpleQuote(spot_price)
r = ql.SimpleQuote(interest_rate)
sigma = ql.SimpleQuote(0.0)  # Will be varied for the Vega profile

today = ql.Settings.instance().evaluationDate
ql.Settings.instance().evaluationDate = today + ql.Period(1, ql.Days)

# Create a Black-Scholes process
spot_handle = ql.QuoteHandle(u)
rate_handle = ql.YieldTermStructureHandle(ql.FlatForward(today, ql.QuoteHandle(r), ql.Actual360()))
dividend_yield_handle = ql.YieldTermStructureHandle(ql.FlatForward(today, ql.QuoteHandle(ql.SimpleQuote(dividend_yield)), ql.Actual360()))
volatility_handle = ql.BlackConstantVol(today, ql.QuoteHandle(sigma), ql.Actual360())
process = ql.BlackScholesMertonProcess(spot_handle, dividend_yield_handle, rate_handle, volatility_handle)

# Create the option
exercise = ql.EuropeanExercise(ql.Date(today + ql.Period(int(365 * expiry), ql.Days)))
option = ql.VanillaOption(ql.PlainVanillaPayoff(option_type, strike_price), exercise)

# Set up the calculation
calculation_date = exercise.lastDate()
ql.Settings.instance().evaluationDate = calculation_date

# Create an array of volatility levels to calculate Vega for
volatility_levels = np.linspace(0.1, 1.5, 100)
vega_values = []

# Calculate the Vega for each volatility level
for vol in volatility_levels:
    sigma.setValue(vol)
    vega = option.vega()
    vega_values.append(vega)

# Plot the Vega profile
plt.figure(figsize=(10, 6))
plt.plot(volatility_levels, vega_values)
plt.title('European ATM Call Option Vega vs. Underlying Volatility')
plt.xlabel('Volatility')
plt.ylabel('Vega')
plt.grid(True)
plt.show()
