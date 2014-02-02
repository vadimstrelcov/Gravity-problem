#include <stdio.h>
#include <math.h>
#include <unistd.h>
typedef struct vect {
    double x,y;
} vect;
typedef struct planet {
    vect r,v,a;
    double m;
} planet;
double l(planet A, planet B) {
    if ( abs(A.r.x-B.r.x)<1.0 || abs(A.r.y-B.r.y)<1.0 ) return 0.0;
    return sqrt( pow(A.r.x-B.r.x,2.0)+pow(A.r.y-B.r.y,2.0) );
}
int main() {
    usleep(3*1000*1000);
    const int n=3;
    const double G=100;
    const int MAX_X=200;
    const int MAX_Y=40;
    planet mas[n];
    int i,j;
    //initialization
    for (i=0;i<n;i++) {
        mas[i].m=1;
        mas[i].a.x=0;
        mas[i].a.y=0;
    }
    mas[0].r.x=0;
    mas[0].r.y=0;
    mas[0].v.x=0.1;
    mas[0].v.y=0;

    mas[1].r.x=MAX_X-1;
    mas[1].r.y=MAX_Y-1;
    mas[1].v.x=-0.2;
    mas[1].v.y=0;

    mas[2].r.x=(MAX_X-1)/2;
    mas[2].r.y=(MAX_Y-1)/2;
    mas[2].v.x=0;
    mas[2].v.y=-0.1;
    //algo
    const double dt=0.1;
    double Time=0;
    while (1) {
        //print
        system("clear");
        printf("%lf\n",Time);
        for (i=0;i<n;i++) {
            printf("rx=%+03.6lf ry=%.6lf vx=%.6lf vy=%.6lf\n",mas[i].r.x,mas[i].r.y,mas[i].v.x,mas[i].v.y);
        }
        //first type of print
        for (i=0;i<MAX_Y;i++) {
            for (j=0;j<MAX_X;j++) {
                int k;
                char flagin=0;
                for (k=0;k<n;k++) {
                    if ( i==(int)mas[k].r.y && j==(int)mas[k].r.x ) {
                        printf("%d",k+1);
                        flagin=1;
                        break;
                    }
                }
                if (!flagin) printf(".");
            }
            printf("\n");
        }
        //second type of print

        usleep(0.01*1000*1000);







        vect FORSE[n][n];
        for (i=0;i<n-1;i++) {
            for (j=i;j<n;j++) {
                if (j==i) {
                    FORSE[i][j].x=0;
                    FORSE[i][j].y=0;
                } else {
                    double L=l(mas[i],mas[j]);
                    double forse=G*mas[i].m*mas[j].m/pow(L,2.0);
                    FORSE[i][j].x=forse*(mas[j].r.x-mas[i].r.x)/L;
                    FORSE[i][j].y=forse*(mas[j].r.y-mas[i].r.y)/L;

                    FORSE[j][i].x=-FORSE[i][j].x;
                    FORSE[j][i].y=-FORSE[i][j].y;
                }
            }
        }
        for (i=0;i<n;i++) {
            vect Forse;
            Forse.x=0;
            Forse.y=0;
            for (j=0;j<n;j++) {
                Forse.x+=FORSE[i][j].x;
                Forse.y+=FORSE[i][j].y;
            }
            mas[i].a.x=Forse.x/mas[i].m;
            mas[i].a.y=Forse.y/mas[i].m;
        }
        planet n_mas[n];
        for (i=0;i<n;i++) {
            n_mas[i].v.x=mas[i].v.x+mas[i].a.x*dt;
            n_mas[i].v.y=mas[i].v.y+mas[i].a.y*dt;

            n_mas[i].r.x=mas[i].r.x+mas[i].v.x*dt+mas[i].a.x*dt*dt/2.0;
            n_mas[i].r.y=mas[i].r.y+mas[i].v.y*dt+mas[i].a.y*dt*dt/2.0;
        }
        for (i=0;i<n;i++) {
            mas[i].v.x=n_mas[i].v.x;
            mas[i].v.y=n_mas[i].v.y;

            mas[i].r.x=n_mas[i].r.x;
            mas[i].r.y=n_mas[i].r.y;
        }
        if (Time/dt==5000) break;
        Time+=dt;
    }
    return 0;
}















