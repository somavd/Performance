#!/usr/bin/env python3
"""
Matrix Multiplication Performance Visualization

This script reads the benchmark results from output_data.csv and creates
comprehensive visualizations showing the performance improvements across
different optimization techniques.
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from pathlib import Path

# Set style for better looking plots
plt.style.use('seaborn-v0_8')
sns.set_palette("husl")

def load_data():
    """Load benchmark data from CSV file"""
    csv_path = Path("results/output_data.csv")
    
    if not csv_path.exists():
        print(f"Error: {csv_path} not found!")
        print("Please run the benchmark first to generate the data.")
        return None
    
    df = pd.read_csv(csv_path)
    return df

def create_performance_plot(df):
    """Create performance comparison plot"""
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))
    
    # Get matrix sizes (excluding the 'Name' column)
    matrix_sizes = [int(col) for col in df.columns[1:]]
    
    # Plot 1: Linear scale
    for _, row in df.iterrows():
        name = row['Name']
        times = row.iloc[1:].values
        ax1.plot(matrix_sizes, times, marker='o', label=name, linewidth=2, markersize=6)
    
    ax1.set_xlabel('Matrix Size (n × n)')
    ax1.set_ylabel('Time (milliseconds)')
    ax1.set_title('Matrix Multiplication Performance\n(Linear Scale)')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    ax1.set_xscale('log', base=2)
    
    # Plot 2: Log scale for better visualization of small differences
    for _, row in df.iterrows():
        name = row['Name']
        times = row.iloc[1:].values
        # Replace zeros with small positive values for log scale
        times_log = np.where(times == 0, 0.1, times)
        ax2.plot(matrix_sizes, times_log, marker='o', label=name, linewidth=2, markersize=6)
    
    ax2.set_xlabel('Matrix Size (n × n)')
    ax2.set_ylabel('Time (milliseconds)')
    ax2.set_title('Matrix Multiplication Performance\n(Log Scale)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    ax2.set_xscale('log', base=2)
    ax2.set_yscale('log')
    
    plt.tight_layout()
    return fig

def create_speedup_plot(df):
    """Create speedup comparison plot"""
    fig, ax = plt.subplots(1, 1, figsize=(12, 8))
    
    # Get matrix sizes
    matrix_sizes = [int(col) for col in df.columns[1:]]
    
    # Calculate speedup relative to Classical
    classical_times = df[df['Name'] == 'Classical'].iloc[0, 1:].values
    
    for _, row in df.iterrows():
        if row['Name'] == 'Classical':
            continue
            
        name = row['Name']
        times = row.iloc[1:].values
        
        # Calculate speedup (avoiding division by zero)
        speedups = []
        for i, (classical, optimized) in enumerate(zip(classical_times, times)):
            if classical == 0:
                speedups.append(1.0)  # No speedup if both are 0
            else:
                speedups.append(classical / optimized if optimized > 0 else float('inf'))
        
        # Filter out infinite values for plotting
        finite_speedups = []
        finite_sizes = []
        for size, speedup in zip(matrix_sizes, speedups):
            if speedup != float('inf') and speedup > 0:
                finite_speedups.append(speedup)
                finite_sizes.append(size)
        
        ax.plot(finite_sizes, finite_speedups, marker='o', label=name, linewidth=2, markersize=6)
    
    ax.set_xlabel('Matrix Size (n × n)')
    ax.set_ylabel('Speedup (× faster)')
    ax.set_title('Performance Speedup Relative to Classical Implementation')
    ax.legend()
    ax.grid(True, alpha=0.3)
    ax.set_xscale('log', base=2)
    ax.set_yscale('log')
    
    plt.tight_layout()
    return fig

def create_summary_table(df):
    """Create a summary table of key metrics"""
    fig, ax = plt.subplots(1, 1, figsize=(14, 8))
    ax.axis('tight')
    ax.axis('off')
    
    # Prepare data for table
    matrix_sizes = [int(col) for col in df.columns[1:]]
    large_sizes = [size for size in matrix_sizes if size >= 256]  # Focus on meaningful sizes
    
    table_data = []
    headers = ['Implementation'] + [f'{size}×{size}' for size in large_sizes]
    
    for _, row in df.iterrows():
        name = row['Name']
        times = []
        for size in large_sizes:
            time_val = row[str(size)]
            if time_val == 0:
                times.append('< 1')
            else:
                times.append(f'{int(time_val)}')
        table_data.append([name] + times)
    
    # Create table
    table = ax.table(cellText=table_data, colLabels=headers, 
                    cellLoc='center', loc='center', 
                    colColours=['#f0f0f0']*len(headers),
                    rowColours=['#f0f0f0']*len(table_data))
    
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.scale(1.2, 1.5)
    
    # Style the table
    for i in range(len(headers)):
        table[(0, i)].set_facecolor('#4CAF50')
        table[(0, i)].set_text_props(weight='bold', color='white')
    
    for i in range(len(table_data)):
        table[(i+1, 0)].set_facecolor('#2196F3')
        table[(i+1, 0)].set_text_props(weight='bold', color='white')
    
    plt.title('Benchmark Results Summary (Time in milliseconds)', 
              fontsize=16, fontweight='bold', pad=20)
    
    return fig

def main():
    """Main function to generate all visualizations"""
    print("Loading benchmark data...")
    df = load_data()
    
    if df is None:
        return
    
    print("Creating visualizations...")
    
    # Create performance plots
    fig1 = create_performance_plot(df)
    fig1.savefig('results/performance_comparison.png', dpi=300, bbox_inches='tight')
    print("✓ Performance plot saved to results/performance_comparison.png")
    
    # Create speedup plot
    fig2 = create_speedup_plot(df)
    fig2.savefig('results/speedup_comparison.png', dpi=300, bbox_inches='tight')
    print("✓ Speedup plot saved to results/speedup_comparison.png")
    
    # Create summary table
    fig3 = create_summary_table(df)
    fig3.savefig('results/results_summary.png', dpi=300, bbox_inches='tight')
    print("✓ Summary table saved to results/results_summary.png")
    
    # Print summary statistics
    print("\n" + "="*60)
    print("BENCHMARK SUMMARY")
    print("="*60)
    
    for _, row in df.iterrows():
        name = row['Name']
        times = row.iloc[1:].values
        
        # Find non-zero times
        non_zero_times = times[times > 0]
        if len(non_zero_times) > 0:
            min_time = np.min(non_zero_times)
            max_time = np.max(non_zero_times)
            print(f"\n{name}:")
            print(f"  Min time: {min_time:.0f}ms")
            print(f"  Max time: {max_time:.0f}ms")
    
    # Calculate speedups for largest matrix
    largest_size = max([int(col) for col in df.columns[1:]])
    classical_time = df[df['Name'] == 'Classical'][str(largest_size)].iloc[0]
    
    print(f"\nSpeedup for {largest_size}×{largest_size} matrices:")
    for _, row in df.iterrows():
        if row['Name'] != 'Classical':
            name = row['Name']
            optimized_time = row[str(largest_size)]
            if optimized_time > 0 and classical_time > 0:
                speedup = classical_time / optimized_time
                print(f"  {name}: {speedup:.1f}× faster")
    
    print("\n" + "="*60)
    print("All visualizations saved to the 'results/' directory!")
    print("="*60)

if __name__ == "__main__":
    main()
