.name "ZORNl2:		sti r1, %:live, %1
           		and r1, %0, r1

           live:	live %1
           		zjmp %:livel2:		sti r1, %:live, %1
                           		and r1, %0, r1

                           live:	live %1
                           		zjmp %:livel2:		sti r1, %:live, %1
                                           		and r1, %0, r1

                                           live:	live %1
                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                           		and r1, %0, r1

                                                           live:	live %1
                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                           		and r1, %0, r1

                                                                           live:	live %1
                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                           		and r1, %0, r1

                                                                                           live:	live %1
                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                           		and r1, %0, r1

                                                                                                           live:	live %1
                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                           		and r1, %0, r1

                                                                                                                           live:	live %1
                                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                                           		and r1, %0, r1

                                                                                                                                           live:	live %1
                                                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                                                           		and r1, %0, r1

                                                                                                                                                           live:	live %1
                                                                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                                                                           		and r1, %0, r1

                                                                                                                                                                           live:	live %1
                                                                                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                                                                                           		and r1, %0, r1

                                                                                                                                                                                           live:	live %1
                                                                                                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                                                                                                           		and r1, %0, r1

                                                                                                                                                                                                           live:	live %1
                                                                                                                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                                                                                                                           		and r1, %0, r1

                                                                                                                                                                                                                           live:	live %1
                                                                                                                                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                                                                                                                                           		and r1, %0, r1

                                                                                                                                                                                                                                           live:	live %1
                                                                                                                                                                                                                                           		zjmp %:livel2:		sti r1, %:live, %1
                                                                                                                                                                                                                                                           		and r1, %0, r1

                                                                                                                                                                                                                                                           live:	live %1
                                                                                                                                                                                                                                                           		zjmp %:live"
.comment "NEVER
DIE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
