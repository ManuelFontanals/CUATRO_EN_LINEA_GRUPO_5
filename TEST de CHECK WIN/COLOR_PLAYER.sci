function COLOR = COLOR_PLAYER(TURNO_JUGADOR)
    if TURNO_JUGADOR then
        COLOR = COLOR_P2;
        return
    end
    COLOR = COLOR_P1;
    
endfunction
