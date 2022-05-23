#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;                       
    SDL_Renderer *renderer = NULL;                 
    int statut = EXIT_FAILURE;

    if(0 != SDL_Init(SDL_INIT_VIDEO))                        //création de la fenêtre 
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());             //différents test d'erreurs pour vérifier que les condition sont respectées 
        goto Quit;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1700, 300, SDL_WINDOW_SHOWN);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);           //création du render pour créer le dessin 
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }
    
    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)          //dessin des touches blanches 
    {
    	fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
    }
    
SDL_Rect touche_blanche;         //fonction pour dessiner des rectangles avec sdl
	
for (int i=0; i<49; i++)
{
	touche_blanche.x = 36*i;
	touche_blanche.y = 0;
	touche_blanche.w = 35;
	touche_blanche.h = 300;
		
}

if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)        // dessin des touches noires 
   {
	fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
   }
	
SDL_Rect touche_noire;         
	
for (int i=0; i<49; i++)
{
if (i%7==0 || (i+6)%7==0 || (i+4)%7==0 || (i+3)%7==0 || (i+2)%7==0) 
	{
		touche_noire.x = 36*i + 25;
		touche_noire.y = 0;
		touche_noire.w = 21;
		touche_noire.h = 180;

	}	
}	
   statut = EXIT_SUCCESS;
SDL_RenderPresent(renderer); //on affiche le render pour avoir le resultat 
SDL_Delay(10000);
Quit:
    if(NULL != renderer)                       //on efface le render et la window pour liberer l'espace 
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}
