.name "lldi-reg-reg-reg"
.comment "Place rg5(5) + rg6(20) + curr_pos in rg3, exe on 60 tick"

ld %5, r5
ld %20, r6
lldi r5, r6, r3
