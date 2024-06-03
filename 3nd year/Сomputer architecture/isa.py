"""
Типы данных для представления и сериализации/десериализации машинного кода.

Особенности:

- Машинный код сериализуется в список JSON.
- Один элемент списка -- одна инструкция.
- Индекс списка -- адрес инструкции.
"""
import json
from collections import namedtuple
from enum import Enum

class Opcode(str, Enum):
    """Opcode для ISA."""
    ADD = "add"
    SUB = "sub"
    MUL = "mul"
    DEV = "dev"
    MOD = "mod"
    MOV = "mov"
    DEFV = "defv"
    JMP = "jmp"
    JMPR = "jmpr"
    HLT = "hlt"
    JNE = "jne"
    JE = "je"
    CMP = "cmp"
    PRINT = "print"
    NOP = "nop"
    READ = "read"
    PRINTSTR = "printstr"
    JLE = "jle"
    JGE = "jge"
    PRINTC = "printc"


class Term(namedtuple('Term', 'pos word')):
    """Описание выражения из исходного текста программы."""
    # сделано через класс, чтобы был docstring



def find_digits_in_string(input_str):
    digits = [int(char) for char in input_str if char.isdigit()]
    return digits


def write_code(filename, code):
    """Записать машинный код в файл."""
    with open(filename, "w", encoding="utf-8") as file:
        file.write(json.dumps(code, indent=4))


def read_code(filename):
    """Прочесть машинный код из файла."""
    with open(filename, encoding="utf-8") as file:
        code = json.loads(file.read())
    return code
