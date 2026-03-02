//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace sf;
//
//class ChessPiece 
//{
//protected:
//    Sprite sprite;
//    Texture texture;
//    bool isWhitePiece;
//    static constexpr int boardSize = 8;
//    //Window size is set to be of 800X800
//    static constexpr float cellWidth = 800.f / boardSize;
//    static constexpr float cellHeight = 800.f / boardSize;
//
//public:
//    ChessPiece(const string& filename, const Vector2f& position, bool isWhite = true, float scale = 1.0f)
//        : isWhitePiece(isWhite) 
//    {
//        //File handelling
//        if (!texture.loadFromFile(filename)) 
//        {
//            cout << "Failed to load texture: " << filename << endl;
//        }
//        else
//        {
//            cout << "Texture loaded successfully for piece" << endl;
//            sprite.setTexture(texture);
//            sprite.setPosition(position);
//            sprite.setScale(scale, scale);
//        }
//    }
//
//    //For proper movement of Chess Pieces
//    virtual bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8])
//    {
//        return true;
//    }
//
//    virtual bool isWhite() const
//    {
//        return isWhitePiece;
//    }
//
//    void draw(RenderWindow& window)
//    {
//        window.draw(sprite);
//    }
//
//    void move(const Vector2f& newPosition)
//    {
//        sprite.setPosition(newPosition);
//    }
//
//    Vector2f getPosition() const 
//    {
//        return sprite.getPosition();
//    }
//    int roundToNearestHundred(int value) 
//    {
//        int remainder = value % 100;
//        if (remainder >= 50) 
//        {
//            return value + (100 - remainder);
//        }
//        else
//        {
//            return value - remainder;
//        }
//    }
//};
//
//class Pawn : public ChessPiece 
//{
//public:
//    Pawn(const Vector2f& position, const string& filename, bool isWhite = true)
//        : ChessPiece(filename, position, isWhite, 0.3f) {}
//
//    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) override
//    {
//        //Finding actual position and taking the differnce from the next position and then moving it
//        Vector2f currentPosition = getPosition();
//        int currentX = static_cast<int>(currentPosition.x / cellWidth);
//        int currentY = static_cast<int>(currentPosition.y / cellHeight);
//        int newX = static_cast<int>(newPosition.x / cellWidth);
//        int newY = static_cast<int>(newPosition.y / cellHeight);
//
//        int deltaX = newX - currentX;
//        int deltaY = newY - currentY;
//
//        // Check if the new position is within the board bounds
//        if (newX < 0 || newX >= boardSize || newY < 0 || newY >= boardSize) 
//        {
//            cout << "Invalid move: Out of bounds" << endl;
//            return false;
//        }
//
//        cout << "Piece Position: " << currentX << " " << currentY << " New Position: " << newX << " " << newY << " DX : " << deltaX << " " << deltaY << endl;
//
//        int direction = (isWhitePiece) ? 1 : -1;
//
//        if (deltaX == 0)
//        {
//            if ((deltaY == direction && board[newY][newX] == nullptr) ||
//                (currentY == (isWhitePiece ? 1 : 6) && deltaY == 2 * direction && board[newY][newX] == nullptr && board[currentY + direction][currentX] == nullptr))
//            {
//                cout << (isWhitePiece ? "White" : "Black") << " pawn moved forward " << abs(deltaY) << " step(s)" << endl;
//                return true;
//            }
//            else 
//            {
//                cout << "Invalid move: Pawn cannot move in that way" << endl;
//                return false;
//            }
//        }
//        
//        else if (abs(deltaX) == 1 && deltaY == direction) 
//        {
//            if (board[newY][newX] != nullptr && board[newY][newX]->isWhite() != isWhitePiece) 
//            {
//                cout << (isWhitePiece ? "White" : "Black") << " pawn captured diagonally" << endl;
//                return true;
//            }
//            else 
//            {
//                cout << "Invalid move: No piece to capture or cannot capture own color" << endl;
//                return false;
//            }
//        }
//        else 
//        {
//            cout << "Invalid move: Pawn cannot move in that way" << endl;
//            return false;
//        }
//    }
//};
//
//
//class Rook : public ChessPiece
//{
//public:
//    Rook(const Vector2f& position, const string& filename, bool isWhite = true)
//        : ChessPiece(filename, position, isWhite, 0.3f) {}
//
//    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8])
//    {
//        //Finding actual position and taking the differnce from the next position and then moving it
//        Vector2f currentPosition = getPosition();
//        int currentX = static_cast<int>(currentPosition.x / 100);
//        int currentY = static_cast<int>(currentPosition.y / 100);
//        int newX = static_cast<int>(newPosition.x / 100);
//        int newY = static_cast<int>(newPosition.y / 100);
//
//        int deltaX = newX - currentX;
//        int deltaY = newY - currentY;
//
//        if (deltaX == 0) 
//        {
//            if (deltaY != 0) 
//            {
//                int step = (deltaY > 0) ? 1 : -1;
//                for (int i = currentY + step; i != newY; i += step) 
//                {
//                    if (board[i][newX] != nullptr) 
//                    {
//                        cout << "Invalid move: Rook cannot jump over other pieces" << endl;
//                        return false;
//                    }
//                }
//            }
//        }
//        else if (deltaY == 0) 
//        {
//            if (deltaX != 0) 
//            {
//                int step = (deltaX > 0) ? 1 : -1;
//                for (int i = currentX + step; i != newX; i += step)
//                {
//                    if (board[newY][i] != nullptr) 
//                    {
//                        cout << "Invalid move: Rook cannot jump over other pieces" << endl;
//                        return false;
//                    }
//                }
//            }
//        }
//        else
//        {
//            cout << "Invalid move: Rook moves horizontally or vertically only" << endl;
//            return false;
//        }
//        if (board[newY][newX] != nullptr && board[newY][newX]->isWhite() == this->isWhite()) 
//        {
//
//            cout << "Invalid move: Rook cannot capture its own piece" << endl;
//            return false;
//        }
//
//        return true;
//    }
//
//
//
//};
//
//
//class Knight : public ChessPiece 
//{
//public:
//    Knight(const Vector2f& position, const string& filename, bool isWhite = true)
//        : ChessPiece(filename, position, isWhite, 0.3f) {}
//
//    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) override
//    {
//        //Finding actual position and taking the differnce from the next position and then moving it
//        Vector2f currentPosition = getPosition();
//        int currentX = static_cast<int>(currentPosition.x / cellWidth);
//        int currentY = static_cast<int>(currentPosition.y / cellHeight);
//        int newX = static_cast<int>(newPosition.x / cellWidth);
//        int newY = static_cast<int>(newPosition.y / cellHeight);
//        int deltaX = newX - currentX;
//        int deltaY = newY - currentY;
//
//        // Check if the new position is within the board bounds
//        if (newPosition.x < 0 || newPosition.x >= boardSize * cellWidth ||
//            newPosition.y < 0 || newPosition.y >= boardSize * cellHeight) 
//        {
//            cout << "Invalid move: Out of bounds" << endl;
//            return false;
//        }
//        //Hard coding the moves of Knight
//        int possibleMoves[8][2] =
//        {
//            {-2, -1}, {-2, 1},
//            {-1, -2}, {-1, 2},
//            {1, -2}, {1, 2},
//            {2, -1}, {2, 1}
//        };
//
//        for (int i = 0; i < 8; ++i)
//        {
//            if (deltaX == possibleMoves[i][0] && deltaY == possibleMoves[i][1]) 
//            {
//
//                if (board[newY][newX] != nullptr) 
//                {
//
//                    if (board[newY][newX] == nullptr || board[newY][newX]->isWhite() != isWhitePiece)
//                    {
//
//                        return true;
//                    }
//                    else 
//                    {
//                        cout << "Invalid move: Knight cannot capture its own piece" << endl;
//                        return false;
//                    }
//
//                }
//                else 
//                {
//                    return true;
//                }
//            }
//        }
//
//        cout << "Invalid move: Knight moves in an L-shape" << endl;
//        return false;
//    }
//};
//
//
//class Bishop : public ChessPiece 
//{
//public:
//    Bishop(const Vector2f& position, const string& filename, bool isWhite = true)
//        : ChessPiece(filename, position, isWhite, 0.3f) {}
//    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8])
//    {
//        //Finding actual position and taking the differnce from the next position and then moving it
//        Vector2f currentPosition = getPosition();
//        float deltaX = abs(newPosition.x - currentPosition.x);
//        float deltaY = abs(newPosition.y - currentPosition.y);
//        deltaX = ceil(deltaX);
//        deltaY = ceil(deltaY);
//        currentPosition.x = ceil(currentPosition.x);
//        currentPosition.y = ceil(currentPosition.y);
//        deltaX = roundToNearestHundred(deltaX);
//        deltaY = roundToNearestHundred(deltaY);
//        cout << "bishop Position: " << currentPosition.x << " " << currentPosition.y << " New Position: " << newPosition.x << " " << newPosition.y << " DX : " << deltaX << " " << deltaY << endl;
//
//        // Check if the new position is within the board bounds
//        if (newPosition.x < 0 || newPosition.x >= boardSize * cellWidth ||
//            newPosition.y < 0 || newPosition.y >= boardSize * cellHeight) 
//        {
//            cout << "Invalid move: Out of bounds" << endl;
//            return false;
//        }
//        if (deltaX == deltaY)
//        {
//            int steps = max(deltaX, deltaY) / cellWidth; 
//            Vector2f stepDelta = Vector2f((newPosition.x - currentPosition.x) / steps,
//                (newPosition.y - currentPosition.y) / steps);
//
//            for (int i = 1; i < steps; i++) 
//            {
//                Vector2f intermediatePosition = currentPosition + stepDelta * static_cast<float>(i);
//                int cellRow = intermediatePosition.y / cellHeight;
//                int cellCol = intermediatePosition.x / cellWidth;
//                if (board[cellRow][cellCol] != nullptr)
//                {
//                    cout << "Invalid move: Bishop cannot jump over other pieces" << endl;
//                    return false;
//                }
//            }
//
//            int destRow = newPosition.y / cellHeight;
//            int destCol = newPosition.x / cellWidth;
//            if (board[destRow][destCol] != nullptr && board[destRow][destCol]->isWhite() == this->isWhite()) {
//                cout << "Invalid move: Bishop cannot capture its own piece" << endl;
//                return false;
//            }
//
//            cout << "Bishop moved" << endl;
//            return true;
//        }
//        else 
//        {
//            cout << "Invalid move: Bishop can only move diagonally" << endl;
//            return false;
//        }
//    }
//
//
//};
//
//class Queen : public ChessPiece 
//{
//public:
//    Queen(const Vector2f& position, const string& filename, bool isWhite = true)
//        : ChessPiece(filename, position, isWhite, 0.3f) {}
//
//    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) override 
//    {
//        //Finding actual position and taking the differnce from the next position and then moving it
//        Vector2f currentPosition = getPosition();
//        float deltaX = abs(newPosition.x - currentPosition.x);
//        float deltaY = abs(newPosition.y - currentPosition.y);
//        deltaX = ceil(deltaX);
//        deltaY = ceil(deltaY);
//        currentPosition.x = ceil(currentPosition.x);
//        currentPosition.y = ceil(currentPosition.y);
//        deltaX = roundToNearestHundred(deltaX);
//        deltaY = roundToNearestHundred(deltaY);
//        cout << "Position: " << currentPosition.x << " " << currentPosition.y << " New Position: " << newPosition.x << " " << newPosition.y << " DX : " << deltaX << " " << deltaY << endl;
//        
//        // Check if the new position is within the board bounds
//        if (newPosition.x < 0 || newPosition.x >= boardSize * cellWidth ||
//            newPosition.y < 0 || newPosition.y >= boardSize * cellHeight) 
//        {
//            cout << "Invalid move: Out of bounds" << endl;
//            return false;
//        }
//
//        if ((deltaX == 0 && deltaY != 0) || (deltaX != 0 && deltaY == 0) || (deltaX == deltaY))
//        {
//            int steps = max(deltaX, deltaY) / cellWidth;
//            Vector2f stepDelta = Vector2f((newPosition.x - currentPosition.x) / steps,
//                (newPosition.y - currentPosition.y) / steps);
//            for (int i = 1; i < steps; ++i) 
//            {
//                Vector2f intermediatePosition = currentPosition + stepDelta * static_cast<float>(i);
//                int cellRow = intermediatePosition.y / cellHeight;
//                int cellCol = intermediatePosition.x / cellWidth;
//                if (board[cellRow][cellCol] != nullptr) 
//                {
//                    cout << "Invalid move: Piece cannot jump over other pieces" << endl;
//                    return false;
//                }
//            }
//            cout << "Queen moved" << endl;
//            int newX = static_cast<int>(newPosition.x / cellWidth);
//            int newY = static_cast<int>(newPosition.y / cellHeight);
//            if (board[newY][newX] == nullptr || board[newY][newX]->isWhite() != isWhitePiece) 
//            {
//                cout << "Queen moved" << endl;
//                return true;
//            }
//            else 
//            {
//                cout << "Invalid move: Destination occupied by own piece or enemy piece" << endl;
//                return false;
//            }
//        }
//        else 
//        {
//            cout << "Invalid move: Piece can only move horizontally, vertically, or diagonally" << endl;
//            return false;
//        }
//    }
//};
//
//class King : public ChessPiece
//{
//public:
//    King(const Vector2f& position, const string& filename, bool isWhite = true)
//        : ChessPiece(filename, position, isWhite, 0.3f) {}
//
//    bool isValidMove(const Vector2f& newPosition, ChessPiece* board[][8]) override 
//    {
//        //Finding actual position and taking the differnce from the next position and then moving it
//        Vector2f currentPosition = getPosition();
//        float deltaX = abs(newPosition.x - currentPosition.x);
//        float deltaY = abs(newPosition.y - currentPosition.y);
//        deltaX = ceil(deltaX);
//        deltaY = ceil(deltaY);
//        currentPosition.x = ceil(currentPosition.x);
//        currentPosition.y = ceil(currentPosition.y);
//        deltaX = roundToNearestHundred(deltaX);
//        deltaY = roundToNearestHundred(deltaY);
//        cout << "Position: " << currentPosition.x << " " << currentPosition.y << " New Position: " << newPosition.x << " " << newPosition.y << " DX : " << deltaX << " " << deltaY << endl;
//
//        // Check if the new position is within the board bounds
//        if (newPosition.x < 0 || newPosition.x >= boardSize * cellWidth ||
//            newPosition.y < 0 || newPosition.y >= boardSize * cellHeight)
//        {
//            cout << "Invalid move: Out of bounds" << endl;
//            return false;
//        }
//        if ((deltaX <= cellWidth && deltaY <= cellHeight) && (deltaX > 0 || deltaY > 0))
//        {
//            int newX = static_cast<int>(newPosition.x / cellWidth);
//            int newY = static_cast<int>(newPosition.y / cellHeight);
//
//            if (board[newY][newX] == nullptr || board[newY][newX]->isWhite() != isWhitePiece) 
//            {
//                cout << "King moved" << endl;
//                return true;
//            }
//            else
//            {
//                cout << "Invalid move: Destination occupied by own piece or enemy piece" << endl;
//                return false;
//            }
//        }
//        else 
//        {
//            cout << "Invalid move: King can only move one box in every direction" << endl;
//            return false;
//        }
//    }
//};
//
//class ChessboardWindow 
//{
//private:
//    RenderWindow window;
//    static const int boardSize = 8;
//    ChessPiece* board[boardSize][boardSize];
//    Vector2i selectedPiece;
//    RectangleShape selectorBox;
//    bool isWhiteTurn;
//    SoundBuffer move;
//    SoundBuffer capture;
//    SoundBuffer exit;
//
//public:
//    ChessboardWindow(int width, int height)
//        : window(VideoMode(width, height), "Chessboard") 
//    {
//        window.setFramerateLimit(60);
//        selectedPiece = Vector2i(-1, -1);
//        selectorBox.setSize(Vector2f(width / boardSize, height / boardSize));
//        selectorBox.setOutlineThickness(3);
//        selectorBox.setOutlineColor(Color::Green);
//        isWhiteTurn = true;
//        for (int i = 0; i < boardSize; i++) 
//        {
//            for (int j = 0; j < boardSize; j++) 
//            {
//                if (i <= 1 || i >= 6)
//                {
//                    if (i == 1) 
//                    {
//                        board[i][j] = new Pawn(Vector2f((j + 0.05f) * (width / static_cast<float>(boardSize)),
//                            (i + 0.05f) * (height / static_cast<float>(boardSize))),
//                            "w_pawn.png");
//                    }
//                    else if (i == 6) 
//                    {
//                        board[i][j] = new Pawn(Vector2f((j + 0.05f) * (width / static_cast<float>(boardSize)),
//                            (i + 0.05f) * (height / static_cast<float>(boardSize))),
//                            "b_pawn.png", false);
//                    }
//                    else 
//                    {
//                        if (i == 0 || i == 7) 
//                        {
//                            if (j == 0 || j == 7)
//                                board[i][j] = new Rook(Vector2f((j + 0.05f) * (width / static_cast<float>(boardSize)),
//                                    (i + 0.05f) * (height / static_cast<float>(boardSize))),
//                                    i == 0 ? "w_rook.png" : "b_rook.png", i == 0 ? true : false);
//                            else if (j == 1 || j == 6)
//                                board[i][j] = new Knight(Vector2f((j + 0.05f) * (width / static_cast<float>(boardSize)),
//                                    (i + 0.05f) * (height / static_cast<float>(boardSize))),
//                                    i == 0 ? "w_knight.png" : "b_knight.png", i == 0 ? true : false);
//                            else if (j == 2 || j == 5)
//                                board[i][j] = new Bishop(Vector2f((j + 0.05f) * (width / static_cast<float>(boardSize)),
//                                    (i + 0.05f) * (height / static_cast<float>(boardSize))),
//                                    i == 0 ? "w_bishop.png" : "b_bishop.png", i == 0 ? true : false);
//                            else if (j == 3)
//                                board[i][j] = new Queen(Vector2f((j + 0.05f) * (width / static_cast<float>(boardSize)),
//                                    (i + 0.05f) * (height / static_cast<float>(boardSize))),
//                                    i == 0 ? "w_queen.png" : "b_queen.png", i == 0 ? true : false);
//                            else if (j == 4)
//                                board[i][j] = new King(Vector2f((j + 0.05f) * (width / static_cast<float>(boardSize)),
//                                    (i + 0.05f) * (height / static_cast<float>(boardSize))),
//                                    i == 0 ? "w_king.png" : "b_king.png", i == 0 ? true : false);
//                        }
//                    }
//                }
//                else
//                {
//                    board[i][j] = nullptr;
//                }
//            }
//        }
//
//        move.loadFromFile("Move.wav");
//        capture.loadFromFile("Capture.wav");
//        Sound capture(capture);
//        exit.loadFromFile("Exit.wav");
//
//    }
//
//    ~ChessboardWindow() 
//    {
//        for (int i = 0; i < boardSize; i++) 
//        {
//            for (int j = 0; j < boardSize; j++) 
//            {
//                if (board[i][j] != nullptr)
//                {
//                    delete board[i][j];
//                }
//            }
//        }
//    }
//
//    //Tell when the game is ended
//    bool isKingCaptured(bool isWhite) 
//    {
//        for (int i = 0; i < boardSize; i++) 
//        {
//            for (int j = 0; j < boardSize; j++)
//            {
//                if (board[i][j] != nullptr && dynamic_cast<King*>(board[i][j]) != nullptr && board[i][j]->isWhite() == isWhite) 
//                {
//                    return false; 
//                }
//            }
//        }
//        Sound exit(exit);
//        exit.play();
//        return true;
//    }
//    void draw() 
//    {
//        window.clear();
//        RectangleShape square(Vector2f(window.getSize().x / float(boardSize), window.getSize().y / float(boardSize)));
//        Color color1(255, 255, 255);
//        Color color2(78, 77, 34);
//        bool isWhite = false;
//
//        for (int i = 0; i < boardSize; i++) 
//        {
//            for (int j = 0; j < boardSize; j++)
//            {
//                square.setPosition(j * (window.getSize().x / float(boardSize)), i * (window.getSize().y / float(boardSize)));
//                square.setFillColor(isWhite ? color1 : color2);
//                isWhite = !isWhite;
//                window.draw(square);
//            }
//            isWhite = !isWhite;
//        }
//
//        for (int i = 0; i < boardSize; i++) 
//        {
//            for (int j = 0; j < boardSize; j++)
//            {
//                if (board[i][j] != nullptr) {
//                    board[i][j]->draw(window);
//                }
//            }
//        }
//
//        if (selectedPiece.x != -1 && selectedPiece.y != -1)
//        {
//            Vector2f squarePosition(selectedPiece.y * (window.getSize().x / float(boardSize)),
//                selectedPiece.x * (window.getSize().y / float(boardSize)));
//            RectangleShape selector(Vector2f(window.getSize().x / float(boardSize), window.getSize().y / float(boardSize)));
//            selector.setPosition(squarePosition);
//            selector.setFillColor(Color::Transparent);
//            selector.setOutlineThickness(7);
//            selector.setOutlineColor(Color::Black);
//            window.draw(selector);
//        }
//
//        window.display();
//    }
//
//    bool isOpen() 
//    {
//        return window.isOpen();
//    }
//
//    void close() 
//    {
//        window.close();
//    }
//    void handleEvents()
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//            {
//                window.close();
//            }
//            else if (event.type == Event::MouseButtonPressed) 
//            {
//                if (event.mouseButton.button == Mouse::Left) 
//                {
//                    Vector2i mousePosition = Mouse::getPosition(window);
//                    int clickedRow = mousePosition.y / (window.getSize().y / boardSize);
//                    int clickedCol = mousePosition.x / (window.getSize().x / boardSize);
//                    cout << "Clicked Cell: " << clickedRow << ", " << clickedCol << endl;
//                    if (selectedPiece.x != -1 && selectedPiece.y != -1) 
//                    {
//                        if ((isWhiteTurn && board[selectedPiece.x][selectedPiece.y]->isWhite()) ||
//                            (!isWhiteTurn && !board[selectedPiece.x][selectedPiece.y]->isWhite()))
//                        {
//                            if (board[selectedPiece.x][selectedPiece.y] != nullptr) 
//                            {
//                                // Calculate the new position of the piece
//                                float cellWidth = window.getSize().x / static_cast<float>(boardSize);
//                                float cellHeight = window.getSize().y / static_cast<float>(boardSize);
//                                Vector2f newPosition = Vector2f((clickedCol + 0.1f) * cellWidth, (clickedRow + 0.1f) * cellHeight);
//
//                                // Check if the move is valid
//                                if (board[selectedPiece.x][selectedPiece.y]->isValidMove(newPosition, board))
//                                {
//                                    // Move the piece if the move is valid
//                                    board[selectedPiece.x][selectedPiece.y]->move(newPosition);
//                                    board[clickedRow][clickedCol] = board[selectedPiece.x][selectedPiece.y];
//                                    board[selectedPiece.x][selectedPiece.y] = nullptr;
//                                    cout << "Moved Piece to: " << clickedRow << ", " << clickedCol << endl;
//                                    Sound move(move);
//                                    cout << "Sound of move is here \n";
//                                    move.play();
//                                    draw();
//                                    isWhiteTurn = !isWhiteTurn;
//                                    cout << (isWhiteTurn ? "White's turn" : "Black's turn") << endl;
//                                }
//                                else 
//                                {
//                                    // If the move is not valid, don't move the piece
//                                    cout << "Invalid move. Piece not moved." << endl;
//                                }
//                            }
//                            // Reset the selected piece
//                            selectedPiece.x = -1;
//                            selectedPiece.y = -1;
//                        }
//                    }
//                }
//                else if (event.mouseButton.button == Mouse::Right)
//                {
//                    // Handle right mouse button press (selecting a piece)
//                    Vector2i mousePosition = Mouse::getPosition(window);
//                    int clickedRow = mousePosition.y / (window.getSize().y / boardSize);
//                    int clickedCol = mousePosition.x / (window.getSize().x / boardSize);
//
//                    if (board[clickedRow][clickedCol] != nullptr) 
//                    {
//                        cout << "Selected Piece: " << clickedRow << ", " << clickedCol << endl;
//                        selectedPiece.x = clickedRow;
//                        selectedPiece.y = clickedCol;
//                    }
//                    draw();
//                }
//            }
//        }
//    }
//    void displayWinner(const string& winner)
//    {
//        RenderWindow winnerWindow(VideoMode(400, 200), "Winner");
//        Font font;
//        if (!font.loadFromFile("arial.ttf")) 
//        {
//            cout << "Error loading font." << endl;
//        }
//        Text winnerText;
//        winnerText.setFont(font);
//        winnerText.setString(winner + " wins!");
//        winnerText.setCharacterSize(40);
//        winnerText.setFillColor(Color::Red);
//        winnerText.setPosition(100, 100);
//
//        while (winnerWindow.isOpen())
//        {
//            Event event;
//            while (winnerWindow.pollEvent(event))
//            {
//                if (event.type == Event::Closed) 
//                {
//                    winnerWindow.close();
//                }
//            }
//            winnerWindow.clear();
//            winnerWindow.draw(winnerText);
//            winnerWindow.display();
//        }
//    }
//
//
//    void run() 
//    {
//        while (true) 
//        { 
//
//            handleEvents();
//            draw();
//
//            // Check if the white king is captured
//            if (isKingCaptured(true))
//            {
//                cout << "Black wins! White king is captured." << endl;
//                displayWinner("Black");
//                break;
//            }
//
//            // Check if the black king is captured
//            if (isKingCaptured(false)) 
//            {
//                cout << "White wins! Black king is captured." << endl;
//                displayWinner("White");
//                break;
//            }
//        }
//    }
//};
//
//class Menu 
//{
//private:
//    RenderWindow window;
//    Texture menubackground;
//    Sprite menuBackground;
//    Font font;
//    Text playButton, exitButton, chessButton;
//
//public:
//    Menu(int width, int height) : window(VideoMode(width, height), "Menu")
//    {
//        window.setFramerateLimit(60);
//        if (!font.loadFromFile("arial.ttf"))
//        {
//            cout << "Fonts in menu not loaded \n";
//        }
//        else
//        {
//            cout << "Font in menu loaded \n";
//        }
//        if (!menubackground.loadFromFile("background.png")) 
//        {
//            cout << "Menu background is not loaded \n";
//        }
//        else 
//        {
//            cout << "Menu background loaded successfully\n";
//        }
//        menuBackground.setTexture(menubackground);
//        menuBackground.setScale((float)window.getSize().x / menuBackground.getLocalBounds().width, (float)window.getSize().y / menuBackground.getLocalBounds().height);
//        exitButton.setFont(font);
//        exitButton.setString("BYE-BYE");
//        exitButton.setCharacterSize(80);
//        exitButton.setFillColor(Color::White);
//        exitButton.setPosition(window.getSize().x / 2 - exitButton.getLocalBounds().width / 2, window.getSize().y / 2);
//        playButton.setFont(font);
//        playButton.setString("LET'S GO");
//        playButton.setCharacterSize(80);
//        playButton.setFillColor(Color::White);
//        playButton.setPosition(window.getSize().x / 2 - playButton.getLocalBounds().width / 2, window.getSize().y / 2 - 100);
//    }
//
//    void handleEvents() 
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//            {
//                window.close();
//            }
//            if (event.type == Event::KeyPressed) 
//            {
//                if (event.key.code == Keyboard::Up) 
//                {
//                    if (playButton.getFillColor() == Color::White)
//                    {
//                        playButton.setFillColor(Color::Black);
//                        exitButton.setFillColor(Color::White);
//                    }
//                }
//                else if (event.key.code == Keyboard::Down)
//                {
//                    if (chessButton.getFillColor() == Color::White) 
//                    {
//                        playButton.setFillColor(Color::White);
//                        exitButton.setFillColor(Color::Black);
//                    }
//                }
//                else if (event.key.code == Keyboard::Enter) 
//                {
//                    if (exitButton.getFillColor() == Color::Black) 
//                    {
//                        cout << "Bye-Bye button selected!" << endl;
//                        window.close();
//                        return;
//                    }
//                    else if (playButton.getFillColor() == Color::Black)
//                    {
//                        cout << "Let's go button selected!" << endl;
//                        window.close();
//                        ChessboardWindow chessboard(800, 800);
//                        chessboard.run();
//                    }
//                }
//            }
//        }
//    }
//
//    void draw()
//    {
//        window.clear();
//        window.draw(menuBackground);
//        window.draw(playButton);
//        window.draw(exitButton);
//        window.draw(chessButton);
//        window.display();
//    }
//
//    bool isOpen()
//    {
//        return window.isOpen();
//    }
//
//    void run()
//    {
//        while (isOpen())
//        {
//            handleEvents();
//            draw();
//        }
//    }
//};
//
//int main()
//{
//    Menu menu(800, 800);
//    menu.run();
//    return 0;
//}