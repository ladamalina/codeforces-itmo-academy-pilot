import random
import sys
import time
from typing import *


def main():
    """
    Для чтения входных данных необходимо получить их
    из стандартного потока ввода (sys.stdin).
    Данные во входном потоке соответствуют описанному
    в условии формату. Обычно входные данные состоят
    из нескольких строк.
    Можно использовать несколько методов:
    * input() -- читает одну строку из потока без символа
    перевода строки;
    * sys.stdin.readline() -- читает одну строку из потока,
    сохраняя символ перевода строки в конце;
    * sys.stdin.readlines() -- вернет список (list) строк,
    сохраняя символ перевода строки в конце каждой из них.
    Чтобы прочитать из строки стандартного потока:
    * число -- int(input()) # в строке должно быть одно число
    * строку -- input()
    * массив чисел -- map(int, input().split())
    * последовательность слов -- input().split()
    Чтобы вывести результат в стандартный поток вывода (sys.stdout),
    можно использовать функцию print() или sys.stdout.write().
    Возможное решение задачи "Вычислите сумму чисел в строке":
    print(sum(map(int, input().split())))
    """
    n = 300_000
    m = 300_000
    sys.stdout.write(f"{n} {m}\n")
    added = set()
    for i in range(m):
        ok = False
        while not ok:
            op = random.randint(0, 2)
            if op == 0:
                u = random.randint(1, n)
                v = random.randint(1, n)
                if u > v:
                    u, v = v, u
                sys.stdout.write(f"+ {u} {v}\n")
                added.add((u, v))
                ok = True
            elif op == 1 and len(added):
                u, v = random.sample(list(added), 1)[0]
                sys.stdout.write(f"- {u} {v}\n")
                added.remove((u, v))
                ok = True
            elif op == 2:
                sys.stdout.write(f"?\n")
                ok = True


if __name__ == "__main__":
    main()
