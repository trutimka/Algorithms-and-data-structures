Задача: Вам дан профиль высот некоторой местности в виде гистограммы с шириной столбца в 1 метр. Сколько воды там могло накопиться после обильных ливней?
Решение должно работать за линейное время и О(1) доп. памяти.

Решение: Используется два указателя (left_pos и right_pos), которые начинаются с крайних позиций вектора. 
cur_left_value и cur_right_value отслеживают максимальные значения слева и справа от текущего положения.
Алгоритм использует движение указателей внутрь вектора, чтобы эмулировать движение снаружи внутрь для определения, где находится вода.
Каждый раз, когда значение вектора меньше или равно текущему максимальному значению, разница добавляется к результату. Это происходит как для левого, так и для правого указателей.
Процесс продолжается до тех пор, пока указатели не сойдутся.