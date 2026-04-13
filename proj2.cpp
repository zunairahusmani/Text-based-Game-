#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cstdlib>
#include<time.h>
#include<stdexcept>
#include<pdcurses.h>

using namespace std;

class player {
    private:
    string name;
   int health, oxygenlevel;

   public:
   //health connected with oxygen 
   player (string n, int h = 100 , int ol=100 ) : name(n),health(h) , oxygenlevel(ol) {}

   int getHealth () const {return health;}
   int getOxygenlevel () const {return oxygenlevel;}

   void addhealth (int h){
     oxygenlevel+=h;
     if(oxygenlevel >100 ) oxygenlevel=100;
    }

   void energydrinkInc (int energy) {
      health += energy;
      if(health > 100) health = 100;
    }
  //if oxygen is less than some % then throw exception error 
   void takeDamage (int damage){
    health -= damage;    
    oxygenlevel -=damage;
    if (oxygenlevel <= 20) {
        throw runtime_error("You couldn't survive. You died. Game over.");
    }
    } 
 
    void status() const {
    initscr();
    start_color();     // Enable color support
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);  // Green for safe
    init_pair(2, COLOR_YELLOW, -1); // Yellow for warning
    init_pair(3, COLOR_RED, -1);    // Red for danger

    mvprintw(1, 0, "Your health is: %d%%", health);

    if (oxygenlevel > 60) {
        attron(COLOR_PAIR(1));
        mvprintw(2, 0, "Your oxygen is: %d%%", oxygenlevel);
        attroff(COLOR_PAIR(1));
    } else if (oxygenlevel > 30) {
        attron(COLOR_PAIR(2));
        mvprintw(2, 0, "Your oxygen is WARNING: %d%%", oxygenlevel);
        attroff(COLOR_PAIR(2));
    } else {
        attron(COLOR_PAIR(3));
        mvprintw(2, 0, "Your oxygen is LOW: %d%%", oxygenlevel);
        attroff(COLOR_PAIR(3));
    }

    refresh();
    getch(); // wait for key press
    endwin();
}

};

class alien {
    private:
    string aname;
    int adamage;
public:

    alien(string n, int d) : aname(n), adamage(d) {}
    string getaname () const{ return aname;}

    void playerATTACKED(player &p) {
        cout << "You got attacked by " << aname << " and you took " << adamage << " damage!" << endl;
        p.takeDamage(adamage);
    }
};

class alienlist{
private:
alien **aliens;
int capacity;
int size;

public:
alienlist (int cap=2 , int s =0) : capacity(cap) , size(s) {
    aliens = new alien* [capacity];
}

~alienlist(){
    for(int i = 0; i < size; i++) {
        delete aliens[i];
    }
    delete [] aliens;
}

void resize (){
capacity *=2;
alien** newalienlist = new alien* [capacity]; //why using double pointer?
for (int i = 0; i < size; i++) {
    newalienlist[i] = aliens[i];
}
delete[] aliens;
aliens = newalienlist;
}
 
void addalien(const alien& a){
    if(size == capacity) resize();
    aliens[size++] = new alien(a);
}

void removeAlien() {  // Changed to remove the first alien since your game seems to have one per portal
    if (size == 0) {
        cout << "No aliens to remove" << endl;
        return;
    }
    delete aliens[0];
    for (int i = 0; i < size - 1; i++) {
        aliens[i] = aliens[i + 1];
    }
    size--;
    cout << "Alien defeated " << endl;
}


bool hasalien () const {return size>0;}
};

class Item { // abstract class 
    public:
    virtual void use (player& p) = 0;
    virtual string getName() const = 0;
    virtual ~Item() {} 
    };
     
    // polymorphism used for items
    
    // inhertance used to acess parent class function in child class 
    class energydrink : public Item  {
    public:
    void use (player& p) override {
        p.energydrinkInc(30);
       
        cout<<"you drank the energy drink you health is now "<<p.getHealth ()<< endl;
    }
     string getName() const override { return "energydrink"; }
    };
    
    class oxygenmask  : public Item  {
    public:
    void use (player& p) override {
        p.addhealth(20);
        cout<<"you used an oxygen mask your oxygen is now" <<  p.getOxygenlevel()<< endl;
    }
          string getName() const override { return "Oxygen Mask"; }  // Correct
    };

    
class Inventory{ // store item in inventory 
public:
Item** items;
int top;
int size;

Inventory(int s = 5 ): size(s) , top(-1) {
    items  = new Item*[size];
}

Item* gettopitem(){
    if(isempty()){
        cout<<"inventory is empty"<<endl;
        return nullptr; 
    }
    else{
        return items[top];
    }
}

void showInventory() {
    if (isempty()) {
        cout << "Inventory is empty" << endl;
        return;
    }
    cout << "items in  Inventory: "; // (Top to Bottom)
    for (int i = top; i >= 0; i--) {
       cout<< items[i]->getName() << " " ;
    }
    cout << endl;
}

void resize() {
    int newSize = size * 2;
    Item** newitems = new Item*[newSize];
    for (int i = 0; i <= top; i++) {
        newitems[i] = items[i];
    }
    delete[] items;
    items = newitems;
    size = newSize;
}

void additem(Item* value){
  if(top==size-1){
    resize();
  }
    top++;
    items[top]=value;
    cout << "Added: "<< value->getName() << " to inventory" << endl;
}

void removeitem(){
    if(isempty()){
        cout<<"no item is in the inventory"<<endl;
    }
    else {
        cout << "Removed " <<items[top]->getName() <<" from inventory" << endl;
        top--;
    }
}

bool isempty(){
    return top==-1;
}

~Inventory() {
    for (int i = 0; i <= top; i++) delete items[i];
    delete [] items;
}

 // Operator Overloading: Compare item count
 //bool operator==(int count) {
  //  return (top + 1) == count;
//}

};




class portals 
{
    // for portals  i have to use map 
    private:
    string desc;
    string alienname;
    int dam;
    Item* item;
    bool hascaptain;

    public:
    portals (string d , string an , int da, bool hs = false) : 
    desc(d) , alienname(an) , dam(da),item(nullptr), hascaptain(hs) {}

    portals() : desc(""), alienname(""), dam(0), item(nullptr), hascaptain(false) {}

    string getDesc() const { return desc; }
    string getAlienName() const { return alienname; }
    int getDamage() const { return dam; }
    Item* getItem() const { return item; }
    bool gethascaptain() const {return hascaptain; }

    
    void setItem(Item* i) { 
         cout << "DEBUG: Setting item for portal " << endl;
        item = i; }  

    ~portals() {
        if(item) delete item;
    }
};


// show path after every movs?
// after every move ask wanna go ahead or show inventry or shiw status 

class game  // for riddle a vector is needed  , operator overloading, recusrrion, exception handling 
//after every fight check health and moves check oxygen if less tha 20 catch exception error 
{
    private:
    map <int,portals> station;
    map <int, vector<int>> p_connection;
    Inventory inv;
    alienlist aliens;
    bool ispathchoosen;
    int currentportal;
    bool repeardthesystem;
    bool cap;

    public:
    game(bool p = false, int c=1, bool rs= false,bool ca = false) : ispathchoosen(p), currentportal(c), repeardthesystem(rs), cap(ca) {}
    ~game() {}

    void addportal (int portalnum, string desc, string alienname, int dam, string itemtype = "" , bool hascap=false ){
        Item* item = nullptr;
        if (itemtype == "energydrink") 
        {item= new energydrink();
        cout << "DEBUG: Created energydrink for portal " << portalnum << endl;}
        if (itemtype == "oxygenmask") 
        {item = new oxygenmask();
        cout << "DEBUG: Created oxygenmask for portal " << portalnum << endl;}

        station[portalnum] = portals(desc,alienname,dam,hascap); 
        if(!alienname.empty())
        aliens.addalien (alien(alienname,dam));
        if (item) 
       { station[portalnum].setItem(item);
        cout << "DEBUG: Assigned item to portal " << portalnum << endl;}
     
    }

    void connection(int from , int to){
        p_connection[from].push_back(to);
    }
    
    void repairSystem(int t) {
        if (t == 0) {
            cout << "System repair failed."<<endl;
            return;
        }
        string input;
        cout << "Type 'fix' ";
        cin >> input;
        if (input == "fix") {
            cout << "System repaired!\n";
            repeardthesystem = true;
            return;
        } else {
            cout << "Incorrect. Try again.\n";
            repairSystem(t - 1);
        }
    } 
    void playgame (player &Player) {
        while( Player.getHealth() > 0 && Player.getOxygenlevel ()> 0  ){
            portals& current = station[currentportal];  // Get current portal
            cout << "Portal " << currentportal << ": " << current.getDesc() << endl;

               if (current.getItem() != nullptr) {
                  cout << "You found a " << current.getItem()->getName()<< " in this portal!" << endl;
                  inv.additem(current.getItem());
                  current.setItem(nullptr);
                }

            if (currentportal == 1 && repeardthesystem == false  ){
                cout<<"you found the radio but it is broken. to move forward you have to rapir the radio system to send signal to earth" <<endl;
                cout<<"to rapir the system: " << endl;
                int tries = 2;
                repairSystem(tries);
                if (repeardthesystem){
                    currentportal++;
                }
                else {
                    cout<<"you were unable to rapir the system and now there is no hope left you cannot send signal to earth"<<endl;
                    cout<<"game over"<<endl;
                    break;
                }
              
            }

            if (currentportal == 2  ){ // handle path choice 
                cout << "Portal " << currentportal << ": " << current.getDesc() << endl;
                if(!ispathchoosen){
                     cout<< "you must now choose a path"<<endl;
                     cout<<"Enter the Blackhole (b) or  Float through the Zero Gravity Corridor (g)";
                     string ans;
                     cin>>ans;
                     if (ans == "b"){
                         ispathchoosen= true;
                        cout<<"you choocsse the blackhole and got lost in the space ."<<endl;
                        cout<<"game end";
                        return; // game ends
                     }
                    else if (ans == "g") {
                        ispathchoosen= true;
                        cout<<"you choose zero gravity corridor and take 10 damage";
                        try {
                            Player.takeDamage(10); 
                            Player.status();
                        } 
                        catch (const runtime_error& e) {
                            cout << e.what() << endl;
                            return; // game end
                        }
                    }
                   else {
                     cout<<"invalid input";
                     continue; // stays in same portal until correct input
                    }
                }
            }
           // cout << "Portal " << currentportal << ": " << current.getDesc() << endl;
            if (!current.getAlienName().empty() && aliens.hasalien()) {  // handles allien if room has  for portal 3,4
                cout<<"you are attcked by" << station[currentportal].getAlienName() << endl;
                cout<<"do you wanna fight? yes(y) , no (n)"<<endl;
                string choice;
                cin>>choice;
                if (choice == "y") {
                    cout << "You killed the " << current.getAlienName() << endl;
                    aliens.removeAlien(); 
                    try {
                        Player.takeDamage(current.getDamage()); 
                        Player.status();
                    } 
                    catch (const runtime_error& e) {
                        cout << e.what() << endl;
                        return; // game end
                    }
                }
                else if(choice == "n") {
                    cout<<" you are a coward. ran away from your enemy. missed a chance to take revenge ?"<<endl;
                }
                else{
                    cout<<"invalid input"<<endl;
                    continue;
                }  
            }

           

            if(current.gethascaptain()){ // find and rescue caption if room has caption 
               cap= true;
               cout<<"there's a cloth. beneatth it you see a hand you removed the cloth and its him!! , the captain you found him."<<endl;
            }

            if (cap){//winning condition
            cout<<"you send the signal to earth and with the caption you left for earth leaving the haunted space station behind. you won"<<endl;
            return; // game end.
            }

            showmenu(Player);
            
            
        }
    }
    void showmenu (player& Player ){
        cout<<"what next?" <<endl;
            int choice;
            do{
                cout<<"1-go forward"<<endl;
                cout<<"2-show inventry"<<endl;
                cout<<"3-show status"<<endl;
                cout<<"4-show portal map"<<endl;
                cout<<"5-exit the game"<<endl;

                cout<<"enter your choice" <<endl;
                cin>>choice;

                switch(choice){
                    case 1:
                    currentportal++;
                    break;

                    case 2:
                    inv.showInventory(); // if inventry is not empty then ask do you want to use what is inside inventry if yes then call use function of that item 
                    if (!inv.isempty()){
                    cout << "Do you want to use the top item? yes(y) or no(n)" << endl;
                    string ans;
                    cin>>ans;
                    if(ans == "y") {
                            Item* item = inv.gettopitem();
                            if(item) {
                                item->use(Player);
                                inv.removeitem();
                            }
                        }// how can i know if it is a energy drink or a oxygen mask? how can i call oxygenmask use and vice versa
                    break;
                    }

                    case 3:
                    Player.status();
                    break;

                    case 4:
                    for (auto& entry : p_connection) {
                        cout << entry.first << " connects to: ";
                        for (int portal : entry.second) cout << portal << " ";
                        cout << endl;
                    }
                    break;

                    case 5:
                    cout<<"you are leaving? are you sure? huh coward!" <<endl;
                    exit(0);
                    
                    default :
                    cout<<"invalid choice" <<endl;

                }

            }
            while(choice != 1 );
     }
};

int main() {
    initscr();         // Start PDCurses mode
    noecho();          // Don't show typed characters
    cbreak();          // Disable line buffering


    move(1, 10); printw("--------------------------------------");
    move(2, 10); printw("       WELCOME TO DARK SIDE STATION       ");
    move(3, 10); printw("--------------------------------------");

    move(5, 0); printw("You awaken alone aboard a colossal space station orbiting the moon.\n");
    printw("You were a subject of an experiment, but everything has gone wrong...\n");
    printw("The once-proud station is now overrun by huge aliens hunting you down.\n");
    printw("Even worse, the crew—your family—are all dead.\n");
    printw("A rumor spreads: the Captain might still be alive, hiding among the monsters.\n");
    printw("You must survive, find the Captain, and send a warning to Earth before it's too late.\n\n");

    printw("Only the Captain holds the access card for the escape pod and radio beacon.\n");
    printw("It's up to you to end these predators… or die trying.\n\n");

    printw("Enter your name to begin: ");
    char playername[50];
    getstr(playername);  // Take input in curses mode

    printw("\nHello %s! Welcome aboard...\n", playername);
    printw("RULES OF THE GAME:\n");
    printw("- Navigate through portals in the haunted station.\n");
    printw("- Fix the broken radio system.\n");
    printw("- Defeat or avoid aliens that block your path.\n");
    printw("- Find the Captain and activate the escape system.\n");
    printw("- Survive... or humanity will be lost.\n\n");
    printw("Good luck, %s!\n", playername);
    refresh();

    getch();   // Pause before clearing
    clear();   // Clear the screen

    endwin();  // End curses mode

    // Now start the real game (with cout / cin)
    player Player(playername);
    game Game;

    Game.addportal(1, "you get up & start searching the portal. you looked at the dead bodies of your crew members. and then you realized something is missing. the radio.", "", 0, "oxygenmask");
    Game.addportal(2, "now you see the opening to another portal but wait what there are 2 identical pathways.", "", 0, "energydrink");
    Game.addportal(3, "after entering the next portal, a monstrous alien blocks your path.", "WAR HAMMER", 30);
    Game.addportal(4, "another portal, another monster", "alien x", 40);
    Game.addportal(5, "you reach the station control desk and you hear a voice. you've heard this voice before.", "", 0, "", true);

    Game.connection(1, 2);
    Game.connection(2, 3);
    Game.connection(3, 4);
    Game.connection(4, 5);

    Game.playgame(Player);
    return 0;
}
