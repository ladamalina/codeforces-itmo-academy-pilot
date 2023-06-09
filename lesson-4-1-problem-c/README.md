# C. Число минимумов на отрезке

https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B

```
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 1024 мегабайта
ввод: стандартный ввод
вывод: стандартный вывод
```

Теперь измените код дерева отрезков, чтобы кроме минимума на отрезке считалось также и число элементов, равных минимуму.

## Входные данные

Первая строка содержит два числа 𝑛 и 𝑚 (1 ≤ 𝑛,𝑚 ≤ 100000) — размер массива и число операций. Следующая строка содержит 𝑛 чисел 𝑎𝑖 — начальное состояние массива (0 ≤ 𝑎𝑖 ≤ 10^9). Далее следует описание операций. Описание каждой операции имеет следущий вид:

- 1 𝑖 𝑣 — присвоить элементу с индексом 𝑖 значение 𝑣 (0 ≤ 𝑖 < 𝑛, 0 ≤ 𝑣 ≤ 10^9).

- 2 𝑙 𝑟 — найти минимум и число элементов, равных минимуму, среди элементов с индексами от 𝑙 до 𝑟−1 (0 ≤ 𝑙 < 𝑟 ≤ 𝑛).

## Выходные данные

Для каждой операции второго типа выведите два числа — минимум на заданном отрезке и число элементов, равных этому минимуму.

## Пример

Входные данные
```
5 5
3 4 3 5 2
2 0 3
1 1 2
2 0 3
1 0 2
2 0 5
```

Выходные данные
```
3 2
2 1
2 3
```
