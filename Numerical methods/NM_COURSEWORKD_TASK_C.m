clear all;
clc;
close all;

%% functions U(x,y,x)=xexp(y)+z+1, V(x,y,z)=yz-x^3-pi and f(x,y,x)=xy^2z-15
maxIT=1000;
tol=1e-8;
x=1; y=1; z=1;
err=sum(abs(x*(exp(y))+z+1)+abs(((y*z)-(x^3))-pi)+abs((x*(y^2)*z)-3.5));
i=1;
while err(i)>tol & i<maxIT
    J(1,1)=exp(y(i));
    J(1,2)=x(i)*exp(y(i));
    J(1,3)=1;
    J(2,1)=-3*(x(i)^2);
    J(2,2)=z(i);
    J(2,3)=y(i);
    J(3,1)=z(i)*(y(i)^2);
    J(3,2)=2*y(i)*z(i)*x(i);
    J(3,3)=(y(i)^2)*x(i);
    F(1,1)=(x(i)*exp(y(i)))+z(i)+1;
    F(2,1)=(y(i)*z(i))-(x(i)^3)-pi;
    F(3,1)=(x(i)*(y(i)^2)*z(i))-3.9;
    X(1,1)=x(i); 
    X(2,1)=y(i);
    X(3,1)=z(i);
    X=J\(-F+J*X);
    x(i+1)=X(1);
    y(i+1)=X(2);
    z(i+1)=X(3);
    F(1)=x(i+1)*exp(y(i+1))+z(i+1)+1;
    F(2)=(y(i+1)*z(i+1))-(x(i+1)^3)-pi;
    F(3)=(x(i+1)*(y(i+1)^2)*z(i+1))-3.9;
    err(i+1)=sum(abs(F));
    i=i+1;
end
figure('color','w','units','centimeters','position',[5 5 7.5 7]);
plot(x,'o-');
hold on;
plot(y,'o-');
hold on;
plot(z,'o-');
xlabel('Iterations');
ylabel('Soltuions');
legend('x','y','z')
figure('color','w');
semilogy(err,'o-');
grid on
xlabel('Iterations');
ylabel('Error: |F(X)|')
total_iterations=i(end)




