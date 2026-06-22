function TRANSICION_END_GAME()
    global M

    for f = 8:-1:1
        M(f,:) = GANA;
        disp(M);
        disp("");
        disp("");
    end
    INICIO();
    ESTADO = 0;
endfunction
