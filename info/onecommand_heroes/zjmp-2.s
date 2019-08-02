.name "zjmp-1"
.comment "Move on map[10] position. Must be executed on 30 tick."


	sub r1, r1, r2 ; -1 + -1 = 0 чтобы установить carry в 1. Переместит каретку в PC = 5
	zjmp %:point
	zjmp %0
	zjmp %0
	zjmp %0
	zjmp %0
point:
	ld %25, r1

