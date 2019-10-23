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
	void setDifficulty(int level);

private:

	int difficulty;
	int enemies[5];
			

};