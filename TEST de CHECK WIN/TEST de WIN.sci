M = grand(8, 4, "uin", 0, 2)

for f = 2:7 
    for c = 2:3
        if (M(f,c)!=0)
            then if (
                    ( M(f-1,c) == M(f,c) ) and ( M(f+1,c) == M(f,c) )
                    or (  ( M(f-1,c-1) == M(f,c) ) and ( M(f+1,c+1) == M(f,c) )  )
                    or (  ( M(f,c-1) == M(f,c) ) and ( M(f,c+1) == M(f,c) )  )
                    or (  ( M(f+1,c-1) == M(f,c) ) and ( M(f-1,c+1) == M(f,c) )  )
                    )
                    then win = M(f,c)
                end
            end
            
    end
end


