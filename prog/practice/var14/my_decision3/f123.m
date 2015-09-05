clear
x=0:0.1*pi:2*pi;
y1=sin(x) + cos(x);
y2=cos(x).*x.^2;
y3=log(x).*x.^2;
xmin=0;
xmax=2*pi;
ymin=min([min(y1),min(y2), min(y3)])
ymax=max([max(y1),max(y2), max(y3)])

plot(x,y1,'b*-', x, y2,'rd-.', x, y3,'g+--');
h=legend('sin(x) + cos(x)','cos(x).*x.^2','log(x).*x.^2',0);
grid on;
axis ( [xmin xmax ymin ymax])
set(gca,'FontName','Arial Cyr');
xlabel('X', 'Fontsize', 16); ylabel('Y', 'Fontsize', 16); 
title('Функции', 'Fontsize', 16);
