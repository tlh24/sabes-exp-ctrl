
H2O = 50;

    tic

for i = 1:1000,
   
    fprintf(1,'> %d - ',i)
    if(rand>0.8), 
        tdtJuice(H2O); 
        fprintf(1,'H2O = %d\n',H2O)
        toc
    end

    pause(5)
end