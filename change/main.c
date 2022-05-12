#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>



void initialisation()
{
    allegro_init();
    install_mouse(); // souris
    install_keyboard(); // clavier
    set_color_depth(desktop_color_depth());

   if (set_gfx_mode(GFX_AUTODETECT,1280,720,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}


void tour_joueur_alea (int nb_joueur, t_joueur*, BITMAP* buffer )
{
    int i = 0;
    i = rand()%(nb_joueur-0+1)+0;    //[0,nb_joueurs]
    textprintf_ex(buffer,font,405,314, makecol(255,255,255) ,-1,"joueur %d :", i); // pour verif
    textprintf_ex(buffer,font,405,325, makecol(255,255,255) ,-1," c'est %s qui commence !", joueur[i].pseudo); // nom du joueur qui commence

}




void prenom(int nb_joueur, BITMAP* buffer,  t_joueur joueur[], BITMAP* fond)
{
    int x = 498;
    int touche;
    char carac;
    int y = 314;
    int stop = 0;
    int  poscarac=0;
    int place= 0;
    int nb = 0;
    int pos = 445;

    for(int i = 0; i < nb_joueur; i++)
    {
        fflush(stdin);
        if(stop != nb_joueur)
        {
             stop = 0;
        }
        else
            stop = 1;

        poscarac = 0;
        textprintf_ex(buffer,font,405,y, makecol(255,255,255) ,-1,"joueur %d :", i+1);


        /// AFFICHAGE DES LETTRES QUE L ON TAPE AU CLAVIER
        while (!stop)
        {
            textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
            if (keypressed())
            {

                touche=readkey();
                carac = (char)touche;

                // afficher le caractère à une position x croissante
                if( carac != '\r' && !key[KEY_BACKSPACE] )
                {
                    textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0),"%c",carac);
                    joueur[i].pseudo[place] = carac;
                    poscarac = poscarac+8;
                }

                if (key[KEY_BACKSPACE] && x+poscarac >= 506)
                {
                    if(x+poscarac == 506)
                    {
                        poscarac=poscarac-8;
                        joueur[i].pseudo[place] = ' ';
                        textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                        place = place-2;
                    }
                    else
                    {
                        nb = nb +1;
                        poscarac=poscarac-8;
                        joueur[i].pseudo[place-1] = ' ';
                        textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                        place = place-2;
                    }
                }

            /// RETOUR CHARIOT : ON VA A LA LIGNE
                if (carac=='\r')
                {
                    y+=10;

                    stop=1;
                }
                place = place+1;

                }
            if (  mouse_b&1 && mouse_x>= 553 && mouse_x <= 729 && mouse_y >= 540 && mouse_y <= 591)
            {
                blit(fond, buffer, 0,0,0,0, 1280, 720);

            }

                blit(buffer, screen, 0, 0, 0 , 0, 1280, 720);
            }

        textprintf_ex(buffer,font,405,pos, makecol(255,255,255) ,-1,"%s", joueur[i].pseudo); // pour verifier
        //textprintf_ex(buffer,font,460,pos, makecol(255,255,255) ,-1,"%d", i); // pour verifier
        pos += 10; // pour verifier
        blit(buffer, screen, 0, 0, 0 , 0, 1280, 720);

    }


}


void menu_principal( BITMAP *buffer, BITMAP *accueil)
{
        blit(accueil,buffer,0,0,0,0,1280,720);
        textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        textprintf_ex(buffer,font,600,258, makecol(0,0,0) ,-1,"STANDARD");
        textprintf_ex(buffer,font,600, 377, makecol(0,0,0),-1,"DOUBLE");
        textprintf_ex(buffer,font,600,486, makecol(0,0,0),-1,"CREDITS");
        textprintf_ex(buffer,font,600, 597, makecol(0,0,0),-1,"QUITTER");


         if ( mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 223 && mouse_y <= 300)
        {
            textprintf_ex(buffer,font,600,258, makecol(255,255,255) ,-1,"STANDARD");
        }

        if(  mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 448 && mouse_y <= 527 )
        {
            textprintf_ex(buffer,font,600,486, makecol(255,255,255),-1,"CREDITS");
        }

         if(  mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 338 && mouse_y <= 411 )
        {
             textprintf_ex(buffer,font,600, 377, makecol(255,255,255),-1,"DOUBLE");
        }

        if( mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 563 && mouse_y <= 627)
        {
            textprintf_ex(buffer,font,600, 597, makecol(255,255,255),-1,"QUITTER");
        }
}


int main(int argc, char *argv[])
{
    int fin;
    int ok;
    int nb_joueur = 0;
    BITMAP *buffer;
    BITMAP *fond;
    BITMAP *creators;
    BITMAP *nbjoueur;
    BITMAP *nom_joueurs;
    BITMAP *accueil;
    t_joueur joueur[nb_joueur];
     srand(time(NULL));


    initialisation();
    // pour voir le pointeur de la souris

    // init. variable de sortie boucle interactive
    fin=0;

    buffer=load_bitmap("accueil.bmp",NULL);
    fond = load_bitmap("fond.bmp", NULL);
    creators = load_bitmap("creators.bmp", NULL);
    nbjoueur =load_bitmap("buffer_nb_joueurs.bmp", NULL);
    nom_joueurs =load_bitmap("noms.bmp", NULL);
    accueil = load_bitmap("accueil.bmp",NULL);


    if (!buffer || !fond || !creators || !nbjoueur || !nom_joueurs)
    {
        allegro_message("pas pu trouver/charger image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    ok = 0;
    clear_bitmap(buffer);



    // Boucle interactive
    while (!fin)
    {

        clear_bitmap(buffer);
        textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        menu_principal(buffer, accueil);


        /// si on appui sur standard
        if (  mouse_b&1 && mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 223 && mouse_y <= 300)
        {

            ok = 0;
            clear_bitmap(buffer);
            blit(nbjoueur,buffer,0,0,0,0,1280,720);


            while(ok!=1)
           {
            textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
            rectfill(buffer, 735, 205 , 758, 236 ,makecol(0,0,0));
            textprintf_ex(buffer,font, 744,218,makecol(255,255,255),-1,"%d",nb_joueur);

                if ( mouse_b&1 && mouse_x>=460 && mouse_x <= 563 && mouse_y >= 330&& mouse_y <= 434 && nb_joueur <= 3) // on ajoute dans les paramètres le blindage du nb de joueur
                {

                    nb_joueur = nb_joueur+1;
                    rectfill(buffer, 735, 205 , 758, 236 ,makecol(0,0,0));
                    usleep(300000);


                }

                if (  mouse_b&1 && mouse_x>=754 && mouse_x <= 870 && mouse_y >= 331 && mouse_y <= 436 && nb_joueur > 0 )
                {

                    nb_joueur = nb_joueur -1;
                    rectfill(buffer, 735, 205 , 758, 236 ,makecol(0,0,0));
                    usleep(300000);

                }
                if ( mouse_b&1 && mouse_x>=458 && mouse_x <= 833 && mouse_y >= 573 && mouse_y <= 654 && nb_joueur >= 2)
                {

                    ok = 1;
                    clear_bitmap(buffer);
                    blit(nom_joueurs,buffer,0,0,0,0,1280,720);
                    textprintf_ex(buffer,font,500,270, makecol(255,255,255) ,-1, " Veuillez entrez vos pseudos :");
                    while(!key[KEY_BACKSPACE])
                    {

                      prenom(nb_joueur, buffer, joueur, fond);

                    }

                    blit(buffer, screen, 0, 0, 0 , 0, 1280, 720);
                }
                if(key[KEY_ESC])
                {
                    ok =1;
                }

             blit(buffer, screen, 0, 0, 0 , 0, 1280, 720);

           }


        }


         /// si on appuie sur double
        if(mouse_b&1 && mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 338 && mouse_y <= 411 )
        {
                while(!key[KEY_ESC])
                {
                blit(fond,buffer,0,0,0,0,1280,720);
                blit(buffer, screen, 0, 0, 0 , 0, 1280, 720);
                }

        }



        /// si on appuie sur CREDITS
        if( mouse_b&1 && mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 448 && mouse_y <= 527 )
        {
            while(!key[KEY_ESC])
            {
                blit(creators,buffer,0,0,0,0,1280,720);
                blit(buffer, screen, 0, 0, 0 , 0, 1280, 720);
            }
        }


        ///si on appuie sur quitter
        if(mouse_b&1 &&  mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 563 && mouse_y <= 627 )
        {
            blit(fond,buffer,0,0,0,0,1280,720);
            fin = 1;
            usleep(300000);
        }
        show_mouse(buffer);
        blit(buffer, screen, 0, 0, 0 , 0, 1280, 720);


        }

    destroy_bitmap(buffer);
    destroy_bitmap(fond);
    destroy_bitmap(creators);
    destroy_bitmap(nbjoueur);


    return 0;
}
END_OF_MAIN();
