#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
using namespace std;

void InitGame(sf::RenderWindow& window);
void ComputeNextGen(sf::RenderWindow& window);
int ReturnNeighbors(int Xval, int Yval);


const int Size = 30;
const int ResX = 1920;
const int ResY = 1080;
const int x = ResX /Size;
const int y = ResY /Size;
const int Probability = 0.1;

sf::RectangleShape PastGameState[x][y];
sf::RectangleShape CurrentGameState[x][y];



int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game Of Life" ,sf::Style::Fullscreen);
    //window.setFramerateLimit(1);
    InitGame(window);
    window.display();

    
    window.setKeyRepeatEnabled(false);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            ComputeNextGen(window);
            memcpy(PastGameState, CurrentGameState, sizeof(CurrentGameState));
            window.display();
        }
        
        //ComputeNextGen(window);
        //auto begin = chrono::high_resolution_clock::now();
        //memcpy(PastGameState, CurrentGameState, sizeof(CurrentGameState));
        //auto end = chrono::high_resolution_clock::now();
        //auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
        ////cout << elapsed.count() << endl;

    }

    return 0;
}

void InitGame(sf::RenderWindow& window)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int num = (rand() % 1000) + 1;
            sf::RectangleShape newRec(sf::Vector2f(Size, Size));
            newRec.setOutlineColor(sf::Color::Black);
            newRec.setOutlineThickness(1);
            newRec.setPosition(i * Size, j * Size);

            if (num > 600)
            {
                newRec.setFillColor(sf::Color::White);
            }
            else
            {
                newRec.setFillColor(sf::Color::Black);
            }
            /*if((i == 96 && j == 54) || (i == 97 && j == 54) || (i == 100 && j == 54) || (i == 101 && j == 54) || (i == 102 && j == 54) || (i == 97 && j == 56) || (i == 99 && j == 55))
            {
                newRec.setFillColor(sf::Color::White);
            }
            
            else
            {
                newRec.setFillColor(sf::Color::Black);
            }*/
            
            window.draw(newRec);
            CurrentGameState[i][j] = newRec;
        }
    }
    memcpy(PastGameState, CurrentGameState, sizeof(CurrentGameState));
}

void ComputeNextGen(sf::RenderWindow& window)
{

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int NeighborCount = ReturnNeighbors(i, j);
            //cout << "XPos: " << i << ", YPos: " << j << ", Count: " << NeighborCount << endl;
            
            if(PastGameState[i][j].getFillColor() == sf::Color::White && NeighborCount == 2)//stay alive
            {
                CurrentGameState[i][j].setFillColor(sf::Color::White);
            }
            if (PastGameState[i][j].getFillColor() == sf::Color::White && NeighborCount == 3)//stay alive
            {
                CurrentGameState[i][j].setFillColor(sf::Color::White);
            }
            
            if(PastGameState[i][j].getFillColor() == sf::Color::White && NeighborCount > 3)//overpop death
            {
                CurrentGameState[i][j].setFillColor(sf::Color::Black);
            }
            else if(PastGameState[i][j].getFillColor() == sf::Color::White && NeighborCount < 2)//underpop death
            {
                CurrentGameState[i][j].setFillColor(sf::Color::Black);
            }
            else if(PastGameState[i][j].getFillColor() == sf::Color::Black && NeighborCount == 3)//rebirth
            {
                CurrentGameState[i][j].setFillColor(sf::Color::White);
            }
            window.draw(CurrentGameState[i][j]);
        }
    }





}

int ReturnNeighbors(int Xval, int Yval)
{
    int XPos = Xval, YPos = Yval;
    int count = 0;
    for (int i = (Xval-1); i <= (Xval+1); i++)
    {
        for (int j = (Yval-1); j <= (Yval+1); j++)
        {
            if (XPos != i || YPos != j)
            {
                int NewVarX = i % x;
                int NewVarY = j % y;
                if (i == -1 && j == -1)
                {
                    NewVarX = (i + x) % x;
                    NewVarY = (j + y) % y;
                }
                else if (i == -1)
                {
                    NewVarX = (i + x) % x;
                }
                else if (j == -1)
                {
                    NewVarY = (j + y) % y;
                }
                if (PastGameState[NewVarX][NewVarY].getFillColor() == sf::Color::White)
                {
                    count++;
                }
            }
            
        }
    }
    return count;
}