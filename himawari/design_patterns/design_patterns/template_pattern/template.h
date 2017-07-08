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

// Now we can extend this class in order to implement actual games;
class Monopoly : public Game
{
public:
    // Implementation of necessary concrete methods
    void initializeGame()
    {
        players_count_ = rand() * 7 / RAND_MAX + 2;
    }

    void MakePlay(int player)
    {
        if (moves_count_ < 20) {
            return;
        }

        const int chances = (moves_count_ > 199) ? 199 : moves_count_;
        const int random = MOVES_WIN_CORRECTION * rand() * 200 / RAND_MAX;

        if (random < chances) {
            player_won_ = player;
        }
    }

    bool EndOfGame()
    {
        return (-1 != player_won_);
    }

    void PrintWinner() {
        assert(player_won_ >= 0);
        assert(player_won_ < players_count_);
        // Display who won
        std::cout << "Monopoly, player " << player_won_ << " won in " << moves_count_ << " moves. " << std::endl;
    }

private:
    enum
    {
        MOVES_WIN_CORRECTION = 20,
    };
};

class Chess : public Game
{
    // Implementation of necessary concrete methods
    void initializeGame()
    {
        players_count_ = 2;
    }

    void MakePlay(int player)
    {
        assert(player < players_count_);
        // Processs a turn for the player

        // Decide winner
        if (moves_count_ < 2) {
            return;
        }

        const int chances = (moves_count_ > 90) ? 90 : moves_count_;
        const int random = MOVES_WIN_CORRECTION * rand() * 100 / RAND_MAX;

        if (random < chances) {
            player_won_ = player;
        }
    }

    bool EndOfGame()
    {
        return (-1 != player_won_);
    }

    void PrintWinner()
    {
        assert(player_won_ >= 0);
        assert(player_won_ < players_count_);

        // Display the winning player
        std::cout << "Player " << player_won_ << " won in " << moves_count_ << " moves." << std::endl;
    }

private:
    enum
    {
        MOVES_WIN_CORRECTION = 7,
    };
};