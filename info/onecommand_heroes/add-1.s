.name "add-1"
.comment "r1 + r2 (228) = r3 - must be 227. Must be executed on 15 tick"

; в r1 ожидаем номер игрока равный -1
ld %228, r2 ; Устанавливаем значение для r2
add r1, r2, r3
