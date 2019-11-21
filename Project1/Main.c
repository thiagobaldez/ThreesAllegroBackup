#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <allegro5\allegro_native_dialog.h>
#include <time.h>

#define LARGURA_TELA 600
#define ALTURA_TELA 600
#define SIZE 5

void error_msg(char* text)
{
	al_show_native_message_box(NULL, "ERRO",
		"Ocorreu o seguinte erro e o programa sera finalizado:",
		text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

int* createMatrix()
{
	int i, randaux;
	time_t t;

	int* gameboard = (int*)calloc(SIZE * SIZE, sizeof(int));

	if (!gameboard)
	{
		error_msg("Falha ao inicializar a Matriz.");
		return NULL;
	}


	srand((unsigned)time(&t));

	randaux = rand() % ((SIZE * SIZE) - 1);
	(gameboard)[randaux] = -1;

	for (i = 0; i < 2;)
	{
		randaux = rand() % ((SIZE * SIZE) - 1);
		if((gameboard)[randaux] == 0)
		{
			(gameboard)[randaux] = 1;
			i++;
		}

	}

	for(i = 0; i < 2;)
	{
		randaux = rand() % ((SIZE * SIZE) - 1);
		if((gameboard)[randaux] == 0)
		{
			(gameboard)[randaux] = 2;
			i++;
		}

	}

	return gameboard;
}

void UpdateMatrix(int* matrix, int* nextNumber)
{
	int i, j;
	ALLEGRO_FONT* fonte = al_load_font("arial.ttf", 48, 0);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			al_draw_textf(fonte, al_map_rgb(0, 0, 0), (LARGURA_TELA / (SIZE * 2)) * j, (ALTURA_TELA / (SIZE * 2)) * i, ALLEGRO_ALIGN_LEFT, "%d", matrix[i * SIZE + j]);
	}

	al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA - 50, ALTURA_TELA - 75, ALLEGRO_ALIGN_LEFT, "%d", *nextNumber);

	al_flip_display();
}

// Se der tempo, colocar todos os MOVE na mesma função e enviar a tecla apertada como parâmetro.
bool moveUp(int* matrix, bool test)
{
	int i, j, offset, aboveLine, thirdline;
	for (i = 1; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{

			offset = i * SIZE + j;
			aboveLine = offset - SIZE;
			//thirdline = offset - SIZE * 2;

			if (i == 1)
			{
				if ((matrix)[offset] != -1)
				{
					if ((((matrix)[aboveLine]) == 0) && (((matrix)[offset]) != 0))
					{
						if (!test)
						{
							((matrix)[aboveLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;						
					}

					else if ((matrix)[aboveLine] + (matrix)[offset] == 3)
					{
						if (!test)
						{
							((matrix)[aboveLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if (((matrix)[offset] > 2) && ((matrix)[aboveLine] == ((matrix)[offset])))
					{
						if (!test)
						{
							((matrix)[aboveLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}					
				}
			}
			else
			{
				thirdline = offset - SIZE * 2;

				if ((matrix)[offset] != -1)
				{
					if (((matrix)[aboveLine] == 0) && ((matrix)[offset] != 0))
					{
						if (!test)
						{
							((matrix)[aboveLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if (((matrix)[aboveLine] + (matrix)[offset] == 3) && ((matrix)[thirdline] != 0))
					{
						if (!test)
						{
							((matrix)[aboveLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[aboveLine] == ((matrix)[offset])) && ((matrix)[thirdline] != 0))
					{
						if (!test)
						{
							((matrix)[aboveLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

bool moveDown(int* matrix, bool test) // Check This!
{
	int i, j, offset, belowLine, thirdline;
	for (i = (SIZE - 2); i > -1; i--)
	{
		for (j = 0; j < SIZE; j++)
		{
			offset = i * SIZE + j;
			belowLine = offset + SIZE;

			if (i == (SIZE - 1)) // ELE CAI ALGUMA VEZ AQUI?
			{
				if ((matrix)[offset] != -1)
				{
					if ((matrix)[belowLine] == 0)
					{
						if (!test)
						{
							((matrix)[belowLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if ((matrix)[belowLine] + (matrix)[offset] == 3)
					{
						if (!test)
						{
							((matrix)[belowLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
						
					}
					else if (((matrix)[offset] > 2) && ((matrix)[belowLine] == ((matrix)[offset])))
					{
						if (!test)
						{
							((matrix)[belowLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

				}
			}
			else
			{
				thirdline = offset + SIZE * 2;

				if ((matrix)[offset] != -1)
				{
					if ((matrix)[belowLine] == 0)
					{
						if (!test)
						{
							((matrix)[belowLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if ( ((matrix)[belowLine] + (matrix)[offset] == 3) && ((matrix)[thirdline] != 0))
					{
						if (!test)
						{
							((matrix)[belowLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[belowLine] == ((matrix)[offset])) && ((matrix)[thirdline] != 0))
					{
						if (!test)
						{
							((matrix)[belowLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

bool moveLeft(int* matrix, bool test)
{
	int i, j, offset, leftLine, thirdline;
	for (i = 1; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			offset = (j * SIZE) + i;
			leftLine = offset - 1;
			//thirdline = offset - 2;

			if (i == 1)
			{
				if ((matrix)[offset] != -1)
				{
					if ((matrix)[leftLine] == 0)
					{
						if (!test)
						{
							((matrix)[leftLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if ((matrix)[leftLine] + (matrix)[offset] == 3)
					{
						if (!test)
						{
							((matrix)[leftLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[leftLine] == ((matrix)[offset])))
					{
						if (!test)
						{
							((matrix)[leftLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

				}
			}
			else
			{
				thirdline = offset - 2;

				if ((matrix)[offset] != -1)
				{
					if ((matrix)[leftLine] == 0)
					{
						if (!test)
						{
							((matrix)[leftLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if (((matrix)[leftLine] + (matrix)[offset] == 3) && ((matrix)[thirdline] != 0))
					{
						if (!test)
						{
							((matrix)[leftLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[leftLine] == ((matrix)[offset])) && ((matrix)[thirdline] != 0))
					{
						if (!test)
						{
							((matrix)[leftLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

bool moveRight(int* matrix, bool test)
{
	int i, j, offset, rightLine, thirdline;
	for (i = (SIZE - 2); i > -1; i--)
	{
		for (j = 0; j < SIZE; j++)
		{
			offset = (j * SIZE) + i;
			rightLine = offset + 1;
			thirdline = offset + 2;

			if (i == (SIZE - 2))
			{
				if ((matrix)[offset] != -1)
				{
					if ((matrix)[rightLine] == 0)
					{
						if (!test)
						{
							((matrix)[rightLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if ((matrix)[rightLine] + (matrix)[offset] == 3)
					{
						if (!test)
						{
							((matrix)[rightLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;						
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[rightLine] == ((matrix)[offset])))
					{
						if (!test)
						{
							((matrix)[rightLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

				}
			}
			else
			{
				thirdline = offset + 2;

				if ((matrix)[offset] != -1)
				{
					if ((matrix)[rightLine] == 0)
					{
						if (!test)
						{
							((matrix)[rightLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if (((matrix)[rightLine] + (matrix)[offset] == 3) && ((matrix)[thirdline] != 0))
					{
						if (!test)
						{
							((matrix)[rightLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[rightLine] == ((matrix)[offset])) && ((matrix)[thirdline] != 0))
					{
						if (!test)
						{
							((matrix)[rightLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

bool hasPossibleMove(int* matrix)
{
	if (moveUp(matrix, true))
		return true;
	else if (moveDown(matrix, true))
		return true;
	else if (moveLeft(matrix, true))
		return true;
	else if (moveRight(matrix, true))
		return true;
	else
		return false;
}

void addNumber(int* matrix, ALLEGRO_EVENT* button, int* nextNumber)
{
	int i, j, emptyIndex = 0, offset, randAux, possibleIndex[SIZE];
	time_t t;

	srand((unsigned)time(&t));

	if (button == ALLEGRO_KEY_UP)
	{
			for (i = 1; i <= SIZE; i++)
			{
				offset = (SIZE * SIZE) - i;
				if (((matrix)[offset]) == 0)
				{
					possibleIndex[emptyIndex] = offset;
					emptyIndex++;
				}
			}

		if (emptyIndex != 0)
		{
			do
			{
				randAux = rand() % emptyIndex;
				randAux = possibleIndex[randAux];
			} while ((matrix)[randAux] != 0);

			(matrix)[randAux] = *nextNumber;
		}
	}
	else if(button == ALLEGRO_KEY_DOWN)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (((matrix)[i]) == 0)
			{
				possibleIndex[emptyIndex] = i;
				emptyIndex++;
			}
		}

		if (emptyIndex != 0)
		{
			do
			{
				randAux = rand() % emptyIndex;
				randAux = possibleIndex[randAux];
			} while ((matrix)[randAux] != 0);

			(matrix)[randAux] = *nextNumber;
		}
	}
	else if(button == ALLEGRO_KEY_LEFT)
	{
			for (i = 1; i <= SIZE; i++)
			{
				offset = (i * SIZE) - 1;
				if (((matrix)[offset]) == 0)
				{
					possibleIndex[emptyIndex] = offset;
					emptyIndex++;
				}
			}

			if (emptyIndex != 0)
			{
				do
				{
					randAux = rand() % emptyIndex;
					randAux = possibleIndex[randAux];
				} while ((matrix)[randAux] != 0);

				(matrix)[randAux] = *nextNumber;
			}
			
	}
	else if(button == ALLEGRO_KEY_RIGHT)
	{
		for (j = 0; j < SIZE; j++)
		{
			offset = (j * SIZE);
			if (((matrix)[offset]) == 0)
			{
				possibleIndex[emptyIndex] = offset;
				emptyIndex++;
			}
		}

		if (emptyIndex != 0)
		{
			do
			{
				randAux = rand() % emptyIndex;
				randAux = possibleIndex[randAux];
			} while ((matrix)[randAux] != 0);

			(matrix)[randAux] = *nextNumber;
		}
	}
}

int generateNextNumber(int* matrix)
{
	int i, nextNumber, randIndex;
	time_t t;

	srand((unsigned)time(&t));
	do
	{
		randIndex = rand() % ((SIZE * SIZE) - 1);
		nextNumber = (matrix)[randIndex];
	} while (nextNumber == -1);

	if (nextNumber == 0)
	{
		do
		{
			nextNumber = rand() % 3;
		} while (nextNumber == 0);
	}
	else if (nextNumber == 1)
	{
		nextNumber = 2;
	}
	else if (nextNumber == 2)
	{
		nextNumber = 1;
	}

	return nextNumber;
}

int main(void)
{
	int* gameboard = NULL;
	int nextNumber;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_EVENT event;


	if (!al_init())
	{
		error_msg("Falha ao inicializar a Allegro");
		return -1;
	}

	al_init_font_addon();

	if (!al_init_ttf_addon())
	{
		error_msg("Falha ao inicializar add-on allegro_ttf");
		return -1;
	}

	font = al_load_font("arial.ttf", 32, 0);
	if (!font)
	{
		error_msg("Falha ao carregar fonte");
		return -1;
	}

	if (!al_install_mouse())
		return 1;

	if (!al_install_keyboard())
		return 1; 

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	if (event_queue == NULL)
		return 1;

	display = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!display)
	{
		error_msg("Falha ao criar janela");
		return -1;
	}

	gameboard = createMatrix();
	if (!gameboard)
	{
		al_destroy_display(display);
		error_msg("Falha ao carregar a Matriz do Jogo.");
		return -1;
	}

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_clear_to_color(al_map_rgb(255, 255, 255));
	nextNumber = generateNextNumber(gameboard);
	UpdateMatrix(gameboard, &nextNumber);
	//printNextNumber();
	al_flip_display();

	while (1) // GameLoop
	{
		al_wait_for_event(event_queue, &event);

		if (al_event_queue_is_empty(event_queue))
		{
			al_flip_display();
			UpdateMatrix(gameboard, &nextNumber);
		}

		switch (event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				al_destroy_font(font);
				al_destroy_display(display);
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					//pauseGame();
					al_destroy_font(font);
					al_destroy_display(display);
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_UP)
				{
					if(moveUp(gameboard, true))
					{
						moveUp(gameboard, false);
						addNumber(gameboard, event.keyboard.keycode, &nextNumber);
						nextNumber = generateNextNumber(gameboard);
						UpdateMatrix(gameboard, &nextNumber);
					}
					
					//if (!hasPossibleMove(gameboardadress))
					//{
					//	//gameEnd();
					//	//al_clear_to_color(al_map_rgb(255, 0, 0));
					//	//al_flip_display();
					//}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
				{
					if (moveDown(gameboard, true))
					{
						moveDown(gameboard, false);
						addNumber(gameboard, event.keyboard.keycode, &nextNumber);
						nextNumber = generateNextNumber(gameboard);
						UpdateMatrix(gameboard, &nextNumber);
					}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				{
					if (moveRight(gameboard, true))
					{
						moveRight(gameboard, false);
						addNumber(gameboard, event.keyboard.keycode, &nextNumber);
						nextNumber = generateNextNumber(gameboard);
						UpdateMatrix(gameboard, &nextNumber);
					}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
				{
					if (moveLeft(gameboard, true))
					{
						moveLeft(gameboard, false);
						addNumber(gameboard, event.keyboard.keycode, &nextNumber);
						nextNumber = generateNextNumber(gameboard);
						UpdateMatrix(gameboard, &nextNumber);
					}
				}

				break;
		}
	}

	return 0;
}