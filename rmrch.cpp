#define DEBUG 0
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define U return

#define far 10.0f
#define epsilon 0.01f
#define E epsilon


typedef float f;
typedef int i;

struct vector {
    float x, y, z;
    vector(){}
    vector(float a, float b, float c){x = a; y = b; z = c;}
    vector operator+(vector r){U vector(x+r.x, y+r.y, z+r.z);} // vector add
    float operator*(vector r){U x * r.x + y * r.y + z * r.z;} // vector dot
    vector operator*(f r){U vector(x*r, y*r, z*r);} //scalar multiply
    vector operator^(vector r){U vector(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.z);} // vector cross
    vector operator!(){U this->normalize();}
    vector operator%(f r){U vector(fmax(x,r),fmax(y,r),fmax(z,r));}
    vector normalize(){U (*this)*(1 / sqrt((*this)*(*this)));}};
typedef vector v;

f S(v p){U sqrt(p*p)-1;}
f M(v o,v d){f t=0;for(i s=100;s--;){f m = S(o+d*t);if(m<E)break;if(m>far)break;t+=m;}U t;}
v N(v p){U !v(S(v(p.x+E,p.y,p.z))-S(v(p.x-E,p.y,p.z)),S(v(p.x,p.y+E,p.z))-S(v(p.x,p.y-E,p.z)),S(v(p.x,p.y,p.z+E))-S(v(p.x, p.y,p.z-E)));}
v P(v n, v l, v d) {U v(0.2, 0.2, 0.2) + v(0.4f, 0.0f, 0.6f)*(l*n)%0.0f+v(0.4f, 0.0f, 0.2f)*pow(fmax((n*(l*n)*2+(l*-1))*d,0),1.4f);}

int main()
{
    printf("P6 512 512 255 "); // PPM header

    vector origin (0.0f, 0.0f, 3.0f);
    vector forward(0.0f, 0.0f, -1.0f);
    vector up     (0.0f, 1.0f, 0.0f);
    vector horiz  (1.0f, 0.0f,0.0f);
    vector light  (3.0f, 3.0f, 3.0f);
    
    for (int y = 512; y--;)
    for (int x = 512; x--;){
        f a = (((float)y) - 256.0)*(1.0f/512.0f), b = (((float)x) - 256.0)*(1.0f/512.0f);
        f t;
        vector direction = (forward + up*a + horiz*b).normalize();
        vector color(0.9f, 0.9f, 0.9f);
        if ((t=M(origin, direction)) < far) { 
            v p = origin+direction*t; 
            color = P(N(p), !(light+(p*-1)), direction * (-1.0f));
        }
        if (!DEBUG) printf("%c%c%c",(int)(color.x*255.0f), (int)(color.y*255.0f), (int)(color.z*255.0f)); 
    }
}
