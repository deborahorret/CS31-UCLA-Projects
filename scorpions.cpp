//
//  main.cpp
//  test
//
//  Created by Deborah Orret on 6/8/17.
//  Copyright © 2017 Deborah Orret. All rights reserved.
//

//
//  main.cpp
//  scorpions
//
//  Created by Deborah Orret on 6/4/17.
//  Copyright © 2017 Deborah Orret. All rights reserved.
//

// scorpions.cpp

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the pit
const int MAXCOLS = 40;             // max number of columns in the pit
const int MAXSCORPIONS = 160;       // max number of scorpions allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Pit;  // This is needed to let the compiler know that Pit is a
// type name, since it's mentioned in the Scorpion declaration.

class Scorpion
{
public:
    // Constructor
    Scorpion(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};

class Player
{
public:
    // Constructor
    Player(Pit *pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   move(int dir);
    void   setDead();
    
private:
    Pit*  m_pit;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

class Pit
{
public:
    // Constructor/destructor
    Pit(int nRows, int nCols);
    ~Pit();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     scorpionCount() const;
    int     numberOfScorpionsAt(int r, int c) const;
    void    display() const;
    
    // Mutators
    bool   addScorpion(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyOneScorpion(int r, int c);
    bool   moveScorpions();
    
private:
    int        m_rows;
    int        m_cols;
    
    Player*    m_player;
    Scorpion*  m_scorpions[MAXSCORPIONS];
    int        m_nScorpions;
    // Helper functions
    bool isPosInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nScorpions);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Pit* m_pit;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int min, int max);
int decodeDirection(char dir);
bool directionToDeltas(int dir, int& rowDelta, int& colDelta);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Scorpion implementation
///////////////////////////////////////////////////////////////////////////

Scorpion::Scorpion(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** A scorpion must be created in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "***** Scorpion created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
}

int Scorpion::row() const
{
    return m_row;
}

int Scorpion::col() const
{
    // DONE:  Return the column the scorpion is at.
    return m_col;
}

void Scorpion::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (randInt(0, NUMDIRS-1))
    {
        case UP:
            // DONE: Move the scorpion up one row if possible.
            if ((row() - 1) > 0) {
                m_row--;
            }
            break;
        case DOWN:
            if ((row() + 1) <=  m_pit->rows()) {
                m_row++;
            }
            break;
        case LEFT:
            if ((col() - 1) > 0) {
                m_col--;
            }
            break;
        case RIGHT:
            if ((col() + 1) <=  m_pit->cols()) {
                m_col++;
            }
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Pit* pp, int r, int c) // (*pp).nameofthememberfunction OR pp-> nameofthefunction
{
    if (pp == nullptr)
    {
        cout << "***** The player must be created in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    // DONE:  Return the row the player is at.
    return m_row;
}

int Player::col() const
{
    // DONE:  Return the column the player is at.
    return m_col;
}

int Player::age() const
{
    // DONE:  Return the player's age.
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    
    // DONE:  If there's a grid position in the indicated direction that is
    //        adjacent to the player and vacant, move the player there.  If
    //        there's a grid position in the indicated direction that is
    //        adjacent to the player and contains one or more scorpions, with
    //        a grid position next to and on the other side of the scorpion(s),
    //        jump over the scorpion(s), killing (destroying) one, and landing
    //        at that position (and dying if a scorpion is there).  If there's
    //        a grid position in the indicated direction that is adjacent to
    //        the player and contains one or more scorpions, with no grid
    //        position next to and on the other side of the scorpion(s),
    //        jump over the scorpion(s), killing (destroying) one, but landing
    //        at that dead scorpion's position (and dying if another scorpion
    //        is there).  In any other case, don't move.
    
    
    switch (dir)
    {
        case UP:
            if((row() > 1))   //not on first row
            {
                int next_to = m_pit->numberOfScorpionsAt(row() - 1, col());
                int one_after = m_pit->numberOfScorpionsAt(row()-2, col());
                if (next_to == 0)
                {
                    m_row--;
                }
                else if(m_pit->numberOfScorpionsAt(1, col()) > 0  && row() == 2) //if the scorpion is on the
                {
                    m_pit->destroyOneScorpion(1, m_pit->rows());
                    m_row--;
                }
                
                else if(next_to > 0 &&
                        one_after == 0) // if there is a scorpion next to you BUT NOT on the space next to it, so u can jump over and kill it
                {
                    m_pit->destroyOneScorpion(row()-1, col()); //destroy that scorpion
                    m_row = m_row - 2; //jump over
                }
                else if(next_to > 0 &&
                        one_after > 0) //if the one next to has a scorpion, and the one after has a scorpion, kill the scorpion next to you and then jump, and die
                {
                    m_pit->destroyOneScorpion(row()-1, col());
                    m_row = m_row - 2; //jump over
                    setDead(); //DIE
                    
                }
            }
            else {
                stand(); //was on first row so stand
            }
            break;
            
        case DOWN:
            
            if(row() < m_pit->rows())   //not on last row
            {
                int next_to = m_pit->numberOfScorpionsAt(row() + 1, col());
                int one_after = m_pit->numberOfScorpionsAt(row() + 2, col());
                
                if (next_to == 0)
                {
                    m_row++;
                }
                else if(m_pit->numberOfScorpionsAt(m_pit->rows(), col()) > 0 && row() == m_pit->rows()-1)
                {
                    m_pit->destroyOneScorpion(m_pit->rows(), col());
                    m_row++;
                }
                else if(next_to > 0 &&
                        one_after == 0) // if there is a scorpion next to you BUT NOT on the space next to it, so u can jump over and kill it
                {
                    m_pit->destroyOneScorpion(row()+1, col()); //destroy that scorpion
                    m_row = m_row + 2; //jump over
                }
                else if(next_to > 0 &&
                        one_after > 0) //if the one next to has a scorpion, and the one after has a scorpion, kill the scorpion next to you and then jump, and die
                {
                    m_pit->destroyOneScorpion(row() + 1, col());
                    m_row = m_row + 2; //jump over
                    setDead(); //DIE
                    
                }
            }
            else {
                stand(); //was on first row so stand
            }
            break;
            
        case LEFT:
            
            if((col() > 1))   //not on first col
            {
                int next_to = m_pit->numberOfScorpionsAt(row(), col()-1);
                int one_after = m_pit->numberOfScorpionsAt(row(), col()-2);
                if (next_to == 0)
                {
                    m_col--;
                }
                else if(m_pit->numberOfScorpionsAt(row(), 1) > 0 && col() ==2 )
                {
                    m_pit->destroyOneScorpion(m_pit->rows(), 1);
                    m_col--;
                }
                else if(next_to > 0 &&
                        one_after == 0) // if there is a scorpion next to you BUT NOT on the space next to it, so u can jump over ad kill it
                {
                    m_pit->destroyOneScorpion(row(), col()-1); //destroy that scorpion
                    m_col = m_col - 2; //jump over
                }
                else if(next_to > 0 &&
                        one_after > 0) //if the one next to has a scorpion, and the one after has a scorpion, kill the scorpion next to you and then jump, and die
                {
                    m_pit->destroyOneScorpion(row(), col()-1);
                    m_col = m_col - 2; //jump over
                    setDead(); //DIE
                    
                }
            }
            else {
                stand(); //was on first row so stand
            }
            break;
            
        case RIGHT:                 //Will move right respectively if player is not on last col
            
            if((col() < m_pit->cols()))   //not on last col
            {
                int next_to = m_pit->numberOfScorpionsAt(row(), col()+1);
                int one_after = m_pit->numberOfScorpionsAt(row(), col()+2);
                if (next_to == 0)
                {
                    m_col++;
                }
                else if(m_pit->numberOfScorpionsAt(row(), m_pit -> cols()) > 0 && col() ==m_pit -> cols() -1 )                 {
                    m_pit->destroyOneScorpion(row(), m_pit->cols());
                    m_col++;
                }
                else if(next_to > 0 &&
                        one_after == 0) // if there is a scorpion next to you BUT NOT on the space next to it, so u can jump over ad kill it
                {
                    m_pit->destroyOneScorpion(row(), col()+1); //destroy that scorpion
                    m_col = m_col + 2; //jump over
                }
                else if(next_to > 0 &&
                        one_after > 0) //if the one next to has a scorpion, and the one after has a scorpion, kill the scorpion next to you and then jump, and die
                {
                    m_pit->destroyOneScorpion(row(), col()+1);
                    m_col = m_col + 2; //jump over
                    setDead(); //DIE
                    
                }
            }
            else {
                stand(); //was on first row so stand
            }
            break;
            
    }
}

bool Player::isDead() const
{
    // DONE: Return whether the player is dead.
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Pit implementation
///////////////////////////////////////////////////////////////////////////

Pit::Pit(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Pit created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nScorpions = 0;
}

Pit::~Pit()
{
    //DONE: Delete the player and all remaining dynamically allocated scorpions.
    for (int i=0; i < m_nScorpions; i++) {
        delete m_scorpions[i];
    }
    delete m_player;
}

int Pit::rows() const
{
    //DONE:  Return the number of rows in the pit.
    return m_rows;
}

int Pit::cols() const
{
    // DONE: Return the number of columns in the pit
    return m_cols;
}

Player* Pit::player() const {
    return m_player;
}

int Pit::scorpionCount() const
{
    return m_nScorpions;
}

int Pit::numberOfScorpionsAt(int r, int c) const
{
    // DONE:  Return the number of scorpions at row r, column c.
    int counter = 0;
    for (int i=0; i < m_nScorpions; i++) {
        Scorpion* num = m_scorpions[i]; //
        if ((*num).row() == r && (*num).col()== c) {
            counter++;
        }
    }
    return counter;
}

void Pit::display() const
{
    // Position (row,col) in the pit coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each scorpion's position
    // DONE:  If one scorpion is at some grid point, set the char to 'S'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    
    
    for (int r = 0; r < rows(); r++) {
        for (int c = 0; c < cols(); c++) {
            int num = numberOfScorpionsAt(r+1, c+1);
            switch (num) {
                case 0:
                    break;
                case 1:
                    grid[r][c] = 'S';
                    break;
                case 2:
                    grid[r][c] = '2';
                    break;
                case 3:
                    grid[r][c] = '3';
                    break;
                case 4:
                    grid[r][c] = '4';
                    break;
                case 5:
                    grid[r][c] = '5';
                    break;
                case 6:
                    grid[r][c] = '6';
                    break;
                case 7:
                    grid[r][c] = '7';
                    break;
                case 8:
                    grid[r][c] = '8';
                    break;
                default:
                    grid[r][c] = '9';
                    break;
            }
        }
    }
    
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (m_player->isDead())
            gridChar = '*';
        else
            gridChar = '@';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, scorpion, and player info
    cout << "There are " << scorpionCount() << " scorpions remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Pit::addScorpion(int r, int c)
{
    if (! isPosInBounds(r, c)) {
        return false;
    }
    // Don't add a scorpion on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    
    // If there are MAXSCORPIONS existing scorpions, return false.
    // Otherwise, dynamically allocate a new scorpion at coordinates (r,c).
    // Save the pointer to the newly allocated scorpionn and return true.
    if (m_nScorpions == MAXSCORPIONS) {
        return false;
    }
    
    m_scorpions[m_nScorpions] = new Scorpion(this, r, c);
    m_nScorpions++;
    return true;
    
    // DONE:  Implement this.
}

bool Pit::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;
    
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Don't add a player on a spot with a scorpion
    if (numberOfScorpionsAt(r, c) > 0)
        return false;
    
    // Dynamically allocate a new Player and add it to the pit
    m_player = new Player(this, r, c);
    return true;
}

bool Pit::destroyOneScorpion(int r, int c)
{
    // DONE:  Destroy one scorpion at row r, column c.  Return true if a
    //        scorpion was destroyed, or false if there were no scorpions there.
    
    int a = 0;
    int num = numberOfScorpionsAt(r, c);
    if(num > 0)
    {
        for (int i = 0; i < m_nScorpions; i++)
        {
            if(m_scorpions[i]->row() == r && m_scorpions[i]->col() == c)
            {
                a = i;
                break;
            }
        }
        delete m_scorpions[a];
        
        for (int i = a; i < m_nScorpions; i++) //loop through and move everything up one
        {
            m_scorpions[i] = m_scorpions[i+1];
        }
        
        m_nScorpions--; //increment the whole thing
        
        return true;
    }
    return false;
}




bool Pit::moveScorpions()
{
    for (int k = 0; k < m_nScorpions; k++)
    {
        // DONE:  Have the k-th scorpion in the pit make one move.
        //        If that move results in that scorpion being in the same
        //        position as the player, the player dies.
        m_scorpions[k]->move();
        if (m_scorpions[k]->row() == m_player->row() && m_scorpions[k]->col() == m_player->col()) {
            m_player->setDead();
        }
    }
    
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

bool Pit::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nScorpions)
{
    if (nScorpions < 0)
    {
        cout << "***** Cannot create Game with negative number of scorpions!" << endl;
        exit(1);
    }
    if (nScorpions > MAXSCORPIONS)
    {
        cout << "***** Trying to create Game with " << nScorpions
        << " scorpions; only " << MAXSCORPIONS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nScorpions > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the scorpions!" << endl;
        exit(1);
    }
    
    // Create pit
    m_pit = new Pit(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_pit->addPlayer(rPlayer, cPlayer);
    
    // Populate with scorpions
    while (nScorpions > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a scorpion where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_pit->addScorpion(r, c);
        nScorpions--;
    }
}

Game::~Game()
{
    delete m_pit;
}

void Game::play()
{
    m_pit->display();
    Player* player = m_pit->player();
    if (player == nullptr)
        return;
    
    while ( ! m_pit->player()->isDead()  &&  m_pit->scorpionCount() > 0)
    {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            player->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    player->move(decodeDirection(action[0]));
                    break;
            }
        }
        if ( ! player->isDead())
            m_pit->moveScorpions();
        m_pit->display();
    }
    if (m_pit->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

// Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

bool directionToDeltas(int dir, int& rowDelta, int& colDelta)
{
    switch (dir)
    {
        case UP:     rowDelta = -1; colDelta =  0; break;
        case DOWN:   rowDelta =  1; colDelta =  0; break;
        case LEFT:   rowDelta =  0; colDelta = -1; break;
        case RIGHT:  rowDelta =  0; colDelta =  1; break;
        default:     return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////
#include <cassert>

#define CHECKTYPE(f, t) { (void)(t)(f); }

void thisFunctionWillNeverBeCalled()
{
    // If the student deleted or changed the interfaces to the public
    // functions, this won't compile.  (This uses magic beyond the scope
    // of CS 31.)
    
    Scorpion(static_cast<Pit*>(0), 1, 1);
    CHECKTYPE(&Scorpion::row,  int  (Scorpion::*)() const);
    CHECKTYPE(&Scorpion::col,  int  (Scorpion::*)() const);
    CHECKTYPE(&Scorpion::move, void (Scorpion::*)());
    
    Player(static_cast<Pit*>(0), 1, 1);
    CHECKTYPE(&Player::row,     int  (Player::*)() const);
    CHECKTYPE(&Player::col,     int  (Player::*)() const);
    CHECKTYPE(&Player::age,     int  (Player::*)() const);
    CHECKTYPE(&Player::isDead,  bool (Player::*)() const);
    CHECKTYPE(&Player::stand,   void (Player::*)());
    CHECKTYPE(&Player::move,    void (Player::*)(int));
    CHECKTYPE(&Player::setDead, void (Player::*)());
    
    Pit(1, 1);
    CHECKTYPE(&Pit::rows,                int     (Pit::*)() const);
    CHECKTYPE(&Pit::cols,                int     (Pit::*)() const);
    CHECKTYPE(&Pit::player,              Player* (Pit::*)() const);
    CHECKTYPE(&Pit::scorpionCount,       int     (Pit::*)() const);
    CHECKTYPE(&Pit::numberOfScorpionsAt, int     (Pit::*)(int,int) const);
    CHECKTYPE(&Pit::display,             void    (Pit::*)(string) const);
    CHECKTYPE(&Pit::addScorpion,         bool    (Pit::*)(int,int));
    CHECKTYPE(&Pit::addPlayer,           bool    (Pit::*)(int,int));
    CHECKTYPE(&Pit::destroyOneScorpion,  bool    (Pit::*)(int,int));
    CHECKTYPE(&Pit::moveScorpions,       bool    (Pit::*)());
    
    Game(1,1,1);
    CHECKTYPE(&Game::play, void (Game::*)());
}

void doBasicTests()
{
    {
        Pit brad(10, 20);
        assert(brad.addPlayer(2, 6));
        Player* pp = brad.player();
        assert(pp->row() == 2  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->setDead();
        assert(pp->row() == 1  &&  pp->col() == 6  && pp->isDead());
    }
    {
        Pit brad(2, 2);
        assert(brad.addPlayer(1, 1));
        assert(brad.addScorpion(2, 2));
        Player* pp = brad.player();
        assert(brad.moveScorpions());
        assert( ! pp->isDead());
        for (int k = 0; k < 1000  &&  brad.moveScorpions(); k++)
            ;
        assert(pp->isDead());
    }
    {
        Pit brad(1, 5);
        assert(brad.addPlayer(1, 1));
        assert(brad.addScorpion(1, 2));
        assert(brad.addScorpion(1, 4));
        assert(brad.addScorpion(1, 4));
        assert(brad.scorpionCount() == 3  &&  brad.numberOfScorpionsAt(1, 4) == 2);
        Player* pp = brad.player();
        pp->move(RIGHT);
        pp->move(RIGHT);
        assert(brad.scorpionCount() == 1  &&  brad.numberOfScorpionsAt(1, 4) == 1);
        pp->move(LEFT);
        assert(brad.scorpionCount() == 0);
        assert(brad.addScorpion(1, 5));
        assert(brad.scorpionCount() == 1);
    }
    cout << "Passed all basic tests" << endl;
}
int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    
    Game g(3, 3, 3);
    doBasicTests();
    // Play the game
    g.play();
}


///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
