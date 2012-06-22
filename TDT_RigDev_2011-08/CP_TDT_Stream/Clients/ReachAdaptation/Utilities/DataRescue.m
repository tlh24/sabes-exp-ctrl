%%% DATA RESCUE -- adapt this in case expt dies early
	clear all
    N = 87;
    newN = 199;
    filename = 'Abe-20-May-2005-4';
    
	eval(sprintf('load -MAT ReachAdaptation_%s_TEMP/VARS.mat',filename));
	
    for j=1:N,
        if(exist(sprintf('ReachAdaptation_%s_TEMP/DATA_%d.mat',filename,j)))
            fprintf(1,'Loading file %d \n',j)
            eval(sprintf('load -MAT ReachAdaptation_%s_TEMP/DATA_%d.mat',filename,j));
            eval(sprintf('DATA_%d.trial = %d;',j,j+newN));
            eval(sprintf('DATA_%d = DATA_%d',j+newN,j));            
            eval(sprintf('save ReachAdaptation_%s_TEMP/DATA_%d DATA_%d;',filename,j+newN,j+newN));
%            eval(sprintf('save AlignmentTests_%s Params TimeStamp Joint2dStruct Data',filename));
        end
    end
%     fprintf(1,'...save data...')
%     eval(sprintf('save AlignmentTests_%s Params TimeStamp Joint2dStruct Data',filename));
%     fprintf(1,'Done!\n')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     clear all
%     for i=1:170,
%         
%     filename = 'Renato3copy-17-Jan-2005';
%         
%         if(exist(sprintf('AlignmentTests_%s.mat_TEMP/DATA_%d',filename,i)))
%             fprintf(1,'Loading file %d \n',i)
%             eval(sprintf('load -MAT AlignmentTests_%s.mat_TEMP/DATA_%d',filename,i));
%             
% 
%             eval(sprintf('DATA_%d.trial = %d;',i,i+244));
%             eval(sprintf('DATA_%d.block = 2;',i));
%             
%             eval(sprintf('DATA_%d',i));
%             eval(sprintf('DATA_%d = DATA_%d;',i+244,i));
%             eval(sprintf('clear DATA_%d',i));
%             eval(sprintf('clear DATA_%d',i+244-1));
%             clear filename;
%             
%          	eval(sprintf('save DATA_%d',i+244));
%             
%             %pause
%             
%         end
%     end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     clear all
%     for i=1:255,
%         
%     filename = 'Renato2copy-17-Jan-2005';
%         
%         if(exist(sprintf('AlignmentTests_%s.mat_TEMP/DATA_%d',filename,i)))
%             fprintf(1,'Loading file %d \n',i)
%             eval(sprintf('load -MAT AlignmentTests_%s.mat_TEMP/DATA_%d',filename,i));
%             
% %            eval(sprintf('DATA_%d = DATA_%d;',i,i));
%             eval(sprintf('clear DATA_%d',i-1));
%             clear filename;
%             
%          	eval(sprintf('save DATA_%d',i));
%             
%             %pause
%             
%         end
%     end
