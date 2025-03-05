#include <Graphics.hpp>
#include <iostream>
using namespace std;

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;

void drawBoard(sf::RenderWindow &window, sf::Font &font) 
{
    window.clear(sf::Color::White);

    sf::RectangleShape line(sf::Vector2f(300, 5));
    line.setFillColor(sf::Color::Black);

    // Draw horizontal lines
    for (int i = 1; i < 3; i++) 
    {
        line.setPosition(50, 50 + i * 100);
        window.draw(line);
    }

    // Draw vertical lines
    line.setSize(sf::Vector2f(5, 300));
    for (int i = 1; i < 3; i++) 
    {
        line.setPosition(50 + i * 100, 50);
        window.draw(line);
    }

    // Draw markers
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (board[i][j] == 'X' || board[i][j] == 'O') 
            {
                sf::Text marker;
                marker.setFont(font);
                marker.setString(board[i][j]);
                marker.setCharacterSize(100);
                marker.setFillColor(sf::Color::Black);
                marker.setPosition(50 + j * 100, 50 + i * 100);
                window.draw(marker);
            }
        }
    }

    window.display();
}

bool placeMarker(int row, int col) 
{
    if (board[row][col] != 'X' && board[row][col] != 'O') 
    {
        board[row][col] = current_marker;
        return true;
    } 
    else 
    {
        return false;
    }
}

int winner() 
{
    // Rows
    for (int i = 0; i < 3; i++) 
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) 
        {
            return current_player;
        }
    }
    // Columns
    for (int i = 0; i < 3; i++) 
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) 
        {
            return current_player;
        }
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
    {
        return current_player;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
    {
        return current_player;
    }
    return 0;
}

void swapPlayerAndMarker() 
{
    if (current_marker == 'X') 
    {
        current_marker = 'O';
    } 
    else 
    {
        current_marker = 'X';
    }

    if (current_player == 1) 
    {
        current_player = 2;
    } 
    else 
    {
        current_player = 1;
    }
}

void game() 
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Tic Tac Toe");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) 
    {
        cout << "Error loading font" << endl;
        return;
    }

    current_player = 1;
    current_marker = 'X';

    drawBoard(window, font);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                int row = (y - 50) / 100;
                int col = (x - 50) / 100;

                if (row >= 0 && row < 3 && col >= 0 && col < 3) 
                {
                    if (placeMarker(row, col)) 
                    {
                        drawBoard(window, font);

                        int player_won = winner();

                        if (player_won == 1) 
                        {
                            cout << "Player one won! Congratulations!" << endl;
                            window.close();
                        }
                        if (player_won == 2) 
                        {
                            cout << "Player two won! Congratulations!" << endl;
                            window.close();
                        }

                        swapPlayerAndMarker();
                    }
                }
            }
        }
    }
}

int main() 
{
    game();
    return 0;
}
