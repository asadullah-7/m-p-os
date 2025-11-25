#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

float result(float v1, float v2, char op)
{
	switch (op)
	{
		case '+' : return v1 + v2;
		case '-' : return v1 - v2;
		case '*' : return  v1 * v2;
		case '%' : return (int)v1 % (int)v2;
		case '/' :
			if(v2 != 0)
			{
				
				return v1 / v2;
			}
			else
			{
				printf("INVLID OPERATION");
				return 0;
			}
		default : return 0;
	}

}

int main()
{
	float x;
	float y;
	char op;
	printf("Enter the value of x: ");
	scanf("%f", &x);
	printf("Enter the value of y: ");
	scanf("%f", &y);
	printf("Enter the operation: (+, -, *, /, %%) etc ");
	scanf(" %c", &op);

	printf("%.2f %c %.2f = %.2f", x, op, y, result(x,y,op));
	return 0;
}



