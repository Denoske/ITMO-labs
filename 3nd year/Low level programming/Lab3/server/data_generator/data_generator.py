import sys
import string
import random

available_types = {"string": "string name", "integer": "integer age", "float": "float height", "boolean": "boolean male"}

def get_input():
    data_type = []
    for arg_index in range(2, len(sys.argv)):
        data_type.append(check_data_type(sys.argv[arg_index]))

    return check_count(sys.argv[1]), data_type


def check_data_type(data_type):
    if data_type in code_generate:
        return data_type
    raise ValueError("Invalid type")


def check_count(count):
    try:
        return int(count)
    except ValueError:
        print("Oops!  That was no valid number.")
        raise ValueError("Invalid count")


def create_data(data_type, count):
    data = ''
    for iter in range(count):
        cur_tuple = "0 "
        if iter != 0:
            cur_tuple = str(random.randint(0, iter - 1)) + ' '
        for type in data_type:
            cur_tuple += code_generate[type]()
        data += cur_tuple.strip()
        data += '\n'
    return data


def get_random_string():
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(20)) + ' '


def get_random_integer():
    return str(random.randrange(1, 99999)) + ' '


def get_random_float():
    return str(round(random.uniform(1, 100), 5)) + ' '


def get_random_boolean():
    return str(bool(random.getrandbits(1))) + ' '


def create_file(data):
    file = open("data.txt", "w+")
    header = sys.argv[1] + ' '
    for types in map(str, list(sys.argv[2::])):
        header += (available_types[types] + ' ')
    file.write(header.strip())
    file.write('\n' + data)
    file.close()


code_generate = {"string": get_random_string, "integer": get_random_integer,
                 "boolean": get_random_boolean, "float": get_random_float}

# human {age[int], name[string], male[bool], height[float]}
if __name__ == '__main__':

    count, data_type = get_input()

    data = create_data(data_type, count)

    create_file(data)