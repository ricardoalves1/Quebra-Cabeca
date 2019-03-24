#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int width = 700;
int height = 700;

int  pos[36];
int movimentos = 0, aux, i;

int lvl = 0;	// Nível escolhido
int tam = 0;	// Tamanho do Quebra-Cabeça


int main()
{

	ALLEGRO_DISPLAY *display = NULL;

	bool play = false;	// Começar a jogar
	bool done = false;	// Sair do jogo
	bool pause = false;	// Pausar o jogo
	bool win = false;	// Ganhar o jogo

	int select = 0;
	int rec_x = 252;
	int rec_xf = 252;
	int rec_y = 400;
	int barra = 0;
	int FPS = 60;
	int view = 0;
	int count = 0;
	int result = 0;


	/* ____________________________________________________________________________________________________________________________________________________ */

	if(!al_init()){
		fprintf(stderr, "Failed to initialize Allegro!\n");
		return -1;
	}

	display = al_create_display(width, height);
	
	if(!display){
		fprintf(stderr, "Failed to initialize display!\n");
		return -1;
	}

	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();


	ALLEGRO_BITMAP 		*image0[9];		// Imagens nível fácil
	ALLEGRO_BITMAP 		*image1[16];	// Imagens nível médio
	ALLEGRO_BITMAP 		*image2[36];	// Imagens nível difícil
	ALLEGRO_BITMAP 		*background[2];	// Fundo
	ALLEGRO_BITMAP 		*full[3];		// Imagens completas
	ALLEGRO_BITMAP 		*menu = NULL;	// Imagem do menu
	ALLEGRO_BITMAP		*name[12];		// Nome Quebra-Cabeça
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER 		*timer = NULL;
	ALLEGRO_FONT 		*font20 = al_load_font("KOMIKAX_.ttf", 20, 0);


	//  Imagens :

			menu = al_load_bitmap("images/menu.png");

			name[0] =  al_load_bitmap("images/name1.png");
			name[1] =  al_load_bitmap("images/name2.png");
			name[2] =  al_load_bitmap("images/name3.png");
			name[3] =  al_load_bitmap("images/name4.png");
			name[4] =  al_load_bitmap("images/name5.png");
			name[5] =  al_load_bitmap("images/name6.png");
			name[6] =  al_load_bitmap("images/name7.png");
			name[7] =  al_load_bitmap("images/name8.png");
			name[8] =  al_load_bitmap("images/name9.png");
			name[9] =  al_load_bitmap("images/name10.png");
			name[10] = al_load_bitmap("images/name11.png");
			name[11] = al_load_bitmap("images/name12.png");

		// Nível Fácil >
			image0[0] = al_load_bitmap("images/lvl1/00.png");
			image0[1] = al_load_bitmap("images/lvl1/01.png");
			image0[2] = al_load_bitmap("images/lvl1/02.png");
			image0[3] = al_load_bitmap("images/lvl1/03.png");
			image0[4] = al_load_bitmap("images/lvl1/04.png");
			image0[5] = al_load_bitmap("images/lvl1/05.png");
			image0[6] = al_load_bitmap("images/lvl1/06.png");
			image0[7] = al_load_bitmap("images/lvl1/07.png");
			image0[8] = NULL;
			

		// Nível Médio >
			image1[0] = al_load_bitmap("images/lvl2/00.jpg");
			image1[1] = al_load_bitmap("images/lvl2/01.jpg");
			image1[2] = al_load_bitmap("images/lvl2/02.jpg");
			image1[3] = al_load_bitmap("images/lvl2/03.jpg");
			image1[4] = al_load_bitmap("images/lvl2/04.jpg");
			image1[5] = al_load_bitmap("images/lvl2/05.jpg");
			image1[6] = al_load_bitmap("images/lvl2/06.jpg");
			image1[7] = al_load_bitmap("images/lvl2/07.jpg");
			image1[8] = al_load_bitmap("images/lvl2/08.jpg");
			image1[9] = al_load_bitmap("images/lvl2/09.jpg");
			image1[10] = al_load_bitmap("images/lvl2/10.jpg");
			image1[11] = al_load_bitmap("images/lvl2/11.jpg");
			image1[12] = al_load_bitmap("images/lvl2/12.jpg");
			image1[13] = al_load_bitmap("images/lvl2/13.jpg");
			image1[14] = al_load_bitmap("images/lvl2/14.jpg");
			image1[15] = NULL;
			

		// Nível Difícil >
			image2[0]  = al_load_bitmap("images/lvl3/00.jpg");
			image2[1]  = al_load_bitmap("images/lvl3/01.jpg");
			image2[2]  = al_load_bitmap("images/lvl3/02.jpg");
			image2[3]  = al_load_bitmap("images/lvl3/03.jpg");
			image2[4]  = al_load_bitmap("images/lvl3/04.jpg");
			image2[5]  = al_load_bitmap("images/lvl3/05.jpg");
			image2[6]  = al_load_bitmap("images/lvl3/06.jpg");
			image2[7]  = al_load_bitmap("images/lvl3/07.jpg");
			image2[8]  = al_load_bitmap("images/lvl3/08.jpg");
			image2[9]  = al_load_bitmap("images/lvl3/09.jpg");
			image2[10] = al_load_bitmap("images/lvl3/10.jpg");
			image2[11] = al_load_bitmap("images/lvl3/11.jpg");
			image2[12] = al_load_bitmap("images/lvl3/12.jpg");
			image2[13] = al_load_bitmap("images/lvl3/13.jpg");
			image2[14] = al_load_bitmap("images/lvl3/14.jpg");
			image2[15] = al_load_bitmap("images/lvl3/15.jpg");
			image2[16] = al_load_bitmap("images/lvl3/16.jpg");
			image2[17] = al_load_bitmap("images/lvl3/17.jpg");
			image2[18] = al_load_bitmap("images/lvl3/18.jpg");
			image2[19] = al_load_bitmap("images/lvl3/19.jpg");
			image2[20] = al_load_bitmap("images/lvl3/20.jpg");
			image2[21] = al_load_bitmap("images/lvl3/21.jpg");
			image2[22] = al_load_bitmap("images/lvl3/22.jpg");
			image2[23] = al_load_bitmap("images/lvl3/23.jpg");
			image2[24] = al_load_bitmap("images/lvl3/24.jpg");
			image2[25] = al_load_bitmap("images/lvl3/25.jpg");
			image2[26] = al_load_bitmap("images/lvl3/26.jpg");
			image2[27] = al_load_bitmap("images/lvl3/27.jpg");
			image2[28] = al_load_bitmap("images/lvl3/28.jpg");
			image2[29] = al_load_bitmap("images/lvl3/29.jpg");
			image2[30] = al_load_bitmap("images/lvl3/30.jpg");
			image2[31] = al_load_bitmap("images/lvl3/31.jpg");
			image2[32] = al_load_bitmap("images/lvl3/32.jpg");
			image2[33] = al_load_bitmap("images/lvl3/33.jpg");
			image2[34] = al_load_bitmap("images/lvl3/34.jpg");
			image2[35] = NULL;

		// Fundo
			background[0] = al_load_bitmap("images/fundo.png");
			background[1] = al_load_bitmap("images/fundo2.png");

		// Imagens completas
			full[0] = al_load_bitmap("images/lvl1.png");
			full[1] = al_load_bitmap("images/lvl2.jpg");
			full[2] = al_load_bitmap("images/lvl3.jpg");
	/* ____________________________________________________________________________________________________________________________________________________ */


	timer = al_create_timer(1.0 / FPS);

	al_install_keyboard();

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	

	void embaralhar(int *vet);


	al_start_timer(timer);

	for(;;){
		
		al_flip_display();

		play = false;

		while(!play)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if(ev.type == ALLEGRO_EVENT_KEY_DOWN)	// Selecionar opção do menu
	        {
	            if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
	            {
	                select++;
	                rec_y += 60;
	                rec_xf = 252;
	                barra = 0;

	                if(select > 3) select = 0;
	                if(rec_y > 580) rec_y = 400;
	            }
	            else if(ev.keyboard.keycode == ALLEGRO_KEY_UP)
	            {
	                select--;
	                rec_y -= 60;
	                rec_xf = 252;
	                barra = 0;

	                if(select < 0) select = 3;
	                if(rec_y < 400) rec_y = 580;
	            }
	            else if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
	            {
	                if(select == 0)			// Jogar nível fácil
	                {
	                	lvl = 0;
	                	tam = 8;
	                	play = true;
	                }
	                else if(select == 1)	// Jogar nível médio
	                {
	                	lvl = 1;
	                	tam = 15;
	                    play = true;
	                }
	                else if(select == 2)	// Jogar nível difícil
	                {
	                	lvl = 2;
	                	tam = 35;
	                	play = true;
	                }
	                else					// Fechar o jogo
	                {	            
	                    al_destroy_timer(timer);
	                	al_destroy_display(display);
	                	al_destroy_event_queue(event_queue);

	                    return 0;
	                }
	            }
	            else if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	            {
	            	al_destroy_timer(timer);
                    al_destroy_display(display);
                    al_destroy_event_queue(event_queue);

                    return 0;
	            }
	        }

	        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				al_destroy_timer(timer);
                al_destroy_display(display);
                al_destroy_event_queue(event_queue);

                return 0;
			}

			barra++;
			count++;

			al_draw_filled_rectangle(rec_x, rec_y + 2, rec_xf, rec_y + 48, al_map_rgb(200, 200, 200));
			
			al_draw_bitmap(menu, 0, 0, 0);

			// Nome Quebra-Cabeça:
				if(count <= 100) al_draw_bitmap(name[0], 206, 50, 0);
				else if(count <= 200) al_draw_bitmap(name[1], 206, 50, 0);
				else if(count <= 300) al_draw_bitmap(name[2], 206, 50, 0);
				else if(count <= 400) al_draw_bitmap(name[3], 206, 50, 0);
				else if(count <= 500) al_draw_bitmap(name[4], 206, 50, 0);
				else if(count <= 600) al_draw_bitmap(name[5], 206, 50, 0);
				else if(count <= 700) al_draw_bitmap(name[6], 206, 50, 0);
				else if(count <= 800) al_draw_bitmap(name[7], 206, 50, 0);
				else if(count <= 900) al_draw_bitmap(name[8], 206, 50, 0);
				else if(count <= 1000) al_draw_bitmap(name[9], 206, 50, 0);
				else if(count <= 1100) al_draw_bitmap(name[10], 206, 50, 0);
				else if(count <= 1200) al_draw_bitmap(name[11], 206, 50, 0);
				else count = 0;

			if(barra <= 200) rec_xf += 3;
			if(rec_xf >= 448) rec_xf = 448;


			al_flip_display();
			al_clear_to_color(al_map_rgb(25,25,25));
		
		}

		RE:
			for(i = 0; i < 36; ++i){
				pos[i] = i;
			}

			movimentos = 0;
			count = 0;

			// Embaralhar as imagens do Quebra-Cabeça
			embaralhar(pos);

			done = false;

		while(!done)
		{

			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);


			if(!pause && !win)
			{

				if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch(ev.keyboard.keycode)
					{
						case ALLEGRO_KEY_SPACE: // Espaço mostra a imagagem completa
							view = 1;
							break;
						case ALLEGRO_KEY_P:		// P - pausa
							view = 0;
							pause = true;
							break;
						case ALLEGRO_KEY_R:		// R - reinicia o jogo
							goto RE;
							break;
					}
				}
				else if(ev.type == ALLEGRO_EVENT_KEY_UP)
				{
					switch(ev.keyboard.keycode)
					{
						case ALLEGRO_KEY_ESCAPE:
							done = true;
							break;
						case ALLEGRO_KEY_UP:	// Move uma imagem para cima
							view = 0;
							if(lvl == 0)
							{
								for(i=0; i<9; ++i){
									if(pos[i] == 8){
										if(i >= 6){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i+3];
										pos[i+3] = aux;
										break;
									}
								}
							}
							else if(lvl == 1)
							{
								for(i=0; i<16; ++i){
									if(pos[i] == 15){
										if(i >= 12){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i+4];
										pos[i+4] = aux;
										break;
									}
								}
							}
							else
							{
								for(i=0; i<36; ++i){
									if(pos[i] == 35){
										if(i >= 30){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i+6];
										pos[i+6] = aux;
										break;
									}
								}
							}

							break;
						case ALLEGRO_KEY_DOWN:	// Move uma imagem para baixo
							view = 0;
							if(lvl == 0)
							{
								for(i=0; i<9; ++i){
									if(pos[i] == 8){
										if(i <= 2){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i-3];
										pos[i-3] = aux;
										break;
									}
								}
							}
							else if(lvl == 1)
							{
								for(i=0; i<16; ++i){
									if(pos[i] == 15){
										if(i <= 3){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i-4];
										pos[i-4] = aux;
										break;
									}
								}
							}
							else
							{
								for(i=0; i<36; ++i){
									if(pos[i] == 35){
										if(i <= 5){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i-6];
										pos[i-6] = aux;
										break;
									}
								}
							}

							break;
						case ALLEGRO_KEY_LEFT:	// Move uma imagem para esquerda
							view = 0;
							if(lvl == 0)
							{
								for(i=0; i<9; ++i){
									if(pos[i] == 8){
										if(i == 2 || i == 5 || i == 8){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i+1];
										pos[i+1] = aux;
										break;
									}
								}
							}
							else if(lvl == 1)
							{
								for(i=0; i<16; ++i){
									if(pos[i] == 15){
										if(i == 3 || i == 7 || i == 11 || i == 15){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i+1];
										pos[i+1] = aux;
										break;
									}
								}
							}
							else
							{
								for(i=0; i<36; ++i){
									if(pos[i] == 35){
										if(i == 5 || i == 11 || i == 17 || i == 23 || i == 29 || i == 35){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i+1];
										pos[i+1] = aux;
										break;
									}
								}
							}

							break;
						case ALLEGRO_KEY_RIGHT:	// Move uma imagem para direita
							view = 0;
							if(lvl == 0)
							{
								for(i=0; i<9; ++i){
									if(pos[i] == 8){
										if(i == 0 || i == 3 || i == 6){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i-1];
										pos[i-1] = aux;
										break;
									}
								}
							}
							else if(lvl == 1)
							{
								for(i=0; i<16; ++i){
									if(pos[i] == 15){
										if(i == 0 || i == 4 || i == 8 || i == 12){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i-1];
										pos[i-1] = aux;
										break;
									}
								}
							}
							else
							{
								for(i=0; i<36; ++i){
									if(pos[i] == 35){
										if(i == 0 || i == 6 || i == 12 || i == 18 || i == 24 || i == 30){
											break;
										}
										movimentos++;
										aux = pos[i];
										pos[i] = pos[i-1];
										pos[i-1] = aux;
										break;
									}
								}
							}

							break;
						case ALLEGRO_KEY_SPACE:
							view = 0;
							break;
					}
				}
			}
			else if(pause)
			{
				if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch(ev.keyboard.keycode)
					{
						case ALLEGRO_KEY_P:
							pause = false;
							break;
						case ALLEGRO_KEY_ESCAPE:
							done = true;
							break;
					}
				}
			}
			
			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				done = true;
			}

			al_draw_bitmap(background[0], 0, 0, 0);

			// Imagens pelo nível :
				if( lvl == 0 )		// Fácil
				{

					if(image0[pos[0]] != NULL) al_draw_bitmap(image0[pos[0]], 50, 50, 0)  ;
					
					if(image0[pos[1]] != NULL) al_draw_bitmap(image0[pos[1]], 250, 50, 0) ;

					if(image0[pos[2]] != NULL) al_draw_bitmap(image0[pos[2]], 450, 50, 0) ;

					if(image0[pos[3]] != NULL) al_draw_bitmap(image0[pos[3]], 50, 250, 0) ;

					if(image0[pos[4]] != NULL) al_draw_bitmap(image0[pos[4]], 250, 250, 0);

					if(image0[pos[5]] != NULL) al_draw_bitmap(image0[pos[5]], 450, 250, 0);

					if(image0[pos[6]] != NULL) al_draw_bitmap(image0[pos[6]], 50, 450, 0) ;

					if(image0[pos[7]] != NULL) al_draw_bitmap(image0[pos[7]], 250, 450, 0);

					if(image0[pos[8]] != NULL) al_draw_bitmap(image0[pos[8]], 450, 450, 0);

				}
				else if( lvl == 1 )	// Médio
				{
					if(image1[pos[0]] != NULL ) al_draw_bitmap(image1[pos[0]], 50, 50, 0);
					
					if(image1[pos[1]] != NULL ) al_draw_bitmap(image1[pos[1]], 200, 50, 0);

					if(image1[pos[2]] != NULL ) al_draw_bitmap(image1[pos[2]], 350, 50, 0);

					if(image1[pos[3]] != NULL ) al_draw_bitmap(image1[pos[3]], 500, 50, 0);

					if(image1[pos[4]] != NULL ) al_draw_bitmap(image1[pos[4]], 50, 200, 0);

					if(image1[pos[5]] != NULL ) al_draw_bitmap(image1[pos[5]], 200, 200, 0);

					if(image1[pos[6]] != NULL ) al_draw_bitmap(image1[pos[6]], 350, 200, 0);

					if(image1[pos[7]] != NULL ) al_draw_bitmap(image1[pos[7]], 500, 200, 0);

					if(image1[pos[8]] != NULL ) al_draw_bitmap(image1[pos[8]], 50, 350, 0);

					if(image1[pos[9]] != NULL ) al_draw_bitmap(image1[pos[9]], 200, 350, 0);

					if(image1[pos[10]] != NULL) al_draw_bitmap(image1[pos[10]], 350, 350, 0);

					if(image1[pos[11]] != NULL) al_draw_bitmap(image1[pos[11]], 500, 350, 0);

					if(image1[pos[12]] != NULL) al_draw_bitmap(image1[pos[12]], 50, 500, 0);

					if(image1[pos[13]] != NULL) al_draw_bitmap(image1[pos[13]], 200, 500, 0);

					if(image1[pos[14]] != NULL) al_draw_bitmap(image1[pos[14]], 350, 500, 0);

					if(image1[pos[15]] != NULL) al_draw_bitmap(image1[pos[15]], 500, 500, 0);

				}
				else				// Difícil
				{
					if(image2[pos[0]]  != NULL) al_draw_bitmap(image2[pos[0]], 50, 50, 0);  
					
					if(image2[pos[1]]  != NULL) al_draw_bitmap(image2[pos[1]], 150, 50, 0)  ;

					if(image2[pos[2]]  != NULL) al_draw_bitmap(image2[pos[2]], 250, 50, 0)  ;

					if(image2[pos[3]]  != NULL) al_draw_bitmap(image2[pos[3]], 350, 50, 0)  ;

					if(image2[pos[4]]  != NULL) al_draw_bitmap(image2[pos[4]], 450, 50, 0)  ;

					if(image2[pos[5]]  != NULL) al_draw_bitmap(image2[pos[5]], 550, 50, 0)  ;

					if(image2[pos[6]]  != NULL) al_draw_bitmap(image2[pos[6]], 50, 150, 0)  ;

					if(image2[pos[7]]  != NULL) al_draw_bitmap(image2[pos[7]], 150, 150, 0) ;

					if(image2[pos[8]]  != NULL) al_draw_bitmap(image2[pos[8]], 250, 150, 0) ;

					if(image2[pos[9]]  != NULL) al_draw_bitmap(image2[pos[9]], 350, 150, 0) ;
					
					if(image2[pos[10]] != NULL) al_draw_bitmap(image2[pos[10]], 450, 150, 0);

					if(image2[pos[11]] != NULL) al_draw_bitmap(image2[pos[11]], 550, 150, 0);

					if(image2[pos[12]] != NULL) al_draw_bitmap(image2[pos[12]], 50, 250, 0) ;

					if(image2[pos[13]] != NULL) al_draw_bitmap(image2[pos[13]], 150, 250, 0);

					if(image2[pos[14]] != NULL) al_draw_bitmap(image2[pos[14]], 250, 250, 0);

					if(image2[pos[15]] != NULL) al_draw_bitmap(image2[pos[15]], 350, 250, 0);

					if(image2[pos[16]] != NULL) al_draw_bitmap(image2[pos[16]], 450, 250, 0);

					if(image2[pos[17]] != NULL) al_draw_bitmap(image2[pos[17]], 550, 250, 0);
					/**/
					if(image2[pos[18]] != NULL) al_draw_bitmap(image2[pos[18]], 50, 350, 0) ;

					if(image2[pos[19]] != NULL) al_draw_bitmap(image2[pos[19]], 150, 350, 0);

					if(image2[pos[20]] != NULL) al_draw_bitmap(image2[pos[20]], 250, 350, 0);

					if(image2[pos[21]] != NULL) al_draw_bitmap(image2[pos[21]], 350, 350, 0);

					if(image2[pos[22]] != NULL) al_draw_bitmap(image2[pos[22]], 450, 350, 0);

					if(image2[pos[23]] != NULL) al_draw_bitmap(image2[pos[23]], 550, 350, 0);

					if(image2[pos[24]] != NULL) al_draw_bitmap(image2[pos[24]], 50, 450, 0) ;

					if(image2[pos[25]] != NULL) al_draw_bitmap(image2[pos[25]], 150, 450, 0);

					if(image2[pos[26]] != NULL) al_draw_bitmap(image2[pos[26]], 250, 450, 0);

					if(image2[pos[27]] != NULL) al_draw_bitmap(image2[pos[27]], 350, 450, 0);

					if(image2[pos[28]] != NULL) al_draw_bitmap(image2[pos[28]], 450, 450, 0);

					if(image2[pos[29]] != NULL) al_draw_bitmap(image2[pos[29]], 550, 450, 0);

					if(image2[pos[30]] != NULL) al_draw_bitmap(image2[pos[30]], 50, 550, 0) ;

					if(image2[pos[31]] != NULL) al_draw_bitmap(image2[pos[31]], 150, 550, 0);

					if(image2[pos[32]] != NULL) al_draw_bitmap(image2[pos[32]], 250, 550, 0);

					if(image2[pos[33]] != NULL) al_draw_bitmap(image2[pos[33]], 350, 550, 0);

					if(image2[pos[34]] != NULL) al_draw_bitmap(image2[pos[34]], 450, 550, 0);

					if(image2[pos[35]] != NULL) al_draw_bitmap(image2[pos[35]], 550, 550, 0);

				}
				

			if(view == 1)
				al_draw_bitmap(full[lvl], 50, 50, 0);
			

			result = 0;

			for(i=0; i<36; ++i){	// Verifica se completou o Quebra-cabeça
				if(pos[i] == i){
					result++;
				}
			}

			if(result == 36){
				win = true;
				al_draw_bitmap(background[1], 0, 0, 0);
				al_draw_textf(font20, al_map_rgb(0, 0, 0), 45, 650, 0, "Você Completou o quebra-cabeça com %d movimentos", movimentos);
		
				if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
					switch(ev.keyboard.keycode)
					{
						case ALLEGRO_KEY_ENTER:
							done = true;
							win = false;
							break;
						case ALLEGRO_KEY_ESCAPE:
							done = true;
							win = false;
							break;
						case ALLEGRO_KEY_R:
							win = false;
							goto RE;
							break;
					}
				}
			}
			else{
				al_draw_textf(font20, al_map_rgb(255, 255, 255), 550, 648, 0, "%i", movimentos);
			}

			if(pause){
				al_draw_bitmap(background[1], 0, 0, 0);
				al_draw_text(font20, al_map_rgb(0, 0, 0), 270, 20, 0, "Jogo pausado");
				al_draw_text(font20, al_map_rgb(0, 0, 0), 170, 650, 0, "Aperte p para voltar ao jogo");
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(25,25,25));
		}

	}
	
	

	al_flip_display();

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	
	
	return 0;
}

void embaralhar(int *vet)	// Troca a posição dos valores de pos[36]
{
	srand(time(NULL));
	
	for (i = 0; i < tam; i++)
	{
		int r = rand() % tam;

		int temp = vet[i];
		vet[i] = vet[r];
		vet[r] = temp;
	}

}