import pandas as pd
import matplotlib.pyplot as plt

def plot_experimental_and_approximation(exp_filename, approx_filename):
    # Load the experimental data
    exp_data = pd.read_csv(exp_filename)
    
    # Load the approximation function data
    approx_data = pd.read_csv(approx_filename)

    # Create the plot
    plt.figure(figsize=(10, 6))  # Optional: Set the size of the figure

    # Scatter plot for the experimental data points
    # Using only x and y; ignoring weight
    plt.scatter(exp_data['x'], exp_data['y'], color='red', label='Experimental Data', alpha=0.6, edgecolors='w')

    # Line plot for the approximation function
    # Sorting may not be necessary if data is already in the correct order
    sorted_approx_data = approx_data.sort_values(by='x')
    plt.plot(sorted_approx_data['x'], sorted_approx_data['y'], color='blue', label='Approximation Function', linewidth=2)

    # Adding plot enhancements
    plt.title('Comparison of Experimental Data and Approximation Function')
    plt.xlabel('X axis')
    plt.ylabel('Y axis')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    # Paths to the CSV files
    experimental_file = '../datasv_02.csv'
    approximation_file = '../aproxfunction.csv'
    
    # Call the function with the file paths
    plot_experimental_and_approximation(experimental_file, approximation_file)
