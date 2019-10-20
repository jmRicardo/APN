#pragma once



class EnemiesManager
{
public:
	
	
	
	EnemiesManager();
	~EnemiesManager();

	void initPosition();
	void init(int level);
	void updatePosition();
	void draw();
	void checkDifficulty(int level);

private:

	int difficulty;
	int enemies;
		

};