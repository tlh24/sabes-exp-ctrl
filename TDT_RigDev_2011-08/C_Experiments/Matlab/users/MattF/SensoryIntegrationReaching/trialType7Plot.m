%  trialType7Plot.m


sv = circleVerts(Data(trial).starttargetpos(:),Data(trial).starttargetwin);
ev = circleVerts(Data(trial).eyetargetpos',Data(trial).eyetargetwin);

figure(71);
set(gcf,'position',[476   209   497   383]);
cla;
plot(eyetargpossibles(:,1),eyetargpossibles(:,2),'ro');
hold on;
plot(handtargpossibles(:,1),handtargpossibles(:,2),'ko');
plot(Data(trial).eyetargetpos(:,1),Data(trial).eyetargetpos(:,2),'ro','markerfacecolor','r');
plot(Data(trial).starttargetpos(:,1),Data(trial).starttargetpos(:,2),'ks','markerfacecolor','k');

eyeidxatreachstart = nearest(Data(trial).eyetrajectorytime,Data(trial).time(1));

plot(sv(1,:),sv(2,:),'b');
hold on;
plot(ev(1,:),ev(2,:),'r');
rectangle('position',[min(Params.wsBounds,[],1) range(Params.wsBounds,1)]);
axis equal;
drawnow;
%     ud = get(gcf,'userdata');
%     ud.sp = ud.sp + 1;
%     subplot(2,1,mod(ud.sp,2)+1);
if ~isempty(Data(trial).handtrajectory)
    plot(squeeze(Data(trial).handtrajectory(1,1,:)),squeeze(Data(trial).handtrajectory(1,2,:)),'b');
    hold on   
end
if ~isempty(Data(trial).eyetrajectory)
  eh=plot(squeeze(Data(trial).eyetrajectory(1,:)),squeeze(Data(trial).eyetrajectory(2,:)),'b.');
  hold on;
  set(eh,'markersize',3.5);
end
if ~isempty(Data(trial).eyebufferatfixation)
  eyexy = Data(trial).eyebufferatfixation;
  eh=plot(squeeze(Data(trial).eyetrajectory(1,:)),squeeze(Data(trial).eyetrajectory(2,:)),'r.');
  set(eh,'markersize',2);
  hold on
  eh=plot(squeeze(Data(trial).eyetrajectory(1,eyeidxatreachstart:end)),squeeze(Data(trial).eyetrajectory(2,eyeidxatreachstart:end)),'r.');
  set(eh,'markersize',5);
  plot(eyexy(:,1),eyexy(:,2),'k.');
end
set(gca,'xlim',Params.wsBounds(:,1)');
set(gca,'ylim',Params.wsBounds(:,2)');
if Data(trial).err == 0
  title(sprintf('Trial %i (correct)',trial));
else
  title(sprintf('Trial %i',trial));
end
