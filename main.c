#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#define WIN64
#if defined WIN32 || defined WIN64
    #define clear() system("cls")
	#include <windows.h>
#else
    #define clear() system("clear")
#endif

enum Color
{
	Black        = 0,
	Grey         = FOREGROUND_INTENSITY,
	LightGrey    = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
	White        = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Blue         = FOREGROUND_BLUE,
	Green        = FOREGROUND_GREEN,
	Cyan         = FOREGROUND_GREEN | FOREGROUND_BLUE,
	Red          = FOREGROUND_RED,
	Purple       = FOREGROUND_RED   | FOREGROUND_BLUE,
	LightBlue    = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
	LightGreen   = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	LightCyan    = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
	LightRed     = FOREGROUND_RED   | FOREGROUND_INTENSITY,
	LightPurple  = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
	Orange       = FOREGROUND_RED   | FOREGROUND_GREEN,
	Yellow       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	BBlack       = 0,
	BGrey        = BACKGROUND_INTENSITY,
	BLightGrey   = BACKGROUND_RED   | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BWhite       = BACKGROUND_RED   | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BBlue        = BACKGROUND_BLUE,
	BGreen       = BACKGROUND_GREEN,
	BCyan        = BACKGROUND_GREEN | BACKGROUND_BLUE,
	BRed         = BACKGROUND_RED,
	BPurple      = BACKGROUND_RED   | BACKGROUND_BLUE,
	BLightBlue   = BACKGROUND_BLUE  | BACKGROUND_INTENSITY,
	BLightGreen  = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BLightCyan   = BACKGROUND_GREEN | BACKGROUND_BLUE  | BACKGROUND_INTENSITY,
	BLightRed    = BACKGROUND_RED   | BACKGROUND_INTENSITY,
	BLightPurple = BACKGROUND_RED   | BACKGROUND_BLUE  | BACKGROUND_INTENSITY,
	BOrange      = BACKGROUND_RED   | BACKGROUND_GREEN,
	BYellow      = BACKGROUND_RED   | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
};

void playerTry(int mystery);
void IATry(int mystery, int max);
int powTen(int puissance);
int getInterval(int mystery);
int numberQuery();
char characterQuery();
int color(WORD theColor);
void write(const char *text, ...);

int main(void)
{
	char choice = 0, max = 0;
	int mystery;
	srand(time(NULL));

	color(White);
	write("Bienvenue dans mon %ocplus ou moins%ow am\x82lior\x82 !\n");
	while (choice != 'n')
	{
		while (choice < 'a' || choice > 'd')
		{
			write("Choisissez le mode de jeu d\x82sir\x82 :\n");
			write(" %ora%ow : C'est vous qui devinez !\n");
			write(" %orb%ow : C'est l'ordinateur qui devine !\n");
			write(" %orc%ow : Mode deux joueurs.\n");
			write(" %ord%ow : quitter\n");
			choice = characterQuery();
			if (choice < 'a' || choice > 'd')
				write("Veuillez entrer un choix valide.\n");
		}
		if (choice == 'a')
		{
			while (max < 'a' || max > 'd')
			{
				write("Veuillez entrer un niveau de difficult\x82 :\n");
				write(" %ora%ow : Tr\x8As facile (entre %og0%ow et %og9%ow)\n");
				write(" %orb%ow : Facile (entre %og0%ow et %og99%ow)\n");
				write(" %orc%ow : Interm%lcdiaire (entre %og0%ow et %og999%ow)\n", 130);
				write(" %ord%ow : Difficile (entre %og0%ow et %og9999%ow)\n");
				max = characterQuery();
				if (max < 'a' || max > 'd')
					write("Veuillez entrer un choix valide.\n");
			}
		}

		switch (choice)
		{
			case 'a':
				playerTry(rand() % powTen(max - 'a' + 1));
			break;
			case 'b':
				write("Veuillez entrer le nombre que l'ordinateur devra deviner : ");
				mystery = numberQuery(10000);
				write("Le nombre \xE0 deviner est entre %og0%ow et %d.\n", getInterval(mystery));
				IATry(mystery, getInterval(mystery));
			break;
			case 'c':
				write("Veuillez entrer le nombre que le joueur 2 devra deviner : ");
				mystery = numberQuery(10000);
				write("Le nombre \xE0 deviner est entre %og0%ow et %d.\n", getInterval(mystery));
				playerTry(mystery);
			break;
			default:
				choice = 'n';
			break;
		}
		while (choice != 'o' && choice != 'n')
		{
			write("Voulez vous rejouer ? (%oro%ow/%orn%ow)\n");
			choice = characterQuery();
			if (choice != 'o' && choice != 'n')
				write("Veuillez entrer %oro%ow pour oui ou %orn%ow pour non.\n");
		}
		max = 0;
	}

	return 0;
}

void playerTry(int mystery)
{
	int askedNumber = -1, totalTime = 0, counter = 0;
	time_t start;

	time(&start);
	for (counter = 0 ; askedNumber != mystery ; counter++)
	{
		write("Quel est le nombre myst\x8Are : ");
		color(LightGreen);
		scanf("%d", &askedNumber);
		while (getchar() != '\n');
		color(White);
		if (askedNumber > mystery)
			write("C'est moins !\n\n");
		else if (askedNumber < mystery)
			write("C'est plus !\n\n");
	}
	totalTime = difftime(time(NULL), start);
	write("Bravo !\n");
	write("Vous avez mis %d essais pour trouver le nombre %d, le tout en %d secondes.\n", counter, mystery, totalTime);
	write("Ce qui fait en moyenne %fs par essai.\n", (double) totalTime / (double) counter);
}

void IATry(int mystery, int max)
{
	int testedNumber = max / 2;
	int min = 0;

	write("l'ordinateur teste le nombre %d.\n", testedNumber);
	while (testedNumber != mystery)
	{
		if (testedNumber < mystery)
		{
			write("C'est plus !\n");
			min = testedNumber;
			testedNumber = (max + min) / 2;
		}
		else if (testedNumber > mystery)
		{
			write("C'est moins !\n");
			max = testedNumber;
			testedNumber = (max + min) / 2;
		}
		write("l'ordinateur teste le nombre %d.\n", testedNumber);
	}
	write("L'IA a trouv\x82 le nombre.\n\n");
}

int powTen(int puissance)
{
	int number;

	for (number = 1 ; puissance ; puissance --)
		number *= 10;

	return number;
}

int getInterval(int mystery)
{
	int i;

	for (i = 10 ; i < mystery ; i *= 10);

	return i;
}

int numberQuery(int max)
{
	int number = -1;

	while (number < 0 || number >= max)
	{
		color(LightGreen);
		scanf("%d", &number);
		while (getchar() != '\n');
		color(White);
		clear();
		if (number < 0 || number >= max)
			write("Veuillez entrer un nombre entre 0 et %d.\n", max-1);
	}

	return number;
}

char characterQuery()
{
	char character;

	color(LightRed);
	character = getchar();
	while (getchar() != '\n');
	color(White);
	clear();

	return character;
}

int color(WORD theColor)
{
    #if defined WIN32 || defined WIN64
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        return SetConsoleTextAttribute(hConsole,theColor) ? 1 : 0;
    #else
        return 2;
    #endif
}

void write(const char *text, ...)
{
    int i = 0;
    va_list pa;
    va_start(pa, text);

    while (text[i] != 0) //Tant que je n'arrive pas au bout de la chaîne principale
    {
        while (text[i] != '%' && text[i] != 0)
        {
            putchar(text[i]);
            i++;
        } //Si fin de chaîne ou variable trouvée je sort de la boucle.
        if (text[i] != 0)
            i++; //Si c'est un % alors j'analyse le caractère d'après.
        switch(text[i])
        {
            case '%'://Si je trouve un double % j'en ajoute un à la chaîne finale.
                putchar('%');
                i++;
            break;
            case 'o':
                i++;
                switch(text[i])
                {
                    case 'c':
                        color(LightCyan);
                        i++;
                    break;
                    case 'g':
                        color(LightGreen);
                        i++;
                    break;
                    case 'r':
                        color(LightRed);
                        i++;
                    break;
                    case 'y':
                        color(Yellow);
                        i++;
                    break;
                    case 'w':
                        color(White);
                        i++;
                    break;
                    default:
                        color(White);
                    break;
                }
            break;
            case 'd'://Si je trouve un d alors c'est un entier.
                color(LightGreen);
                printf("%d", va_arg(pa, int)); //je l'ajoute à la chaîne finale,
                color(White);
                i++;
            break;
            case 'f':
                color(LightGreen);
                printf("%.1f", va_arg(pa, double));
                color(White);
                i++;
            break;
            case 'c': //Si c'est un caractère je l'ajoute bêtement à la chaîne finale.
                putchar(va_arg(pa, int));
                i++;
            break;
            case 's':
                color(LightPurple);
                printf(va_arg(pa, char*));
                color(White);
                i++;
            break;
            case 'l':
				i++;
				if (text[i] == 'c')
					printf("%lc", va_arg(pa, int));
				else
					printf("%%lc");
				i++;
            break;
            case 0: //Si c'est la fin de chaîne alors je sort du switch sans rien faire
            break;
            default://Et si je trouve un % sans rien de spécial derrière alors je l'affiche tout simplement.
                putchar('%');
            break;
        }
    }

    va_end(pa);
}
