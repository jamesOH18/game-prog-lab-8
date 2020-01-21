#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}


// Vertices for one Triangle
float vertices[] = { -1.0f,-1.0f,1.0f ,
1.0f,-1.0f,1.0f,
1.0f,1.0f,1.0f,
-1.0f,1.0f,1.0f,
-1.0f,-1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f,1.0f,-1.0f,
-1.0f,1.0f,-1.0f };




// Colors for those vertices
float colors[] = { 1.0f, 0.0f, 0.0f, 
0.0f, 1.0f, 0.0f, 
0.0f, 0.0f, 1.0f };

// Index to be drawn
unsigned int vertex_index[] = { 0,1,2,
2,3,0,
5,1,0,
0,4,5,
1,5,6,
6,2,1,
3,2,6,
6,7,3,
4,0,3,
3,7,4,
6,5,4,
4,7,6
};

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0, 0, -8);
	glEnable(GL_CULL_FACE);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f / 60.0f)
	{
		clock.restart();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			for (int i = 0; i < 24; i += 3)
			{
				
				vector.x = vertices[i];
				vector.y = vertices[i + 1];
				vector.z = vertices[i + 2];
				vector = matrix.rotationZ(0.01) * vector;
				vertices[i + 2] = vector.z;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			for (int i = 0; i < 24; i += 3)
			{
				
				vector.x = vertices[i];
				vector.y = vertices[i + 1];
				vector.z = vertices[i + 2];
				vector = matrix.rotationY(0.01) * vector;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
				vertices[i] = vector.x;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			for (int i = 0; i < 24; i += 3)
			{
				vector.x = vertices[i];
				vector.y = vertices[i + 1];
				vector.z = vertices[i + 2];
				vector = matrix.rotationX(0.01) * vector;
				vertices[i] = vector.x;
				vertices[i + 2] = vector.z;
				vertices[i + 1] = vector.y;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			for (int i = 0; i < 24; i += 3)
			{
				float z = vertices[i+2];
				vertices[i+2] = 1;
				vector.x = vertices[i];
				vector.y = vertices[i + 1];
				vector.z = vertices[i + 2];
				vector = matrix.translation({ 0.01, 0.01, 0.0 }) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i+2] = z;
				
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			for (int i = 0; i < 24; i += 3)
			{
				gpp::MyVector3 vector;
				vector.x = vertices[i];
				vector.y = vertices[i + 1];
				vector.z = vertices[i + 2];
				vector = matrix.scale(1.01) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			for (int i = 0; i < 24; i += 3)
			{
				gpp::MyVector3 vector;
				vector.x = vertices[i];
				vector.y = vertices[i + 1];
				vector.z = vertices[i + 2];
				vector = matrix.scale(0.99) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
			}
		}
	}
	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 36);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

