%  quickDataPlot.m

if 1
  usetrials = [1:trial];
else
  usetrials = [1:10];
  %usetrials = [11:20];
  %usetrials = [21:30];
end
thesedata = Data(usetrials);

ERR = cat(1,thesedata(:).err);
SP = cat(1,thesedata(~ERR).startpt);
EP = cat(1,thesedata(~ERR).endpt);
RT = cat(1,thesedata(:).reachtargetpos);
ET = cat(1,thesedata(:).eyetargetpos);
ST = cat(1,thesedata(:).starttargetpos);
RVCT = RT-ST;
FBSHIFT = cat(1,thesedata(:).fbshift);
gbff = cat(1,thesedata(:).givebonusfeedbackflag);
stFB = cat(1,thesedata(:).starttargetfeedback);
fbonrp = cat(1,thesedata(:).fbonreachproportion)
nomfbloc = ST+FBSHIFT;

correctIdx = find(~ERR);
stfbONidx = find(stFB);
stfbOFFidx = find(~stFB);
bfONidx = find(gbff);

figure;
rectangle('position',[min(Params.wsBounds,[],1) range(Params.wsBounds,1)]);
hold on;
plot(RT(:,1),RT(:,2),'go','markersize',10);
hold on;
plot(ET(:,1),ET(:,2),'ro','markerfacecolor','r');
plot(ST(:,1),ST(:,2),'gs');
plot(nomfbloc(stfbONidx,1),nomfbloc(stfbONidx,2),'c^');
plot(nomfbloc(stfbOFFidx,1),nomfbloc(stfbOFFidx,2),'cv');
plot(nomfbloc(bfONidx,1),nomfbloc(bfONidx,2),'m.');
plot([ST(:,1)'; nomfbloc(:,1)'],[ST(:,2)'; nomfbloc(:,2)']);
axis equal;
title('All Trials');

figure;
rectangle('position',[min(Params.wsBounds,[],1) range(Params.wsBounds,1)]);
hold on;
plot(RT(correctIdx,1),RT(correctIdx,2),'go');
hold on;
plot(ET(correctIdx,1),ET(correctIdx,2),'r.');
plot(ST(correctIdx,1),ST(correctIdx,2),'gs');
axis equal;
title('Correct Trials Only');


figure;
subplot(2,1,1);
plot(RVCT(:,1),RVCT(:,2),'go');
hold on;
plot(RVCT(bfONidx,1),RVCT(bfONidx,2),'m.');
axis equal;
subplot(2,1,2);
hist(cat(1,thesedata(:).nominalreachdirection));
xlabel('Reach dir');

figure;
hist(gbff,unique(gbff));
xlabel('Endpoint FB?');

figure;
plot(SP(:,1),SP(:,2),'b.');
hold on;
plot(EP(:,1),EP(:,2),'g.');
plot(RT(correctIdx,1),RT(correctIdx,2),'go','markersize',20);
axis equal;