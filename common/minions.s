.name "Minions V1"
.comment "Just fo fun"
	ld %15, r3
	ld %1, r4
head:
	ld %1, r2 
	st r2, -510
	st r1, -511
	st r1, 6 
	live %21
	sub r3, r4, r3
	zjmp %:body
	fork %:head
body:
	st r1, 6
	live %21
	st r1, 6
	live %21
	st r1, 6
	live %21
	st r1, 6
	live %21
	st r1, 6
	live %21
	st r1, 6
	live %21
	st r1, 6
	live %21
	ld %66, r5
	ld %65, r6
	ld %78, r7
	ld %10, r8
	aff r5
	aff r6
	aff r7
	st r1, 6
	live %21
	st r1, 6
	live %21
	aff r6
	aff r7
	aff r6
	aff r8
	st r1, 6
	live %21
