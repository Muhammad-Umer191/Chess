#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class ChessPiece 
{
protected:
    Sprite sprite;
    Texture texture;
    bool isWhitePiece;
    static constexpr int BOARD_SIZE = 8;
    static constexpr float cellWidth = 800.f / BOARD_SIZE; //window size of 800x800
    static constexpr float cellHeight = 800.f / BOARD_SIZE;

public:
    ChessPiece(const string& filename, const Vector2f& position, bool isWhite = true, float scale = 1.0f)
        : isWhitePiece(isWhite)
    {
        if (!texture.loadFromFile(filename)) 
        {
            cout << "Failed to load texture: " << filename << endl; // Use cout for error messages
        }
        else 
        {
            cout << "Texture loaded successfully for piece" << endl; // Use cout for general messages
            sprite.setTexture(texture);
            sprite.setPosition(position);
            sprite.setScale(scale, scale);
        }
    }

    virtual bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8])
    {
        return true;
    }

    virtual bool isWhite() const 
    {
        return isWhitePiece;
    }

    void draw(RenderWindow& window) 
    {
        window.draw(sprite);
    }

    void move(const Vector2f& newPosition) 
    {
        sprite.setPosition(newPosition);
    }

    Vector2f getPosition() const 
    {
        return sprite.getPosition();
    }
    int round_to_nearest_hundred(int value) 
    {
        int remainder = value % 100;
        if (remainder >= 50) 
        {
            return value + (100 - remainder);
        }
        else 
        {
            return value - remainder;
        }
    }
}; 

class Pawn : public ChessPiece
{
public:
    Pawn(const Vector2f& position, const string& filename, bool isWhite = true)
        : ChessPiece(filename, position, isWhite, 0.3f) {}

    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) override
    {
        //Finding actual position and taking the differnce from the next position and then moving it
        Vector2f currentPosition = getPosition();
        int currentX = static_cast<int>(currentPosition.x / cellWidth);
        int currentY = static_cast<int>(currentPosition.y / cellHeight);
        int newX = static_cast<int>(newPosition.x / cellWidth);
        int newY = static_cast<int>(newPosition.y / cellHeight);

        int deltaX = newX - currentX;
        int deltaY = newY - currentY;

        // Check if the new position is within the board bounds
        if (newX < 0 || newX >= BOARD_SIZE|| newY < 0 || newY >= BOARD_SIZE)
        {
            cout << "Invalid move: Out of bounds" << endl;
            return false;
        }

        cout << "Piece Position: " << currentX << " " << currentY << " New Position: " << newX << " " << newY << " DX : " << deltaX << " " << deltaY << endl;

        int direction = (isWhitePiece) ? 1 : -1;

        if (deltaX == 0)
        {
            if ((deltaY == direction && board[newY][newX] == nullptr) ||
                (currentY == (isWhitePiece ? 1 : 6) && deltaY == 2 * direction && board[newY][newX] == nullptr && board[currentY + direction][currentX] == nullptr))
            {
                cout << (isWhitePiece ? "White" : "Black") << " pawn moved forward " << abs(deltaY) << " step(s)" << endl;
                return true;
            }
            else
            {
                cout << "Invalid move: Pawn cannot move in that way" << endl;
                return false;
            }
        }

        else if (abs(deltaX) == 1 && deltaY == direction)
        {
            if (board[newY][newX] != nullptr && board[newY][newX]->isWhite() != isWhitePiece)
            {
                cout << (isWhitePiece ? "White" : "Black") << " pawn captured diagonally" << endl;
                return true;
            }
            else
            {
                cout << "Invalid move: No piece to capture or cannot capture own color" << endl;
                return false;
            }
        }
        else
        {
            cout << "Invalid move: Pawn cannot move in that way" << endl;
            return false;
        }
    }
};



class Rook : public ChessPiece 
{
public:
    Rook(const Vector2f& position, const string& filename, bool isWhite = true)
        : ChessPiece(filename, position, isWhite, 0.3f) {}

    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) 
    {
        Vector2f currentPosition = getPosition();
        int currentX = static_cast<int>(currentPosition.x / 100);
        int currentY = static_cast<int>(currentPosition.y / 100);
        int newX = static_cast<int>(newPosition.x / 100);
        int newY = static_cast<int>(newPosition.y / 100);

        int deltaX = newX - currentX;
        int deltaY = newY - currentY;

        if (deltaX == 0) {
            if (deltaY != 0) {
                int step = (deltaY > 0) ? 1 : -1;
                for (int i = currentY + step; i != newY; i += step)
                {
                    if (board[i][newX] != nullptr) 
                    {
                        cout << "Invalid move: Rook cannot jump over other pieces" << endl;
                        return false;
                    }
                }
            }
        }
        else if (deltaY == 0)
        {
            if (deltaX != 0) 
            {
                int step = (deltaX > 0) ? 1 : -1;
                for (int i = currentX + step; i != newX; i += step) 
                {
                    if (board[newY][i] != nullptr) 
                    {
                        cout << "Invalid move: Rook cannot jump over other pieces" << endl;
                        return false;
                    }
                }
            }
        }
        else {
            cout << "Invalid move: Rook moves horizontally or vertically only" << endl;
            return false;
        }

        // Check if destination square is occupied by a piece of the same color
        if (board[newY][newX] != nullptr && board[newY][newX]->isWhite() == this->isWhite()) {

            cout << "Invalid move: Rook cannot capture its own piece" << endl;
            return false;
        }

        return true;
    }



};


class Knight : public ChessPiece {
public:
    Knight(const Vector2f& position, const string& filename, bool isWhite = true)
        : ChessPiece(filename, position, isWhite, 0.3f) {}

    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) override {
        Vector2f currentPosition = getPosition();

        int currentX = static_cast<int>(currentPosition.x / cellWidth);
        int currentY = static_cast<int>(currentPosition.y / cellHeight);
        int newX = static_cast<int>(newPosition.x / cellWidth);
        int newY = static_cast<int>(newPosition.y / cellHeight);

        // Calculate the differences
        int deltaX = newX - currentX;
        int deltaY = newY - currentY;

        if (newPosition.x < 0 || newPosition.x >= BOARD_SIZE * cellWidth ||
            newPosition.y < 0 || newPosition.y >= BOARD_SIZE * cellHeight) {
            cout << "Invalid move: Out of bounds" << endl;
            return false;
        }

        int possibleMoves[8][2] =
        {
            {-2, -1}, {-2, 1},
            {-1, -2}, {-1, 2},
            {1, -2}, {1, 2},
            {2, -1}, {2, 1}
        };

        for (int i = 0; i < 8; ++i) {
            if (deltaX == possibleMoves[i][0] && deltaY == possibleMoves[i][1]) {

                if (board[newY][newX] != nullptr) {

                    if (board[newY][newX] == nullptr || board[newY][newX]->isWhite() != isWhitePiece) {

                        return true;
                    }
                    else {
                        // Invalid move: destination square is occupied by a piece of the same color
                        cout << "Invalid move: Knight cannot capture its own piece" << endl;
                        return false;
                    }

                }
                else {
                    return true;
                }
            }
        }

        cout << "Invalid move: Knight moves in an L-shape" << endl;
        return false;
    }
};


class Bishop : public ChessPiece {
public:
    Bishop(const Vector2f& position, const string& filename, bool isWhite = true)
        : ChessPiece(filename, position, isWhite, 0.3f) {}
    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) {
        Vector2f currentPosition = getPosition();
        float deltaX = abs(newPosition.x - currentPosition.x);
        float deltaY = abs(newPosition.y - currentPosition.y);
        deltaX = ceil(deltaX);
        deltaY = ceil(deltaY);
        currentPosition.x = ceil(currentPosition.x);
        currentPosition.y = ceil(currentPosition.y);
        deltaX = round_to_nearest_hundred(deltaX);
        deltaY = round_to_nearest_hundred(deltaY);
        cout << "bishop Position: " << currentPosition.x << " " << currentPosition.y << " New Position: " << newPosition.x << " " << newPosition.y << " DX : " << deltaX << " " << deltaY << endl;

        // Check if the new position is within the board bounds
        if (newPosition.x < 0 || newPosition.x >= BOARD_SIZE * cellWidth ||
            newPosition.y < 0 || newPosition.y >= BOARD_SIZE * cellHeight) {
            cout << "Invalid move: Out of bounds" << endl;
            return false;
        }

        // Bishop can move diagonally
        if (deltaX == deltaY) {
            int steps = max(deltaX, deltaY) / cellWidth; // Number of steps in the direction of movement
            Vector2f stepDelta = Vector2f((newPosition.x - currentPosition.x) / steps,
                (newPosition.y - currentPosition.y) / steps);


            // Check each intermediate position to see if it's empty
            for (int i = 1; i < steps; ++i) {
                Vector2f intermediatePosition = currentPosition + stepDelta * static_cast<float>(i);
                int cellRow = intermediatePosition.y / cellHeight;
                int cellCol = intermediatePosition.x / cellWidth;
                if (board[cellRow][cellCol] != nullptr) {
                    cout << "Invalid move: Bishop cannot jump over other pieces" << endl;
                    return false;
                }
            }

            // Check if the destination square is occupied by a piece of the same color
            int destRow = newPosition.y / cellHeight;
            int destCol = newPosition.x / cellWidth;
            if (board[destRow][destCol] != nullptr && board[destRow][destCol]->isWhite() == this->isWhite()) {
                cout << "Invalid move: Bishop cannot capture its own piece" << endl;
                return false;
            }

            cout << "Bishop moved" << endl;
            return true;
        }
        else {
            cout << "Invalid move: Bishop can only move diagonally" << endl;
            return false;
        }
    }


};

class Queen : public ChessPiece {
public:
    Queen(const Vector2f& position, const string& filename, bool isWhite = true)
        : ChessPiece(filename, position, isWhite, 0.3f) {}

    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) override {
        Vector2f currentPosition = getPosition();
        float deltaX = abs(newPosition.x - currentPosition.x);
        float deltaY = abs(newPosition.y - currentPosition.y);
        deltaX = ceil(deltaX);
        deltaY = ceil(deltaY);
        currentPosition.x = ceil(currentPosition.x);
        currentPosition.y = ceil(currentPosition.y);
        deltaX = round_to_nearest_hundred(deltaX);
        deltaY = round_to_nearest_hundred(deltaY);
        cout << "Position: " << currentPosition.x << " " << currentPosition.y << " New Position: " << newPosition.x << " " << newPosition.y << " DX : " << deltaX << " " << deltaY << endl;

        // Check if the new position is within the board bounds
        if (newPosition.x < 0 || newPosition.x >= BOARD_SIZE * cellWidth ||
            newPosition.y < 0 || newPosition.y >= BOARD_SIZE * cellHeight) {
            cout << "Invalid move: Out of bounds" << endl;
            return false;
        }

        // Check if the move is horizontal, vertical, or diagonal
        if ((deltaX == 0 && deltaY != 0) || (deltaX != 0 && deltaY == 0) || (deltaX == deltaY)) {
            int steps = max(deltaX, deltaY) / cellWidth; // Number of steps in the direction of movement
            Vector2f stepDelta = Vector2f((newPosition.x - currentPosition.x) / steps,
                (newPosition.y - currentPosition.y) / steps);

            // Check each intermediate position to see if it's empty
            for (int i = 1; i < steps; ++i) {
                Vector2f intermediatePosition = currentPosition + stepDelta * static_cast<float>(i);
                int cellRow = intermediatePosition.y / cellHeight;
                int cellCol = intermediatePosition.x / cellWidth;
                if (board[cellRow][cellCol] != nullptr) {
                    cout << "Invalid move: Piece cannot jump over other pieces" << endl;
                    return false;
                }
            }
            cout << "Piece moved" << endl;

            // Merge code snippet here
            int newX = static_cast<int>(newPosition.x / cellWidth);
            int newY = static_cast<int>(newPosition.y / cellHeight);
            //   bool isWhitePiece = /* your logic to determine whether the piece is white */;

            if (board[newY][newX] == nullptr || board[newY][newX]->isWhite() != isWhitePiece) {
                cout << "Queen moved" << endl;
                return true;
            }
            else {
                cout << "Invalid move: Destination occupied by own piece or enemy piece" << endl;
                return false;
            }
            // End merge

        }
        else {
            cout << "Invalid move: Piece can only move horizontally, vertically, or diagonally" << endl;
            return false;
        }
    }
};

class King : public ChessPiece {
public:
    King(const Vector2f& position, const string& filename, bool isWhite = true)
        : ChessPiece(filename, position, isWhite, 0.3f) {}

    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) override {
        Vector2f currentPosition = getPosition();
        float deltaX = abs(newPosition.x - currentPosition.x);
        float deltaY = abs(newPosition.y - currentPosition.y);
        deltaX = ceil(deltaX);
        deltaY = ceil(deltaY);
        currentPosition.x = ceil(currentPosition.x);
        currentPosition.y = ceil(currentPosition.y);
        deltaX = round_to_nearest_hundred(deltaX);
        deltaY = round_to_nearest_hundred(deltaY);
        cout << "Position: " << currentPosition.x << " " << currentPosition.y << " New Position: " << newPosition.x << " " << newPosition.y << " DX : " << deltaX << " " << deltaY << endl;

        // Check if the new position is within the board bounds
        if (newPosition.x < 0 || newPosition.x >= BOARD_SIZE * cellWidth ||
            newPosition.y < 0 || newPosition.y >= BOARD_SIZE * cellHeight) {
            cout << "Invalid move: Out of bounds" << endl;
            return false;
        }

        // Check if the move is one box in every direction
        if ((deltaX <= cellWidth && deltaY <= cellHeight) && (deltaX > 0 || deltaY > 0)) {
            // Check if the destination position is empty or contains an opponent's piece
            int newX = static_cast<int>(newPosition.x / cellWidth);
            int newY = static_cast<int>(newPosition.y / cellHeight);
            // bool isWhitePiece = /* your logic to determine whether the piece is white */

            if (board[newY][newX] == nullptr || board[newY][newX]->isWhite() != isWhitePiece) {
                cout << "King moved" << endl;
                return true;
            }
            else {
                cout << "Invalid move: Destination occupied by own piece or enemy piece" << endl;
                return false;
            }
        }
        else {
            cout << "Invalid move: King can only move one box in every direction" << endl;
            return false;
        }
    }
};

class ChessboardWindow {
private:
    RenderWindow window;
    static const int BOARD_SIZE = 8;
    ChessPiece* board[BOARD_SIZE][BOARD_SIZE];
    Vector2i selectedPiece;
    RectangleShape selectorBox;
    bool isWhiteTurn;

public:
    ChessboardWindow(int width, int height)
        : window(VideoMode(width, height), "Chessboard") {
        window.setFramerateLimit(60);
        selectedPiece = Vector2i(-1, -1);
        selectorBox.setSize(Vector2f(width / BOARD_SIZE, height / BOARD_SIZE));
        selectorBox.setOutlineThickness(3);
        selectorBox.setOutlineColor(Color::Green);
        isWhiteTurn = true;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (i <= 1 || i >= 6) {
                    if (i == 1) {
                        board[i][j] = new Pawn(Vector2f((j + 0.05f) * (width / static_cast<float>(BOARD_SIZE)),
                            (i + 0.05f) * (height / static_cast<float>(BOARD_SIZE))),
                            "w_pawn.png");
                    }
                    else if (i == 6) {
                        board[i][j] = new Pawn(Vector2f((j + 0.05f) * (width / static_cast<float>(BOARD_SIZE)),
                            (i + 0.05f) * (height / static_cast<float>(BOARD_SIZE))),
                            "b_pawn.png", false);
                    }
                    else {
                        if (i == 0 || i == 7) {
                            if (j == 0 || j == 7)
                                board[i][j] = new Rook(Vector2f((j + 0.05f) * (width / static_cast<float>(BOARD_SIZE)),
                                    (i + 0.05f) * (height / static_cast<float>(BOARD_SIZE))),
                                    i == 0 ? "w_rook.png" : "b_rook.png", i == 0 ? true : false);
                            else if (j == 1 || j == 6)
                                board[i][j] = new Knight(Vector2f((j + 0.05f) * (width / static_cast<float>(BOARD_SIZE)),
                                    (i + 0.05f) * (height / static_cast<float>(BOARD_SIZE))),
                                    i == 0 ? "w_knight.png" : "b_knight.png", i == 0 ? true : false);
                            else if (j == 2 || j == 5)
                                board[i][j] = new Bishop(Vector2f((j + 0.05f) * (width / static_cast<float>(BOARD_SIZE)),
                                    (i + 0.05f) * (height / static_cast<float>(BOARD_SIZE))),
                                    i == 0 ? "w_bishop.png" : "b_bishop.png", i == 0 ? true : false);
                            else if (j == 3)
                                board[i][j] = new Queen(Vector2f((j + 0.05f) * (width / static_cast<float>(BOARD_SIZE)),
                                    (i + 0.05f) * (height / static_cast<float>(BOARD_SIZE))),
                                    i == 0 ? "w_queen.png" : "b_queen.png", i == 0 ? true : false);
                            else if (j == 4)
                                board[i][j] = new King(Vector2f((j + 0.05f) * (width / static_cast<float>(BOARD_SIZE)),
                                    (i + 0.05f) * (height / static_cast<float>(BOARD_SIZE))),
                                    i == 0 ? "w_king.png" : "b_king.png", i == 0 ? true : false);
                        }
                    }
                }
                else {
                    board[i][j] = nullptr;
                }
            }
        }
    }

    ~ChessboardWindow() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] != nullptr) {
                    delete board[i][j];
                }
            }
        }
    }

    bool isKingCaptured(bool isWhite) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] != nullptr && dynamic_cast<King*>(board[i][j]) != nullptr && board[i][j]->isWhite() == isWhite) {
                    return false; // King is still on the board
                }
            }
        }
        return true; // King is captured
    }
    void draw() {
        window.clear();
        RectangleShape square(Vector2f(window.getSize().x / float(BOARD_SIZE), window.getSize().y / float(BOARD_SIZE)));
        Color color1(255, 255, 255);
        Color color2(78, 77, 34);
        bool isWhite = false;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                square.setPosition(j * (window.getSize().x / float(BOARD_SIZE)), i * (window.getSize().y / float(BOARD_SIZE)));
                square.setFillColor(isWhite ? color1 : color2);
                isWhite = !isWhite;
                window.draw(square);
            }
            isWhite = !isWhite;
        }

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] != nullptr) {
                    board[i][j]->draw(window);
                }
            }
        }

        if (selectedPiece.x != -1 && selectedPiece.y != -1) {
            Vector2f squarePosition(selectedPiece.y * (window.getSize().x / float(BOARD_SIZE)),
                selectedPiece.x * (window.getSize().y / float(BOARD_SIZE)));
            RectangleShape selector(Vector2f(window.getSize().x / float(BOARD_SIZE), window.getSize().y / float(BOARD_SIZE)));
            selector.setPosition(squarePosition);
            selector.setFillColor(Color::Transparent);
            selector.setOutlineThickness(9);
            selector.setOutlineColor(Color::Yellow);
            window.draw(selector);
        }

        window.display();
    }

    bool isOpen() {
        return window.isOpen();
    }

    void close() {
        window.close();
    }
    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePosition = Mouse::getPosition(window);
                    int clickedRow = mousePosition.y / (window.getSize().y / BOARD_SIZE);
                    int clickedCol = mousePosition.x / (window.getSize().x / BOARD_SIZE);
                    cout << "Clicked Cell: " << clickedRow << ", " << clickedCol << endl;
                    if (selectedPiece.x != -1 && selectedPiece.y != -1) {
                        if ((isWhiteTurn && board[selectedPiece.x][selectedPiece.y]->isWhite()) ||
                            (!isWhiteTurn && !board[selectedPiece.x][selectedPiece.y]->isWhite())) {
                            if (board[selectedPiece.x][selectedPiece.y] != nullptr) {
                                // Calculate the new position
                                float cellWidth = window.getSize().x / static_cast<float>(BOARD_SIZE);
                                float cellHeight = window.getSize().y / static_cast<float>(BOARD_SIZE);
                                Vector2f newPosition = Vector2f((clickedCol + 0.1f) * cellWidth, (clickedRow + 0.1f) * cellHeight);

                                // Check if the move is valid
                                if (board[selectedPiece.x][selectedPiece.y]->isValidMove(newPosition, board)) {
                                    // Move the piece if the move is valid
                                    board[selectedPiece.x][selectedPiece.y]->move(newPosition);
                                    board[clickedRow][clickedCol] = board[selectedPiece.x][selectedPiece.y];
                                    board[selectedPiece.x][selectedPiece.y] = nullptr;
                                    cout << "Moved Piece to: " << clickedRow << ", " << clickedCol << endl;
                                    draw();
                                    isWhiteTurn = !isWhiteTurn;
                                    cout << (isWhiteTurn ? "White's turn" : "Black's turn") << endl;
                                }
                                else {
                                    // If the move is not valid, don't move the piece
                                    cout << "Invalid move. Piece not moved." << endl;
                                }
                            }
                            // Reset the selected piece
                            selectedPiece.x = -1;
                            selectedPiece.y = -1;
                        }
                    }
                }
                else if (event.mouseButton.button == Mouse::Right) {
                    // Handle right mouse button press (selecting a piece)
                    Vector2i mousePosition = Mouse::getPosition(window);
                    int clickedRow = mousePosition.y / (window.getSize().y / BOARD_SIZE);
                    int clickedCol = mousePosition.x / (window.getSize().x / BOARD_SIZE);

                    if (board[clickedRow][clickedCol] != nullptr) {
                        cout << "Selected Piece: " << clickedRow << ", " << clickedCol << endl;
                        selectedPiece.x = clickedRow;
                        selectedPiece.y = clickedCol;
                    }
                    draw();
                }
            }
        }
    }
    void displayWinner(const string& winner) {
        // Display a message indicating the winner
        RenderWindow winnerWindow(VideoMode(400, 200), "Winner");
        Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font." << endl;
            // Handle font loading error
        }
        Text winnerText;
        winnerText.setFont(font);
        winnerText.setString(winner + " wins!");
        winnerText.setCharacterSize(40);
        winnerText.setFillColor(Color::White);
        winnerText.setPosition(100, 100);

        while (winnerWindow.isOpen()) {
            Event event;
            while (winnerWindow.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    winnerWindow.close();
                }
            }
            winnerWindow.clear();
            winnerWindow.draw(winnerText);
            winnerWindow.display();
        }
    }

   void run() {
    while (true) {
        handleEvents();
        draw();

        // Check if the white king is captured
        if (isKingCaptured(true)) {
            cout << "Black wins! White king is captured." << endl;
            displayWinner("Black");
            window.close(); // Close the window when the white king is captured
            break;
        }

        // Check if the black king is captured
        if (isKingCaptured(false)) {
            cout << "White wins! Black king is captured." << endl;
            displayWinner("White");
            window.close(); // Close the window when the black king is captured
            break;
        }
    }
}

};

class Menu {
private:
    RenderWindow window;
    Texture menubackground;
    Sprite menuBackground;
    Font font;
    Text playButton, exitButton, chessButton;

public:
    Menu(int width, int height) : window(VideoMode(width, height), "Menu") {
        window.setFramerateLimit(60);
        if (!font.loadFromFile("arial.ttf")) {
            cout << "Fonts in menu not loaded \n";
        }
        else {
            cout << "Font in menu loaded \n";
        }
        if (!menubackground.loadFromFile("background.jpeg")) {
            cout << "Menu background is not loaded \n";
        }
        else {
            cout << "Menu background loaded successfully\n";
        }
        menuBackground.setTexture(menubackground);
        menuBackground.setScale((float)window.getSize().x / menuBackground.getLocalBounds().width, (float)window.getSize().y / menuBackground.getLocalBounds().height);
        exitButton.setFont(font);
        exitButton.setString("EXIT");
        exitButton.setCharacterSize(80);
        exitButton.setFillColor(Color::Yellow);
        exitButton.setPosition(window.getSize().x / 2 - exitButton.getLocalBounds().width / 2, window.getSize().y / 2);
        playButton.setFont(font);
        playButton.setString("START");
        playButton.setCharacterSize(80);
        playButton.setFillColor(Color::Yellow);
        playButton.setPosition(window.getSize().x / 2 - playButton.getLocalBounds().width / 2, window.getSize().y / 2 - 100);

          }

    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    if (playButton.getFillColor() == Color::White) {
                        playButton.setFillColor(Color::Blue);
                        exitButton.setFillColor(Color::White);
                        chessButton.setFillColor(Color::White);
                    }
                }
                else if (event.key.code == Keyboard::Down) {
                    if (chessButton.getFillColor() == Color::White) {
                        playButton.setFillColor(Color::White);
                        exitButton.setFillColor(Color::White);
                        chessButton.setFillColor(Color::Red);
                    }
                }
                else if (event.key.code == Keyboard::Enter) {
                    if (exitButton.getFillColor() == Color::White) {
                        cout << "Bye-Bye button selected!" << endl;
                        window.close();
                        ChessboardWindow chessboard(800, 800);
                        chessboard.run();
                    }
                    else if (playButton.getFillColor() == Color::White) {
                        cout << "Let's go button selected!" << endl;
                        window.close();
                        ChessboardWindow chessboard(800, 800);
                        chessboard.run();
                    }
                    else if (chessButton.getFillColor() == Color::White) {
                        cout << "Chessboard button selected!" << endl;
                        window.close();
                        ChessboardWindow chessboard(800, 800);
                        chessboard.run();
                    }
                }
            }
        }
    }

    void draw()
    {
        window.clear();
        window.draw(menuBackground);
        window.draw(playButton);
        window.draw(exitButton);
        window.draw(chessButton);
        window.display();
    }

    bool isOpen()
    {
        return window.isOpen();
    }

    void run()
    {
        while (isOpen())
        {
            handleEvents();
            draw();
        }
    }
};

int main()
{
    Menu menu(800, 600);
    menu.run();
    return 0;
}