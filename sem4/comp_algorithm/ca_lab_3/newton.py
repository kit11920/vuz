from prettytable import PrettyTable


def print_tab_sep_diff_newton(data):
    tab = PrettyTable()
    tab.field_names = ['x', 'y'] + list(map(lambda x: f'Y{x}', range(1, len(data[0]) - 1)))
    for i in range(len(data)):
        row_list = list(map(lambda x: float(f'{x:.5f}'), data[i]))
        row_list += (len(data[0]) - len(data[i])) * ['-']
        tab.add_row(row_list)
    print(tab)


# tab - таблица для разделенных разностей n порядка
def sep_diff_newton(tab, begi, endi):
    diff = endi - begi
    if len(tab[begi]) > diff + 1:
        return tab[begi][diff + 1]

    if diff == 1:
        # print(tab)
        # print(f'(begi, endi) = {begi, endi}')
        y = (tab[begi][1] - tab[endi][1]) / (tab[begi][0] - tab[endi][0])
        tab[begi].append(y)
        return y

    y = (sep_diff_newton(tab, begi, endi - 1) - sep_diff_newton(tab, begi + 1, endi)) / (tab[begi][0] - tab[endi][0])
    tab[begi].append(y)
    return y


def build_tab_sep_diff_n_newton(data):
    tab = list()
    for i in range(len(data)):
        tab.append(data[i][:2])
    sep_diff_newton(tab, 0, len(tab) - 1)
    return tab


def count_polynom_newton(tab, x):
    polynom = tab[0][1]
    for i in range(2, len(tab[0])):
        part = tab[0][i]
        for i in range(i - 1):
            part *= x - tab[i][0]
        polynom += part

    return polynom


def polynom_newton_from_short_data(data, x, n, printing=False):
    tab = build_tab_sep_diff_n_newton(data)
    if printing:
        print('Полином Ньютона')
        print_tab_sep_diff_newton(tab)

    polynom = count_polynom_newton(tab, x)
    if printing:
        print(f'P{n}({x}) = {polynom:.5f}')
    return polynom


def get_short_data(data, x, size):
    min_diff = abs(x - data[0][0])
    ind = i = 0
    for i in range(1, len(data)):
        if abs(x - data[i][0]) < min_diff:
            ind = i
            min_diff = abs(x - data[i][0])

    before = size // 2
    after = size - before - 1
    # print(f'before = {before}, after = {after}, ind = {ind}')
    if ind >= before and i - ind >= after:
        st_ind = ind - before
        end_ind = ind + after
    elif ind <= after:
        st_ind, end_ind = 0, size - 1
    else:
        st_ind, end_ind = i - size + 1, i

    return data[st_ind:end_ind + 1]


def polynom_newton(big_data, x, n, printing=False):
    short_data = get_short_data(big_data, x, n + 1)
    y = polynom_newton_from_short_data(short_data, x, n, printing)
    return y
