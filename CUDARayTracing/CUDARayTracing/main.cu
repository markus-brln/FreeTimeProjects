#include "main.ih"

//int SIZE_X = 1366;
//int SIZE_Y = 768;
int SIZE_X = 768;
int SIZE_Y = 768;


__global__ void print_hello_device()
{
	printf("hello from global function\n");
}


int main()
{
	print_hello_device << <1, 1 >> > ();
	cudaDeviceSynchronize();

	Model model;						// scene with objects
	sf::RenderWindow window{            // sf::Window is view 
		sf::VideoMode(SIZE_X, SIZE_Y),
		"Raytracing"
	};
	//window.setFramerateLimit(30);       // in case someone has a Threadripper CPU...

										// controller draws on window, changes model
	Controller controller{ model, window };

	controller.run();                   // start the game loop

    return 0;
}