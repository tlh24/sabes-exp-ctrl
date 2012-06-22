%  trialType6Plot.m
%
%
%  MF Oct. 16, 2007
%

eyeidxatreachstart = nearest(Data(trial).eyetrajectorytime,Data(trial).time(1));

figure(97);
set(gcf,'position',[476   320   372   272]);
cla;
plot(sv(1,:),sv(2,:),'b');
hold on;
plot(sv(1,:)+thisshift(1),sv(2,:)+thisshift(2),'c--');
plot(rv(1,:),rv(2,:),'g');
plot(ev(1,:),ev(2,:),'r');
rectangle('position',[min(Params.wsBounds,[],1) range(Params.wsBounds,1)]);
axis equal;
drawnow;
%     ud = get(gcf,'userdata');
%     ud.sp = ud.sp + 1;
%     subplot(2,1,mod(ud.sp,2)+1);
if ~isempty(Data(trial).traj)
    plot(squeeze(Data(trial).handtrajectory(1,1,:)),squeeze(Data(trial).handtrajectory(1,2,:)),'b');
    hold on
    plot(squeeze(Data(trial).traj(1,1,:)) + thisshift(1), ...
        squeeze(Data(trial).traj(1,2,:)) + thisshift(2),'c--');
    plot(squeeze(Data(trial).traj(1,1,:)),squeeze(Data(trial).traj(1,2,:)),'g');
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

if 0
    figure(98);
    subplot(4,1,1);
    plot(Data(trial).handtrajectorytime,squeeze(Data(trial).handtrajectory(1,1,:)));
    axis tight;
    subplot(4,1,2);
    plot(Data(trial).handtrajectorytime,squeeze(Data(trial).handtrajectory(1,2,:)));
    axis tight;
    subplot(4,1,3);
    plot(Data(trial).eyetrajectorytime,squeeze(Data(trial).eyetrajectory(1,:)));
    axis tight;
    subplot(4,1,4);
    plot(Data(trial).eyetrajectorytime,squeeze(Data(trial).eyetrajectory(2,:)));
    axis tight;
end