# A. Дерево отрезков на сумму

https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A

```
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 1024 мегабайта
ввод: стандартный ввод
вывод: стандартный вывод
```

В этой задаче вам нужно написать обычное дерево отрезков на сумму.

## Входные данные

Первая строка содержит два числа 𝑛 и 𝑚 (1 ≤ 𝑛,𝑚 ≤ 100000) — размер массива и число операций. Следующая строка содержит 𝑛 чисел 𝑎𝑖 — начальное состояние массива (0 ≤ 𝑎𝑖 ≤ 10^9). Далее следует описание операций. Описание каждой операции имеет следущий вид:

- 1 𝑖 𝑣 — присвоить элементу с индексом 𝑖 значение 𝑣 (0 ≤ 𝑖 < 𝑛, 0 ≤ 𝑣 ≤ 10^9).

- 2 𝑙 𝑟 — вычислить сумму элементов с индексами от 𝑙 до 𝑟−1 (0 ≤ 𝑙 < 𝑟 ≤ 𝑛). 

## Выходные данные

Для каждой операции второго типа выведите соответствующую сумму.

## Пример

Входные данные
```
5 5
5 4 2 3 5
2 0 3
1 1 1
2 0 3
1 3 1
2 0 5
```

Выходные данные
```
11
8
14
```
