#include "../structures.h"
#include "../prototypes.h"


void affichage_son(BITMAP *buffer, BITMAP *cursor, SAMPLE* s, int* clic )
{

    if(mouse_b&1 && mouse_x>= 0 && mouse_x <= 65 && mouse_y >= 0&& mouse_y <= 50 && !*clic)
    {
        rest(100);
        *clic = 1;
        //stop_sample(s);
        adjust_sample(s, 0, 0, 1000, 1);

    }
    if (mouse_b&1 && mouse_x>= 0 && mouse_x <= 65 && mouse_y >= 0&& mouse_y <= 50 && *clic)
    {
        rest(100);
        *clic = 0;
        adjust_sample(s, 255, 128, 1000, 1);
        //play_sample(s, 255, 128, 1000, 1);
    }


}


void prenom(int *nb_joueur, BITMAP* buffer, char pseudo[4][20], BITMAP* fond, BITMAP *cursor, int* num, int y, int*clic, SAMPLE* son_menu, BITMAP* son_on, BITMAP* son_off)
{
    int x = 498;
    int touche;
    char carac;
    //int y = 314;
    int stop = 0;
    int  poscarac=0;
    int place= 0;
    int nb = 0;
    int compteur = 0;

    fflush(stdin);
    if(stop != *nb_joueur)
        stop = 0;
    else
        stop = 1;

    poscarac = 0;
    textprintf_ex(buffer,font,405,y, makecol(255,255,255),-1,"joueur %d :", (*num)+1);


    /// AFFICHAGE DES LETTRES QUE L'ON TAPE AU CLAVIER
    while (stop != 1)
    {
        textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        affichage_son(buffer, cursor, son_menu, &(*clic));

        if (*clic)
        {
            draw_sprite(buffer, son_off, 0, 0);
        }
        else
        {
            draw_sprite(buffer, son_on, 0, 0);
        }
        if (keypressed())
        {

            touche=readkey();
            carac = (char)touche;

            // afficher le caractère à une position x croissante
            if( carac != '\r' && !key[KEY_BACKSPACE] && compteur != 19)
            {
                textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0),"%c",carac);
                pseudo[*num][place] = carac;
                poscarac = poscarac+8;
                compteur = compteur +1;
            }

            if (key[KEY_BACKSPACE] && x+poscarac >= 506)
            {
                if(x+poscarac == 506)
                {
                    poscarac=poscarac-8;
                    pseudo[*num][place] = ' ';
                    textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                    place = place-2;
                    compteur = compteur -1;
                }
                else
                {
                    nb = nb +1;
                    poscarac=poscarac-8;
                    pseudo[*num][place-1] = ' ';
                    textprintf_ex(buffer,font,x+poscarac,y,makecol(255,255,255),makecol(0,0,0)," ");
                    place = place-2;
                    compteur = compteur -1;
                }
            }

            /// RETOUR CHARIOT : ON VA A LA LIGNE
            if (carac== '\r')
            {
                y+=10;
                stop=1;
                *num = *num +1;
            }
            place = place+1;
            //display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}


void menu_principal(BITMAP *buffer, BITMAP *accueil, BITMAP *cursor,  FONT* myfont )
{
    clear_bitmap(buffer);
    blit(accueil,buffer,0,0,0,0,SCREEN_W,SCREEN_H);


    display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
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


int menu(BITMAP* buffer, BITMAP *fond, BITMAP *cursor, char pseudo[4][20], SAMPLE* son_menu, FONT* myfont, BITMAP* son_on, BITMAP* son_off, int* choix_double)
{
    int fin;
    int ok;
    int nb_joueur = 0;
    int nb = 0;
    int y = 314;
    int clic = 0;
    BITMAP *creators;
    BITMAP *choix_nb_joueurs;
    BITMAP *nom_joueurs;
    BITMAP *accueil;
    FONT* font_nbjoueur;

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
            }
        }


        ///si on appuie sur quitter
        if(mouse_b&1 &&  mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 563 && mouse_y <= 627 )
        {
            allegro_message("Merci d'avoir joue !");
            allegro_exit();
            exit(0);
        }

        int sortir;

        /// si on appui sur standard
        if (mouse_b&1 && mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 223 && mouse_y <= 300)
        {
            ok = 0;
            sortir = 0;
            *choix_double = 0;
            while(ok!=1 && sortir!=1)
            {

                clear_bitmap(buffer);
                blit(choix_nb_joueurs,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                affichage_son(buffer, cursor, son_menu, &clic);
                if (clic)
                {
                    draw_sprite(buffer, son_off, 0, 0);
                }
                else
                {
                    draw_sprite(buffer, son_on, 0, 0);
                }

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
                }
                if(mouse_b&2)
                {
                    //ok=1;
                    sortir = 1;

                }


                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            }
            if(sortir != 1)
            {
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


                while(nb != nb_joueur)
                {

                    prenom(&nb_joueur, buffer, pseudo, fond, cursor, &nb, y, &clic, son_menu, son_on, son_off);
                    display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                    y = y + 15;

                }
                fin = 1;
            }

        }
        /// si on appuie sur double
        if(mouse_b&1 && mouse_x>= 423 && mouse_x <= 834 && mouse_y >= 338 && mouse_y <= 411 )
        {
            clear_bitmap(buffer);
            *choix_double = 1;
            install_keyboard();
            blit(nom_joueurs,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            textprintf_ex(buffer,font,500,270, makecol(255,255,255),-1, " Veuillez entrez vos pseudos :");
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            nb_joueur = 4;
            while(nb != nb_joueur)
            {
                prenom(&nb_joueur, buffer, pseudo, fond, cursor, &nb, y, &clic, son_menu, son_on, son_off);
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                y = y + 15;
            }
            fin = 1;
        }
    }
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    destroy_bitmap(creators);
    destroy_bitmap(choix_nb_joueurs);
    return nb_joueur;
}
