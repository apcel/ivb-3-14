x=-20:0.2:20; y=-20:0.2:20; 
[X,Y]=meshgrid(x,y); 
r = (X.^2 + Y.^2).^0.5
Z= r + cos(r)./r.^2
mesh(X,Y,Z)
title('r + cos(r)/(r^2)', 'Fontsize', 16);
