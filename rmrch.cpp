#define DEBUG 0
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define U return

#define far 10.0f
#define epsilon 0.01f
#define E epsilon


typedef float F;
typedef int I;

struct vector {
    float x, y, z;
    vector(){}
    vector(float a, float b, float c){x = a; y = b; z = c;}
    vector operator+(vector r){U vector(x+r.x, y+r.y, z+r.z);} // vector add
    float operator*(vector r){U x * r.x + y * r.y + z * r.z;} // vector dot
    vector operator*(F r){U vector(x*r, y*r, z*r);} //scalar multiply
    vector operator^(vector r){U vector(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.z);} // vector cross
    vector operator!(){U this->normalize();}
    vector operator%(F r){U vector(fmax(x,r),fmax(y,r),fmax(z,r));}
    vector normalize(){U (*this)*(1 / sqrt((*this)*(*this)));}};
typedef vector v;

F S(v p){U sqrt(p*p)-1;}
I M(v o,v d,F&t)
{
    for(I s=100;s--;)
    {
        F m = S(o+d*t);
        if(m<E)U 2;
        if(m>far)break;
        t+=m;
    }
    t=-o.z/d.z;
    U (0.001f<d.y);
}
v N(v p){U !v(
        S(v(p.x+E,p.y,p.z))-S(v(p.x-E,p.y,p.z)),
        S(v(p.x,p.y+E,p.z))-S(v(p.x,p.y-E,p.z)),
        S(v(p.x,p.y,p.z+E))-S(v(p.x, p.y,p.z-E)));}

vector phong(v n, v l, v d)
{
    static F a = 1.4f; static v ka(0.2, 0.2, 0.2), kd(0.4f, 0.0f, 0.6f), ks(0.4f, 0.0f, 0.2f);
    vector reflection = n*(l*n)*2+(l*-1);
    vector one (1.0f, 1.0f, 1.0f);

    vector ambient = ka;
    vector diffuse = kd*(l*n)%0.0f;
    vector refl = ks*pow(fmax(reflection*d,0),a);

    vector color = ambient + diffuse + refl;
    return color;
}

int main()
{
    printf("P6 512 512 255 "); // PPM header

    vector origin (0.0f, 0.0f, 3.0f);
    vector forward(0.0f, 0.0f, -1.0f);
    vector up     (0.0f, 1.f, 0.f);
    vector horiz  (1.f, 0.f,0.0f);
    vector light  (3.0f, 3.0f, 3.0f);
    
    for (int y = 512; y--;)
    for (int x = 512; x--;){
        F a = (((float)y) - 256.0)*(1.0f/512.0f), b = (((float)x) - 256.0)*(1.0f/512.0f);
        F t=0; I i;
        vector direction = (forward + up*a + horiz*b).normalize();
        vector color(0.9f, 0.9f, 0.9f);
        i=M(origin, direction,t);
        v p = origin+direction*t; 
        F P = -origin.z/direction.z;
        if (i==2) { 
            color = phong(N(p), !(light+(p*-1)), direction * (-1.0f));
        } else if (i&1)
            color = v(0.1f, 0.4f, 0.8f) * (pow(1-direction.y, 4));
        else 
            color = v(0.7f,0.7f,0.7f)*
                    ((I)(ceil(p.x*4)+
                         ceil(p.y*4)) 
                     & 1);
        if (!DEBUG) printf("%c%c%c",(int)(color.x*255.0f), (int)(color.y*255.0f), (int)(color.z*255.0f)); 
    }
}
