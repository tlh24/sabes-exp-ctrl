
DO_MANUAL = 1;

[a,b] = meshgrid(-10:1:10 , -10:2:10)

plot(a,b,'o')

	if(DO_MANUAL)
		%% WAITFORBUTTONPRESS gets charachter
		c=char(255);
        set(gcf,'currentcha',c);
        p=[0 0];
        set(gcf,'currentpoint',p);
        
        while( double(c)==255 & sum(abs(p))==0 )
            c = get(gcf,'currentcha')
            p = get(gcf,'currentpoint')
            pause(.01);
        end

        switch(c)
			case {char(13)}, % Return
				done=1; 
				update=0;
				return_flag=0;
			case {[],char(0),char(255)}, % mouse action
				g=get(gca,'currentpoint')
			    aa =g(1,1);
			    update=1;
			otherwise,
				update=0;
				beep
		end
		
		if( update )
          plot(a,b,'o'); hold on;
          plot(g(1,1),g(1,2),'+'); hold off;
          fprintf(1,'Updated\n')   
        end
		
	else % ~Do_Manual
		done=1;
		return_flag=0;
	end
