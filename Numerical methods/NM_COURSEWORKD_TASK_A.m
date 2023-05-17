clear all;
clc;
close all;

%% Physical Parameters
L=0.5;
lambda=100;
Tb=350;
Sc=10;
Sp=-120; %Source term S=Sc +SpT
qa=5000;

%% Numerical Parametres
n=51;
%% Mkaing the mesh
xO=linspace(0,L,n);
dx=L/(n-1);
Dx=dx; %xO: nodes positions
DxB=Dx/2;
%% Creating the matrix
A=zeros(n,n);
B=zeros(n,1);
A(1,1)=lambda/dx-Sp*DxB;
A(1,2)=-lambda/dx;
B(1)=Sc*DxB+qa;
A(n,n)=1;
B(n)=Tb;
for i=2:n-1
    A(i,i-1)=-lambda/dx;
    A(i,i)=2*lambda/dx-Sp*Dx;
    A(i,i+1)=-lambda/dx;
    B(i)=Sc*Dx;
end
%% Matlab backslash
T=A\B;
figure
plot(xO,T,'rs');
grid on;
xlabel('x [m]');
ylabel('T [K]');
hold on
%% Comparison with theoretical solution
mul1=sqrt(abs(Sp)/lambda);
mul2=-sqrt(abs(Sp)/lambda);
C1=(Tb+((qa/(lambda*mul2))*(exp(mul2*L)))+(Sc/Sp))/((exp(mul1*L))-((mul1/mul2)*(exp(mul2*L))));
C2=((-qa/lambda)-(C1*mul1))/(mul2);
Ttheo=(C1*exp(mul1*xO))+(C2*exp(mul2*xO))-(Sc/Sp);
plot(xO,Ttheo,'k-');
legend('Backslash','Exact');
error_backslash=mean(abs(T-Ttheo')); %Need to transpose Tteo
%% Check of residuals
residual_backslash=sum(abs(B-A*T))/sum(abs(diag(A).*T)); %Defined as [B-A*T]/[diag(A).T]
%% Checking for convergence order with different values of n
n=[ 11 21 51 101 201 501 1001];
for j=1:numel(n)
    xO=linspace(0,L,n(j));
    dx=L/(n(j)-1);
    Dx=dx;
    DxB=Dx/2;
    A=zeros(n(j),n(j));
    B=zeros(n(j),1);
    A(1,1)=lambda/dx-Sp*DxB;
    A(1,2)=-lambda/dx;
    B(1)=Sc*DxB+qa;
    A(n(j),n(j))=1;
    B(n(j))=Tb;
    for i=2:n(j)-1
        A(i,i-1)=-lambda/dx;
        A(i,i)=2*lambda/dx-Sp*Dx;
        A(i,i+1)=-lambda/dx;
        B(i)=Sc*Dx;
    end
    T=A\B;
    figure;
    plot(xO,T,'rs');
    grid on;
    xlabel('x [m]');
    ylabel('T [K]');
    hold on
    %theoretical solution
    Ttheo=(C1*(exp(mul1*xO)))+(C2*(exp(mul2*xO)))-(Sc/Sp);
    plot(xO,Ttheo,'k-');
    legend('Backslash','Exact'); 
    title(['n=',num2str(n(j))]);
    error(j)=mean(abs(T-Ttheo'));
end
dx=L./(n-1);
figure
loglog(dx,error,'o-');
grid on;
xlabel('\deltax [m]');
ylabel('mean(|T-T_{theo}|) [K]');


    




