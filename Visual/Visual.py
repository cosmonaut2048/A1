import pandas as pd
import matplotlib.pyplot as plt

plt.style.use('seaborn-v0_8-darkgrid')
plt.rcParams.update({'font.size': 11, 'axes.titlesize': 12, 'axes.labelsize': 11})

ALGORITHMS = {
    'StandardQuickSort': {'color': '#1f77b4', 'marker': 'o'},
    'StandardMergeSort': {'color': '#ff7f0e', 'marker': 's'},
    'TernaryQuickSort': {'color': '#2ca02c', 'marker': '^'},
    'StringMergeSort': {'color': '#d62728', 'marker': 'D'},
    'MSDRadixSort': {'color': '#9467bd', 'marker': 'v'},
    'MSDRadixSortWithCutoff': {'color': '#8c564b', 'marker': 'p'}
}

DATA_TYPES = ['Random', 'ReverseSorted', 'AlmostSorted', 'CommonPrefix', 'VeryLongCommonPrefix']
LOG_SCALE_TYPES = ['CommonPrefix', 'VeryLongCommonPrefix']


def plot_metric(df, metric_name, ylabel, title, filename):
    fig, axes = plt.subplots(5, 1, figsize=(14, 24), sharex=False)

    for idx, data_type in enumerate(DATA_TYPES):
        ax = axes[idx]
        data = df[df['DataType'] == data_type]

        for algo_name, config in ALGORITHMS.items():
            algo_data = data[data['Algorithm'] == algo_name]
            if not algo_data.empty:
                ax.plot(algo_data['Size'], algo_data[metric_name],
                        marker=config['marker'], linewidth=2, markersize=6,
                        label=algo_name, color=config['color'])

        ax.set_ylabel(ylabel, fontweight='bold')
        ax.set_title(data_type, fontsize=13, fontweight='bold', loc='left')
        ax.legend(loc='best', fontsize=8, ncol=2)
        ax.grid(True, alpha=0.3)

        if data_type in LOG_SCALE_TYPES:
            ax.set_yscale('log')
            ax.set_ylabel(f'{ylabel} (лог. шкала)', fontweight='bold')

    axes[-1].set_xlabel('Размер массива (N)', fontsize=12, fontweight='bold')
    for ax in axes[:-1]:
        ax.set_xlabel('')

    plt.suptitle(title, fontsize=16, fontweight='bold', y=0.995)
    plt.tight_layout()
    plt.savefig(filename, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"{filename} created.")

df = pd.read_csv('sorting_results.csv')

# Построение графиков
plot_metric(df, 'Comparisons', 'Количество сравнений',
            'Анализ количества посимвольных сравнений',
            'all_comparisons.png')

plot_metric(df, 'TimeMicroseconds', 'Время (микросекунды)',
            'Анализ времени выполнения',
            'all_time.png')
