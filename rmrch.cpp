#define DEBUG 0

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct vector
{
    float x, y, z;
    vector(){}
    vector(float a, float b, float c){x = a; y = b; z = c;}
    vector operator+(vector r){return vector(x+r.x, y+r.y, z+r.z);} // vector add
    float operator*(vector r){return x * r.x + y * r.y + z * r.z;} // vector dot
    vector operator*(float r){return vector(x*r, y*r, z*r);} //scalar multiply
    vector operator^(vector r){return vector(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.z);} // vector cross
    vector normalize(){return (*this)*(1 / sqrt((*this)*(*this)));}
};

float signed_distance(vector p)
{
    return sqrt(p*p)-1;
}

#define far 10.0f
#define epsilon 0.001f


typedef float f;
typedef int i;
typedef vector v;

float march_ray(v o,v d){
    f t=0;
    for(i s=100;s--;){f m = signed_distance(o+d*t);t+=m;if(m<epsilon)break;if(m>far)break;}
    return t;
}

vector normal(vector p){
    return vector(signed_distance(v(p.x+epsilon, p.y, p.z)) - signed_distance(v(p.x-epsilon, p.y, p.z)),
                   signed_distance(v(p.x, p.y+epsilon, p.z)) - signed_distance(v(p.x, p.y - epsilon, p.z)),
                   signed_distance(v(p.x, p.y, p.z+epsilon)) - signed_distance(v(p.x, p.y, p.z-epsilon))).normalize();}

vector phong(v n, v l, v d)
{
    static float a = 1.3f; static v ka(0.1, 0.1, 0.1), kd(0.3f, 0.0f, 0.1f), ks(0.5f, 0.8f, 0.9f);
    vector reflection = n*(l*n)*2+(l*-1);
    vector one (1.0f, 1.0f, 1.0f);

    vector ambient = ka;
    vector diffuse = kd*(l*n);
    vector refl = ks *(pow(abs(reflection*d), a));
    if (DEBUG) printf("%f %f %f | %f\n", reflection.x, reflection.y, reflection.z, reflection*d);
    if (DEBUG) printf("%f %f %f, %f %f %f, %f %f %f\n", ambient.x, ambient.y, ambient.z, diffuse.x, diffuse.y, diffuse.z, refl.x, refl.y, refl.z);
    vector color = ambient + diffuse + refl;
    if (DEBUG) printf("%f %f %f\n", color.x, color.y, color.z);

    return color;
}
                


int main()
{
    printf("P6 512 512 255 "); // PPM header

    vector origin (0.0f, 0.0f, 3.0f);
    vector forward(0.0f, 0.0f, -1.0f);
    vector up     (0.0f, 1.0f, 0.0f);
    vector horiz  (1.0f, 0.0f,0.0f);
    vector light  (0.0f, 2.0f, 2.0f);
    
    for (int y = 512; y--;)
    for (int x = 512; x--;){
        float a = (((float)y) - 256.0)*(1.0f/512.0f);
        float b = (((float)x) - 256.0)*(1.0f/512.0f);
        f t;
        vector direction = (forward + up*a + horiz*b).normalize();
        vector color(0.9f, 0.9f, 0.9f);
        if ((t=march_ray(origin, direction)) < far) { 
            v p = origin+direction*t; 
            color = phong(normal(p), (light+(p*-1)).normalize(), direction * (-1.0f));
        }
        if (!DEBUG) printf("%c%c%c",(int)(color.x*255.0f), (int)(color.y*255.0f), (int)(color.z*255.0f)); 
    }
}
