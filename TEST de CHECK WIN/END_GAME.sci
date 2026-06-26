function END_GAME()
    global ESTADO
    global GANA
    global TURNO_JUGADOR
    
    GANA = WinCondition(M)
    
    if GANA <> 0 then
        ESTADO = 5;
        return;
    end
    
    TURNO_JUGADOR = ~TURNO_JUGADOR;
    
    if CPU == 0 then
        ESTADO = 1;
        return;
    end
    
    if TURNO_JUGADOR then
        ESTADO = 3;
        return;
    end
    ESTADO = 1;
    
endfunction
