function TotalTrials_RT(name)

ct   = 0;
n    = 0;
nc   = 0;
z    = 0;
done = 0;
filename = name;

totalErrors = 10;
for ierr=1:totalErrors,
    eval(sprintf('nerr%s = 0;',num2str(ierr)));
end

ERRstr = {'Timeout at Start Position'...
    'Broke Hand Hold at Start Position'...
    'Broke Hand Hold at Start Position During Eye Reaching'...
    'Timeout to Reach Eye Target'...
    'Missed Hold at Eye Fixation Point during Delay'...
    'Broke Hold at Start Position While Holding Eye Fixation'...
    'Broke Eye Hold Too Early During Hand Reaching'...
    'Timeout to Reach Target'...
    'Missed Hold at Reach Target'...
    'Missed Hold at Eye Fixation Point During Target Hold'};

while(~done)
    fnm = sprintf('ReachTuning_%s-%d.mat',filename,ct+1);
    if(exist(fnm)),
        load(fnm);
        z = size(DATA);
        z = z(2);
        for i=1:z,
            n=n+1;
            if (DATA(i).err==0), nc=nc+1; end

            for ierr = 1:totalErrors,
                if(DATA(i).err==ierr),
%%%                    eval(sprintf('nerr%s = nerr%s +1;'),num2str(ierr),num2str(ierr));
                    eval(sprintf('nerr%d = nerr%d+1;',ierr,ierr));
                end
            end
            
        end
    else
        test = sprintf('ReachTuning_%s-%d.mat',filename,ct+2);
        if(~exist(test)), done = 1; end
    end
    
    ct=ct+1;
end

fprintf(1,'Correct trials: %d - Total trials: %d \n',nc,n);
fprintf(1,'Ratio correct = %.2f \n\n',nc/n)
fprintf(1,'Errors Statistics\n')
for ierr = 1:totalErrors,         
        eval(sprintf('errpct = (nerr%d/n)*100;',ierr));
        fprintf(1,'Error %d - %.1f pct - %s\n',ierr,errpct,ERRstr{ierr})
end



