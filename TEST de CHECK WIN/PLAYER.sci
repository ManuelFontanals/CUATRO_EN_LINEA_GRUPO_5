function PLAYER()
     global ESTADO
     global COLUMNA FILA
     
     disp("");
     if (TURNO_JUGADOR & CPU==0) then
         disp("Juega Player 2");
     else 
         disp("Juega Player 1");
     end
     disp("");
    
while(ESTADO==1)
    disp("INGRESE:");disp("- 0 COLUMNA 1");disp("- 1 COLUMNA 2");
    disp("- 2 COLUMNA 3");disp("- 3 COLUMNA 4");disp("- 8 CONFIRMAR JUGADA");
    disp("- 12 RESET");
    Teclado_Accionado = input("Ingrese accion: ")
    select Teclado_Accionado
        
            // Si es 16 entonces no hace nada
            case 16 then
                return
        
            // Elije si CPU activo o no
            case 0 then
                COLUMNA = 1
        
            // Elije diff de CPU
            case 1 then
                COLUMNA = 2
        
            case 2 then
                COLUMNA = 3
        
            case 3 then
                COLUMNA = 4
        
            // CAMBIA DE ESTADO A TRANSICION
            case 8 then
                ESTADO = 2
        
            case 12 then
                INICIO()
                ESTADO = 0
                 
            else
                // buzzer
                Teclado_Accionado = 16
        
        end
	Teclado_Accionado = 16;
end
    
endfunction
