function TRANSICION()
    global ESTADO
    global COLUMNA
    global COLOR
    
    c = COLUMNA;
    COLOR = COLOR_PLAYER(TURNO_JUGADOR)
    if (M(1,c) <> 0) then
        disp("JUGADA INVALIDA");
        ESTADO = 1
        return;
    end 
    
    JUGADA_ACEPTADA()
    
endfunction
