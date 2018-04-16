# generl
import numpy as np

# import for data frame
from pandas import read_csv, read_json, Series
import pandas as pd

# drawing
from matplotlib import pyplot as plt
import seaborn

def natural_cycles():
    df = read_csv('anafile_challenge_170522.csv')  # 'df_100.csv')
    df = df.rename(columns={'Country': 'Country', ' Age': 'Age', ' NumBMI': 'NumBMI',
                       ' Pill': 'Pill', ' NCbefore': 'NCbefore',
                       ' FPlength': 'FPlength', ' Weight': 'Weight',
                       ' CycleVar': 'CycleVar', ' TempLogFreq': 'TempLogFreq',
                       ' SexLogFreq': 'SexLogFreq', ' DaysTrying': 'DaysTrying',
                       ' CyclesTrying': 'CyclesTrying',
                       '  ExitStatus': 'ExitStatus',
                       ' AnovCycles ': 'AnovCycles'})
    print(df.columns)
    print("len", len(df))

    df_status = df.groupby('ExitStatus')
    print("Counts", df_status.count())
    print("average Age", df_status['Age'].mean())
    print(df.pivot_table(index='ExitStatus', columns='Pill',
                         aggfunc={'Age': 'mean', 'CyclesTrying': 'mean'}))
    print(df.pivot_table(index='ExitStatus', columns='NCbefore',
                         aggfunc={'Age': 'mean', 'CyclesTrying': 'mean'}))
    print(df.pivot_table(index='ExitStatus',
                         aggfunc={'SexLogFreq': 'mean', 'TempLogFreq': 'mean'}))
    print(df.pivot_table(index='ExitStatus', columns='FPlength',
                         aggfunc={'CyclesTrying': 'mean' }))
    print(df.pivot_table(index='ExitStatus', columns='FPlength',
                         aggfunc={'Weight': 'mean' }))
    print(df.pivot_table(index='ExitStatus', columns='CycleVar',
                         aggfunc={'CyclesTrying': 'mean'}))

    df_preg = df[df['ExitStatus'] == ' Pregnant']
    age_bins = pd.cut(df_preg['Age'], [20, 25, 30, 35, 40, 45])
    #print(age_bins)
    df_preg.head
    print(len(df_preg))
    plt.figure("Cycles trying vs Age -Pill / no pill- Pregnant")
    ax3 = plt.subplot(111)
    df_preg.pivot_table('CyclesTrying', index=age_bins, columns=['Pill']).plot(ax=ax3)
    ax3.set_ylabel("Mean Cycles Trying")
    plt.xticks(np.arange(5), ('20-25', '25-30', '30-35', '35-40', '40-45'))
    plt.figure("Cycles trying vs Age -NCbefore- Pregnant")
    ax4 = plt.subplot(111)
    df_preg.pivot_table('CyclesTrying', index=age_bins, columns=['NCbefore']).plot(ax=ax4)
    ax4.set_ylabel("Mean Cycles Trying")
    plt.xticks(np.arange(5), ('20-25', '25-30', '30-35', '35-40', '40-45'))
    plt.figure("Cycles trying vs Age -Cycle Var- Pregnant")
    ax5 = plt.subplot(111)
    df_preg.pivot_table('CyclesTrying', index=age_bins, columns=['CycleVar']).plot(ax=ax5)
    ax5.set_ylabel("Mean Cycles Trying")
    plt.xticks(np.arange(5), ('20-25', '25-30', '30-35', '35-40', '40-45'))
    plt.figure("Cycles trying vs Age -FPlength- Pregnant")
    ax5 = plt.subplot(111)
    df_preg.pivot_table('CyclesTrying', index=age_bins, columns=['FPlength']).plot(ax=ax5)
    ax5.set_ylabel("Mean Cycles Trying")
    plt.xticks(np.arange(5), ('20-25', '25-30', '30-35', '35-40', '40-45'))

    age_bins_all = pd.cut(df['Age'], [20, 25, 30, 35, 40, 45])
    plt.figure("TempLogFreq vs Age -ExitStatus")
    fig78, (ax7, ax8) = plt.subplots(2, 1)
    df.pivot_table('TempLogFreq', index=age_bins_all, columns=['ExitStatus'],
                   aggfunc='mean').plot(ax=ax7)
    ax7.set_ylabel("Mean TemplogFreq")
    df.pivot_table('TempLogFreq', index=age_bins_all, columns=['ExitStatus'],
                   aggfunc='std').plot(ax=ax8)
    ax8.set_ylabel("sigma TemplogFreq")
    #plt.xticks(np.arange(5), ('20-25', '25-30', '30-35', '35-40', '40-45'))

    df_1cycle = df[df['CyclesTrying'] == 1]
    age_bins_1c = pd.cut(df_1cycle['Age'], [20, 25, 30, 35, 40, 45])
    plt.figure("TempLogFreq vs Age -ExitStatus - 1 cycle")
    ax9 = plt.subplot(111)
    df_1cycle.pivot_table('TempLogFreq', index=age_bins_1c, columns=['ExitStatus'],
                   aggfunc='mean').plot(ax=ax9)
    ax9.set_ylabel("Mean TemplogFreq")
    plt.xticks(np.arange(5), ('20-25', '25-30', '30-35', '35-40', '40-45'))
    df_preg_do = df[(df['ExitStatus'].isin([' Pregnant', ' Dropout']))]
    bin_logt = pd.cut(df_preg_do['TempLogFreq'],
                      pd.IntervalIndex.from_tuples([(0, 0.4), (0.8, 1)],
                                                   closed='right'))
    plt.figure("CyclesTrying-TempLogFreq")
    ax10 = plt.subplot(111)
    df_preg_do.pivot_table('Age', index='CyclesTrying', columns = [bin_logt, 'ExitStatus'],
                    aggfunc='count').plot(logy=True, ax=ax10, colormap='Accent')


    sex_f = pd.cut(df_preg['SexLogFreq'], [0.05, 0.15, 0.30, 0.45, 0.60, 0.8, 1])
    plt.figure("Cycles trying vs Age -SexLogFreq- Pregnant")
    ax5 = plt.subplot(111)
    df_preg.pivot_table('CyclesTrying', index=age_bins, columns=[sex_f]).plot(ax=ax5)
    ax5.set_ylabel("Mean Cycles Trying")
    plt.xticks(np.arange(5), ('20-25', '25-30', '30-35', '35-40', '40-45'))

    temp_f = pd.cut(df_preg['TempLogFreq'], [0.05, 0.15, 0.30, 0.45, 0.60, 0.8, 1])
    plt.figure("Cycles trying vs Age -TempLogFreq- Pregnant")
    ax6 = plt.subplot(111)
    df_preg.pivot_table('CyclesTrying', index=age_bins, columns=[temp_f]).plot(ax=ax6)
    ax6.set_ylabel("Mean Cycles Trying")
    plt.xticks(np.arange(5), ('20-25', '25-30', '30-35', '35-40', '40-45'))



def main():
    seaborn.set()
    #seaborn.set_palette(seaborn.color_palette("YlOrBr", 11))
    natural_cycles()
    plt.show()

if __name__ == "__main__":
    main()