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
%% Making the mesh
xO=linspace(0,L,n);
dx=L/(n-1);
Dx=dx; %xO: nodes positions
DxB=Dx/2;
TaB=(Sc*DxB+qa);
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
%% Gauss-seidel method
maxit=30000;
toll=1e-12;
T0=(Sc*DxB+qa)*ones(n,1);
figure
%% omega while loop
omega=1.1;
while omega<2.1
    subplot(1,2,1);
    [T_GaussSeidelB4,nIterB4,residual_GaussSeidelB4]=GaussSeidelTB2(T0,A,B,maxit,toll,omega);
    txt=['omega=',num2str(omega)];
    plot(xO,T_GaussSeidelB4,'DisplayName',txt)
    hold on
    subplot(1,2,2);
    semilogy(residual_GaussSeidelB4,'DisplayName',txt)
    omega=omega+0.1;
    hold on;
end

%% Comparison with theoretical solution
mul1=sqrt(abs(Sp)/lambda);
mul2=-sqrt(abs(Sp)/lambda);
C1=(Tb+((qa/(lambda*mul2))*(exp(mul2*L)))+(Sc/Sp))/((exp(mul1*L))-((mul1/mul2)*(exp(mul2*L))));
C2=((-qa/lambda)-(C1*mul1))/mul2;
Ttheo=(C1*(exp(mul1*xO)))+(C2*(exp(mul2*xO)))-(Sc/Sp);
%% plots
subplot(1,2,1);
plot(xO,Ttheo,'k-', 'DisplayName','theoretical')
grid on;
ylabel('Temp [K]');
xlabel('x[m]');
legend show 
error_GaussSeidel=mean(abs(T_GaussSeidelB4-Ttheo'))
residual_GaussSeidelB4=residual_GaussSeidelB4(end)
%% Plot of residuals against iterations
subplot(1,2,2);
grid on;
ylabel('residuals');
xlabel('iterations');
legend show




