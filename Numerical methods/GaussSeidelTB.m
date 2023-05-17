function [x,m,res]=GaussSeidelTB(x,A,B,maxit,toll) %list of outputs=name of function(List of inputs)
res=sum(abs(B-A*x))/sum(abs(diag(A).*x));
m=0;
while (res>toll & m<maxit)
    m=m+1;
    for i=1:numel(x)
    x(i)=B(i)/A(i,i)-A(i,1:i-1)/A(i,i)*x(1:i-1)-A(i,i+1:end)/A(i,i)*x(i+1:end);
    end
    res(m)=sum(abs(B-A*x))/sum(abs(diag(A).*x));
end
 