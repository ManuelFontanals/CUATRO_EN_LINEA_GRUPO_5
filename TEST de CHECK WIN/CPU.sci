function CPU_JUEGA()
    global COLUMNA
    global ESTADO
    f = 1;
    c = 1;
    
    vector = [1 2 3 4];
    if M(1,1)<>0 then
        vector(1) = [];
    end
    if M(1,2)<>0 then
        vector(2) = [];
    end
    if M(1,3)<>0 then
        vector(3) = [];
    end
    if M(1,4)<>0 then
        vector(4) = [];
    end
// ESTO ES LO MISMO PERO EN "C"
// 
//#include <stdio.h>
//
//  int main(void)
//  {
//    int v[4] = {1, 2, 3, 4};
//    int n = 4; // cantidad de elementos válidos
//
//    int pos = 1; // eliminar el segundo elemento
//
//    for (int i = pos; i < n - 1; i++)
//    {
//        v[i] = v[i + 1];
//    }
//
//    n--;
//
//    for (int i = 0; i < n; i++)
//    {
//        printf("%d ", v[i]);
//    }
//
//    return 0;
//  }
    
if CPU_DIFF == 1 then
//  FACIL
        i = grand(1,1,"uin",1,length(vector));
        COLUMNA = vector(i);
    else if CPU_DIFF == 2 then
//      MEDIA

    else
//      DIFICIL

    end
end
    ESTADO = 2;
    
endfunction
