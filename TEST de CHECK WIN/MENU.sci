function MENU()
    global ESTADO
    global CPU CPU_DIFF
    global COLOR_P1 COLOR_P2

    while(ESTADO==0)
    disp("INGRESE:");disp("- 4 CPU ON/OFF");disp("- 5 CPU DIFF facil");
    disp("- 6 CPU DIFF media");disp("- 7 CPU DIFF alta");disp("- 8 INICIO JUEGO");
    disp("- 9 COLOR P1 down");disp("- 10 COLOR P1 up");
    disp("- 13 COLOR P2 down");disp("- 14 COLOR P2 up");
    Teclado_Accionado = input("Ingrese accion: ")
select Teclado_Accionado

    // Si es 16 entonces no hace nada
    case 16 then
        return

    // Elije si CPU activo o no
    case 4 then
        CPU = ~CPU

    // Elije diff de CPU
    case 5 then
        CPU_DIFF = 1

    case 6 then
        CPU_DIFF = 2

    case 7 then
        CPU_DIFF = 3

    // CAMBIA DE ESTADO A P1
    case 8 then
        ESTADO = 1

    // Cambia color P1 y P2, subida
    case 10 then
        if COLOR_P1 < 3 then
            COLOR_P1 = COLOR_P1 + 1
        else
            COLOR_P1 = 1
        end

    case 14 then
        if COLOR_P2 < 3 then
            COLOR_P2 = COLOR_P2 + 1
        else
            COLOR_P2 = 1
        end

    // Cambia color P1 y P2, bajada
    case 9 then
        if COLOR_P1 > 1 then
            COLOR_P1 = COLOR_P1 - 1
        else
            COLOR_P1 = 3
        end

    case 13 then
        if COLOR_P2 > 1 then
            COLOR_P2 = COLOR_P2 - 1
        else
            COLOR_P2 = 3
        end

    else
        // buzzer
        Teclado_Accionado = 16

end
	Teclado_Accionado = 16;
end
//    if ESTADO == 1 then	
//        INICIO_JUEGO();
//    end

    
endfunction
