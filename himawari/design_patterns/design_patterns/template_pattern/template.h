#include <ctime>
#include <assert.h>
#include <iostream>

class Game
{
public:
    Game()
    {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    // A template method
    void PlayOneGame(const int players_count = 0)
    {
        if (players_count) {
            this->players_count_ = players_count;
        }

        InitializeGame();
        assert(this->players_count_);

        int j = 0;
        while (!EndOfGame()) {
            MakePlay(j);
            j = (j + 1) % this->players_count_;
            if (!j) {
                ++moves_count_;
            }
        }

        PrintWinner();
    }

protected:
    virtual void initializeGame() = 0;
    virtual void MakePlay(int player) = 0;
    virtual bool EndOfGame() = 0;
    virtual void PrintWinner() = 0;

private:
    void InitializeGame()
    {
        moves_count_ = 0;
        player_won_ = -1;
        initializeGame();
    }

protected:
    int players_count_ = 0;
    int moves_count_ = 0;
    int player_won_ = -1;
};