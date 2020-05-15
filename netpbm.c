#include <stdio.h>
#include <stdlib.h>

#define TOGGLE 1	//Set to 0 to swap between binary and ASCII encoding (For P1, P4 auto set to 0)

int skipWhiteSpaces() {
	int currentIndex = getchar();
	while(currentIndex == '\n' || currentIndex == '\t' || currentIndex == 32	/*<space>*/) {	
		currentIndex = getchar();
	}
	return currentIndex;
}

int findValue(int currentIndex) {
	int value = currentIndex - '0'; 
	if(currentIndex < '0' || currentIndex > '9')
		return -1;
		
	currentIndex = getchar();	
	while(currentIndex!='\n' && currentIndex!='\t' & currentIndex!=32	/*<space>*/) {
		if(currentIndex < '0' || currentIndex > '9' || currentIndex == EOF)
			return -1;
		value = value*10 + (currentIndex - '0');
		currentIndex = getchar();
	}
	return value;
}

int main() {
	int magicNum, width, height, maxValue, currentIndex, toggle, count = 0;
	int red, green, blue, grayscaleColor, convertedColor;
	int currentColumn, currentRow, bit, byte = 0;
	int currentColor, mask = 128	/*10000000 (Binary)*/;
	
	if(getchar() == 'P')	
		magicNum = getchar() - '0';
	else {
		printf("Input Error!");
		return 1;
	}
	if(magicNum < 1 || magicNum > 6) {
		printf("Input Error!");
		return 1;	
	}
	
	currentIndex = skipWhiteSpaces();
	do {									//Skip all Comments
		if (currentIndex == '#') {			
			do {
				currentIndex = getchar();
			} while(currentIndex != '\n');	
			currentIndex = skipWhiteSpaces();
		}
	} while(currentIndex == '#');
	
	width = findValue(currentIndex);
	height = findValue(skipWhiteSpaces());
	if(height == -1) {
		printf("Input Error!");
		return 1;	
	}
	
	if(TOGGLE == 0 || magicNum == 1 || magicNum == 4)
		toggle = 0;
	else
		toggle = 1;
	
	if(toggle) {
		maxValue = findValue(skipWhiteSpaces());
		if(maxValue == -1) {
			printf("Input Error!");
			return 1;	
		}

		printf("P%d\n%d %d\n", magicNum-1, width, height);
		
		switch(magicNum) {
			case 3 :	//P3 -> P2
				printf("%d\n", maxValue);
				
				while(count < (width*height)) {
					red = findValue(skipWhiteSpaces());
					if(red == -1) {
						printf("Input Error!");
						return 1;	
					}
					green = findValue(skipWhiteSpaces());
					if(green == -1) {
						printf("Input Error!");
						return 1;	
					}
					blue = findValue(skipWhiteSpaces());
					if(blue == -1) {
						printf("Input Error!");
						return 1;	
					}
					convertedColor = (0.299*red) + (0.587*green) + (0.114*blue);
					printf("%d ", convertedColor);
					count++;
				}
				break;
			case 2 :	//P2 -> P1
				printf("%d ", maxValue);
				
				while(count < (width*height)) {
					grayscaleColor = findValue(skipWhiteSpaces());
					if(grayscaleColor == -1) {
						printf("Input Error!");
						return 1;
					}
					if(grayscaleColor > (maxValue+1)/2)
						convertedColor = 0;
					else
						convertedColor = 1;
						
					printf("%d ", convertedColor);
					count++;
				} 
				break;
			case 6 :	//P6 -> P5
				printf("%d ", maxValue);
				while(count < (width*height)) {
					red = getchar();				
					green = getchar();			
					blue = getchar();
					if(blue == EOF) {
						printf("\nInput Error!");
						return 1;
					}						
					convertedColor = (0.299*red) + (0.587*green) + (0.114*blue);
					printf("%c", convertedColor);
					count++;
				}
				break;
			case 5 :	//P5 -> P4
				for(currentRow = 1; currentRow <= height; currentRow++) {
					for(currentColumn = 1; currentColumn <= (width/8); currentColumn++) {
						for(bit = 1; bit <= 8; bit++) {
							grayscaleColor = getchar();	
							if(grayscaleColor == EOF) {
								printf("\nInput Error!");
								return 1;
							}			
							if(grayscaleColor <= (maxValue+1)/2)
								grayscaleColor = 1;
							else	
								grayscaleColor = 0;	
												
							byte = (byte*2) + grayscaleColor;
						}
						printf("%c", byte);
						byte = 0;
					}
					if(width % 8) {
						for(bit = 1; bit <= (width%8); bit++) {
							grayscaleColor = getchar();	
							if(grayscaleColor == EOF) {
								printf("\nInput Error!");
								return 1;
							}		
							if(grayscaleColor <= (maxValue+1)/2)
								grayscaleColor = 1;
							else	
								grayscaleColor = 0;		
											
							byte = (byte*2) + grayscaleColor;
						}
						for(bit = 1; bit <= (8-(width%8)); bit++)
							byte = (byte*2) + 1;
							
					printf("%c", byte);
					byte = 0;
					}
				}
				break;
		}
	} else {
		switch(magicNum) {
			case 3 :	//P3 -> P6	
				maxValue = findValue(skipWhiteSpaces());
				if(maxValue == -1) {
					printf("Input Error!");
					return 1;	
				} else
					printf("P%d\n%d %d\n%d\n", magicNum+3, width, height, maxValue);
				
				while(count < (width*height)*3) {
					currentColor = findValue(skipWhiteSpaces());
					if(currentColor == -1) {
						printf("\nInput Error!");
						return 1;
					}
					printf("%c", currentColor);
					count++;
				}
				break;
			case 6 :	//P6 -> P3
				maxValue = findValue(skipWhiteSpaces());
				if(maxValue == -1) {
					printf("Input Error!");
					return 1;	
				} else
					printf("P%d\n%d %d\n%d\n", magicNum-3, width, height, maxValue);
				
				while(count < (width*height)*3) {
					currentColor = getchar();
					if(currentColor == EOF) {
						printf("\nInput Error!");
						return 1;
					}		
					printf("%d ", currentColor);
					count++;
				}
				break;
			case 2 :	//P2 -> P5
				maxValue = findValue(skipWhiteSpaces());
				if(maxValue == -1) {
					printf("Input Error!");
					return 1;	
				} else
					printf("P%d\n%d %d\n%d\n", magicNum+3, width, height, maxValue);
				
				while(count < (width*height)) {
					currentColor = findValue(skipWhiteSpaces());
					if(currentColor == -1) {
						printf("\nInput Error!");
						return 1;
					}
					printf("%c", currentColor);
					count++;
				}
				break;
			case 5 :	//P5 -> P2
				maxValue = findValue(skipWhiteSpaces());
				if(maxValue == -1) {
					printf("Input Error!");
					return 1;	
				} else
					printf("P%d\n%d %d\n%d\n", magicNum-3, width, height, maxValue);
				
				while(count < (width*height)) {
					currentColor = getchar();
					if(currentColor == EOF) {
						printf("\nInput Error!");
						return 1;
					}	
					printf("%d ", currentColor);
					count++;
				}
				break;
			case 1 :	//P1 -> P4
				printf("P%d\n%d %d\n", magicNum+3, width, height);
				for(currentRow = 1; currentRow <= height; currentRow++) {
					for(currentColumn = 1; currentColumn <= (width/8); currentColumn++) {
						for(bit = 1; bit <= 8; bit++) {
							currentColor = findValue(skipWhiteSpaces());
							if(currentColor == -1) {
								printf("\nInput Error!");
								return 1;
							}					
							byte = (byte*2) + currentColor;
						}
						printf("%c", byte);
						byte = 0;
					}
					if(width % 8) {
						for(bit = 1; bit <= (width%8); bit++) {
							currentColor = findValue(skipWhiteSpaces());
							if(currentColor == -1) {
								printf("\nInput Error!");
								return 1;
							}					
							byte = (byte*2) + currentColor;
						}
						for(bit = 1; bit <= (8-(width%8)); bit++) 
							byte = (byte*2) + 1;
							
						printf("%c", byte);
						byte = 0;
					}
				}
				break;
			case 4 :	//P4 -> P1
				printf("P%d\n%d %d\n", magicNum-3, width, height);
				for(currentRow = 1; currentRow <=height ; currentRow++) {
					for(currentColumn = 1; currentColumn <= (width/8); currentColumn++) {
						currentColor = getchar();
						if(currentColor == EOF) {
							printf("\nInput Error!");
							return 1;
						}	
						for(bit = 1; bit <= 8; bit++) {
							if(currentColor & mask)
								printf("1 ");
							else
								printf("0 ");
								
							mask>>=1;
						}
						mask = 128;						
					}
					if(width % 8) {
						currentColor = getchar();
						if(currentColor == EOF) {
							printf("\nInput Error!");
							return 1;
						}	
						for(bit = 1; bit <= (width%8); bit++) {
							if(currentColor & mask)
								printf("1 ");
							else
								printf("0 ");
								
							mask>>=1;
						}
					}	
				}
		}
	}
}
