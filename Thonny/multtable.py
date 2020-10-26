def show_mtable(cols, rows=None):
    """
    Function printing multiplication table.
    rows, cols - ints, dimensions of table. If rows not provided: rows = cols.
    """
    if not rows:
        rows = cols

    # Calculate column width (minimum 2 chars spacing)
    width = len(str(rows * cols)) + 2

    # First row: header
    print(' ' * width + '|', end='')
    for num in range(1, cols+1):
        print('{0:>{1}}'.format(num, width), end='')
    print('\n' + '-' * ((cols + 1) * width + 1))

    # Rest of rows
    for row in range(1, rows+1):
        print('{0:>{1}} |'.format(row, width-1), end='')
        for col in range(1, cols+1):
            print('{0:>{1}}'.format(row*col, width), end='')
        print()


def main():
    show_mtable(10)


if __name__ == "__main__": main()