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
#define epsilon 0.001
typedef float f;
typedef int i;

float march_ray(vector o, vector d){
    f t=0;
    for(i s=100;s--;){f m = signed_distance(o+d*t);t+=m;if(m<epsilon)break;if(m>far)break;}
    return t;}


int main()
{
    printf("P6 512 512 255 "); // PPM header

    vector origin (0.0f, 0.0f, 3.0f);
    vector forward(0.0f, 0.0f, -1.0f);
    vector up     (0.0f, 1.0f, 0.0f);
    vector horiz  (1.0f, 0.0f,0.0f);
    
    for (int y = 512; y--;){
    for (int x = 512; x--;)
    {
        float a = (((float)y) - 256.0)*(1.0f/512.0f);
        float b = (((float)x) - 256.0)*(1.0f/512.0f);
        vector direction = forward + up*a + horiz*b;
        vector color(0, 0, 0);
        if (march_ray(origin, direction) < far) color.x = 200;
        //printf("%f %f %f, %f %f, %f\n", direction.x, direction.y, direction.z, a, b, color.x);
        printf("%c%c%c",(int)color.x, (int)color.y, (int)color.z); 
    }}
}
