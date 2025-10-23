#include "lifegame.hpp"

Game setUpGame(int nx, int ny, float width, float height){
	Game game(nx, ny, width, height);

	int cx = nx / 2;
	int cy = ny / 2;


	// game.life[cx+2][cy+1].alive = 1;
	// game.life[cx+2][cy+1].lifeTime = 25;
	// game.life[cx+2][cy+1].age = static_cast<float>(glfwGetTime());
	// game.life[cx+2][cy+2].alive = 1;
	// game.life[cx+2][cy+2].age = static_cast<float>(glfwGetTime());
	// game.life[cx+2][cy+2].lifeTime = 25;
	// game.life[cx+2][cy+3].alive = 1;
	// game.life[cx+2][cy+3].age = static_cast<float>(glfwGetTime());
	// game.life[cx+1][cy+3].lifeTime = 25;
	// game.life[cx+1][cy+1].alive = 1;
	// game.life[cx+1][cy+1].lifeTime = 25;
	// game.life[cx+1][cy+2].alive = 1;
	// game.life[cx+1][cy+2].lifeTime = 25;
	// game.life[cx+1][cy+2].age = static_cast<float>(glfwGetTime());
	// game.life[cx+1][cy+3].alive = 1;
	// game.life[cx+1][cy+3].lifeTime = 25;
	// game.life[cx+1][cy+3].age = static_cast<float>(glfwGetTime());
	// game.life[cx][cy+3].alive = 1;
	// game.life[cx][cy+3].lifeTime = 25;
	// game.life[cx][cy+2].alive = 1;
	// game.life[cx][cy+2].lifeTime = 25;
	// game.life[cx][cy+1].alive = 1;
	// game.life[cx][cy+1].lifeTime = 25;
	// game.life[cx][cy+1].age = static_cast<float>(glfwGetTime());

	for(int i = cx- cx/4; i < nx - cx/4; i++){
		for(int j = cy- cy/4; j < ny - cy/4; j++){

			if(i == cx || j == cy ){
				game.life[i][j].alive = 1;
				game.life[i][j].lifeTime = 25;
				game.life[i][j].age = static_cast<float>(glfwGetTime());
			}

			// int random = rand() % 2001;

			// if(random < 1){
			// 	game.life[i][j].alive = 1;
			// 	game.life[i][j].lifeTime = 25;
			// 	game.life[i][j].age = static_cast<float>(glfwGetTime());
			// }
		}
	}

	game.setUpVertices();

	return game;
}

void updateGame(Game& game, bool aléatoire){
	
	std::vector<std::vector<Cell>> next_step = game.life;
	
	#pragma omp parallel for
	for(int i = 0; i < game.nx; i++){
		for(int j = 0; j < game.ny; j++){

			bool droite      = (i + 1 < game.nx)             ? game.life[i + 1][j].alive            : false;
			bool gauche      = (i - 1 >= 0)                  ? game.life[i - 1][j].alive            : false;
			bool haut        = (j - 1 >= 0)                  ? game.life[i][j - 1].alive            : false;
			bool bas         = (j + 1 < game.ny)             ? game.life[i][j + 1].alive            : false;
			bool bas_droite  = (i + 1 < game.nx && j + 1 < game.ny) ? game.life[i + 1][j + 1].alive : false;
			bool bas_gauche  = (i - 1 >= 0 && j + 1 < game.ny) ? game.life[i - 1][j + 1].alive      : false;
			bool haut_droite = (i + 1 < game.nx && j - 1 >= 0) ? game.life[i + 1][j - 1].alive      : false;
			bool haut_gauche = (i - 1 >= 0 && j - 1 >= 0) ? game.life[i - 1][j - 1].alive 	      : false;

			int voisins = 0;
			voisins += droite;
			voisins += gauche;
			voisins += haut;
			voisins += bas;
			voisins += haut_droite;
			voisins += haut_gauche;
			voisins += bas_droite;
			voisins += bas_gauche;


			// if(game.life[i][j].lifeTime == 0)
			// 	next_step[i][j].alive = 0;
			// next_step[i][j].lifeTime -= 1;

			// int random = rand() % 101;


			if (game.life[i][j].alive) {
			    // survit si 2-4 voisins
			    if (voisins > 4 || voisins < 2){
			    	next_step[i][j].lifeTime = 0;
			        next_step[i][j].alive = 0;
			    }
			    // if (voisins == 3)
			    // 	next_step[i][j].lifeTime += 1;
			} else {
			    // naissance si 3 voisins
			    if (voisins == 3){
			    	// if(aléatoire){
			    	// 	if(random==99)
			    	// 		next_step[i][j].mutation = "killer";
			    	// 	if(random==98)
			    	// 		next_step[i][j].mutation = "creator";
			    	// 	if(random==100){
			    	// 		next_step[i][j].mutation = "long-life";
			    	// 		next_step[i][j].lifeTime = 50;
			    	// 	}
			    	// }
			    	next_step[i][j].lifeTime = 25;
			        next_step[i][j].alive = 1;
			        next_step[i][j].age = static_cast<float>(glfwGetTime());
			    }
			}
		
		}
	}


	for(int i = 0; i < game.nx; i++){
		for(int j = 0; j < game.ny; j++){

			next_step[i][j].age ++;

			// int random = rand() % 101;


			// if(game.life[i][j].mutation == "creator"){
			// 	next_step[i-1][j-1].alive = 1; next_step[i-1][j-1].lifeTime = 25;
			// 	next_step[i+1][j+1].alive = 1; next_step[i+1][j+1].lifeTime = 25;
			// 	next_step[i-1][j+1].alive = 1; next_step[i-1][j+1].lifeTime = 25;
			// 	next_step[i+1][j-1].alive = 1; next_step[i+1][j-1].lifeTime = 25;
			// }

			// if(game.life[i][j].mutation == "killer"){
			// 	int quart = random / 8;

			// 	Cell list[] = {
			// 		game.life[i-1][j-1], game.life[i][j-1], game.life[i+1][j-1],game.life[i+1][j], game.life[i+1][j+1], game.life[i][j+1], game.life[i+1][j+1]
			// 	};

			// 	Cell morte = list[quart - 1];

			// 	morte.lifeTime = 0;
			// 	morte.alive = 0;
			// }

		}
	}

	game.life = next_step;
	game.setUpVertices();
}




