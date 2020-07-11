// GameAppCplus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// ---------- PROBLEM WARRIORS BATTLE TILL DEATH ----------
// Make this

#include <iostream>
#include <time.h>
#include <string>

class Warrior
{
private:
    std::string name;
    int health;
    int attackMax;
    int blockMax;
public:
    Warrior(std::string, int, int, int);
    ~Warrior();

    std::string GetName() {
        return this->name;
    }

    int GetHealth() {
        return this->health;
    }

    void SetHealth(int health) {
        this->health = health;
    }

    int Attack() {
        //std::cout << "this->attackMax = " << this->attackMax << "\n";
        return std::rand() % this->attackMax;
    }
    int Block() {
        //std::cout << "this->blockMax = " << this->blockMax << "\n";
        return std::rand() % this->blockMax;
    }
};

class Battle {
public:
    // We pass warriors into the function by reference so we can
    // track continued damage to each
    static void StartFight(Warrior& worrior1, Warrior& worrior2);
    static std::string GetAttackResults(Warrior& worrior1, Warrior& worrior2);
};
// warrio defination
Warrior::Warrior(std::string name, int health, int attackMax, int blockMax) {
    this->name = name;
    this->health = health;
    this->attackMax = attackMax;
    this->blockMax = blockMax;
}
Warrior::~Warrior() {
    std::cout << this->name << " is Destroyed..\n ";
}

// battle defination
// We continue to loop having each warrior take turns attacking
// until a warriors health < 0
void Battle::StartFight(Warrior& worrior1, Warrior& worrior2)
{
    while (true) {
        std::string attackResults1 = GetAttackResults(worrior2, worrior1);
        std::string attackResults2 = GetAttackResults(worrior1, worrior2);
        // comapre if both attack results === game over, end game
        if (attackResults1.compare("Game Over") == 1) {
            std::cout << "\n\nwe can not continue \n";
            break;
        }
        if (attackResults2.compare("Game Over") == 1) {
            std::cout << "\n\nwe can not continue \n";
            break;
        }
        else {
            std::cout << "Attack Result # 1 = " << attackResults1 
                      << "Attack Result # 2 = " << attackResults2;
            //std::cout << attackResults.compare("Game Over");
            std::cout << "\nwe can continue \n";
        }
    }
}
/*
Thor attacks Hulk and deals 12 damage
Hulk is down to 28 health
Hulk attacks Thor and deals 3 damage
Thor is down to 37 health
Thor attacks Hulk and deals 14 damage
Hulk is down to 14 health
Hulk attacks Thor and deals 0 damage
Thor is down to 37 health
Thor attacks Hulk and deals 14 damage
Hulk is down to 0 health
Hulk has Died and Thor is Victorious
Game Over
*/
std::string Battle::GetAttackResults(Warrior& worriorA, Warrior& worriorB)
{
    // Random attack and calculate damage
    int attackA = worriorA.Attack();
    int blockB = worriorB.Block();
    int damageDealsB = ceil(attackA - blockB);
    // not accept - value so
    damageDealsB = damageDealsB <= 0 ? 0 : damageDealsB;

    int nowHealthB = worriorB.GetHealth() - damageDealsB;
    worriorB.SetHealth(nowHealthB);
        //.SetHealth(worriorB.GetHealth() - damageDealsB);
    printf("%s attacks %s and deals %d damage\n",
        worriorA.GetName().c_str(),
        worriorB.GetName().c_str(),
        damageDealsB
    );
    printf("%s is down to %d health\n",
        worriorB.GetName().c_str(),
        worriorB.GetHealth()
    );
    // if health finished then game over
    if (worriorB.GetHealth() <= 0) {
        printf("\n\n##############################\n");        
        printf("%s is the loser with health %d and %s is the winner with health %d\n",
            worriorA.GetName().c_str(), worriorB.GetHealth(),
            worriorB.GetName().c_str(), worriorA.GetHealth()
        );
        printf("##############################\n\n");
        return "Game Over\n";
    } else {
        return "Continue Fighting\n";
    }
}

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    // Create Warriors
    Warrior hulk("Hulk", 150, 25, 12);
    Warrior thor("Thor", 100, 30, 10);

    // Create battle and have it run on its own till completion
    Battle::StartFight(hulk, thor);

    //std::string s1 = "Geeks";
    //std::string s2 = "Geeks";
    //int results = s1.compare(s2); // -1 not match, 0 = match
    //printf("Results = %d \n", results);
    return 0;
}


