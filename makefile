pong:
	g++ -std=c++11 -lGL -lglut -lGLU -o pong AIController.cpp Ball.cpp Board.cpp main.cpp Paddle.cpp PlayerController.cpp Pong.cpp PongGame.cpp Menu.cpp MenuItem.cpp PongText.cpp PongTextDraw.cpp

clean:
	rm pong
