#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
//Structure to keep track of various locations
struct Point
{
  int x;
  int y;
  Point(int _x, int _y): x(_x), y(_y)
  {

  }
};

//Structure for the Player object
struct Player
{
  int food;
  int health;
  bool alive;
  int x;
  int y;

  Player() : food(64), health(10), alive(true)
  {}
  void loseHealth()
  {
    if(health>0)
      health--;
    if(health==0)
      alive = false;
  }
  void gainHealth()
  {
    if(health<10)
      health++;
  }
};

typedef const int cint;         //Google typedef to see what this means
typedef const Point cPoint;

char* create_dungeon(int, int, Point&, Point&);      //Creates the dungeon
void traversal(char*, Point&, cPoint&, cint, cint); //Used for moving inside dungeon
void combat(Player&, int);  //Used for simulating combat
void trap_statements();  //3 statements that show at random when the player activates a trap
void food_statements();  //3 statements that show at random when the player finds food
void hit_statements();   //3 statements that show at random when the player hits enemy
void get_hit_statements();//3 statements that show at random when the player gets hit
void print_dungeon(char*, cint, cint);//The function to print the dungeon
void checking_input(char x, char* dungeon, int width, Point& start_point, int, bool&);
int main ()
{
    srand(time(0));
    int width;
    int height;
    cout<<"Width: ";cin >> width;
    cout<<"Height: ";cin >> height;
    if(width < 8 || height < 8)
    {
        width = 16;
        height = 16;
        cout<<"Value less than 8, switching to default value which is 16x16\n";
    }
    Point start_point(0,0);
    Point exit_point(0,0);
    char* dungeon = NULL;
    dungeon = create_dungeon(width, height, start_point, exit_point);
    traversal(dungeon, start_point, exit_point, width, height);
    delete dungeon;
    return 0;
}
// Function checks the input and changes the indexes of the player according to the input
void checking_input(char x, char* dungeon, int width, Point& start_point, int height, bool& detectWall)
{
    if(x == 'u'&& dungeon[(width*(start_point.y-1)) + start_point.x] != 'w' )
        {
            start_point.y -= 1;

        }
    if(x == 'd' && dungeon[(width*(start_point.y+1)) + start_point.x] != 'w')
        {
            start_point.y += 1;

        }
    if(x == 'r' && dungeon[(width*start_point.y) + start_point.x+1] != 'w')
        {
            start_point.x += 1;

        }
    if(x == 'l' && dungeon[(width*start_point.y) + start_point.x-1] != 'w')
        {
           start_point.x -= 1;

        }
    if(x == 'u'&& dungeon[(width*(start_point.y-1)) + start_point.x] == 'w' )
        {
            if (start_point.y-1 == 0)
            {
                cout<<"You have reached the end of the room"<<endl;
            }
            else
            {
                cout<<"There is a wall here. You cannot move up"<<endl;
            }
            detectWall = true;
        }
    if(x == 'd' && dungeon[(width*(start_point.y+1)) + start_point.x] == 'w')
        {
            if (start_point.y+1 == height-1)
            {
                cout<<"You have reached the end of the room"<<endl;
            }
            else
            {
                cout<<"There is a wall here. You cannot move down"<<endl;
            }
            detectWall = true;
        }
    if(x == 'r' && dungeon[(width*start_point.y) + start_point.x+1] == 'w')
        {
            if (start_point.x+1 == width-1)
            {
                cout<<"You have reached the end of the room"<<endl;
            }
            else
            {
                cout<<"There is a wall here. You cannot move right"<<endl;
            }
            detectWall = true;
        }
    if(x == 'l' && dungeon[(width*start_point.y) + start_point.x-1] == 'w')
        {
           if (start_point.x-1 == 0)
            {
                cout<<"You have reached the end of the room"<<endl;
            }
            else
            {
                cout<<"There is a wall here. You cannot move left"<<endl;
            }
            detectWall = true;
        }

}
//prints the created dungeon
void print_dungeon(char *dungeon,cint width,cint height)
{
   for(int i = 0; i < width*height; i++)
    {
        if(i%(width) == 0)
        {
            cout << endl;
        }
        cout << dungeon[i];
    }
    cout << endl;
}
// Function to call one of the three possible random statements in which the player can fall into a trap
void trap_statements()
{
  int t_statement = rand() % 3;
  if(t_statement == 0)
  {
      cout << "An dungeon_arrow came flying out of a nearby wall and hit you in your posterior.This will leave you a scar.\n";
  }
  if(t_statement == 1)
  {
      cout << "You walked into some spikes that sprung out of the floor.\n";
  }
  if(t_statement == 2)
  {
      cout << "You stepped into a bear trap and got yourself injured.\n";
  }
}
// Function to call one of the three possible random statements in which the player can find food
void food_statements()
{
  int f_statement = rand() % 3;
  if(f_statement == 0)
  {
      cout << "You found a rat as big as a rabbit.That will go down well with a bit of wasp juice if you have any.\n";
  }
  if(f_statement == 1)
  {
      cout << "You found some bread roll here.maybe there is a secret bakery near by.\n";
  }
  if(f_statement == 2)
  {
      cout << "You found some well cooked chicken, atleast you thought it was while eating it.\n";
  }
}
// Function to call one of the three possible random statements in which the player can hit/kill an enemy
void hit_statements()
{
  int h_statement = 0;
  h_statement = rand() % 3;
  cout<<h_statement;
  if(h_statement == 0)
  {
      cout << "Your roundhouse kick sent your enemy flying right into a gutter.\n You killed one enemy!\n";
  }
  if(h_statement == 1)
  {
      cout << "You made an excellent jab that knocked the lights out of your enemy.\n You killed one enemy!\n";
  }
  if(h_statement == 2)
  {
      cout << "Your speed is unmatched and delivered a Stone Cold Stunner.\n You killed one enemy!\n";
  }
}
// Function to call one of the three possible random statements in which the player can get hit by an enemy
void get_hit_statements()
{
  int geth_statement = rand() % 3;
  if(geth_statement == 0)
  {
      cout << "The enemy avoided your attack and gave you a nasty scratch.\n You lost 1 health\n";
  }
  if(geth_statement == 1)
  {
      cout << "The enemy threw a rock that hit you on the temple and shook you bad.\n You lost 1 health\n";
  }
  if(geth_statement == 2)
  {
      cout << "You were not prepared for a sudden lunging attack that hit you hard..\n You lost 1 health\n";
  }
}
// Function to move the player and come across different things (enemy,trap,health e.t.c) and execute different function
// according to that (combat, food_statements, trap_statements)
void traversal(char* dungeon, Point& start_point, cPoint& exit_point,cint width, cint height)
{
    Player p1;// p1 is the players name
    char input_move;// input for the movement of the player
    bool detectWall = false;
    while(input_move != 'x' && p1.alive == true && p1.food != 0)
    {
        print_dungeon(dungeon,width,height);// prints the dungeon
        cout<<"In which direction you want to move,u(up),d(down),r(right),l(left)\npress x if you want to die there and then.";
        cin >> input_move; cout<<endl;
        dungeon[(width*start_point.y) + start_point.x] = ' ';
        checking_input(input_move, dungeon, width, start_point, height, detectWall); // this function checks the input by the user and moves the player in that direction
        if(start_point.x == exit_point.x && start_point.y == exit_point.y)
        {
            cout<<"Congratulations!!!! you found your way out of the dungeon \n";
            break;
        }
        if(dungeon[(width*start_point.y) + start_point.x] == 'F')
        {
            int food = 4 + (rand() % (5));
            p1.food += food;
            cout<<"You found some food that will last you for " << food << " more days.\n";
            food_statements();
        }
        if(dungeon[(width*start_point.y) + start_point.x] == 'H')
        {
            cout << "You found some health.\n";
            p1.gainHealth();
            cout << "Your current health is : " << p1.health;
        }
        if(dungeon[(width*start_point.y) + start_point.x] == 'T')
        {
           trap_statements();
           p1.loseHealth();
           cout << "Your current health is : " << p1.health;
        }
        if(dungeon[(width*start_point.y) + start_point.x] == 'E')
        {
           int enemy_no = 2 + (rand() % (3));
           cout<<"You came across " << enemy_no << " enemies. its time to fight.\n";
           combat(p1, enemy_no);
        }
        if((dungeon[(width*start_point.y) + start_point.x] == ' ') && (!(detectWall)))
        {
           cout<<"There's nothing here!!!\n"<<endl;
        }
        detectWall = false;
       // if(start_point.x == 0 || start_point.y == 0 || )
        dungeon[(width*start_point.y) + start_point.x] = 'P';
        p1.food --;
        cout<<"\nYou have food for "<< p1.food << " more days.";
    }
}

void combat(Player& player, int enemies)
{
    cout<<"*******************************\n**********  Start Of Combat  ***********\n ************************************\n";
    while (player.alive == true && enemies != 0)
    {
        int probability_of_players_attack = rand() % 100;
        if(probability_of_players_attack < 30)
        {
            hit_statements();
            enemies --;
        }
        for(int g_hit = 0; g_hit < enemies; g_hit ++)
        {
            int probability_of_enemy_attack = rand() % 100;
            if(probability_of_enemy_attack < 10)
            {
                get_hit_statements();
                player.loseHealth();
            }
        }
    }
    cout<<"**********************************\n*************  End Of Combat  *************\n*********************************\n";
    cout<<"Your current health is : " << player.health;
}
//function is responsible for the overall creation of the dungeon like placing the the walls, characters at random in the dungeon
char* create_dungeon(int width, int height,Point& ref_startPoint, Point& ref_exitPoint)
{
    char* dungeon_arr = new char[width*height];//dungeon_arr is the single dimensional array which is the dungeon
    for(int i = 0; i < width*height; i++)
    {
        dungeon_arr[i] = ' ';
    }
        for(int i = 0; i < height; i++)
        {
             if(i == 0 || i == height - 1)
             {
                for(int j = 0; j < width; j++)
                {
                    dungeon_arr[(width * i) + j] = 'w';
                }
             }
             else
             {
                 for(int j = 0; j < width; j += width-1)
                 {
                     dungeon_arr[(width*i)+j] = 'w';
                 }
                 for(int j = 1 ; j < width - 1 ; j++)
                 {

                     int probability_of_characs = rand() % 100;
                     if (probability_of_characs < 20)
                     {
                         int probability_among_characs = rand() % 100;
                         if(probability_among_characs <= 15)
                         {
                             dungeon_arr[(width*i)+j] = 'E';
                         }
                         else if (probability_among_characs > 15 && probability_among_characs <= 30)
                         {
                             dungeon_arr[(width*i)+j] = 'H';
                         }
                         else if (probability_among_characs > 30 && probability_among_characs <= 45)
                         {
                              dungeon_arr[(width*i)+j] = 'T';
                         }
                         else if (probability_among_characs > 45 && probability_among_characs <= 60)
                         {
                              dungeon_arr[(width*i)+j] = 'F';
                         }
                         else
                         {
                              dungeon_arr[(width*i)+j] = 'w';
                         }
                     }
                 }
             }
        }
        int rand_start_row = 1 + (rand() % ((height-2)));
        int rand_exit_row = 1 + (rand() % ((height-2)));
        for(int i = 1; i < width-1; i+= width-3)
        {
            if(i == 1)
            {
                ref_startPoint.x = i;
                if(dungeon_arr[(width*rand_start_row) + ref_startPoint.x] == ' ')
                {
                    ref_startPoint.y = rand_start_row;
                    dungeon_arr[(width*ref_startPoint.y) + ref_startPoint.x] = 'P';
                }
                else
                {
                    ref_startPoint.y = 1;
                    dungeon_arr[(width*ref_startPoint.y) + ref_startPoint.x] = 'P';

                }
            }

            else
            {
               ref_exitPoint.x = i;
               if(dungeon_arr[(width*rand_exit_row) + ref_exitPoint.x] == ' ')
                {
                    ref_exitPoint.y = rand_exit_row;
                    dungeon_arr[(width*ref_exitPoint.y) + ref_exitPoint.x] = 'X';
                }
                else
                {

                    ref_exitPoint.y = height - 2;
                    dungeon_arr[(width*ref_exitPoint.y) + ref_exitPoint.x] = 'X';
                }
            }
        }
    return dungeon_arr;
}
