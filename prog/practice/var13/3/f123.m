clear

xmin=0;
xmax=2*pi;
step=pi/10;
x=xmin:step:xmax;
clear('step');


y1=x.*sin(x);
y2=sin(x)+x.^2;
y3=sin(x)+x;

ymin=min([min(y1),min(y2), min(y3)])
ymax=max([max(y1),max(y2), max(y3)])

plot(x,y1,'b*-', x, y2,'rd-.', x, y3,'g+--');
h=legend('x * sin(x)','sin(x) + x^2','sin(x) + x',0);
grid on;
axis ( [xmin xmax ymin ymax])
set(gca,'FontName','Arial Cyr');
xlabel('X', 'Fontsize', 16); ylabel('Y', 'Fontsize', 16);
title('Functions', 'Fontsize', 16);