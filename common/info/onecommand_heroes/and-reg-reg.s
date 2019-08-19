.name "and-reg-reg"
.comment "r1 (0xffffffff) & r2 (0x000000ff) = r4 (0x000000ff = 255). Must be executed on 11 tick"

ld %255, r2 ; Записываем в регистр 
and r1, r2, r4 ; Производим битовое умножение
