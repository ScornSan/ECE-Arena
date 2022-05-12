#include "../structures.h"
#include "../prototypes.h"


void affichage_son(BITMAP *buffer, BITMAP *cursor, SAMPLE* s, int* clic )
{

    if(mouse_b&1 && mouse_x>= 0 && mouse_x <= 65 && mouse_y >= 0&& mouse_y <= 50 && !*clic)
    {
        rest(100);
        *clic = 1;
        stop_sample(s);

    }
    if (mouse_b&1 && mouse_x>= 0 && mouse_x <= 65 && mouse_y >= 0&& mouse_y <= 50 && *clic)
    {
        rest(100);
        *clic = 0;
        play_sample(s, 255, 128, 1000, 1);

    }
}


void prenom(int *nb_joueur, BITMAP* buffer, char pseudo[4][20], BITMAP* fond, BITMAP *cursor, int i, int y)
{
    int x = 498;
    int touche;
    char carac;
    //int y = 314;
    int stop = 0;
    int  poscarac=0;
    int place= 0;
    int nb = 0;

    fflush(stdin);
    if(stop != *nb_joueur)
        stop = 0;
    else
        stop = 1;

    poscarac = 0;
    textprintf_ex(buffer,font,405,y, makecol(255,255,255),-1,"joueur %d :", i+1);


    /// AFFICHAGE DES LETTRES QUE L'ON TAPE AU CLAVIER
    while (stop != 1)
    {
        //display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        if (keypressed())
        {

            touche=readkey();
            carac = (char)touche;

            // afficher le caract�re � une position x croissante
            if( carac != '\r' && !key[KEY_BACKSPACE] )
            {
                textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0),"%c",carac);
                pseudo[i][place] = carac;
                poscarac = poscarac+8;
            }

            if (key[KEY_BACKSPACE] && x+poscarac >= 506)
            {
                if(x+poscarac == 506)
                {
                    poscarac=poscarac-8;
                    pseudo[i][place] = ' ';
                    textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                    place = place-2;
                }
                else
                {
                    nb = nb +1;
                    poscarac=poscarac-8;
                    pseudo[i][place-1] = ' ';
                    textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                    place = place-2;
                }
            }

            /// RETOUR CHARIOT : ON VA A LA LIGNE
            if (carac== '\r')
            {
                y+=10;
                stop=1;
            }
            place = place+1;
            //display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        }
        if ( mouse_b&1 && mouse_x>= 553 && mouse_x <= 729 && mouse_y >= 540 && mouse_y <= 591)
        {
            blit(fond, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);

        }
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}


void menu_principal(BITMAP *buffer, BITMAP *accueil, BITMAP *cursor,  FONT* myfont )
{
    clear_bitmap(buffer);
    blit(accueil,buffer,0,0,0,0,SCREEN_W,SCREEN_H);



    //textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
    textprintf_ex(buffer,myfont,575,243, makecol(0,0,0),-1,"STANDARD");
    textprintf_ex(buffer,myfont,585, 362, makecol(0,0,0),-1,"DOUBLE");
    textprintf_ex(buffer,myfont,585,471, makecol(0,0,0),-1,"CREDITS");
    textprintf_ex(buffer,myfont,585, 582, makecol(0,0,0),-1,"QUITTER");

    if ( mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 223 && mouse_y <= 300)
    {
        textprintf_ex(buffer,myfont,575,243, makecol(255,255,255),-1,"STANDARD");
    }

    if(  mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 338 && mouse_y <= 411 )
    {
        textprintf_ex(buffer,myfont,585, 362, makecol(255,255,255),-1,"DOUBLE");
    }

    if(  mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 448 && mouse_y <= 527 )
    {
        textprintf_ex(buffer,myfont,585,471, makecol(255,255,255),-1,"CREDITS");
    }

    if( mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 563 && mouse_y <= 627)
    {
        textprintf_ex(buffer,myfont,585, 582, makecol(255,255,255),-1,"QUITTER");
    }

}


int menu(BITMAP* buffer, BITMAP *fond, BITMAP *cursor, char pseudo[4][20], SAMPLE* son_menu, FONT* myfont)
{
    int fin;
    int ok;
    int nb_joueur = 0;
    int y = 314;
    int installation_clavier = 0;
    int clic = 0;
    BITMAP *creators;
    BITMAP *choix_nb_joueurs;
    BITMAP *nom_joueurs;
    BITMAP *accueil;
    FONT* font_nbjoueur;
    BITMAP *son_on;
    BITMAP *son_off;

    son_on=load_bitmap("BITMAP/son_on.bmp", NULL);
    son_off=load_bitmap("BITMAP/son_off.bmp", NULL);

    // init. variable de sortie boucle interactive
    fin=0;


    creators = load_bitmap("BITMAP/creators.bmp", NULL);
    choix_nb_joueurs =load_bitmap("BITMAP/buffer_nb_joueurs.bmp", NULL);
    nom_joueurs =load_bitmap("BITMAP/noms.bmp", NULL);
    accueil = load_bitmap("BITMAP/accueil.bmp",NULL);
    font_nbjoueur = load_font("FONT/font_nbjoueur.pcx", NULL, NULL);


    if (!fond || !creators || !choix_nb_joueurs || !nom_joueurs)
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
        //textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        menu_principal(buffer, accueil, cursor, myfont);
        affichage_son(buffer, cursor, son_menu, &clic);
        if (clic)
        {
            draw_sprite(buffer, son_off, 0, 0);
        }
        else
        {
            draw_sprite(buffer, son_on, 0, 0);
        }
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(20);

        /// si on appuie sur CREDITS
        if( mouse_b&1 && mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 448 && mouse_y <= 527 )
        {
            while(!key[KEY_ESC] && !(mouse_b&2))
            {
                blit(creators,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }


        ///si on appuie sur quitter
        if(mouse_b&1 &&  mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 563 && mouse_y <= 627 )
        {
            allegro_message("Merci d'avoir joue !");
            allegro_exit();
            exit(0);
        }

        /// si on appui sur standard
        if (mouse_b&1 && mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 223 && mouse_y <= 300)
        {
            ok = 0;

            while(ok!=1)
            {
                clear_bitmap(buffer);
                blit(choix_nb_joueurs,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                //textprintf_ex(buffer,font,96,36,makecol(255,0,255), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
                textprintf_ex(buffer, font_nbjoueur, 744,198,makecol(0,0,0),-1,"%d",nb_joueur);
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);

                if (mouse_b&1 && mouse_x>=460 && mouse_x <= 563 && mouse_y >= 330&& mouse_y <= 434 && nb_joueur <= 3)
                {

                    nb_joueur = nb_joueur+1;
                    rest(100);
                }
                if (mouse_b&1 && mouse_x>=754 && mouse_x <= 870 && mouse_y >= 331 && mouse_y <= 436 && nb_joueur > 0)
                {

                    nb_joueur = nb_joueur -1;
                    rest(100);
                }
                // On appuie sur ok
                if ((mouse_b&1) && (mouse_x > 458) && (mouse_x < 833) && (mouse_y > 573) && (mouse_y < 654) && (nb_joueur >= 2))
                {
                    ok = 1;
                    //blit(buffer, screen, 0, 0, 0, 0, SCREEN_W / 2, SCREEN_H);
                }
                if(key[KEY_ESC] || mouse_b&2)
                {
                    ok =1;
                }
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }

            install_keyboard();
            clear_bitmap(buffer);
            blit(nom_joueurs,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            textprintf_ex(buffer,font,500,270, makecol(255,255,255),-1, " Veuillez entrez vos pseudos :");
            //display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            /*while(!key[KEY_BACKSPACE])
            {
                prenom(nb_joueur, buffer, joueur, fond, cursor);
            }*/
            rest(200);


            for (int i = 0; i < nb_joueur; i++)
            {
                prenom(&nb_joueur, buffer, pseudo, fond, cursor, i, y);
                y = y + 15;
            }
            fin = 1;

        }
        /// si on appuie sur double
        if(mouse_b&1 && mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 338 && mouse_y <= 411 )
        {
            while(!key[KEY_ESC] && !(mouse_b&2))
            {
                blit(fond,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    destroy_bitmap(creators);
    destroy_bitmap(choix_nb_joueurs);
    return nb_joueur;
}
