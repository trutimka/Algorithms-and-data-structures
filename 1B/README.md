Я изначально просчитываю значения для каждого промежутка от 0 до R, где R = {0..N}. Таким образом за линию получаю массив предварительных ответов. Далее, чтобы дать ответ на конкретный запрос мне надо взять значение из parr[r] и поделить на значение parr[l - 1]. Так я найду ответ на промежутке, но с неправильной степенью, соответственно, возвожу в нужную степень.