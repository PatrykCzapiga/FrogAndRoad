#include <allegro.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
void init(void){
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    set_color_depth( 32 );
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );}


int main()
{
    init();
    PALETTE palette;

    int car_x[11]={-64,640,256,448,64,256,448,640,-64,256,448}, car_y[3]={461,396,331};
    int log_x[6]={-64,256,64,192,320,640}, log_y[3]={201, 136, 71};
    const char * icar[4]={"images/car1.bmp","images/car2.bmp","images/car3.bmp","images/car4.bmp"};
    const char * icarl[4]={"images/car1l.bmp","images/car2l.bmp","images/car3l.bmp","images/car4l.bmp"};
    BITMAP * car[11] = {NULL};
    BITMAP * log[6] = {NULL};
    BITMAP * bufor = NULL;
    BITMAP * frog = NULL;
    BITMAP * tlo = NULL;
    int kolor;
    frog = load_bmp( "images/frog.bmp", palette );
    tlo = load_bmp( "images/tlo.bmp", palette );
    int poziom=1;

    while(poziom<7)
    {
        for(int i=0; i!=11;i++)             //Losowanie koloru aut
    {
    kolor=rand()%4;
        if(i<8)
        car[i] = load_bmp( icar[kolor], palette);
        else
        car[i] = load_bmp( icarl[kolor], palette);
    }

    for(int i=0; i!=6; i++) log[i] = load_bmp ( "images/log.bmp", palette );   //Ladowanie tekstur klod

    bufor = create_bitmap( 800, 600 );
    int k1=0;
    int k2=0;
    int frog_x=350, frog_y=526;
    while (true)            //Petla glowna
    {
            if( (key[ KEY_LEFT ])&&(frog_x>16) )
            {
                 frog_x-=5;
                 k1=0;
                 k2=0;
            }
            if( (key[ KEY_RIGHT ])&&(frog_x<704) )
            {
                frog_x+=5;
                k1=0;
                k2=0;
            }
            if( (key[ KEY_UP ])&&(frog_y>16))
            {
             k1++;
             if(k1==6)
             {
                 frog_y-=65;
                 k1=0;
                 k2=0;
             }

            }
            if( (key[ KEY_DOWN ])&&(frog_y<523))
            {
                k2++;
                if(k2==6)
                {
                     frog_y+=65;
                     k2=0;
                     k1=0;
                }

            }
            if( (key[ KEY_ESC ]))
                {
                    destroy_bitmap( tlo );
                    for(int i=0; i<11; i++) destroy_bitmap ( car[i] );

                    destroy_bitmap ( frog );
                    destroy_bitmap ( bufor );
                    allegro_exit();
                    return 0;
               }

            rest(10);

            masked_blit( tlo, bufor, 0,0, 0,0, 800, 600);

            //ruch klod
            for(int i=0; i<6; i++)
            {
                if(i<2)
                {
                if(log_x[i]>900) log_x[i]=-64;
                log_x[i]+=poziom;
                masked_blit( log[i], bufor, 0,0, log_x[i], log_y[0], log[i]->w, log[i]->h );
                }

                if((i>1)&&(i<4))
                {
                if(log_x[i]>900) log_x[i]=-64;
                log_x[i]+=poziom;
                masked_blit( log[i], bufor, 0,0, log_x[i], log_y[2], log[i]->w, log[i]->h );
                }

                if(i>3)
                {
                if(log_x[i]<-100) log_x[i]=900;
                log_x[i]-=poziom;
                masked_blit( log[i], bufor, 0,0, log_x[i], log_y[1], log[i]->w, log[i]->h );
                }
            }
            //ruch aut
            for(int i=0; i<11; i++)
            {
                if(i<4)
                {
                if(car_x[i]>900) car_x[i]=-128;
                car_x[i]+=poziom;
                masked_blit( car[i], bufor, 0,0, car_x[i], car_y[0], car[i]->w, car[i]->h );
                }

                if((i>3)&&(i<8))
                {
                if(car_x[i]>900) car_x[i]=-128;
                car_x[i]+=poziom;
                masked_blit( car[i], bufor, 0,0, car_x[i], car_y[2], car[i]->w, car[i]->h );
                }

                if(i>7)
                {
                if(car_x[i]<-100) car_x[i]=900;
                car_x[i]-=poziom;
                masked_blit( car[i], bufor, 0,0, car_x[i], car_y[1], car[i]->w, car[i]->h );
                }
            }

            masked_blit( frog, bufor, 0,0, frog_x, frog_y, frog->w, frog->h );
            masked_blit( bufor, screen, 0, 0, 0, 0, 800,600);
            bool kolizja=false;
            for(int i=0; i<11; i++)
            {
                if(i<4)
                {
                    if( (frog_y==car_y[0])&&(frog_x>car_x[i])&&(frog_x<(car_x[i]+car[i]->w)))
                    kolizja=true;
                }

                if((i>3)&&(i<8))
                {
                    if( (frog_y==car_y[2])&&(frog_x>car_x[i])&&(frog_x<(car_x[i]+car[i]->w)))
                    kolizja=true;
                }

                if(i>7)
                {
                    if( (frog_y==car_y[1])&&(frog_x>car_x[i])&&(frog_x<(car_x[i]+car[i]->w)))
                    kolizja=true;
                }
            }


                    if((frog_y==log_y[0])&& (((frog_x>log_x[0]) && (frog_x<(log_x[0]+log[0]->w))) || ((frog_x>log_x[1]) && (frog_x<(log_x[1]+log[1]->w)))  ))
                    kolizja=false;
                    else if(frog_y==log_y[0]) kolizja=true;


                    if((frog_y==log_y[1])&& (((frog_x>log_x[4])&& (frog_x<(log_x[4]+log[4]->w))) || ((frog_x>log_x[5]) && (frog_x<(log_x[5]+log[5]->w)))  ))
                    kolizja=false;
                    else if(frog_y==log_y[1]) kolizja=true;

                    if((frog_y==log_y[2])&& (((frog_x>log_x[2]) && (frog_x<(log_x[2]+log[2]->w))) || ((frog_x>log_x[3]) && (frog_x<(log_x[3]+log[3]->w)))  ))
                    kolizja=false;
                    else if(frog_y==log_y[2]) kolizja=true;


            if(kolizja==true)
            {
            break;
            }

            if(frog_y==6)
            {
            poziom++;
            break;
            }


    }


    }
    destroy_bitmap( tlo );
    for(int i=0; i<11; i++) destroy_bitmap ( car[i] );
    destroy_bitmap ( frog );
    destroy_bitmap ( bufor );
    allegro_exit();
    cout << "WYGRALES GRATULACJE" << endl;
    system("pause");
    return 0;
}
END_OF_MAIN();
