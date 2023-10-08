import math as m

opt = 'O3'
filetab = f'./tabs/tab.txt'

t_avg_ch_dict = dict()
t_avg_nch_dict = dict()
rse_ch_dict = dict()
rse_nch_dict = dict()

with open(filetab, 'w') as f:
    f.write(f"# tab_{opt} \n")
    f.write(f'Row_matrix\tTime_not_cached\tTime_cached\tRse_not_cached\tRse_cached\tln_not_cached\tln_cached\n')
    #f.write(f'| --- | --- | --- | --- | --- | --- | --- |\n')

for row in range(10, 5011, 100):
    # cached
    sum = 0
    n = 0
    filename = f'./data/data_{opt}_ch_100x{row}.txt'
    with open(filename, 'r') as f:
        time = f.readline()
        while time != '':
            time = int(time)
            sum += time
            n += 1
            time = f.readline()
    t_avg_ch = sum / n  # среднее значение
    t_avg_ch_dict[row] = t_avg_ch

    if sum == 0:
        rse_ch = 0.0
    else:
        s2 = 0  # дисперсия
        with open(filename, 'r') as f:
            time = int(f.readline())
            s2 += (time - t_avg_ch) ** 2
        s2 /= (n - 1)
        s = s2 ** 0.5  # стандартное отклонение
        stderr = s / (n ** 0.5)  # стандартная ошибка
        rse_ch = stderr / t_avg_ch * 100  # относительная стандартная ошибка
    rse_ch_dict[row] = rse_ch

    # not_cached
    sum = 0
    n = 0
    filename = f'./data/data_{opt}_nch_100x{row}.txt'
    with open(filename, 'r') as f:
        time = f.readline()
        while time != '':
            time = int(time)
            sum += time
            n += 1
            time = f.readline()
    t_avg_nch = sum / n  # среднее значение
    t_avg_nch_dict[row] = t_avg_nch

    if sum == 0:
        rse_nch = 0.0
    else:
        s2 = 0  # дисперсия
        with open(filename, 'r') as f:
            time = int(f.readline())
            s2 += (time - t_avg_nch) ** 2
        s2 /= (n - 1)
        s = s2 ** 0.5  # стандартное отклонение
        stderr = s / (n ** 0.5)  # стандартная ошибка
        rse_nch = stderr / t_avg_nch * 100  # относительная стандартная ошибка
    rse_nch_dict[row] = rse_nch

for row in range(10, 5011 - 100, 100):
    #cached
    if t_avg_ch_dict[row] == 0 or t_avg_ch_dict[row + 100] == 0:
        lns_ch = 0.0
    else:
        lns_ch = (m.log(t_avg_ch_dict[row + 100]) + m.log(t_avg_ch_dict[row]) / (m.log(row + 100) + m.log(row)))

    # not cached
    if t_avg_nch_dict[row] == 0 or t_avg_nch_dict[row + 100] == 0:
        lns_nch = 0.0
    else:
        lns_nch = (m.log(t_avg_nch_dict[row + 100]) + m.log(t_avg_nch_dict[row]) / (m.log(row + 100) + m.log(row)))

    with open(filetab, 'a') as f:
        # print(f' {row}  {t_avg_nch_dict[row]}  {t_avg_ch_dict[row]:.2} {rse_nch_dict[row]:.2}  {rse_ch_dict[row]:.2}  {lns_nch:.2}  {lns_ch:.2}  \n')
        # f.write(f' {row}  {t_avg_nch_dict[row]}  {t_avg_ch_dict[row]}  '
        #         f'{rse_nch_dict[row]:.2}  {rse_ch_dict[row]:.2}  {lns_nch:.2}  {lns_ch:.2}  \n')
        f.write(f'{row}\t{t_avg_nch_dict[row]:.2g}\t{t_avg_ch_dict[row]:.2g}\t'
                f'{rse_nch_dict[row]:.2g}\t{rse_ch_dict[row]:.2g}\t{lns_nch:.2g}\t{lns_ch:.2g}\n')

