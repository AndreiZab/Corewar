.name "fork-1"
.comment "Spawn new carriage each 800 ticks"

fork %0
ld %5, r2 ; "Родившие" каретки получат r2 = 5 через 5 тиков (805, 1606, ...)

; На данный момент каретки появляются на 800 и 1601 тиках
; 1600 будет если картека тут же должна принимать в себя команду
; Проверить