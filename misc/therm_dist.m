clear
clc

n = 10000;
d = zeros(n,1);
for ii = 1:n
    d(ii) = (randi(201)-1) * (randi(201)-1) / 100;
end

figure(1);
clf
hold on
hist(d,0:400);
hold off