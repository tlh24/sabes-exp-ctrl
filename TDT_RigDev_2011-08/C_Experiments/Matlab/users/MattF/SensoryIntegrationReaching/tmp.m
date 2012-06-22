%%tmp.m

N=100;

figure;
for i = 1:N
  [start,reach,eye,swi,handcenter,nomrvect] = SIRGetTestTrialTargs(Params,[]);
  plot(start(1),start(2),'o');
  hold on;
  plot(reach(1),reach(2),'gs');
  plot(eye(1),eye(2),'ro');
  plot(handcenter(1),handcenter(2),'k*');
end
rectangle('position',[min(Params.wsBounds,[],1) range(Params.wsBounds,1)]);
axis equal;

% Params.BlockSettings(4).Settings = {'Params.adaptationOnFlag = 1;';                 ...
%     'Params.adaptation.PadaptationParams = 0.7;';   ...
%     'Params.adaptation.WashInFlag = 0;';            ...
%     'Params.visFB(1).zeroshiftproportion = 1;';     ...
%     'Params.visFB(1).P_starttargetfeedback = 0.7;'; ...
%     };