import random


def read_input_type(types):
    input_num = -1
    message = "Введите цифру для выбора варианта ввода "
    for i in range(len(types)):
        message += types[i] + ": " + str(i) + ", "
    message = message[0:-2] + ": "
    while input_num not in range(len(types)):
        try:
            input_num = int(input(message))
        except Exception:
            input_num = -1
    return input_num


def get_matrix_file(filename):
    with open(filename, 'rt') as file:
        try:
            dimension = int(file.readline())
            matrix = []
            for line in file:
                new_row = list(map(float, line.strip().split()))
                if len(new_row) != (dimension + 1):
                    raise ValueError
                matrix.append(new_row)
            if len(matrix) != dimension:
                raise ValueError
        except ValueError:
            return None
    return matrix, dimension


def get_matrix_input():
    while True:
        try:
            dimension = int(input("Порядок матрицы: "))
            if dimension <= 0:
                print("Порядок матрицы должен быть положительным.")
            else:
                break
        except ValueError:
            print("Порядок матрицы должен быть целым числом.")
    matrix = []
    print("Введите коэффициенты матрицы через пробел:")
    try:
        for i in range(dimension):
            matrix.append(list(map(float, input().strip().split())))
            if len(matrix[i]) != (dimension + 1):
                raise ValueError
    except ValueError:
        return None
    return matrix, dimension


def get_random_matrix():
    while True:
        try:
            dimension = int(input("Порядок матрицы: "))
            if dimension <= 0:
                print("Порядок матрицы должен быть положительным числом.")
            else:
                break
        except ValueError:
            print("Порядок матрицы должен быть целым числом.")
    matrix = [[0]*(dimension+1) for i in range(dimension)]
    for i in range(dimension):
        for j in range(dimension + 1):
            matrix[i][j] = random.randrange(-20, 20)
    return matrix, dimension


def print_matrix(matrix, dimension):
    for i in range(dimension):
        output_string = ""
        for j in range(dimension):
            output_string += str(matrix[i][j]) + " "
        output_string += "| " + str(matrix[i][dimension])
        print(output_string)


def print_answer(answer, dimension):
    for i in range(dimension):
        print("x" + str(i + 1) + " = " + str(answer[i]))


def print_discrepancy(discrepancy):
    for string in discrepancy:
        print(str(string[0]) + " - " + str(string[1]) + " = " + str(string[2]))
#print()