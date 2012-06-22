
function ErrorsDistribution(name)

% 1    'Timeout at Start Position'...
% 2    'Broke Hand Hold at Start Position'...
% 3    'Broke Hand Hold at Start Position During Eye Reaching'...
% 4    'Timeout to Reach Eye Target'...
% 5    'Missed Hold at Eye Fixation Point during Delay'...
% 6    'Broke Hold at Start Position While Holding Eye Fixation'...
% 7    'Broke Eye Hold Too Early During Hand Reaching'...
% 8    'Timeout to Reach Target'...
% 9    'Missed Hold at Reach Target'...
% 10   'Missed Hold at Eye Fixation Point During Target Hold'

ct   = 0;
n    = 0;
nc   = 0;
z    = 0;
done = 0;
filename = name;

fprintf(sprintf('\nLoading file %s...\n',filename))
load(sprintf('%s',filename))

TRIAL  = cat(1,DATA(:).trial);
ERROR  = cat(1,DATA(:).err);

plot(TRIAL,ERROR,'o')
axis([0 max(TRIAL) 0 10])

totalErrors = 10;
for ierr=1:totalErrors, % set errors to zero
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

z = size(DATA);
z = z(2);
for i=1:z,
    n=n+1;
    if (DATA(i).err==0), nc=nc+1; end

    for ierr = 1:totalErrors,
        if(DATA(i).err==ierr),
            eval(sprintf('nerr%d = nerr%d+1;',ierr,ierr));
        end
    end

end

fprintf(1,'Correct trials: %d - Total trials: %d \n',nc,n);
fprintf(1,'Ratio correct = %.2f \n\n',nc/n)
fprintf(1,'Errors Statistics\n')
for ierr = 1:totalErrors,         
        eval(sprintf('errpct = (nerr%d/n)*100;',ierr));
        fprintf(1,'Error %d - %.1f pct - %s\n',ierr,errpct,ERRstr{ierr})
end






