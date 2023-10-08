import math as m

opts = "O0 O2".split()
indexes = "1a 1b 1c".split()
sorts = "s us".split()

# tab 2
opt2 = 'O2'
index2 = '1a'
t_avgs_us = dict()


def get_time_reps_rse(filename):
    sum = 0
    n = 0

    with open(filename, 'r') as f:
        time = f.readline()
        while time != '':
            time = int(time)
            sum += time
            n += 1
            time = f.readline()
    t_avg = sum / n  # среднее значение

    if sum == 0:
        rse = 0.0
    else:
        s2 = 0  # дисперсия

        with open(filename, 'r') as f:
            time = int(f.readline())
            s2 += (time - t_avg) ** 2
        s2 /= (n - 1)
        s = s2 ** 0.5  # стандартное отклонение
        stderr = s / (n ** 0.5)  # стандартная ошибка
        rse = stderr / t_avg * 100  # относительная стандартная ошибка
    # print(filename, rse)

    return (t_avg, n, rse)


for opt in opts:
    for index in indexes:
        filetab = f'./tabs/tab_{opt}_{index}_1.txt'
        with open(filetab, 'w') as f:
            f.write(f"# tab_{opt}_{index}_1\n")
            f.write(f"Случайный массив \t Упорядоченный массив\n")
            f.write(f'Размер массива \t Время \t Кол-во повторов \t RSE \t Время \t Кол-во повторов \t RSE\n')
        for size in range(10, 5011, 500):
            with open(filetab, 'a') as f:
                f.write(f'{size}\t')

                # sorted
                filename = f"./data/data_{opt}_{index}_s_{size}.txt"
                t_avg, n, rse = get_time_reps_rse(filename)

                f.write(f'{t_avg:.2g}\t{n}\t{rse:.2g}\t')

                # unsorted
                filename = f"./data/data_{opt}_{index}_us_{size}.txt"
                t_avg, n, rse = get_time_reps_rse(filename)

                if (opt == opt2 and index == index2):
                    t_avgs_us[size] = (t_avg, n, rse)

                f.write(f'{t_avg:.2g}\t{n}\t{rse:.2g}\n')


# tab 2
opt = opt2
index = index2

filetab = f'./tabs/tab_{opt2}_{index2}_us_2.txt'

with open(filetab, 'w') as f:
    f.write(f"# tab_{opt}_{index2}_us_2\n")
    f.write(f'Размер массива \t Время \t Кол-во повторов \t RSE \t ln - ln \n')

for size in range(10, 5011 - 500, 500):
    if t_avgs_us[size][0] == 0 or t_avgs_us[size + 500][0] == 0:
        lns = 0.0
    else:
        lns = (m.log(t_avgs_us[size + 500][0]) + m.log(t_avgs_us[size][0])) / (m.log(size + 500) + m.log(size))

    with open(filetab, 'a') as f:
        f.write(f'{size}\t{t_avgs_us[size][0]:.2g}\t{t_avgs_us[size][1]}\t{t_avgs_us[size][2]:.2g}\t{lns:.2} \n')
        # f.write(f'| {size} | {t_avgs[size]} | {lns:.2} |\n')
