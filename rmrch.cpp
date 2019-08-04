#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define U return
typedef float F;typedef int I;struct V{F x,y,z;V(F a,F b,F c){x=a;y=b;z=c;}V operator+(V r){U V(x+r.x,y+r.y,z+r.z);}F operator*(V r){U x*r.x+y*r.y+z*r.z;} V operator*(F r){U V(x*r,y*r,z*r);}
V operator^(V r){U V(y*r.z-z*r.y,z*r.x-x*r.z,x*r.y-y*r.z);}V operator%(F r){U V(fmax(x,r),fmax(y,r),fmax(z,r));}V operator!(){U (*this)*(1 / sqrt((*this)*(*this)));}};F E=0.01f;
F S(V p){U sqrt(p*p)-1;}F M(V o,V d){F t=0;for(I s=100;s--;){F m = S(o+d*t);if(m<0.01f)break;if(m>10.0f)break;t+=m;}U t;}
V N(V p){U !V(S(V(p.x+E,p.y,p.z))-S(V(p.x-E,p.y,p.z)),S(V(p.x,p.y+E,p.z))-S(V(p.x,p.y-E,p.z)),S(V(p.x,p.y,p.z+E))-S(V(p.x, p.y,p.z-E)));}
V P(V n, V l, V d) {U V(0.2, 0.2, 0.2) + V(0.4f, 0.0f, 0.6f)*(l*n)%0.0f+V(0.4f, 0.0f, 0.2f)*pow(fmax((n*(l*n)*2+(l*-1))*d,0),1.4f);}
I main(){printf("P6 512 512 255 ");V O(0.0f, 0.0f, 3.0f);for(I y = 512;y--;)for(I x=512;x--;){
F t=0;V direction=!(V(0.0f,0.0f,-1.0f)+V(0.0f,1.0f,0.0f)*(((F)y)-256.0)*(1.0f/512.0f)+V(1.0f,0.0f,0.0f)*(((F)x)-256.0)*(1.0f/512.0f));
V C(0.9f, 0.9f, 0.9f);if((t=M(O,direction))<10.0f){V p=O+direction*t;C=P(N(p),!(V(3.0f,3.0f,3.0f)+(p*-1)),direction*(-1.0f));}printf("%c%c%c",(I)(C.x*255.0f),(I)(C.y*255.0f),(I)(C.z*255.0f));}}
