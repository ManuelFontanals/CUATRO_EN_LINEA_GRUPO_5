function win = WinCondition(M)
    //M = grand(8, 4, "uin", 0, 2);
    
    win = 0;
    
    for f = 2:7
        for c = 2:3
            if M(f,c) <> 0 then
                if ( ...
                    (M(f-1,c)   == M(f,c) & M(f+1,c)   == M(f,c)) | ...
                    (M(f-1,c-1) == M(f,c) & M(f+1,c+1) == M(f,c)) | ...
                    (M(f,c-1)   == M(f,c) & M(f,c+1)   == M(f,c)) | ...
                    (M(f+1,c-1) == M(f,c) & M(f-1,c+1) == M(f,c)) ...
                   ) then
                    win = M(f,c);
                    return;
                end
            end
        end
    end
    
    if M(1,2) <> 0 then
        if ((M(1,1)== M(1,2) & M(1,2) == M(1,3))|...
            (M(1,2)== M(1,3) & M(1,3) == M(1,4))) then
            win = M(1,2);
            return;   
        end
    end
    
    if M(8,2) <> 0 then
        if ((M(8,1)== M(8,2) & M(8,2) == M(8,3))|...
            (M(8,2)== M(8,3) & M(8,3) == M(8,4))) then
            win = M(8,2);
            return;
        end
    end
    
    for f = 2:7
        if M(f,1)<>0 then
            if( M(f-1,1)== M(f,1) & M(f+1,1)== M(f,1) ) then
                win = M(f,1);
                return;
            end
        end
    end
    
    for f = 2:7
        if M(f,4)<>0 then
            if( M(f-1,4)== M(f,4) & M(f+1,4)== M(f,4) ) then
                win = M(f,4);
                return;
            end
        end
    end
    
    if ( M(1,1)<>0 & M(1,2)<>0 & (M(1,3)<>0) & (M(1,4)<>0) ) then
        win = 5
        return;
    end
    
endfunction
