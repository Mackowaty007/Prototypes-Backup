#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
	FILE* inputFile;
	FILE* outputFile;
	char ch;
	char ignoreThisLine = 'F';
	char printLineBeggining = 'T';
	char skipUntilNextSpaceBar = 'F';
	int  vertecieCounter = 0;

	// Opening file in reading mode
	inputFile = fopen("monkey.obj", "r");
	// Create a file to be used as output
	outputFile = fopen ("shape.h", "w");

	if (NULL == inputFile) {
		printf("file can't be opened \n");
	}

	fputs("#pragma once\n\n", outputFile);
	fputs("float vertecies[][3] = {\n",outputFile);

	
	do {
		ch = fgetc(inputFile);

		//check if this line is a comment or a useless element
		if (ch == '#' || ch == 'o' || ch == 'n' || ch == 't'){
			ignoreThisLine = 'T';
		}
		
		//start a new line
		if (ch == '\n'){
			ignoreThisLine = 'F';
		}

		//put the good stuff in the file
		if(ignoreThisLine == 'F'){
			//vertecies
			if(ch == 'v'){
				//skips the first space bar
				ch = fgetc(inputFile);
				if(ch == 'n' || ch == 't'){
					goto skip;
				}
				ch = fgetc(inputFile);

				fputc('{',outputFile);

				//write stuff until end of the line
				while(ch != '\n'){
					fputc(ch, outputFile);
					ch = fgetc(inputFile);
					if (ch == ' '){
						ch = ',';
					}
				}

				fputs("},\n",outputFile);
			}
			//faces
			if(ch == 'f'){
				if(printLineBeggining == 'T'){
					printLineBeggining = 'F';
					fputs("};",outputFile);
					fputs("\n\nint polygons[][4] = {\n",outputFile);
				}

				//skips the first space bar
				ch = fgetc(inputFile);
				ch = fgetc(inputFile);

				fputc('{',outputFile);

				//write stuff until end of the line
				while(ch != '\n'){
					if(skipUntilNextSpaceBar == 'F'){
						fputc(ch, outputFile);
					}

					ch = fgetc(inputFile);

					if (ch == ' ' || ch == '\n'){
						skipUntilNextSpaceBar = 'F';
					}
					if (ch == ' '){
						putc(',',outputFile);
						ch = fgetc(inputFile);
						vertecieCounter ++;
					}
					if (ch == '/'){
						skipUntilNextSpaceBar = 'T';
					}
				}
				//if there are too many vertecies per polygon
				if (vertecieCounter > 3){
					printf("you have a model with too many vertecies per polygon!\n");
				}
				//if your model has too little vertecies set their value to NULL = (-1)
				else if (vertecieCounter == 2){
					fputs(",0",outputFile);
				}
				vertecieCounter = 0;
				fputs("},\n",outputFile);
			}
			skip:
		}
	}while (ch != EOF);

	fputs("};",outputFile);

	// Closing the file
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
