import matplotlib.pyplot as plt
import pandas as pd
import sys

def visualize_pareto_front(data_file):
    try:
        # Read the data from the CSV file
        data = pd.read_csv(data_file)
        if data.empty:
            print("Data file is empty. Nothing to plot.")
            return

        # Plotting
        plt.figure(figsize=(10, 6))
        plt.plot(data['Total_Distance'], data['Total_Flow_Capacity'], marker='o', linestyle='-', color='b')
        
        # Annotate each point with its corresponding alpha value
        for i, row in data.iterrows():
            plt.text(row['Total_Distance'], row['Total_Flow_Capacity'], f"  α={row['Alpha']:.1f}", fontsize=9)

        plt.title('Pareto-Optimal Front')
        plt.xlabel('Total Distance (Cabling Cost)')
        plt.ylabel('Total Flow Capacity')
        plt.grid(True)
        
        # Highlight the balanced solution (alpha=0.5)
        balanced_solution = data[data['Alpha'] == 0.5]
        if not balanced_solution.empty:
            plt.plot(balanced_solution['Total_Distance'], balanced_solution['Total_Flow_Capacity'], marker='*', markersize=15, color='r', label='Balanced Solution (alpha=0.5)')
            plt.legend()

        print("Displaying Pareto front visualization. Close the plot window to exit.")
        plt.show()

    except FileNotFoundError:
        print(f"Error: Could not find the data file '{data_file}'.")
    except Exception as e:
        print(f"An error occurred during visualization: {e}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        visualize_pareto_front(sys.argv[1])
    else:
        # Default file if none provided
        visualize_pareto_front('pareto_data.csv')
