function JUGADA_ACEPTADA()
    global M
    global ESTADO
    
    c = COLUMNA;
    M(1,c) = COLOR;
    for f=2:8
        disp(M);
        disp("");
        disp("");
        if ( M(f,c) <> 0 ) then
            ESTADO = 4;
            return;
        end
        M(f,c) = COLOR;
        f = f-1;
        M(f,c) = 0; 
        f = f+1;
    end
    disp(M);
    ESTADO = 4
endfunction
