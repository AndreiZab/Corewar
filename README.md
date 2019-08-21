# О проекте
*Corewar* это игра, где четыре игрока(чемпиона) противостоят друг другу на виртуальной арене. Они пытаются остановить друг друга, перезаписывая инструкции, которые должны быть выполнены последовательно в пределах одного пространства памяти. Все противники это программы написанные на языке ассемблер.

В этом проекте нас просят сделать чемпиона, виртуальную машину(арену) для игры и компилятор с ассемблера в байт-код.
Доступны были только внешние функции C: write, malloc, free, open, close, read, lseek.
Большинство библиотечных функций написаны самостоятельно и находятся в папке libft.

# Разделение проекта на части

### Компилятор
Это программа, которая будет компилировать написанный на языке ассемблера код чемпиона в байт-код, который будет интерпретироваться виртуальной машиной напрямую.

Этапы:
* Лексический анализ ассемблер кода, получение токенов(лексем) и построение абстрактного синтаксического дерева
* Синтаксический анализ кода: парсинг и валидация лексем, а также обработка ошибок. В случае ошибки происходит поиск места, в котором она была вызвана, и формируется сообщение об ошибке
* Компиляция полученных команд в байт-код

### Виртуальная машина (Интерпретатор)
После того, как мы получили файл с байт-кодом, наступает время работы виртуальной машины.
Её задача — выделить участок памяти, разместить на этом участке код чемпионов и каретки, которые будут его исполнять.
А затем следить за ходом битвы, чтобы объявить чемпиона-победителя после её завершения.

Этапы:
* Разбор игроков, записанных в байт-коде, сгенерированном компилятором
* Настроить среду игры (инициализировать игроков, проверить действующие инструкции байт-кода и т.д.)
* Выполнить код каждого игрока параллельно
* Остановить, когда все игроки, кроме одного, мертвы

### Визуализация
Отображает текущее состояние вертуальной машины в реальном времени

# Установка
make
//добавить sdl2

# Usage
./asm champ.s


./disasm [-cf] file1.cor [file2.cor ...]  
* -c - colored mode  
* - f - file-format mode  


./corewar [-cva] [-dump nbr_cycles] [-dinfo] [[-n champ_number] champ.cor]  
Flags:  
* -c - colored mode  
+ -v - visualization mode  
- -a - enable aff output  
Dump memory:  
* -dump nbr_cycle - output dump memory  
* -dinfo - output additional information on -dump  
Champions:  
* champ.cor - binary file with champions code  
		


# Визуализация
Тут должны быть картинки, представь их

# Команда
[Larlune](https://github.com/PofigistVip)

[Qclubfoo](https://github.com/qclubfoo)

[Rhealitt](https://github.com/AndreiZab)

# Лицензия
Do what you want 
