function PLAYING()
global ESTADO
while ESTADO <> 5
        select ESTADO
            case 0 then
                MENU();
            case 1 then
                PLAYER();
            case 2 then
                TRANSICION();
            case 3 then
                CPU_JUEGA();
            case 4 then
                END_GAME();
            case 5 then
                TRANSICION_END_GAME();
        end
end
endfunction
